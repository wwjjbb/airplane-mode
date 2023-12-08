# SPDX-FileCopyrightText: None
# SPDX-License-Identifier: CC0-1.0

project('airplanemode', 'cpp',
        version : '0.5.0',
        license : 'GPL-2.0-only',
        default_options : [
            'prefix=/usr',
            'sysconfdir=/etc',
            'cpp_std=c++17'
        ],
        meson_version : '>= 1.2.3',
)

## Set defines based on options
## ============================

cpp_args = []
if (get_option('use_system_bus'))
    cpp_args += '-DUSE_SYSTEM_BUS'
endif

if (get_option('use_system_config'))
    cpp_args += '-DUSE_SYSTEM_CONFIG'
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

qt5 = import('qt5')
qt5_dep = dependency('qt5', modules: ['Core', 'DBus', 'Sql', ])


kf5_plasma_dep = dependency('KF5Plasma',
    cmake_module_path: '/usr/share/ECM/find-modules',
    )

kf5_i18n_dep = dependency('KF5I18n',
    cmake_module_path: '/usr/share/ECM/find-modules',
    )

qdbusxml2cpp = find_program('qdbusxml2cpp', dirs: [ '/usr/lib64/qt5/bin' ], required: true)

plasmapkg2 = find_program('plasmapkg2', required: true)

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
