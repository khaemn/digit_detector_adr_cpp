#ifndef DIGITDETECTOR_H
#define DIGITDETECTOR_H

#include <memory>

#include <QObject>

#include <fdeep/fdeep.hpp>

#include <opencv2/imgproc.hpp>

class DigitDetector : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString digit READ digit NOTIFY digitChanged)


public:
    explicit DigitDetector(QObject *parent = nullptr);

    // For debug only.
    void init();

    Q_INVOKABLE void test_recognizing(const QString& file);
    QString digit() const;

    static constexpr auto MNIST_WIDTH = 28;
    static constexpr auto MNIST_HEIGHT = 28;

    static void registerQmlType();

signals:
    void digitChanged(QString digit);

public slots:

private:
    fdeep::tensor5 as_native_tensor(const cv::Mat& input);

    fdeep::tensor5 raw_predict(const fdeep::tensor5& input);

    cv::Mat as_cv_mat(const fdeep::tensor5& input);

private:
    QString m_digit;
    std::unique_ptr<fdeep::model> m_model;
};

#endif // DIGITDETECTOR_H
