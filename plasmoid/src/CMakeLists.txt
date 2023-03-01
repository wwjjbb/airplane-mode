# SPDX-FileCopyrightText: 2023 Bill Binder <dxtwjb@gmail.com>
# SPDX-License-Identifier: CC0-1.0

set(OtherAppletFiles airplanemode.h
               package/metadata.json
               package/contents/images/mode-off.png
               package/contents/images/mode-on.png
               package/ui/main.qml
           )
add_custom_target(OtherApplet SOURCES ${OtherAppletFiles})

add_definitions(-DTRANSLATION_DOMAIN=\"plasma_applet_com.wwjjbb.plasma.airplanemode\")

add_library(plasma_applet_airplanemode MODULE airplanemode.cpp)

target_link_libraries(plasma_applet_airplanemode
                      Qt5::Gui
                      KF5::Plasma
                      KF5::I18n
                      dbusif)


install(TARGETS plasma_applet_airplanemode DESTINATION ${KDE_INSTALL_PLUGINDIR}/plasma/applets)

configure_file(metadata.json.in ${CMAKE_CURRENT_SOURCE_DIR}/package/metadata.json)

plasma_install_package(package com.wwjjbb.plasma.airplanemode)
