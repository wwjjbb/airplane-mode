/*
    SPDX-FileCopyrightText: 2024 wjb <bill@w-j-b.com>
    SPDX-License-Identifier: LGPL-2.1-or-later
*/

import QtQuick 2.15
import QtQuick.Layouts 1.0

import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.components 3.0 as PlasmaComponents
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.plasma5support 2.0 as Plasma5Support

PlasmoidItem {

    width: 128
    height:128

    Plasmoid.backgroundHints: "NoBackground"
    preferredRepresentation: compactRepresentation

    Plasmoid.icon: ""
    toolTipMainText: "Airplane Mode"
    toolTipSubText: airMode ? "ON: WiFi/Bluetooth are disabled" : "OFF: WiFi/Bluetooth are enabled"

    property bool airMode: plasmoid.airMode
    property string stateIcon: airMode ? "mode-on" : "mode-off"

    fullRepresentation: ColumnLayout {
        id: full
        anchors.fill: parent
        PlasmaComponents.Label {
            text: "fullRepresentation has to be here??"
        }
    }

    compactRepresentation: ColumnLayout {
        anchors.fill: parent
        Image {
            //Layout.fillHeight: true
            //Layout.fillWidth: true
            //fillMode: Image.PreserveAspectFit
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            source: "../images/" + stateIcon + ".png"

            MouseArea {
                anchors.fill: parent
                onClicked: plasmoid.toggleAirMode()
            }
        }
    }
}
