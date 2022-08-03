/*	$NetBSD: echo.c,v 1.7 1997/07/20 06:07:03 thorpej Exp $	*/

// ע�ͣ���Ȩ��Ϣ�ͷַ���ɣ����������������Щ��Ϣ������󲿷ֳ��򶼻���������������Ϣ���Ժ󽫲�����ʾ��
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
// ��Ȩ��Ϣ�ͳ���汾��ʶ�������ǽ������ַ�������ʽ�����ڿ�ִ�г����С�
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

// ��׼��ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �ں���������ʹ�ú���Ϊ����pre-ANSI���������ز���
// int main __P((int, char*[]));

int main(int argc, char** argv)  // ���������������ʼִ��
// int argc; ��������ĸ���
// char* argv[]; ʵ�Σ��ӳ�������ʼ����NULL������
{
    // ����Ϊtrueʱ����������Ի��з�����
    int nflag;

    /* This utility may NOT do getopt(3) option parsing. */
    // ��ʵ�ó�����ܲ����getopt(3)ѡ�������
    if (*++argv && !strcmp(*argv, "-n"))  // ��һ��������-n
    {
        ++argv;
        nflag = 1;  // �����ò���������nflag
    }
    else
        nflag = 0;

    while (*argv)  // �в���Ҫ����
    {
        (void)printf("%s", *argv);  // ��ӡ�ò���
        if (*++argv)  // ���滹�в���ô��������argv��
            putchar(' ');  // ��ӡ�ָ��ո�
    }
    if (!nflag)  // ����ָ����-n�������û��з����������
        putchar('\n');
    exit(0);  // �˳�����ָʾ�ɹ���
}
