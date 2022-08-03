/*	$NetBSD: expand.c,v 1.6 1997/10/18 14:45:57 lukem Exp $	*/

/*
 * Copyright (c) 1980, 1993
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
//#include <sys/cdefs.h>
#ifndef lint
__COPYRIGHT(
    "@(#) Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n");
#endif /* not lint */

#ifndef lint
    #if 0
static char sccsid[] = "@(#)expand.c	8.1 (Berkeley) 6/9/93";
    #endif
__RCSID("$NetBSD: expand.c,v 1.6 1997/10/18 14:45:57 lukem Exp $");
#endif /* not lint */

// 头文件
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>

/*
 * expand - expand tabs to equivalent spaces
 */
// expand - 将制表符扩展到等效空间
// 全局变量
int nstops;
int tabstops[100];

// 函数的前置声明
// static void getstops __P((char*));
// int main __P((int, char**));
// static void usage __P((void));

static void getstops(char*);
static void usage(void);

int main(int argc, char** argv)
// int argc;
// char* argv[];
{
    // main中的局部变量
    int c, column;
    int n;

    /* handle obsolete syntax */
    // 处理过时的语法
    while (argc > 1 && argv[1][0] && isdigit(argv[1][1]))
    {
        getstops(&argv[1][1]);
        argc--;
        argv++;
    }

    // 使用getopt进行参数处理
    while ((c = getopt(argc, argv, "t:")) != -1)
    {
        switch (c)
        {
        case 't':
            // 处理-t选项
            getstops(optarg);
            break;
        case '?':  // 聚合越来的switch标记
        default:
            usage();
            /* NOTREACHED */
        }  // switch块结束
    }
    argc -= optind;
    argv += optind;

    // 至少循环一次
    do
    {
        // 处理其余参数
        if (argc > 0)
        {
            if (freopen(argv[0], "r", stdin) == NULL)
            {
                perror(argv[0]);
                exit(1);
            }
            argc--, argv++;
        }
        column = 0;
        // 读取字符，直到读到EOF
        while ((c = getchar()) != EOF)
        {
            switch (c)
            {
            case '\t':  // 制表符
                if (nstops == 0)
                {
                    do
                    {
                        putchar(' ');
                        column++;
                    } while (column & 07);
                    continue;  // 处理下一个字符
                }
                if (nstops == 1)
                {
                    do
                    {
                        putchar(' ');
                        column++;
                    } while (((column - 1) % tabstops[0]) != (tabstops[0] - 1));
                    continue;
                }
                for (n = 0; n < nstops; n++)
                    if (tabstops[n] > column)
                        break;
                if (n == nstops)
                {
                    putchar(' ');
                    column++;
                    continue;
                }
                while (column < tabstops[n])
                {
                    putchar(' ');
                    column++;
                }
                continue;

            case '\b':  // 退格符
                if (column)
                    column--;
                putchar('\b');
                continue;

            default:  // 所有其他字符
                putchar(c);
                column++;
                continue;

            case '\n':  // 换行符
                putchar(c);
                column = 0;
                continue;
            }  // switch块结束
        }  // while块结束
    } while (argc > 0);  // do块结束
    exit(0);
}

static void getstops(char* cp)  // 剖析制表位说明
// char* cp;
{
    int i;

    nstops = 0;
    for (;;)
    {
        i = 0;
        while (*cp >= '0' && *cp <= '9')  // 将字符串转换为数字
            i = i * 10 + *cp++ - '0';
        if (i <= 0 || i > 256)
        {
bad:
            fprintf(stderr, "Bad tab stop spec\n");  // 抱怨不合理的说明
            exit(1);
        }
        if (nstops > 0 && i <= tabstops[nstops - 1])  // 检验上升的次序
            goto bad;
        tabstops[nstops++] = i;
        if (*cp == 0)  // 跳出循环
            break;
        if (*cp != ',' && *cp != ' ')  // 检验合法的定界符
            goto bad;
        cp++;
    }  // break会将控制权转到此处
}

static void
    usage()  // 打印程序使用说明并退出
{
    (void)fprintf(stderr, "usage: expand [-t tablist] [file ...]\n");
    exit(1);
}
