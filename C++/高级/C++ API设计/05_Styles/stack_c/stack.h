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
// ָ��stack���ݽṹ�Ĳ�͸��ָ��
typedef struct Stack* StackPtr;

/* Create a new stack data structure */
// ����һ���µ�stack���ݽṹ
StackPtr StackCreate();
/* Destroy an existing stack data structure */
// �������е�stack���ݽṹ
void StackDestroy(StackPtr stack);

/* Push a new value onto the stack */
// ����ֵѹ��stack
void StackPush(StackPtr stack, int val);
/* Pop the last value from the stack */
// ��stack�е������һ��ֵ
int StackPop(StackPtr stack);
/* Return 1 if the stack contains no values */
// ���stack�������κ�ֵ���򷵻�1
int StackIsEmpty(const StackPtr stack);

#endif
