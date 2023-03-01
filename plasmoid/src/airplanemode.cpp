/*
    SPDX-FileCopyrightText: 2023 wjb <bill@w-j-b.com>
    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "airplanemode.h"
#include "rfkilladaptor.h"
#include <KLocalizedString>
#include <QTimer>

AirplaneMode::AirplaneMode(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args), _airMode(false)
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
        qDebug() << "Error referencing DBus interface: " << error.message();
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

    connect(_rfkill, &RfKillManagerAdaptor::statusChanged, this,
            &AirplaneMode::setAirMode);

    // TODO (LOW) figure out to call a C++ method from QML
    // Until then use a signal!
    connect(this, &AirplaneMode::toggleAirMode, this,
            &AirplaneMode::toggleStatus);

    _rfkill->requestStatus();
}

void AirplaneMode::setAirMode(bool newStatus)
{
    qDebug() << "Received updated status: " << newStatus;
    if (newStatus != _airMode) {
        _airMode = newStatus;
        emit airModeChanged();
    }
}

void AirplaneMode::toggleStatus()
{
    qDebug() << "Requesting status change: " << !_airMode;
    _rfkill->setStatus(!_airMode);
}

K_PLUGIN_CLASS_WITH_JSON(AirplaneMode, "package/metadata.json")

#include "airplanemode.moc"
