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

// ͷ�ļ�
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>

/*
 * expand - expand tabs to equivalent spaces
 */
// expand - ���Ʊ����չ����Ч�ռ�
// ȫ�ֱ���
int nstops;
int tabstops[100];

// ������ǰ������
// static void getstops __P((char*));
// int main __P((int, char**));
// static void usage __P((void));

static void getstops(char*);
static void usage(void);

int main(int argc, char** argv)
// int argc;
// char* argv[];
{
    // main�еľֲ�����
    int c, column;
    int n;

    /* handle obsolete syntax */
    // �����ʱ���﷨
    while (argc > 1 && argv[1][0] && isdigit(argv[1][1]))
    {
        getstops(&argv[1][1]);
        argc--;
        argv++;
    }

    // ʹ��getopt���в�������
    while ((c = getopt(argc, argv, "t:")) != -1)
    {
        switch (c)
        {
        case 't':
            // ����-tѡ��
            getstops(optarg);
            break;
        case '?':  // �ۺ�Խ����switch���
        default:
            usage();
            /* NOTREACHED */
        }  // switch�����
    }
    argc -= optind;
    argv += optind;

    // ����ѭ��һ��
    do
    {
        // �����������
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
        // ��ȡ�ַ���ֱ������EOF
        while ((c = getchar()) != EOF)
        {
            switch (c)
            {
            case '\t':  // �Ʊ��
                if (nstops == 0)
                {
                    do
                    {
                        putchar(' ');
                        column++;
                    } while (column & 07);
                    continue;  // ������һ���ַ�
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

            case '\b':  // �˸��
                if (column)
                    column--;
                putchar('\b');
                continue;

            default:  // ���������ַ�
                putchar(c);
                column++;
                continue;

            case '\n':  // ���з�
                putchar(c);
                column = 0;
                continue;
            }  // switch�����
        }  // while�����
    } while (argc > 0);  // do�����
    exit(0);
}

static void getstops(char* cp)  // �����Ʊ�λ˵��
// char* cp;
{
    int i;

    nstops = 0;
    for (;;)
    {
        i = 0;
        while (*cp >= '0' && *cp <= '9')  // ���ַ���ת��Ϊ����
            i = i * 10 + *cp++ - '0';
        if (i <= 0 || i > 256)
        {
bad:
            fprintf(stderr, "Bad tab stop spec\n");  // ��Թ�������˵��
            exit(1);
        }
        if (nstops > 0 && i <= tabstops[nstops - 1])  // ���������Ĵ���
            goto bad;
        tabstops[nstops++] = i;
        if (*cp == 0)  // ����ѭ��
            break;
        if (*cp != ',' && *cp != ' ')  // ����Ϸ��Ķ����
            goto bad;
        cp++;
    }  // break�Ὣ����Ȩת���˴�
}

static void
    usage()  // ��ӡ����ʹ��˵�����˳�
{
    (void)fprintf(stderr, "usage: expand [-t tablist] [file ...]\n");
    exit(1);
}
