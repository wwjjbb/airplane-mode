// SPDX-FileCopyrightText: 2023 Bill Binder <dxtwjb@gmail.com>
// SPDX-License-Identifier: GPL-2.0-only
#pragma once

#include <linux/rfkill.h>
#include <unistd.h>

class DevRfKill
{
  public:
    static bool exists();
    static int blockAll(bool block);
    static int isBlocked();

    static constexpr const char *deviceName = "/dev/rfkill";

  private:
    DevRfKill();

    static int openDevice(int readonly, int nonblocking);
    static int writeEvent(int fd, rfkill_event *event);
    static int readEvent(int fd, rfkill_event *event);
};
