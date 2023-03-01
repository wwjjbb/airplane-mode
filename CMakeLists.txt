# SPDX-FileCopyrightText: 2023 Bill Binder <dxtwjb@gmail.com>
# SPDX-License-Identifier: CC0-1.0

cmake_minimum_required(VERSION 3.25)

project(airplane-mode VERSION 0.4)

find_package(ECM 1.4.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

# Whether to use the DBus System Bus (DEFAULT) or Session Bus
# The service has be run by root for System Bus or as a user for Session Bus.
option(USE_SYSTEM_BUS "Use the DBus SystemBus (ON) or SessionBus (OFF)" ON)

# The state can be in /etc/rfkill (DEFAULT) or ~/.config/rfkill
# Depends if you want to run the service as root or a user.
option(USE_SYSTEM_CONFIG "Rfkill state is persisted in /etc/rfkill (ON) or ~/.config/rfkill (OFF)" ON)

find_package(KF5 REQUIRED COMPONENTS
    Plasma
    I18n
)

find_package(Qt5 CONFIG REQUIRED COMPONENTS
    Quick
    Core
    DBus
)

add_compile_definitions(
    $<$<CONFIG:DEBUG>:DEBUG_MODE>
    $<$<CONFIG:RELEASE>:QT_NO_DEBUG_OUTPUT>
)

if (USE_SYSTEM_BUS)
    add_compile_definitions(USE_SYSTEM_BUS)
endif()

if (USE_SYSTEM_CONFIG)
    add_compile_definitions(USE_SYSTEM_CONFIG)
endif()

add_subdirectory(init)
add_subdirectory(dbusif)
add_subdirectory(dbusserver)
add_subdirectory(plasmoid)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

# NOTE: Generate the archive with "$ ninja -v package_source"
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_IGNORE_FILES
    CMakeLists.txt.user
    .hg/
    .hgtags
    "plasmoid/src/package/metadata.json$"
)
set(CPACK_VERBATIM_VARIABLES YES)
include(CPack)
