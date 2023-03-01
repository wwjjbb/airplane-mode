// SPDX-FileCopyrightText: 2023 Bill Binder <dxtwjb@gmail.com>
// SPDX-License-Identifier: GPL-2.0-only

#include <iostream>

#include "devrfkill.h"

int main(int, char **)
{
    bool ok = DevRfKill::exists();
    std::cout << "DevRfKill::.exists(): " << ok << std::endl;

    int blocked = DevRfKill::isBlocked();
    std::cout << "DevRfKill::isBlocked(): " << blocked << std::endl;

    std::cout << std::endl;

    bool reqd = blocked ? false : true;

    int status = DevRfKill::blockAll(reqd);
    std::cout << "DevRfKill::blockAll(" << reqd << "): " << status << std::endl;
    blocked = DevRfKill::isBlocked();
    std::cout << "DevRfKill::isBlocked(): " << blocked << std::endl;

    std::cout << std::endl;

    status = DevRfKill::blockAll(!reqd);
    std::cout << "DevRfKill::blockAll(" << !reqd << "): " << status
              << std::endl;
    blocked = DevRfKill::isBlocked();
    std::cout << "DevRfKill::isBlocked(): " << blocked << std::endl;

    return 0;
}
