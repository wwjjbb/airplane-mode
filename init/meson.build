# SPDX-FileCopyrightText: None
# SPDX-License-Identifier: CC0-1.0

install_data('rfkillmanager', install_dir: get_option('sysconfdir') / 'init.d')

custom_target('zz_config_files',
    input: [ 'rfkillmanager' ],
    output: 'nothing',
    command: 'ls',
    )
