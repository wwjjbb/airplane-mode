// SPDX-FileCopyrightText: 2023 Bill Binder <dxtwjb@gmail.com>
// SPDX-License-Identifier: GPL-2.0-only

#include "rfkillmanager.h"

#include "rfkilladaptor.h"

#include <QDBusConnection>
#include <QObject>
#include <QProcess>
#include <iostream>

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
#ifdef TRACE
    std::cerr << "RfKillManager::setStatus: " << status << " (was " << _demandedState << ")" << std::endl;
#endif
    _demandedState = status;

    emit requireStatus(_demandedState);
}

RfKillManager::RfKillManager(QObject *parent) : QObject(parent)
{
    // Don't need to keep a reference because the instance is
    // attached to this object, and owned by it.
    new RfKillManagerAdaptor(this);

#ifdef USE_SYSTEM_BUS
    QDBusConnection dbus = QDBusConnection::systemBus();
#ifdef TRACE
    std::cerr << "RfKillManager(): using System Bus" << std::endl;
#endif
#else
    QDBusConnection dbus = QDBusConnection::sessionBus();
    std::cerr << "RfKillManager(): using Session Bus" << std::endl;
#endif
    if (!dbus.registerService(SERVICE_NAME)) {
        std::cerr << "RfKillManager(): failed to register service: " << SERVICE_NAME << std::endl;
    } else {
#ifdef TRACE
        std::cerr << "RfKillManager(): registered service: " << SERVICE_NAME << std::endl;
#endif
    }
    dbus.registerObject("/", this);
}

RfKillManager::~RfKillManager()
{
}

bool RfKillManager::demandedState() const
{
#ifdef TRACE
    std::cerr << "RfKillManager::demandedState() -> " << _demandedState << std::endl;
#endif
    return _demandedState;
}

///
/// \brief RfKillManager::requestStatus
///
/// Ask for a statusChange message
///
void RfKillManager::requestStatus()
{
#ifdef TRACE
    std::cerr << "RfKillManager::requestStatus (dbus) -> " << _actualState << std::endl;
#endif

    emit statusChanged(_actualState);
}

void RfKillManager::setActualState(bool state)
{
    if (_actualState != state) {
        // TODO (LOW) probably log the state change here
#ifdef TRACE
        std::cerr << "RfKillManager::setActualState - notify actual state has "
                    "changed to "
                 << state << std::endl;
#endif
        _actualState = state;
        emit statusChanged(_actualState);
    }
}
