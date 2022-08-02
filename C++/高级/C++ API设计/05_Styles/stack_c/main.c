/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
/**
 * \file   main.c
 * \author Martin Reddy
 * \brief  An example of a plain C syle API.
 *
 * Copyright (c) 2010, Martin Reddy. All rights reserved.
 * Distributed under the X11/MIT License. See LICENSE.txt.
 * See http://APIBook.com/ for the latest
 */

#include "stack.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    printf("%d,%s", argc, argv[0]);
    printf("\n");

    /* Create a new stack */
    // 创建一个新的stack
    StackPtr stack = StackCreate();
    int val;

    /* push and pop a value to the stack */
    // 推送并弹出一个值到stack
    printf("Empty: %d\n", StackIsEmpty(stack));
    StackPush(stack, 10);
    printf("Empty: %d\n", StackIsEmpty(stack));
    val = StackPop(stack);
    printf("Popped off: %d\n", val);
    printf("Empty: %d\n", StackIsEmpty(stack));

    /* clean up the stack */
    // 清理stack
    StackDestroy(stack);
    return 0;
}
