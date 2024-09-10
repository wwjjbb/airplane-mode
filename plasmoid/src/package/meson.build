# SPDX-FileCopyrightText: None
# SPDX-License-Identifier: CC0-1.0

plasmoid_contents = 'contents'
plasmoid_images = plasmoid_contents / 'images'
plasmoid_ui = plasmoid_contents / 'ui'

custom_target('zz_qml_package',
   input: [
       #'metadata.json',
       plasmoid_contents / 'screenshot.png',
       plasmoid_images / 'mode-off.png',
       plasmoid_images / 'mode-on.png',
       plasmoid_images / 'pairs.svgz',
       plasmoid_images / 'pairs.svgz.license',
       plasmoid_ui / 'main.qml',
       ],
   output: 'nothing',
   command: 'ls',
   )

# Install QML app globally
# Files under package/contents are installed under:
#    /usr/share/plasma/plasmoids/com.wwjjbb.plasma.airplanemode
# where com.wwjjbb.plasma.airplanemode is the app's ID defined in metadata.json

plasmoid_home = get_option('datadir') / 'plasma' / 'plasmoids' / applet_id

install_data('metadata.json', install_dir: plasmoid_home)
install_data(plasmoid_contents / 'screenshot.png', install_dir: plasmoid_home / plasmoid_contents)
install_data(plasmoid_images / 'mode-off.png', install_dir: plasmoid_home / plasmoid_images)
install_data(plasmoid_images / 'mode-on.png', install_dir: plasmoid_home / plasmoid_images)
install_data(plasmoid_images / 'pairs.svgz', install_dir: plasmoid_home / plasmoid_images)
install_data(plasmoid_images / 'pairs.svgz.license', install_dir: plasmoid_home / plasmoid_images)
install_data(plasmoid_ui / 'main.qml', install_dir: plasmoid_home / plasmoid_ui)

# Generate the appdata xml file using kpackagetool. and install into /usr/share/metainfo
# The tool/meson seemed to require absolute paths for the parameters. No idea what the
# current working dir is, I'd have assumed the current directory but apparently not.

metainfo_appdata_xml = applet_id + '.appdata.xml'
metainfo = custom_target('metainfo',
    output: metainfo_appdata_xml,
    input: 'metadata.json',
    command: [ kpackagetool,
               '--appstream-metainfo',
               meson.current_source_dir(),
               '--appstream-metainfo-output',
               meson.current_build_dir() / metainfo_appdata_xml,
             ],
    install: true,
    install_dir: get_option('datadir') / 'metainfo',
    )

