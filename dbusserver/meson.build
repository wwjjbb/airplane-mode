# SPDX-FileCopyrightText: None
# SPDX-License-Identifier: CC0-1.0

service_moc_headers = [ 'maintask.h', 'rfkillmanager.h', ]

service_moc_files = qt.compile_moc(
    headers: service_moc_headers,
    dependencies: [ qt_dep, ],
    )

service_hdr = [
    'devrfkill.h',
    ]

devrfkill_src = [
    'devrfkill.cpp',
    ]

service_src = [
    'main.cpp',
    'maintask.cpp',
    'rfkillmanager.cpp',
    ]

devrfkill_lib = static_library('devrfkill', devrfkill_src, )

executable(
    'rfkillmanager_service',
    service_src,
    service_moc_files,
    extra_files: [ service_moc_headers, service_hdr, ],
    link_with: devrfkill_lib,
    dependencies: [qt_dep, if_dep, ],
    install: true,
    install_dir: get_option('sbindir'),
    )

executable('test_devrfkill',
    'test_devrfkill.cpp',
    link_with: devrfkill_lib,
    install: false,
    )
