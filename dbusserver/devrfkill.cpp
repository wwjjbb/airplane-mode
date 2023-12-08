// SPDX-FileCopyrightText: 2023 Bill Binder <dxtwjb@gmail.com>
// SPDX-License-Identifier: GPL-2.0-only

#include "devrfkill.h"

#include <cstdint>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <linux/rfkill.h>
#include <unistd.h>

DevRfKill::DevRfKill()
{
}

// Checks whether the rfkill device exists
// If not, none of the other methods will work
// (Existence of /dev/rfkill is a kernel config option)
bool DevRfKill::exists()
{
    return access(deviceName, F_OK) == 0;
}

// Soft blocks or unblocks all devices
// Returns:
//  0 : ok
// <0 : failed
//
int DevRfKill::blockAll(bool block)
{
    rfkill_event event = {.idx = 0,
                          .type = 0,
                          .op = RFKILL_OP_CHANGE_ALL,
                          .soft = __u8(block ? 1 : 0),
                          .hard = __u8(0)};

    int result = 0;
    // Open device file for write in blocking mode
    int fd = openDevice(0, 0);
    if (fd < 0)
        result = fd;
    else {
        result = writeEvent(fd, &event);
        close(fd);
    }

    return result;
}

// 1 if all devices are blocked (hard or soft)
// 0 otherise (i.e something is not blocked)
// <0 error (treat as NOT blocked)
int DevRfKill::isBlocked()
{
    rfkill_event event;
    int result = 1;

    // Open device file for read in non-blocking mode
    int fd = openDevice(1, 1);
    if (fd < 0) {
        return fd;
    }

    while (true) {
        int rstate = readEvent(fd, &event);
        if (rstate < 0) {
            result = -1;
            break;
        } else if (rstate == 1) {
            break;
        } else if (event.soft == 0 && event.hard == 0) {
            result = 0; // A device is unblocked
        }
    }

    close(fd);
    return result;
}

// Open the device file
// Returns:
//  0+ : valid file descriptor (file is open)
// <0  : failed, (value is the -ve error code, file is not open)
int DevRfKill::openDevice(int readonly, int nonblocking)
{
    int fd;

    fd = open(deviceName, readonly ? O_RDONLY : O_RDWR);
    if (fd < 0) {
        return -errno;
    } else if (nonblocking && fcntl(fd, F_SETFL, O_NONBLOCK) < 0) {
        close(fd);
        return -errno;
    }
    return fd;
}

// Writes an event to the given file descriptor
// Return:
//    0 : written ok
//   <0 : error
int DevRfKill::writeEvent(int fd, rfkill_event *event)
{
    size_t count = sizeof(*event);
    const uint8_t *buffer = (const uint8_t *)event;
    int retries = 5;
    while (count) {
        ssize_t written;

        errno = 0;
        written = write(fd, buffer, count);
        if (written > 0) {
            count -= written;
            if (count) {
                buffer += written;
            }
        } else if (errno != EINTR && errno != EAGAIN) {
            // Ignore these error codes, but finish when any other
            return -1;
        }

        if (retries-- < 0) {
            std::cerr << "DevRfKill::writeEvent - stuck" << std::endl;
            return -1;
        }

        if (count) {
            // Block for 50ms before trying again
            usleep(50000);
        }
    }
    return 0;
}

// Reads an event to the given file descriptor
// Returns:
//    1 = reached end of data
//    0 = got an event
//   <0 = error
int DevRfKill::readEvent(int fd, rfkill_event *event)
{
    char *buffer = (char *)event;
    size_t reqd = sizeof(*event);

    int retries = 5;
    while (reqd > 0) {
        ssize_t len = read(fd, buffer, reqd);
        if (len > 0) {
            reqd -= len;
            if (reqd) {
                buffer = buffer + len;
                usleep(50000);
            } else {
                return 0;
            }
        } else if (len < 0) {
            if (errno != EINTR && errno != EAGAIN) {
                return -1;
            } else if (reqd == sizeof(*event) && errno == EAGAIN) {
                return 1;
            }
        }

        if (retries-- < 0) {
            std::cerr << "DevRfKill::readEvent - stuck" << std::endl;
            return -1;
        }
    }
    return 0;
}
