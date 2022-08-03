/*	$NetBSD: echo.c,v 1.7 1997/07/20 06:07:03 thorpej Exp $	*/

// 注释（版权信息和分发许可），编译器会忽略这些信息。本书大部分程序都会包含这样的许可信息，以后将不再显示。
/*
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "echo.h"

// #include <sys/cdefs.h>
// 版权信息和程序版本标识符，它们将会以字符串的形式出现在可执行程序中。
#ifndef lint
__COPYRIGHT(
    "@(#) Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n");
#endif /* not lint */

#ifndef lint
    #if 0
static char sccsid[] = "@(#)echo.c	8.1 (Berkeley) 5/31/93";
    #else
__RCSID("$NetBSD: echo.c,v 1.7 1997/07/20 06:07:03 thorpej Exp $");
    #endif
#endif /* not lint */

// 标准库头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 在函数声明中使用宏是为了向pre-ANSI编译器隐藏参数
// int main __P((int, char*[]));

int main(int argc, char** argv)  // 函数从这个函数开始执行
// int argc; 程序参数的个数
// char* argv[]; 实参（从程序名开始，以NULL结束）
{
    // 当其为true时，输出不会以换行符结束
    int nflag;

    /* This utility may NOT do getopt(3) option parsing. */
    // 此实用程序可能不会对getopt(3)选项解析。
    if (*++argv && !strcmp(*argv, "-n"))  // 第一个参数是-n
    {
        ++argv;
        nflag = 1;  // 跳过该参数并设置nflag
    }
    else
        nflag = 0;

    while (*argv)  // 有参数要处理
    {
        (void)printf("%s", *argv);  // 打印该参数
        if (*++argv)  // 下面还有参数么？（增加argv）
            putchar(' ');  // 打印分隔空格
    }
    if (!nflag)  // 除非指定了-n，否则用换行符结束输出。
        putchar('\n');
    exit(0);  // 退出程序，指示成功。
}
