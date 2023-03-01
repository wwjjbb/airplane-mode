// SPDX-FileCopyrightText: 2023 Bill Binder <dxtwjb@gmail.com>
// SPDX-License-Identifier: GPL-2.0-only

#include <QProcess>
#include <iostream>

#include "rfkilladaptor.h"
#include "rfkillmanager.h"

///
/// \brief RfKillManager::setStatus
///
/// This sets the required rfkill status.
/// Whenever the value is changed, calls "rfkill" to attempt to set the required
/// status value. Afterwards, this should trigger a status read.
///
/// \param status
///
void RfKillManager::setStatus(const bool status)
{
    _demandedState = status;

    emit requireStatus(_demandedState);
}

RfKillManager::RfKillManager(QObject *parent) : QObject(parent)
{
    new RfKillManagerAdaptor(this);

#ifdef USE_SYSTEM_BUS
    QDBusConnection dbus = QDBusConnection::systemBus();
    qDebug() << "System Bus";
#else
    QDBusConnection dbus = QDBusConnection::sessionBus();
    qDebug() << "Session Bus";
#endif
    if (!dbus.registerService(SERVICE_NAME)) {
        qDebug() << "Failed to register service: " << SERVICE_NAME;
    }
    dbus.registerObject("/", this);
}

RfKillManager::~RfKillManager()
{
}

bool RfKillManager::demandedState() const
{
    return _demandedState;
}

///
/// \brief RfKillManager::requestStatus
///
/// Ask for a statusChange message
///
void RfKillManager::requestStatus()
{
    qDebug() << "RfKillManager::requestStatus (dbus) -> " << _actualState;

    emit statusChanged(_actualState);
}

void RfKillManager::setActualState(bool state)
{
    if (_actualState != state) {
        // TODO (LOW) probably log the state change here
        qDebug() << "RfKillManager::statusChanged - notify actual state has "
                    "changed to "
                 << state;
        _actualState = state;
        emit statusChanged(_actualState);
    }
}

#include "moc_rfkillmanager.cpp"
