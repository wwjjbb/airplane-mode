#! /usr/bin/env bash
# SPDX-FileCopyrightText: 2023 Bill Binder <dxtwjb@gmail.com>
# SPDX-License-Identifier: CC0-1.0
$XGETTEXT `find . -name \*.js -o -name \*.qml -o -name \*.cpp` -o $podir/plasma_applet_org.kde.plasma.airplanemode.pot
