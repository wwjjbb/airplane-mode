SPDX-FileCopyrightText: 2023 Bill Binder <dxtwjb@gmail.com>
SPDX-License-Identifier: CC0-1.0

Plasma-AirplaneMode
-------------------

Description
-----------

The plasmoid provides an Airplane Mode switch for the desktop.

The icon shows whether Airplane Mode is ON (transmitters disabled) or OFF
(transmitters enabled).

Clicking on the icon toggles the Airplane Mode switch. All transmitters are
disabled when the switch is ON, and are enabled when the switch is OFF.

When the mouse is moved over the icon, a popup window confirms the current
state of the transmitters.

The Airplane Mode state is saved so that it can be re-applied when the PC is
restarted or woken up after hibernating/sleeping, i.e. if you turn the PC off
with Airplane Mode on, it will start up with Airplane Mode on.

It's intended for PCs without a dedicated hardware RF kill switch, but will
work with a PC that has such a switch. The plasmoid cannot change the state if
the hardware kill switch is on, but it will correctly show the state.

Licenses
--------

The plasmoid/applet is licensed under LGPL-2.1-or-later, because that's how the
initial boilerplate was generated from KAppTemplate. It makes sense because the
applet is a shared library dynamically linked with Qt libraries, using Qt under
the LGPL.

The rfkillmanager_service is licensed under GPL-2.0-only, because it's an
executable application dynamically linked with Qt libraries (under GPL-2.0-only)
and because other Gentoo openrc services appear to be GPL-2.0-only.

The DBus interface files are CC0-1.0 because they are generated. These are the
only link between the applet and the service, so I think thats ok.

The project is compliant with version 3.0 of the REUSE Specification.

How It Works
------------

The /dev/rfkill device file provides the information about whether transmitters
are soft-blocked and/or hard-blocked. The device file also allows transmitters
to be soft-blocked. Transmitters are disabled if they are soft or hard blocked,
and enabled if they are not blocked at all.

The plasmoid is a QML/C++ applet - QML for the visual appearance, and C++ to
manage the communications with the service.

There is a long-running service which regularly monitors the state of the
/dev/rfkill device to determine whether transmitters are disabled or enabled.
The service compares the actual state of the transmitters with the required
state, so that it can switch them on or off, as required. The service notifies
the plasmoid whenever the status changes.

When the plasmoid is clicked, it requests the service to enable or disable the
transmitters. The service changes the soft block state for the rfkill
accordingly, then sends the updated state back to the plasmoid for display. If
the hardware kill switch is on, clicking the plasmoid will have no effect as
software cannot override the hardware selection. The service saves the
requested status in a file (/etc/rfkill) whenever it changes, so that it can
be retrieved when the PC is restarted.

The service is started before bluetooth and network, so that it can retrieve
the required state from /etc/rfkill and set Airplane Mode before any transmissions start.

The service provides a DBus interface which is used by plasmoid applet to
request changes and to be notified of the actual state.

?????
-----

It would probably be worth trying to get the system into a reasonable state
when hardware rfkill has been selected and is then released. As it stands:

  * if the user tried to turn off Airplane Mode via plasmoid, nothing will
    appear to have happened but the request to turn off soft-block will have
    been sent. This will be actioned as soon as hardware kill is released.

  * if the user didn't touch the plasmoid, the system will drop back to
    whatever the soft block state was when the h/w kill was selected.

      * if soft blocked, Airplane Mode will stay selected until turned off via
        the plasmoid.

      * if not soft blocked, Airplane Mode will be off.

This would probably look quite random to the user, who would have to click the
icon again sometimes.

Could set the required Airplane Mode state to OFF as soon as see the hardware
kill applied. This would have no effect on the transmitters until the hardware
kill is released, but would then ensure that soft blocks would come off at the
same time. Think this could be managed by monitoring whether a hard block is
active or not (currently does not distinguish between soft/hard blocks), and
watching for changes. Also might help knowing if hard blocked as would be able
to stop continually changing the soft status)

Build Options
-------------
See meson_options.txt - these default to runtime options, they can be changed

   meson configure -D<option>=<value>

e.g. meson configure -Denable_tracing=true

Building
--------

* Unpack source archive into directory

Command line:

* cd into top level directory
* mkdir ../build
* meson setup ../build .
  * there are two build options which are defaulted to live build values
  * USE_SYSTEM_BUS (defaults to ON)
  * USE_SYSTEM_CONFIG (defaults to ON)

QtCreator:

* Open the top-level meson.build as a project and select the Desktop kit.
* As required using Build menu actions

Generate Source Archive
-----------------------

Commit all changes, then run "meson dist":

  $ cd <top-level build directory>
  $ meson dist

The archive is in the meson-dist/ directory.

Installing
----------

It's a standard meson install, so
  # cd <top-level build directory>
  # meson install --destdir <DESTDIR>

Afterwards:

* take a look at /usr/share/dbus-1/system.d/com.wwjjbb.RfKillManager.conf
  * very little idea what I was doing here, all I know is "it works".
  * whether it's safe???

* add /etc/init.d/rfkillmanager to the default run level

* start /etc/init.d/rfkillmanager
  * this will terminate immediately if /dev/rfkill does not exist, but it would
    be better to check CONFIG_RFKILL is set before installing.

Debugging
---------

Stop any installed copy of the rfkillmanager_service from running first.

Set the meson build options:
  * Set the install prefix to install into user area, bearing in mind the
    plasmoid applet has to go in exactly the right place or it won't work.
    As long as confident that the install locations are correct, it's easiest
    to run "meson install" as root.
  * USE_SYSTEM_BUS -> ON
    * OFF lets you run the service as a user rather than root, which is useful
      for running under debugger.
  * USE_SYSTEM_CONFIG -> ON
    * ON changes the config file to be /etc/rfkill, which is writable
      by root. Otherwise its ~/.config/rfkill for a user.

Setup For Testing
-----------------

The software writes to std::cerr a lot - but this is turned OFF by default for
normal cases, and ON for errors.

* Console A - use for installing the software
  * cd <top-level build directory>
  * as root if using the default install prefix & System Bus, or normal user
    if using local install prefix & User Bus
  * run the "pkill rfkillmanager" command from here if running the rfkillmanager
    in console B
  * run the "meson install" command from here
  * Note: if, as root, you accidentally compile something, the normal user won't
    be able to compile next time. In this case, run
        # chmod <user>:<user> -R ../build
    to assign the build files back to the normal user.

* QtCreator (with this project open) - for edit/build
  * could use the actual debugger with the service & Session bus, if desperate,
    but its just messages passing along so just as easy with trace messages.
  * alternatively, run "meson compile" in the top build directory in yet another
    console window.

* Console B, any directory,
  * login as user account for Session Bus, or as root for System Bus
  * start/stop rfkillmanager_service , or watch it's debug messages
    * can use rc-service if installed in live location
  * can be the dbusservice directory of the build if using Session Bus.
  * to see the debug from the service, run "/usr/sbin/rfkillmanager_service" after
    installing from console A

* Console C, any user directory
  * Run "plasmoidviewer -a com.wwjjbb.plasma.airplanemode"
  * Watch it's debug chatter in the console and interact in the viewer window.
