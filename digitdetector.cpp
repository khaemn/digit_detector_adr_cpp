#include "digitdetector.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QtQml>
#include <QImage>

DigitDetector::DigitDetector(QObject *parent) : QObject(parent)
{

}

void DigitDetector::init()
{
     QString path_prefix;
 #ifdef ANDROID
     path_prefix = "assets:/jsons/";
 #else
     path_prefix = ":/assets:/android-sources/assets/";
 #endif

     QString model_path = path_prefix.append("mnist.json");
     QFile model_file(model_path);
     qCritical() << "Opening QFile with model path: " << model_file.open(QFile::ReadOnly);
     QTextStream qstream(&model_file);

     qCritical() << "Creating instream...";
     // Inefficient solution, but for now a single workaround for Android loading:
     std::istringstream iss(qstream.readAll().toStdString());

     try {
         qCritical() << "Loading model from " << model_path;
         m_model = std::make_unique<fdeep::model>(fdeep::read_model(iss, true));
     }
     catch(std::exception& e) {
         qCritical() << "Exception : " << e.what();
     }
     catch(...) {
         qCritical() << "Unknown exception!";
     }
     qCritical() << "Model file loaded ok";

}

void DigitDetector::test_recognizing(const QString &file)
{
    using namespace cv;

    qCritical() << "Test recognition. Reading the file " << file;
    QImage image(file);
    cv::Mat mat(image.height(), image.width(), CV_8UC4, image.bits());
    //Mat image = imread("/home/vova/Free/qml-adr-test/android-sources/assets/three.png");
    //Mat image = imread(":/assets:/android-sources/assets/three.png");

    qCritical() << "Converting to FDeep tensor...";
    auto input = as_native_tensor(mat);
    qCritical() << "Performing NN froward pass...";
    fdeep::tensor5 prediction = raw_predict(input);
    qCritical() << "Converting prediction to readable format...";
    auto readable_prediction = fdeep::show_tensor5(prediction);

    qCritical() << "Prediction for " << file << " : "
                << QString::fromStdString(readable_prediction);
    qCritical() << "Test recognition finished ok.";
}

QString DigitDetector::digit() const
{
    return m_digit;
}

void DigitDetector::registerQmlType()
{
    qmlRegisterType<DigitDetector>("DigitDetector", 1, 0, "DigitDetector");
}

fdeep::tensor5 DigitDetector::as_native_tensor(const cv::Mat &input)
{
    cv::Mat greyed;
    cv::cvtColor(input, greyed, CV_RGB2GRAY);
    cv::resize(greyed, greyed, cv::Size(MNIST_WIDTH, MNIST_HEIGHT));

    return fdeep::tensor5_from_bytes(greyed.ptr(),
                                     greyed.rows, greyed.cols, greyed.channels());;
}

fdeep::tensor5 DigitDetector::raw_predict(const fdeep::tensor5 &input)
{
    return m_model->predict({input})[0]; // result is a vector of tensors!;
}

cv::Mat DigitDetector::as_cv_mat(const fdeep::tensor5 &input)
{
    cv::Mat res_image(cv::Size(input.shape().width_, input.shape().height_), CV_8UC1);
    fdeep::tensor5_into_bytes(input,
                              res_image.data,
                              res_image.rows * res_image.cols * res_image.channels());
    return res_image;
}
