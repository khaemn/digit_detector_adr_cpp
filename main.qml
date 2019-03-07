import QtQuick 2.0
import QtMultimedia 5.0

Rectangle {
    id: root

    readonly property bool isLandscape: width > height

    anchors.fill: parent
    color: "blue"


    Camera {
        id: camera

        imageProcessing.whiteBalanceMode: CameraImageProcessing.WhiteBalanceFlash

        exposure {
            exposureCompensation: -1.0
            exposureMode: Camera.ExposurePortrait
        }

        flash.mode: Camera.FlashRedEyeReduction

        imageCapture {
            onImageCaptured: {
                photoPreview.source = preview  // Show the preview in an Image
            }
        }
    }

    Rectangle {
        anchors.centerIn: parent
        width: root.width * 0.9
        height: root.height * 0.9
        color: "grey"

        VideoOutput {
            source: camera
            anchors.fill: parent
            anchors.margins: 20
            focus : visible // to receive focus and capture key events when visible
            rotation: isLandscape ? 0 : -90
        }

        Text {
            anchors.centerIn: parent
            text: "Height " + root.height + ", width " + root.width + ", c++14 " + __context_overallsum
            color: "white"
            font.pixelSize: 26
        }
    }

    Image {
        id: digit
        source: "qrc:/assets:/android-sources/assets/three.png"
        anchors.centerIn: parent

        MouseArea {
            anchors.fill: parent
            onClicked: {
                __context_detector.test_recognizing(":/assets:/android-sources/assets/three.png");
            }
        }
    }
}
