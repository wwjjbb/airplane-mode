// SPDX-FileCopyrightText: 2023 Bill Binder <dxtwjb@gmail.com>
// SPDX-License-Identifier: GPL-2.0-only
#pragma once

#include <QFileInfo>
#include <QProcess>
#include <QSettings>
#include <QtCore>

#include "rfkillmanager.h"

class MainTask : public QObject
{
    Q_OBJECT

  public:
    MainTask(QObject *parent = 0);
    virtual ~MainTask();

  public slots:
    void run();
    void tick();

  signals:
    void finished();
    void actualStateChange(bool state);

  private slots:
    void setDemanded(bool demanded);

  private:
    void checkStatus();
#ifdef USE_SYSTEM_CONFIG
    const QString StateSettingsFile{"/etc/rfkill"};
#else
    const QString StateSettingsFile{"~/.config/rfkill"};
#endif
    const QString BlockStatusSetting{"block"};

    QSettings *_stateSettings = nullptr;
    RfKillManager *_rfkill = nullptr;
    QCoreApplication *_app = nullptr;

    int _counter;
    bool _demandedStatus;
    bool _actualStatus;
};
