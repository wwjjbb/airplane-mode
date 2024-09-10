/*
    SPDX-FileCopyrightText: 2023 wjb <bill@w-j-b.com>
    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "airplanemode.h"
#include "rfkilladaptor.h"

#include <KLocalizedString>
#include <QDBusInterface>
#include <QTimer>
#include <iostream>

AirplaneMode::AirplaneMode(QObject *parent, const KPluginMetaData &data,
                           const QVariantList &args)
    : Plasma::Applet(parent, data, args), _airMode(false)
{
    _interface = new QDBusInterface("com.wwjjbb.RfKillManager", "/", "",
#ifdef USE_SYSTEM_BUS
                                    QDBusConnection::systemBus(),
#else
                                    QDBusConnection::sessionBus(),
#endif
                                    this);
    if (!_interface->isValid()) {
        QDBusError error = _interface->lastError();
        std::cerr << "Error referencing DBus interface: " << error.message().toStdString() << std::endl;
    }

    // The adaptor needs to be attached to an interface object,
    // i.e. NOT TO THIS CLASS!!!
    _rfkill = new RfKillManagerAdaptor(_interface);

    // Defer initialisation till after constructor completes
    QTimer::singleShot(100, this, &AirplaneMode::start);
}

AirplaneMode::~AirplaneMode()
{
    delete _rfkill;
}

bool AirplaneMode::airMode()
{
    return _airMode;
}

void AirplaneMode::start()
{

    bool okset = connect(_rfkill, &RfKillManagerAdaptor::statusChanged, this,
            &AirplaneMode::setAirMode);
    if (!okset) {
        std::cerr << "AirplaneMode::start() failed to connect AirplaneMode::setAirMode" << std::endl;
    }

    // TODO (LOW) figure out to call a C++ method from QML
    // Until then use a signal!
    bool oktoggle = connect(this, &AirplaneMode::toggleAirMode, this,
            &AirplaneMode::toggleStatus);
    if (!oktoggle) {
        std::cerr << "AirplaneMode::start() failed to connect AirplaneMode::toggleStatus" << std::endl;
    }

    _rfkill->requestStatus();
}

void AirplaneMode::setAirMode(bool newStatus)
{
#ifdef TRACE
    std::cerr << "Received updated status: -> " << newStatus << std::endl;
#endif
    if (newStatus != _airMode) {
        _airMode = newStatus;
#ifdef TRACE
        std::cerr << "Sending 'airModeChanged'" << std::endl;
#endif
        emit airModeChanged();
    }
}

void AirplaneMode::toggleStatus()
{
#ifdef TRACE
    std::cerr << "Requesting status change: -> " << !_airMode << std::endl;
#endif
    _rfkill->setStatus(!_airMode);
}

K_PLUGIN_CLASS_WITH_JSON(AirplaneMode, "package/metadata.json")

#include "airplanemode.moc"
