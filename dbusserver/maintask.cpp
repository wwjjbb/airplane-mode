// SPDX-FileCopyrightText: 2023 Bill Binder <dxtwjb@gmail.com>
// SPDX-License-Identifier: GPL-2.0-only

#include "maintask.h"
#include "devrfkill.h"

#include <QDir>
#include <QFileInfo>
#include <QJsonDocument>
#include <QProcess>
#include <iostream>

MainTask::MainTask(QObject *parent)
    : QObject(parent), _counter(0), _demandedStatus(false), _actualStatus(false)
{
    _stateSettings =
        new QSettings(StateSettingsFile, QSettings::NativeFormat, this);
    _rfkill = new RfKillManager(this);
    _app = dynamic_cast<QCoreApplication *>(parent);
}

MainTask::~MainTask()
{
    // The objects are parented by this object so are cleaned up automatically
    // qDebug() << "Goodbye!";
}

void MainTask::run()
{
    // Fail if no rfkill device
    if (!DevRfKill::exists()) {
        std::cerr << "Failed : Device not present \"" << DevRfKill::deviceName
                  << "\" (missing CONFIG_RFKILL?)" << std::endl;

        // Exit with error code for "file not found"
        _app->exit(ENOENT);
    }

    bool oksetdem = connect(_rfkill, &RfKillManager::requireStatus, this,
            &MainTask::setDemanded);
    if (!oksetdem) {
        std::cerr << "MainTask::run() failed to connect MainTask::setDemanded" << std::endl;
    }
    bool oksetactual = connect(this, &MainTask::actualStateChange, _rfkill,
            &RfKillManager::setActualState);
    if (!oksetactual) {
        std::cerr << "MainTask::run() failed to connect RfKillManager::setActualState" << std::endl;
    }

    _demandedStatus = _stateSettings->value(BlockStatusSetting, false).toBool();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainTask::tick);
    _counter = 0;
    timer->start(1000);
}

void MainTask::tick()
{
    _counter++;
    if (_counter >= 1000)
        _counter = 0;

    if (_demandedStatus != _actualStatus) {
        DevRfKill::blockAll(_demandedStatus);
    }
    checkStatus();
}

void MainTask::checkStatus()
{
    int status = DevRfKill::isBlocked();
    if (status < 0) {
        std::cerr << "Failed to determine rfkill state, assume not blocked" << std::endl;
        status = 0;
    }

    // TODO (LOW) log the change to system log when this changes state?
    // If so, do it where the value gets filtered

    _actualStatus = (status == 1);

    // TODO (LOW) do not emit actualStateChanged unless an actual change
    // It does get filtered before it goes to dbus, so low priority
#ifdef TRACE
    std::cerr << "MainTask::checkStatus() sending actualStatus -> " << _actualStatus << std::endl;
#endif
    emit actualStateChange(_actualStatus);
}

void MainTask::setDemanded(bool demanded)
{
#ifdef TRACE
    std::cerr << "MainTask::setDemanded() -> " << demanded << std::endl;
#endif
    if (demanded != _demandedStatus) {
#ifdef TRACE
        std::cerr << "MainTask::setDemanded() - this is a change" << std::endl;
#endif

        _demandedStatus = demanded;

        _stateSettings->setValue(BlockStatusSetting, _demandedStatus);
    }
}
