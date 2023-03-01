# SPDX-FileCopyrightText: 2023 Bill Binder <dxtwjb@gmail.com>
# SPDX-License-Identifier: CC0-1.0

# For QtCreator to show files
set(HeaderFiles rfkilladaptor.h com.wwjjbb.RfKillManager.xml com.wwjjbb.RfKillManager.conf)
add_custom_target(OtherIf SOURCES ${HeaderFiles})

set(dbusif_SRCS rfkilladaptor.cpp )

add_library(dbusif STATIC ${dbusif_SRCS})

target_link_libraries(dbusif Qt5::Core Qt5::DBus)

install(FILES com.wwjjbb.RfKillManager.conf DESTINATION ${KDE_INSTALL_DBUSDIR}/system.d)
