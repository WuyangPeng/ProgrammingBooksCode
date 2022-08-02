A		[a-z_A-Z]
M		[a-z_A-Z0-9]
	int skipping;
%%
"/*"			{skipping = 1;}
"*/"			{skipping = 0;}
"%"			{extern	int	brkcount;
			 if (! skipping)
				if (++brkcount == 2)
					return 0; /* end-of-file */
				else
					return DEFBRK;
			}
":"			{if (! skipping) return COLON;}
[1-9][0-9]*		{if (! skipping) return INTEGER;}
0[0-7]*			{if (! skipping) return INTEGER;}
0x[0-9A-Fa-f]+		{if (! skipping) return INTEGER;}
is			{if (! skipping) return IS;}
on			{if (! skipping) return ON;}
"="			;
-?iint			{if (! skipping) return IINT;}
-?oint			{if (! skipping) return OINT;}
-?csr			{if (! skipping) return CSR;}
-?ivec			{if (! skipping) return IVEC;}
-?irq			{if (! skipping) return IRQ;}
-?ovec			{if (! skipping) return OVEC;}
-?i			{if (! skipping) return INIT;}
-?o			{if (! skipping) return OPEN;}
-?c			{if (! skipping) return CLOSE;}
-?r			{if (! skipping) return READ;}
-?g			{if (! skipping) return GETC;}
-?p			{if (! skipping) return PUTC;}
-?w			{if (! skipping) return WRITE;}
-?s			{if (! skipping) return SEEK;}
-?n			{if (! skipping) return CNTL;}
[ \t]+			;
"\n"			{extern int linectr;
			 linectr++;
			}
{A}{M}*			{if (! skipping) return IDENT;}
.			{if (! skipping) return yytext[0];}
