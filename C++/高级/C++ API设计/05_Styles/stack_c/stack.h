/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
/**
 * \file   stack.h
 * \author Martin Reddy
 * \brief  An example of a plain C style API.
 *
 * Copyright (c) 2010, Martin Reddy. All rights reserved.
 * Distributed under the X11/MIT License. See LICENSE.txt.
 * See http://APIBook.com/ for the latest
 */

#ifndef STACK_H
#define STACK_H

/* An opaque pointer to a stack data structure */
// 指向stack数据结构的不透明指针
typedef struct Stack* StackPtr;

/* Create a new stack data structure */
// 创建一个新的stack数据结构
StackPtr StackCreate();
/* Destroy an existing stack data structure */
// 销毁现有的stack数据结构
void StackDestroy(StackPtr stack);

/* Push a new value onto the stack */
// 将新值压入stack
void StackPush(StackPtr stack, int val);
/* Pop the last value from the stack */
// 从stack中弹出最后一个值
int StackPop(StackPtr stack);
/* Return 1 if the stack contains no values */
// 如果stack不包含任何值，则返回1
int StackIsEmpty(const StackPtr stack);

#endif
