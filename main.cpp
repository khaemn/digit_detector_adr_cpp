#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <iostream>

// #include "digitdetector.h"

// https://github.com/EN10/KerasMNIST

//void check_eigen()
//{
//    using Eigen::MatrixXd;
//    MatrixXd m(2,2);
//    m(0,0) = 3;
//    m(1,0) = 2.5;
//    m(0,1) = -1;
//    m(1,1) = m(1,0) + m(0,1);
//    std::cout << m << std::endl;
//}
//double check_fourteens_and_hardstl()
//{
//    // Checking to_string std function
//    std::string pi = "pi is " + std::to_string(3.1415926);
//    std::string perfect = std::to_string(1+2+4+7+14) + " is a perfect number";
//    std::cout << pi << '\n';
//    std::cout << perfect << '\n';

//    // Store a generalized lambda, that squares a number, in a variable
//    auto func = [](auto input) { return input * input; };

//    std::unique_ptr<int> test_cpp14_uniq = std::make_unique<int>(6);
//    std::vector<std::unique_ptr<int>> test_cpp14_vec = std::vector<std::unique_ptr<int>>();
//    // Usage examples:
//    // square of an int
//    std::cout << func(10) << std::endl;

//    // square of a double
//    std::cout << func(2.345) << std::endl;

//    // square of a complex number
//    std::cout << func(std::complex<double>(3, -2)) << std::endl;

//    auto overallsum = func(20) + func(20.);
//    return overallsum;
//}


int main(int argc, char *argv[])
{
//    double ovsum = check_fourteens_and_hardstl();
//    check_eigen();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

//    DigitDetector::registerQmlType();
//    DigitDetector detector;

//    detector.init();

    QQmlApplicationEngine engine;
    QQuickView view(&engine, nullptr);
//    engine.rootContext()->setContextProperty("__context_overallsum", ovsum);
//    engine.rootContext()->setContextProperty("__context_detector", &detector);
    view.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    view.show();

    return app.exec();
}
