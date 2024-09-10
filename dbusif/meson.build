# SPDX-FileCopyrightText: None
# SPDX-License-Identifier: CC0-1.0

if_moc_headers = [ 'rfkilladaptor.h', ]

if_moc_files = qt.compile_moc(
    headers: if_moc_headers,
    dependencies: qt_dep
    )

if_src = [
    'rfkilladaptor.cpp',
    ]

if_lib = static_library(
    'dbusif',
    if_src,
    if_moc_files,
    extra_files: [ if_moc_headers, ],
    dependencies: [ qt_dep, ],
    install: false
    )

if_dep = declare_dependency(
    link_with: if_lib,
    include_directories: '.')

custom_target('zz_dbus_files',
    input: [
        'com.wwjjbb.RfKillManager.conf',
        'com.wwjjbb.RfKillManager.xml',
        'com.wwjjbb.RfKillManager.xml.license',
        'generate_interface',
        'rfkilladaptor.cpp.license',
        'rfkilladaptor.h.license',
        ],
    output: 'nothing',
    command: 'ls',
    )

# Install dbus interface file

install_data('com.wwjjbb.RfKillManager.conf',
             install_dir: get_option('datadir') / 'dbus-1' / 'system.d' )
