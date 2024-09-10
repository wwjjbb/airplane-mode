# SPDX-FileCopyrightText: None
# SPDX-License-Identifier: CC0-1.0

# The version number is also in metadata.json

project('airplanemode', 'cpp',
        version : '0.6.0',
        license : 'GPL-2.0-only',
        default_options : [
            'prefix=/usr',
            'sysconfdir=/etc',
            'cpp_std=c++17'
        ],
        meson_version : '>= 1.5.1',
)

cpp = meson.get_compiler('cpp')

## Set defines based on options
## ============================

cpp_args = []
if (get_option('use_system_bus'))
    cpp_args += '-DUSE_SYSTEM_BUS'
endif

if (get_option('use_system_config'))
    cpp_args += '-DUSE_SYSTEM_CONFIG'
endif

if (get_option('enable_tracing'))
    cpp_args += '-DTRACE'
endif

add_global_arguments(cpp_args, language: 'cpp')

## Check the version numbers agree
## ===============================

# There is a version in the header above, and in the metadata.json
# file in the QML package. It proved awkward to syn them automatically,
# so just check they agree and stop the build of not.
# This command only runs at configure time but that should be ok.
# The script echoes the application ID if the versions match.
metacheck = run_command('check_version_consistent', check: true)
applet_id = metacheck.stdout().strip()
assert(applet_id != '', 'Applet ID not found in metadata.json')

## Check the dependencies
## ======================

qt = import('qt6')
qt_dep = dependency('qt6', modules: ['Core', 'DBus', 'Sql', ])

# kde-plasma/libplasma
kf_plasma_dep = dependency('Plasma',
    cmake_module_path: '/usr/share/ECM/find-modules',
    )

kf_what = dependency('KF6Wallet',
    cmake_module_path: '/usr/share/ECM/find-modules',
    )

kf_kconfigcore_lib = cpp.find_library('KF6ConfigCore')

kf_config_dep = declare_dependency(
    include_directories: [
        '/usr/include/KF6/KConfigCore',
        '/usr/include/KF6/KConfig',
        ],
    dependencies: kf_kconfigcore_lib
    )

kf_i18n_dep = dependency('KF6I18n',
    cmake_module_path: '/usr/share/ECM/find-modules',
    )

qdbusxml2cpp = find_program('qdbusxml2cpp', dirs: [ '/usr/lib64/qt6/bin' ], required: true)

kpackagetool = find_program('kpackagetool6', required: true)

## Do the build
## ============

subdir('dbusif')
subdir('dbusserver')
subdir('init')
subdir('plasmoid')

## Show files in IDE
## =================

custom_target('zz_license_files',
    input: [
        'LICENSES' / 'CC0-1.0.txt',
        'LICENSES' / 'GPL-2.0-only.txt',
        'LICENSES' / 'LGPL-2.1-or-later.txt',
        ],
    output: 'nothing1',
    command: 'ls',
    )


custom_target('zz_project_files',
    input: [
        'readme.txt',
        'meson_options.txt',
        ],
    output: 'nothing2',
    command: 'ls',
    )
