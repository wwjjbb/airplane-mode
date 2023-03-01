# SPDX-FileCopyrightText: 2023 Bill Binder <dxtwjb@gmail.com>
# SPDX-License-Identifier: CC0-1.0

# For QtCreator to show files
set(InitFiles rfkillmanager)
add_custom_target(OtherInit SOURCES ${InitFiles})

install(PROGRAMS rfkillmanager DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/init.d)
