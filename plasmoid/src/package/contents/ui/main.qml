/*
    SPDX-FileCopyrightText: 2023 wjb <bill@w-j-b.com>
    SPDX-License-Identifier: LGPL-2.1-or-later
*/

import QtQuick 2.1
import QtQuick.Layouts 1.1
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.components 2.0 as PlasmaComponents

Item {

    width: 128
    height:128

    Plasmoid.backgroundHints: "NoBackground"
    Plasmoid.preferredRepresentation: Plasmoid.compactRepresentation

    Plasmoid.icon: ""
    Plasmoid.toolTipMainText: "Airplane Mode"
    Plasmoid.toolTipSubText: airMode ? "ON: WiFi/Bluetooth are disabled" : "OFF: WiFi/Bluetooth are enabled"

    property bool airMode: Plasmoid.nativeInterface.airMode
    property string stateIcon: airMode ? "mode-on" : "mode-off"

    Plasmoid.compactRepresentation: ColumnLayout {
        anchors.fill: parent
        Image {
            //Layout.fillHeight: true
            //Layout.fillWidth: true
            //fillMode: Image.PreserveAspectFit
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            source: "../images/" + stateIcon + ".png"

            MouseArea {
                anchors.fill: parent
                onClicked: Plasmoid.nativeInterface.toggleAirMode()
            }
        }
    }
}
