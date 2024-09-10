# SPDX-FileCopyrightText: None
# SPDX-License-Identifier: CC0-1.0

subdir('resources')
subdir('package')

plasmoid_moc_hdr = [
    'airplanemode.h',
    ]

plasmoid_moc_files = qt.compile_moc(
    headers: plasmoid_moc_hdr,
    sources: 'airplanemode.cpp',
    dependencies: [ qt_dep, kf_plasma_dep, kf_i18n_dep, ],
    )

plasmoid_src = [
    'airplanemode.cpp',
    ]

plasmoid_lib = library('airplanemode',
    plasmoid_src,
    plasmoid_moc_files,
    extra_files: plasmoid_moc_hdr,
    name_prefix: 'com.wwjjbb.plasma.',
    dependencies: [ qt_dep, kf_plasma_dep, kf_i18n_dep, if_dep, kf_config_dep, ],
    install: true,
    install_dir: get_option('libdir') / 'qt6' / 'plugins' / 'plasma' / 'applets',
    )
