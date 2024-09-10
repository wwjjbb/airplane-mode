// SPDX-FileCopyrightText: 2023 Bill Binder <dxtwjb@gmail.com>
// SPDX-License-Identifier: GPL-2.0-only

#include <QtCore>
#include <csignal>

#include "maintask.h"

int main(int argc, char **argv)
{
    // TODO (LOW) use /etc/conf.d/rfkill to define values which are passed
    // to this process via command switches:
    //   - POLL_INTERVAL=1000
    QCoreApplication a(argc, argv);

    // Exit cleanly if interrupted/terminated
    signal(SIGINT, [](int) { QCoreApplication::exit(0); });
    signal(SIGTERM, [](int) { QCoreApplication::exit(0); });

    MainTask *mt = new MainTask(&a);
    QObject::connect(mt, &MainTask::finished, &a, &QCoreApplication::quit,
                     Qt::QueuedConnection);

    // This gives the event loop a chance to start.
    // TODO (LOW) is there a better way to wait?
    QTimer::singleShot(500, mt, &MainTask::run);

    return a.exec();
}
