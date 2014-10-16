import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {

    id: applicationWindow1
    visible: true
    width: 1080
    height: 1920
    title: qsTr("Cgminer Watcher")
    menuBar: MenuBar {

        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Visit CryptAxe.com")
                onTriggered: {
                    axedroid.visitCryptAxe()
                }
            }
            /*
            MenuItem {
                text: qsTr("Upgrade To Plus")
            }
            */
            MenuItem {
                text: qsTr("Help (On Website)")
                onTriggered: {
                    axedroid.visitAppPage()
                }
            }

            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Grid {
        id: settingsGrid
        x: 25
        y: 366
        width: applicationWindow1.width - 50
        height: applicationWindow1.height / 3
        spacing: 0
        columns: 1
        visible: false
        anchors.top: grid2.bottom
        anchors.topMargin: 10

        Rectangle {
            id: settingsRectangle
            width: settingsGrid.width
            height: settingsGrid.height
            color: "#ffffff"
            opacity: 50
            radius: 10

            ColumnLayout {
                width: settingsRectangle.width
                height: settingsRectangle.height
                anchors.horizontalCenter: settingsRectangle.horizontalCenter
                anchors.verticalCenter: settingsRectangle.verticalCenter
                id: settingsColumn
                spacing: 0

                Text {
                    id: iplabel
                    text: qsTr("IP Address:")
                }

                TextField {
                    id: ipTextField
                    anchors.top: iplabel.bottom
                    width: settingsRectangle.width
                    placeholderText: "Ex: 192.168.0.1"
                    text: axedroid.getIPAddress(0)
                    font.pixelSize: rectangle4.height * 0.2
                    onTextChanged: {
                        console.log("Text Changed: ")
                        console.log(ipTextField.text)
                        console.log("\n")
                        axedroid.setIPAddress(0, ipTextField.text)
                    }
                }
                Text {
                    id: portLabel
                    text: qsTr("Port:")
                    anchors.top: ipTextField.bottom
                }
                TextField {
                    id: portTextField
                    anchors.top: portLabel.bottom
                    width: settingsRectangle.width
                    font.pixelSize: rectangle4.height * 0.2
                    text: axedroid.getPort(0)
                    onTextChanged: {
                        console.log("The port number has changed to: " + portTextField.text)
                        axedroid.setPort(0, portTextField.text)
                    }
                }
                Button {
                    id: helpButton
                    anchors.top: portTextField.bottom
                    anchors.topMargin: 20
                    text: "Help (opens website)"
                    onClicked: {
                        axedroid.visitAppPage()
                    }
                }
            }
        }
    }

    ComboBox {
        id: minerSelect
        x: 258
        y: 8
        width: parent.width - 20
        height: 75
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        enabled: false

        model: ListModel {
            id: cbItems
            ListElement { text: "Miner 1"}
            ListElement { text: "Miner 2"}
            //ListElement { text: "Upgrade to premium for more slots"}
        }
    }

    Grid {
        id: grid1
        x: 25
        y: 366
        width: parent.width - 50
        height: parent.height / 3
        spacing: 20
        columns: 2
        state: "viewMiner"
        anchors.top: grid2.bottom
        anchors.topMargin: 10


        states: [
            State {
                name: "viewSettings"
                PropertyChanges {target: grid1; visible: false}
            },
            State {
                name: "viewMiner"
                PropertyChanges {target: grid1; visible: true}
            }
        ]

        Rectangle {
            id: rectangle2
            width: (grid1.width / 2) - 10
            height: (grid1.height / 2) -10
            color: "#ffffff"
            opacity: 50
            radius: 10

            Text {
                id: text1
                x: 99
                y: 116
                text: axedroid.getMHS
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: parent.height * 0.2
            }
        }

        Rectangle {
            id: rectangle3
            x: 3
            y: -3
            width: (grid1.width / 2) - 10
            height: (grid1.height / 2) -10
            color: "#ffffff"
            radius: 10

            Text {
                id: text2
                x: 99
                y: 116
                text: axedroid.getAcc
                font.pixelSize: parent.height * 0.2
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                font.bold: true
            }
        }

        Rectangle {
            id: rectangle4
            x: -3
            y: 0
            width: (grid1.width / 2) - 10
            height: (grid1.height / 2) -10
            color: "#ffffff"
            radius: 10

            Text {
                id: text3
                x: 99
                y: 116
                text: axedroid.getRej
                font.pixelSize: parent.height * 0.2
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                font.bold: true
            }
        }

        Rectangle {
            id: rectangle5
            x: -7
            y: 1
            width: (grid1.width / 2) - 10
            height: (grid1.height / 2) -10
            color: "#ffffff"
            radius: 10

            Text {
                id: text4
                x: 99
                y: 116
                text: axedroid.getHwerr
                font.pixelSize: parent.height * 0.2
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                font.bold: true
            }
        }
    }

    Grid {
        id: grid2
        x: 25
        y: 99
        width: parent.width - 50
        height: parent.height / 8
        opacity: 1
        rows: 1
        columns: 3
        spacing: 20


        Rectangle {
            id: rectangle1
            width: (parent.width / 3) -10
            height: parent.height
            color: axedroid.getConStatusColor
            opacity: 0.8
            z: -1
            radius: 25

            Text {
                id: text5
                x: 333
                y: 0
                text: qsTr("Connection")
                style: Text.Raised
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: parent.height * 0.2
            }
        }

        Rectangle {
            id: rectangle6
            x: 0
            y: 0
            width: (parent.width / 3) -10
            height: parent.height
            color: axedroid.getPoolStatusColor
            opacity: 0.8
            radius: 25

            Text {
                id: text6
                x: 333
                y: 0
                text: qsTr("Pool")
                style: Text.Raised
                font.bold: true
                font.pixelSize: parent.height * 0.2
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
            z: -1
        }

        Rectangle {
            id: rectangle7
            x: -9
            y: -4
            width: (parent.width / 3) -10
            height: parent.height
            color: axedroid.getMinStatusColor
            opacity: 0.8
            radius: 25

            Text {
                id: text7
                x: 333
                y: 0
                text: qsTr("Miner")
                style: Text.Raised
                font.bold: true
                font.pixelSize: parent.height * 0.2
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
            z: -1
        }
    }

    Rectangle {
        id: rectangle8
        x: -268
        y: 8
        width: parent.width
        height: parent.height
        color: "#000000"
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        z: -1
    }

    Grid {
        width: parent.width - 50
        id: grid3
        x: 25
        height: 200
        anchors.top: grid1.bottom
        anchors.topMargin: 32
        flow: Qt.TopToBottom
        rows: 2
        columns: 2

        Flickable {
            id: flickable1
            width: grid3.width
            height: rectangle4.height / 2
            maximumFlickVelocity: 50000
            boundsBehavior: Flickable.DragAndOvershootBounds
            flickableDirection: Flickable.HorizontalFlick
            z: 1

            onFlickStarted: {
                console.log("Flick Started\n")
                if (grid1.visible) {
                    console.log("Settings grid1 to invisible\n")
                    grid1.visible = false
                    settingsGrid.visible = true
                    text8.text = "<<    Swipe to go home    >>"
                }
                else {
                    console.log("Settings grid1 to visible\n")
                    grid1.visible = true
                    settingsGrid.visible = false
                    text8.text = "<<    Swipe to view settings    >>"
                }
            }

            Rectangle {
                id: rectangle9
                x: 0
                y: 0
                width: parent.width
                height: parent.height
                radius: 25
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.top: parent.top
                anchors.left: parent.left
                border.width: 5
                border.color: "#0b77c6"
                Text {
                    id: text8
                    x: 57
                    y: 48
                    color: "#000000"
                    text: qsTr("<<    Swipe to view settings    >>")
                    font.pixelSize: parent.height * 0.2
                    anchors.verticalCenter: rectangle9.verticalCenter
                    anchors.horizontalCenter: rectangle9.horizontalCenter
                }
        }
        }
    }
}
