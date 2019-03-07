QT += quick multimedia
CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    digitdetector.cpp

RESOURCES += qml.qrc

CONFIG += mobility
MOBILITY =

INCLUDEPATH += /usr/local/include/

linux:!android {
    LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs
}

android {
    ANDROID_EXTRA_LIBS += /media/vova/Auxiliary/Android/crystax-ndk-10.3.2/sources/crystax/libs/armeabi-v7a/libcrystax.so
    LIBS += -L"/media/vova/Auxiliary/Android/crystax-ndk-10.3.2/sources/crystax/libs/armeabi-v7a/" \
    -lcrystax
    # Additional import path used to resolve QML modules in Qt Creator's code model
    # QML_IMPORT_PATH = /media/vova/Auxiliary/Qt5.11.0/clang-adr/qml
    DEFINES += EIGEN_MAX_CPP_VER=11
    DEFINES += ANDROID

    INCLUDEPATH += $${OPENCV_PATH}/sdk/native/jni/include/
    OPENCV_PATH = /media/vova/Auxiliary/Downloads/OpenCV-android-sdk
    ANDROID_PACKAGE_SOURCE_DIR=$$_PRO_FILE_PWD_/android-sources

    # Change the last part (armeabi-v7a) according to your build
    OPENCV3RDPARTYLIBS = $$OPENCV_PATH/sdk/native/3rdparty/libs/armeabi-v7a
    OPENCVNATIVELIBS = $$OPENCV_PATH/sdk/native/libs/armeabi-v7a

    LIBS += $$OPENCV3RDPARTYLIBS/liblibtiff.a \
        $$OPENCV3RDPARTYLIBS/liblibjpeg.a \
        $$OPENCV3RDPARTYLIBS/liblibjasper.a \
        $$OPENCV3RDPARTYLIBS/liblibpng.a \
        $$OPENCV3RDPARTYLIBS/libIlmImf.a \
        $$OPENCV3RDPARTYLIBS/libtbb.a

    LIBS += $$OPENCVNATIVELIBS/libopencv_core.a \
        $$OPENCVNATIVELIBS/libopencv_androidcamera.a \
        $$OPENCVNATIVELIBS/libopencv_flann.a \
        $$OPENCVNATIVELIBS/libopencv_imgproc.a \
        $$OPENCVNATIVELIBS/libopencv_highgui.a \
        $$OPENCVNATIVELIBS/libopencv_features2d.a \
        $$OPENCVNATIVELIBS/libopencv_calib3d.a \
        $$OPENCVNATIVELIBS/libopencv_ml.a \
        $$OPENCVNATIVELIBS/libopencv_objdetect.a \
        $$OPENCVNATIVELIBS/libopencv_photo.a \
        $$OPENCVNATIVELIBS/libopencv_stitching.a \
        $$OPENCVNATIVELIBS/libopencv_superres.a \
        $$OPENCVNATIVELIBS/libopencv_ts.a \
        $$OPENCVNATIVELIBS/libopencv_video.a \
        $$OPENCVNATIVELIBS/libopencv_videostab.a \
        $$OPENCVNATIVELIBS/libopencv_java.so \
        $$OPENCVNATIVELIBS/libopencv_info.so

#    jsons.files = android-sources/assets/mnist.json \
#         android-sources/assets/dense.json \
#         android-sources/assets/one.png \
#         android-sources/assets/two.png \
#         android-sources/assets/three.png
#    jsons.path = /assets/jsons/
#    INSTALLS += jsons
}


# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    digitdetector.h
