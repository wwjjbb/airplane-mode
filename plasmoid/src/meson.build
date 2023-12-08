# SPDX-FileCopyrightText: None
# SPDX-License-Identifier: CC0-1.0

subdir('resources')
subdir('package')

plasmoid_moc_hdr = [
    'airplanemode.h',
    ]

plasmoid_moc_files = qt5.compile_moc(
    headers: plasmoid_moc_hdr,
    sources: 'airplanemode.cpp',
    dependencies: [ qt5_dep, kf5_plasma_dep, kf5_i18n_dep, ],
    )

plasmoid_src = [
    'airplanemode.cpp',
    ]

plasmoid_lib = library('airplanemode',
    plasmoid_src,
    plasmoid_moc_files,
    name_prefix: 'plasma_applet_',
    dependencies: [ qt5_dep, kf5_plasma_dep, kf5_i18n_dep, if_dep, ],
    install: true,
    install_dir: get_option('libdir') / 'qt5' / 'plugins' / 'plasma' / 'applets',
    )
