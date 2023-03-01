// SPDX-FileCopyrightText: 2023 Bill Binder <dxtwjb@gmail.com>
// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include <QObject>
#include <QProcess>

#define SERVICE_NAME "com.wwjjbb.RfKillManager"

class RfKillManager : public QObject
{
    Q_OBJECT

    Q_CLASSINFO("D-Bus Interface", SERVICE_NAME)

  signals:
    /// DBus Signal: Reports changes to the actual state
    Q_SCRIPTABLE void statusChanged(const bool status);
    void requireStatus(bool demanded);

  public slots:
    /// DBus Method: Request switch ON or OFF
    Q_SCRIPTABLE void setStatus(const bool status);
    /// DBus Method: Request actual status
    Q_SCRIPTABLE void requestStatus();
    void setActualState(bool state);

  public:
    RfKillManager(QObject *parent = nullptr);
    virtual ~RfKillManager();
    bool demandedState() const;

  private:
    bool _demandedState;
    bool _actualState;
};
