/*TITLE "who's afraid" assert header file*/

/****keyword-flag*** "%v %f %n" */
/* "1 7-May-96,0:15:00 WASSERT.H" */

/****revision-history****/
/*1 WASSERT.H 7-May-96,0:15:00 Working version.                               */
/****revision-history****/

#ifndef WASSERT_H
#define WASSERT_H

#ifndef NODEBUG
#define wassert(p) ((p) ? (void)0 : (void) WAssertFail( \
  "Assertion failed: %s, file %s, line %d\n", \
   #p, __FILE__, __LINE__ ) )
#define Vecassert(i,c) ((i<c) ? (void)0 : (void) VecAssertFail(\
  "You have tried to use element %d of a Vec which has only %d elements.\n",\
  i,c) )
#else
#define wassert(p)
#define Vecassert(i,c)
#endif

int WAssertFail(char* p_FormatString, char* p_Message,
    char* p_FileName, unsigned p_LineNumber);

int VecAssertFail(char* p_FormatString, unsigned p_Index, unsigned p_Count);
#endif
