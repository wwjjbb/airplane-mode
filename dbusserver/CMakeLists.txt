# SPDX-FileCopyrightText: 2023 Bill Binder <dxtwjb@gmail.com>
# SPDX-License-Identifier: CC0-1.0

set(HeaderFiles maintask.h rfkillmanager.h devrfkill.h)
add_custom_target(OtherService SOURCES ${HeaderFiles} )

set(service_SRCS main.cpp maintask.cpp rfkillmanager.cpp devrfkill.cpp)

add_executable(rfkillmanager_service ${service_SRCS} )
target_link_libraries(rfkillmanager_service Qt5::Core Qt5::DBus dbusif)

add_executable(rfkill_test test_devrfkill.cpp devrfkill.cpp)

install(TARGETS rfkillmanager_service DESTINATION ${CMAKE_INSTALL_SBINDIR})

# TODO (MEDIUM) write an ebuild

