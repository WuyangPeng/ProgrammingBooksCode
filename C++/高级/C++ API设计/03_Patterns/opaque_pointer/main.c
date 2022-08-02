/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
/**
 * \file   main.c
 * \author Martin Reddy
 * \brief  An opaque pointer example in plain C.
 *
 * Copyright (c) 2010, Martin Reddy. All rights reserved.
 * Distributed under the X11/MIT License. See LICENSE.txt.
 * See http://APIBook.com/ for the latest
 */

#include "autotimer.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    printf("%d,%s", argc, argv[0]);
    printf("\n");

    // create a new auto timer
    AutoTimerPtr timer = AutoTimerCreate("MyTimer");
    int i;

    for (i = 0; i < 1000; ++i)
    {
        printf(".");
    }
    printf("\n");

    // destroy the auto timer - will output its time alive
    // 销毁自动计时器_——将输出存活的时间
    AutoTimerDestroy(timer);

    return 0;
}
