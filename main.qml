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
                        color: closeButton.Material.rippleColor
                        layer.enabled: true
                        layer.effect: OpacityMask {
                            maskSource: closeButtonBackground
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

            Button {
                id: minimizeButton
                anchors.right: closeButton.right
                anchors.top: parent.top
                anchors.rightMargin: 44
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
                        color: minimizeButton.Material.rippleColor
                        layer.enabled: true
                        layer.effect: OpacityMask {
                            maskSource: minimizeButtonBackground
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

            Button {
                id: launchButton
                x: 634
                y: 361
                width: 144
                height: 114
                topInset: 0
                bottomInset: 0
                background: Rectangle {
                    id: launchButtonBackground
                    color: "#00ff33"
                    radius: 4
                    Ripple {
                        clipRadius: 4
                        width: parent.width
                        height: parent.height
                        pressed: launchButton.pressed
                        anchor: launchButton
                        active: launchButton.down || launchButton.visualFocus || launchButton.hovered
                        color: "#26000000"
                        layer.enabled: true
                        layer.effect: OpacityMask {
                            maskSource: launchButtonBackground
                        }
                    }
                }
                layer.enabled: true
                layer.effect: ElevationEffect {
                    elevation: launchButton.pressed? 1: 8
                }
                Text {
                    text: qsTr("启动游戏")
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 18
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
                Text {
                    color: "#ffffff"
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 19
                    text: qsTr("新闻什么的还没有捏")
                }

//                Image {
//                    id: image
//                    x: 0
//                    y: 0
//                    width: parent.width
//                    height: parent.height - 50
//                    source: "file:/home/redbear/Pictures/illust_66908482_20210127_160011.png"
//                    layer.enabled: true
//                    layer.effect: OpacityMask { // 上面有圆角，下面没圆角
//                        maskSource: Rectangle {
//                            width: image.width
//                            height: image.height
//                            radius: 4
//                            Rectangle {
//                                width: 4
//                                height: 4
//                                anchors.left: parent.left
//                                anchors.bottom: parent.bottom
//                            }
//                            Rectangle {
//                                width: 4
//                                height: 4
//                                anchors.right: parent.right
//                                anchors.bottom: parent.bottom
//                            }
//                        }
//                    }
//                }
                //        Rectangle {
                //            id: mask
                //            x: 0
                //            y: 0
                //            width: 284
                //            height: 152
                //            visible: false
                //            radius: 4
                //            color: "#17191a"
                //        }
                //        OpacityMask {
                //            x: 0
                //            y: 0
                //            width: 284
                //            height: 152
                //            source: image
                //            maskSource: mask
                //        }
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

                    Button {
                        id: changeUserNameButton
                        width: parent.width - 20
                        height: 50
                        anchors.horizontalCenter: parent.horizontalCenter
                        topInset: 0
                        bottomInset: 0
                        background: Rectangle {
                            id: changeUserNameButtonBackground
                            color: "#4815b7"
                            radius: 4
                            layer.enabled: true
                            layer.effect: ElevationEffect {
                                elevation: 8
                            }

                            Ripple {
                                clipRadius: 4
                                width: parent.width
                                height: parent.height
                                pressed: changeUserNameButton.pressed
                                anchor: changeUserNameButton
                                active: changeUserNameButton.down || changeUserNameButton.visualFocus || changeUserNameButton.hovered
                                color: "#26000000"
                                layer.enabled: true
                                layer.effect: OpacityMask {
                                    maskSource: changeUserNameButtonBackground
                                }
                            }
                        }
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
                model: ListModel {
                    ListElement {
                        version: "1.19-pure"
                        background: "pure_background.png"
                    }
                }
                Component.onCompleted: model = gameListModel
                delegate: Button {
                    id: gameVersionButton
                    width: parent.width
                    height: 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    topInset: 0
                    bottomInset: 0
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
                        color: gameList.color
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
                                maskSource: gameVersionButtonBackground
                            }
                        }
                    }
                }
            }
        }
    }




    /*##^##
Designer {
    D{i:0;formeditorZoom:1.1}
}
##^##*/
