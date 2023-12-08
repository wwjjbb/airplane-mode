/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp com.wwjjbb.RfKillManager.xml -a rfkilladaptor
 *
 * qdbusxml2cpp is Copyright (C) 2022 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "rfkilladaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class RfKillManagerAdaptor
 */

RfKillManagerAdaptor::RfKillManagerAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

RfKillManagerAdaptor::~RfKillManagerAdaptor()
{
    // destructor
}

void RfKillManagerAdaptor::requestStatus()
{
    // handle method call com.wwjjbb.RfKillManager.requestStatus
    QMetaObject::invokeMethod(parent(), "requestStatus");
}

void RfKillManagerAdaptor::setStatus(bool status)
{
    // handle method call com.wwjjbb.RfKillManager.setStatus
    QMetaObject::invokeMethod(parent(), "setStatus", Q_ARG(bool, status));
}

