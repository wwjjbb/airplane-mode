/*
    SPDX-FileCopyrightText: 2023 wjb <bill@w-j-b.com>
    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef AIRPLANEMODE_H
#define AIRPLANEMODE_H


#include <Plasma/Applet>
#include <QDBusInterface>
#include "rfkilladaptor.h"

class AirplaneMode : public Plasma::Applet
{
    Q_OBJECT
    Q_PROPERTY(bool airMode READ airMode NOTIFY airModeChanged)

signals:
    void airModeChanged();

public:
    AirplaneMode( QObject *parent, const QVariantList &args );
    ~AirplaneMode();

    bool airMode();

signals:
    void toggleAirMode();

private slots:
    void start();
    void setAirMode(bool newStatus);
    void toggleStatus();

private:
    RfKillManagerAdaptor *_rfkill;
    QDBusInterface *_interface;
    bool _airMode;
    int _counter{0};
};

#endif
