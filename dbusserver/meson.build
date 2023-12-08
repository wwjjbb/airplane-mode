# SPDX-FileCopyrightText: None
# SPDX-License-Identifier: CC0-1.0

service_moc_headers = [ 'maintask.h', 'rfkillmanager.h', ]

service_moc_files = qt5.compile_moc(
    headers: service_moc_headers,
    dependencies: [ qt5_dep, ],
    )

service_hdr = [
    'devrfkill.h',
    ]

service_src = [
    'devrfkill.cpp',
    'main.cpp',
    'maintask.cpp',
    'rfkillmanager.cpp',
    ]

executable(
    'rfkillmanager_service',
    service_src,
    service_moc_files,
    extra_files: [ service_moc_headers, service_hdr, ],
    dependencies: [qt5_dep, if_dep, ],
    install: true,
    install_dir: get_option('sbindir'),
    )

executable('test_devrfkill',
    'test_devrfkill.cpp', 'devrfkill.cpp',
    install: false,
    )
