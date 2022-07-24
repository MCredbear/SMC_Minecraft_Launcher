import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls.Material.impl 2.15
import QtQuick.Controls 6.2
import Qt5Compat.GraphicalEffects

Window {
    id: window

    width: 800
    height: 500

    minimumWidth: 800
    minimumHeight: 500

    visible: true
    color: "transparent"
    title: qsTr("SMC Minecraft Launcher")
    flags: Qt.Window | Qt.FramelessWindowHint

    MouseArea {
        anchors.fill: parent
        cursorShape: pressed? Qt.SizeAllCursor: Qt.ArrowCursor
        property real oldX
        property real oldY
        onPressed: {
            oldX = mouseX
            oldY = mouseY
        }
        onMouseXChanged: {
            var changedX = Math.round(mouseX - oldX)
            window.x = window.x + changedX
        }
        onMouseYChanged: {
            var changedY = Math.round(mouseY - oldY)
            window.y = window.y + changedY
        }
    }

    MouseArea {
        anchors.left: parent.left
        anchors.top: parent.top
        preventStealing: true
        width: 4
        height: 4
        cursorShape: Qt.SizeFDiagCursor
        property real oldX
        property real oldY
        onPressed: {
            oldX = mouseX
            oldY = mouseY
        }
        onMouseXChanged: {
            var changedX = Math.round(mouseX - oldX)
            if ((window.x + changedX >= 0) & (window.width - changedX > window.minimumWidth))
        {
            window.x = window.x + changedX
            window.width = window.width - changedX
        }
    }
    onMouseYChanged: {
        var changedY = Math.round(mouseY - oldY)
        if ((window.y + changedY >= 0) & (window.height - changedY > window.minimumHeight))
    {
        window.y = window.y + changedY
        window.height = window.height - changedY
    }
}
}

MouseArea {
    anchors.right: parent.right
    anchors.top: parent.top
    preventStealing: true
    width: 4
    height: 4
    cursorShape: Qt.SizeBDiagCursor
    property real oldX
    property real oldY
    onPressed: {
        oldX = mouseX
        oldY = mouseY
    }
    onMouseXChanged: {
        var changedX = Math.round(mouseX - oldX)
        if (Screen.desktopAvailableWidth - window.x - window.width - changedX >= 0)
            window.width = window.width + changedX
        }
        onMouseYChanged: {
            var changedY = Math.round(mouseY - oldY)
            if ((window.y + changedY >= 0) & (window.height - changedY > window.minimumHeight))
        {
            window.y = window.y + changedY
            window.height = window.height - changedY
        }
    }
}

MouseArea {
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    preventStealing: true
    width: 4
    height: 4
    cursorShape: Qt.SizeBDiagCursor
    property real oldX
    property real oldY
    onPressed: {
        oldX = mouseX
        oldY = mouseY
    }
    onMouseXChanged: {
        var changedX = Math.round(mouseX - oldX)
        if ((window.x + changedX >= 0) & (window.width - changedX > window.minimumWidth))
    {
        window.x = window.x + changedX
        window.width = window.width - changedX
    }
}
onMouseYChanged: {
    var changedY = Math.round(mouseY - oldY)
    if (Screen.desktopAvailableHeight - window.y - window.height - changedY >= 0)
        window.height = window.height + changedY
    }
}

MouseArea {
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    preventStealing: true
    width: 4
    height: 4
    cursorShape: Qt.SizeFDiagCursor
    property real oldX
    property real oldY
    onPressed: {
        oldX = mouseX
        oldY = mouseY
    }
    onMouseXChanged: {
        var changedX = Math.round(mouseX - oldX)
        if (Screen.desktopAvailableWidth - window.x - window.width - changedX >= 0)
            window.width = window.width + changedX
        }
        onMouseYChanged: {
            var changedY = Math.round(mouseY - oldY)
            if (Screen.desktopAvailableHeight - window.y - window.height - changedY >= 0)
                window.height = window.height + changedY
            }
        }

        MouseArea {
            anchors.top: parent.top
            preventStealing: true
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - 8
            height: 4
            cursorShape: Qt.SizeVerCursor
            property real oldY
            onPressed: {
                oldY = mouseY
            }
            onMouseYChanged: {
                var changedY = Math.round(mouseY - oldY)
                if ((window.y + changedY >= 0) & (window.height - changedY > window.minimumHeight))
            {
                window.y = window.y + changedY
                window.height = window.height - changedY
            }
        }
    }

    MouseArea {
        anchors.bottom: parent.bottom
        preventStealing: true
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 8
        height: 4
        cursorShape: Qt.SizeVerCursor
        property real oldY
        onPressed: {
            oldY = mouseY
        }
        onMouseYChanged: {
            var changedY = Math.round(mouseY - oldY)
            if (Screen.desktopAvailableHeight - window.y - window.height - changedY >= 0)
                window.height = window.height + changedY
            }
        }

        MouseArea {
            anchors.left: parent.left
            preventStealing: true
            anchors.verticalCenter: parent.verticalCenter
            width: 4
            height: parent.height - 8
            cursorShape: Qt.SizeHorCursor
            property real oldX
            onPressed: {
                oldX = mouseX
            }
            onMouseXChanged: {
                var changedX = Math.round(mouseX - oldX)
                if ((window.x + changedX >= 0) & (window.width - changedX > window.minimumWidth))
            {
                window.x = window.x + changedX
                window.width = window.width - changedX
            }
        }
    }

    MouseArea {
        anchors.right: parent.right
        preventStealing: true
        anchors.verticalCenter: parent.verticalCenter
        width: 4
        height: parent.height - 8
        cursorShape: Qt.SizeHorCursor
        property real oldX
        onPressed: {
            oldX = mouseX
        }
        onMouseXChanged: {
            var changedX = Math.round(mouseX - oldX)
            if (Screen.desktopAvailableWidth - window.x - window.width - changedX >= 0)
                window.width = window.width + changedX
            }
        }

    Rectangle {
        id: rectangle
            anchors.fill: parent
            color: "#17191a"
            radius: 8

            Button {
                id: closeButton
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.rightMargin: 4
                anchors.topMargin: 4
                width: 40
                height: 40
                topInset: 0
                bottomInset: 0
                onReleased: {
                    window.close()
                }

                background: Rectangle {
                    id: closeButtonBackground
                    color: "#17191a"
                    radius: width / 2
                    Ripple {
                        clipRadius: width / 2
                        width: parent.width
                        height: parent.height
                        pressed: closeButton.pressed
                        anchor: closeButton
                        active: closeButton.down || closeButton.visualFocus || closeButton.hovered
                        color: "#2f000000"
                        layer.enabled: true
                        layer.effect: OpacityMask {
                            maskSource: Rectangle {
                                width: closeButtonBackground.width
                                height: closeButtonBackground.height
                                radius: width / 2
                            }
                        }
                    }
                }
                Rectangle {
                    width: 20
                    height: 1
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    rotation: 45
                }
                Rectangle {
                    width: 20
                    height: 1
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    rotation: -45
                }
            }

            Text {
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.topMargin: 6
                anchors.leftMargin: 10
                verticalAlignment: Text.AlignVCenter
                font.family: "Arial"
                font.weight: Font.Light
                font.pointSize: 20
                color: "#ffffff"
                text: "SMC Minecraft Launcher"
            }

            Button {
                id: minimizeButton
                anchors.right: closeButton.left
                anchors.top: parent.top
                anchors.rightMargin: 4
                anchors.topMargin: 4
                width: 40
                height: 40
                topInset: 0
                bottomInset: 0
                onReleased: {
                    window.showNormal() // it seems a feature/bug of frameless window that causes this
                    window.showMinimized()
                }

                background: Rectangle {
                    id: minimizeButtonBackground
                    color: "#17191a"
                    radius: width / 2
                    Ripple {
                        clipRadius: width / 2
                        width: parent.width
                        height: parent.height
                        pressed: minimizeButton.pressed
                        anchor: minimizeButton
                        active: minimizeButton.down || minimizeButton.visualFocus || minimizeButton.hovered
                        color: "#2f000000"
                        layer.enabled: true
                        layer.effect: OpacityMask {
                            maskSource: Rectangle {
                                width: minimizeButtonBackground
                                height: minimizeButtonBackground
                                radius: width / 2
                            }
                        }
                    }
                }
                Rectangle {
                    width: 20
                    height: 1
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Rectangle {
                id: cover
                x: 300
                y: 94
                width: 478
                height: 223
                color: "#17191a"
                radius: 4
                layer.enabled: true
                layer.effect: ElevationEffect {
                    elevation: 8
                }
                Image {
                    anchors.fill: parent
                    source: "file:/home/redbear/SMC_Minecraft_Launcher/pure_background.png"
                    fillMode: Image.PreserveAspectCrop
                    layer.enabled: true
                    layer.effect: OpacityMask {
                        maskSource: cover
                    }
                }
            }

            Material_Button {
                id: launchButton
                x: 634
                y: 361
                width: 144
                height: 114
                color: "#85ff00"
                rippleColor: "#2f000000"
                Text {
                    text: qsTr("启动游戏")
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 18
                }
                onReleased: {
                    if (gameListView.currentIndex !== -1) launcher.launchGame(gameListView.currentIndex)
                }
            }

            Rectangle {
                id: news
                x: 300
                y: 361
                width: 310
                height: 114
                color: "#17191a"
                radius: 4
                layer.enabled: true
                layer.effect: ElevationEffect {
                    elevation: 8
                }
                Material_Image {
                    anchors.fill: parent
                    anchors.bottomMargin: 50
                    source: "file:/home/redbear/SMC_Minecraft_Launcher/pure_background.png"
                    fillMode: Image.PreserveAspectCrop
                    radius: 4
                    roundLeftTop: true
                    roundRightTop: true
                    roundRightBottom: false
                    roundLeftBottom: false
                }
                Text {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.rightMargin: 10
                    anchors.leftMargin: 10
                    height: 50
                    color: "#ffffff"
                    text: qsTr("新闻")
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 20
                }
            }


            Rectangle {
                id: profile
                x: 56
                y: 94
                width: 216
                height: 173
                color: "#5016d1"
                radius: 4
                layer.enabled: true
                layer.effect: ElevationEffect {
                    elevation: 8
                }
                Column {
                    anchors.fill: parent
                    spacing: 10
                    Rectangle {
                        width: 1
                        height: 1
                        color: "transparent"
                    }

                    TextInput {
                        width: parent.width - 20
                        height: 50
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "MCredbear"
                        verticalAlignment: Text.AlignVCenter
                        clip: true
                        font.pointSize: 18
                    }

                    Material_Button {
                        id: changeUserNameButton
                        width: parent.width - 20
                        height: 50
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "#4815b7"
                        Text {
                            text: qsTr("更改用户名")
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.pointSize: 18
                        }
                    }
                }
            }
        }

        Rectangle {
            id: gameList
            x: 56
            y: 302
            width: 216
            height: 173
            color: "#17191a"
            radius: 4
            layer.effect: ElevationEffect {
                elevation: 8
            }
            layer.enabled: true
            ListView {
                id: gameListView
                anchors.fill: parent
                model: gameListModel
                currentIndex: -1
                delegate: Button {
                    id: gameVersionButton
                    width: parent.width
                    height: 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    topInset: 0
                    bottomInset: 0
                    onReleased: {
                        gameListView.currentIndex = index
                    }
                    Text {
                        color: "#3d3d3d"
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        anchors.leftMargin: 10
                        text: modelData.version
                        font.pointSize: 17
                    }
                    background: Rectangle {
                        id: gameVersionButtonBackground
                        color: (gameListView.currentIndex == index)? "#333333" : gameList.color
                        radius: 4
                        Ripple {
                            clipRadius: 4
                            width: parent.width
                            height: parent.height
                            pressed: gameVersionButton.pressed
                            anchor: gameVersionButton
                            active: gameVersionButton.down || gameVersionButton.visualFocus || gameVersionButton.hovered
                            color: "#26000000"
                            layer.enabled: true
                            layer.effect: OpacityMask {
                                maskSource: Rectangle{
                                    width: gameVersionButtonBackground.width
                                    height: gameVersionButtonBackground.height
                                }
                            }
                        }
                    }
                }
            }
        }
    }




    /*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
