/* /////////////////////////////////////////////////////////////////////////////
 * File:        findfirstfile_sequence_motivation_test.cpp
 *
 * Purpose:     Implementation file for the findfirstfile_sequence_motivation_test project.
 *
 * Created:     18th September 2005
 * Updated:     26th January 2006
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2005-2006, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              This source code is placed into the public domain 2005
 *              by Synesis Software Pty Ltd. There are no restrictions
 *              whatsoever to your use of the software. 
 *
 *              This source code is provided by Synesis Software Pty Ltd "as is"
 *              and any warranties, whether expressed or implied, including, but
 *              not limited to, the implied warranties of merchantability and
 *              fitness for a particular purpose are disclaimed. In no event
 *              shall the Synesis Software Pty Ltd be liable for any direct,
 *              indirect, incidental, special, exemplary, or consequential
 *              damages (including, but not limited to, procurement of
 *              substitute goods or services; loss of use, data, or profits; or
 *              business interruption) however caused and on any theory of
 *              liability, whether in contract, strict liability, or tort
 *              (including negligence or otherwise) arising in any way out of
 *              the use of this software, even if advised of the possibility of
 *              such damage. 
 *
 *              Neither the name of Synesis Software Pty Ltd nor the names of
 *              any subdivisions, employees or agents of Synesis Software Pty
 *              Ltd, nor the names of any other contributors to this software
 *              may be used to endorse or promote products derived from this
 *              software without specific prior written permission. 
 *
 * ////////////////////////////////////////////////////////////////////////// */


/* STLSoft Header Files */
#include <stlsoft/stlsoft.h>

#include <winstl/winstl.h>
#include <winstl/error_desc.hpp>
#include <winstl/findfile_sequence.hpp>

/* Pantheios Header Files */
#include <pantheios/pantheios.hpp>
#include <pantheios/implicit_link/core.h>
#include <pantheios/implicit_link/fe_simple.h>
#include <pantheios/implicit_link/be_Win32Debugger.h>


/* Standard C++ Header Files */
#include <exception>

#if !defined(__WATCOMC__) && \
    (   !defined(_MSC_VER) || \
        _MSC_VER >= 1100)

#else /* ? __WATCOMC__ */
namespace std
{
    using ::exception;
}
#endif /* __WATCOMC__ */


/* Standard C Header Files */
#include <shlobj.h>
#include <stdio.h>
#include <tchar.h>


/* /////////////////////////////////////////////////////////////////////////////
 * Globals and constants
 */

extern "C" const char FE_SIMPLE_PROCESS_IDENTITY[]  = "findfirstfile_sequence_motivation_test";

/* /////////////////////////////////////////////////////////////////////////////
 * Function declarations
 */
#if 0

#if 1
/* 1 */ void ClearDirectory(LPCTSTR lpszDir, LPCTSTR lpszFilePattern)
/* 2 */ {
/* 3 */   TCHAR           szPath[1 + _MAX_PATH];
/* 4 */   TCHAR           szFind[1 + _MAX_PATH];
/* 5 */   WIN32_FIND_DATA find;
/* 6 */   HANDLE          hFind;
/* 7 */   LPTSTR          pszLast;
/* 8 */ 
/* 9 */   pantheios::log_DEBUG( _T("ClearDirectory(\""), lpszDir
/*10 */                       , _T("\", \""), lpszFilePattern, _T("\")"));
/*11 */   ::lstrcpy(szFind, lpszDir);
/*12 */   if( (pszLast = szFind + lstrlen(lpszDir) - 1) != NULL && 
/*13 */       *pszLast != _T('\\'))
/*14 */   {
/*15 */     ::lstrcat(szFind, _T("\\"));
/*16 */   }
/*17 */   ::lstrcat(szFind, lpszFilePattern);
/*18 */   hFind = ::FindFirstFile(szFind, &find);
/*19 */   if(INVALID_HANDLE_VALUE != hFind)
/*20 */   {
/*21 */     do
/*22 */     {
/*23 */       if(find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
/*24 */       {
/*25 */         continue;
/*26 */       }
/*27 */       ::lstrcpy(szPath, lpszDir); 
/*28 */       ::lstrcat(szPath, _T("\\"));
/*29 */       ::lstrcat(szPath, find.cFileName);
/*30 */       if(::DeleteFile(szPath)) 
/*31 */       {
/*32 */         pantheios::log_INFORMATIONAL( _T("Successfully deleted \"")
/*33 */                                     , szPath, _T("\""));
/*34 */         ::SHChangeNotify(SHCNE_DELETE, SHCNF_PATH, szPath, NULL);
/*35 */       }
/*36 */       else
/*37 */       {
/*38 */         pantheios::log_ERROR( _T("Unable to delete \""), szPath
/*39 */                   , _T("\": "), winstl::error_desc(::GetLastError()));
/*40 */       }
/*41 */     }
/*42 */     while(::FindNextFile(hFind,&find));
/*43 */     ::FindClose(hFind);
/*44 */   }
/*45 */ 
/*46 */   ::lstrcpy(szFind, lpszDir);
/*47 */   ::lstrcat(szFind, _T("\\*.*"));
/*48 */   hFind = ::FindFirstFile(szFind, &find);
/*49 */   if(INVALID_HANDLE_VALUE != hFind)
/*50 */   {
/*51 */     do
/*52 */     {
/*53 */       if( (find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
/*54 */           lstrcmp(find.cFileName, _T(".")) &&
/*55 */           lstrcmp(find.cFileName, _T("..")))
/*56 */       {
/*57 */         ::lstrcpy(szPath, lpszDir);
/*58 */         ::lstrcat(szPath, _T("\\"));
/*59 */         ::lstrcat(szPath, find.cFileName);
/*60 */         ClearDirectory(szPath, lpszFilePattern); 
/*61 */       }
/*62 */     }
/*63 */     while(::FindNextFile(hFind, &find));
/*64 */     ::FindClose(hFind);
/*65 */   }
/*66 */ }
#else /* ? 0 */
/* 1 */ void ClearDirectory(LPCTSTR lpszDir, LPCTSTR lpszFilePattern)
/* 2 */ {
/* 3 */   typedef winstl::basic_findfile_sequence<TCHAR>  ffs_t;
/* 4 */ 
/* 5 */   pantheios::log_DEBUG( _T("ClearDirectory(\""), lpszDir
/* 6 */                       , _T("\", \""), lpszFilePattern, _T("\")"));
/* 7 */   ffs_t files(lpszDir, lpszFilePattern, ffs_t::files);
/* 8 */   { for(ffs_t::const_iterator b = files.begin(); b != files.end(); ++b)
/* 9 */   {
/*10 */     if(::DeleteFile(stlsoft::c_str_ptr(*b)))
/*11 */     {
/*12 */       pantheios::log_INFORMATIONAL(_T("Successfully deleted \""), *b, _T("\""));
/*13 */       ::SHChangeNotify(SHCNE_DELETE, SHCNF_PATH, stlsoft::c_str_ptr(*b), NULL); 
/*14 */     }
/*15 */     else
/*16 */     {
/*17 */       pantheios::log_ERROR(_T("Unable to delete \""), *b
/*18 */                             , _T("\": "), winstl::error_desc(::GetLastError()));
/*19 */     }
/*20 */   }}
/*21 */ 
/*22 */   ffs_t directories(lpszDir, _T("*.*"), ffs_t::directories | ffs_t::skipReparseDirs);
/*23 */   { for(ffs_t::const_iterator b = directories.begin(); b != directories.end(); ++b)
/*24 */   {
/*25 */     ClearDirectory(stlsoft::c_str_ptr(*b), lpszFilePattern);
/*26 */   }}
/*27 */ }
#endif /* 0 */

#else /* ? 0 */

#if 0
/* 1 */ void ClearDirectory(LPCTSTR lpszDir, LPCTSTR lpszFilePattern)
/* 2 */ {
/* 3 */   TCHAR           szPath[1 + _MAX_PATH];
/* 4 */   TCHAR           szFind[1 + _MAX_PATH];
/* 5 */   WIN32_FIND_DATA find;
/* 6 */   HANDLE          hFind;
/* 7 */   size_t          cchDir;
/* 8 */   LPTSTR          tokenBuff;
/* 9 */   LPTSTR          token;
/*10 */ 
/*11 */   pantheios::log_DEBUG( _T("ClearDirectory(\""), lpszDir
/*12 */                       , _T("\", \""), lpszFilePattern, _T("\")"));
/*13 */   ::lstrcpy(szFind, lpszDir);
/*14 */   if(szFind[::lstrlen(lpszDir) - 1] != _T('\\'))
/*15 */   {
/*16 */     ::lstrcat(szFind, _T("\\"));
/*17 */   }
/*18 */   cchDir    = ::lstrlen(szFind);
/*19 */   tokenBuff = ::_tcsdup(lpszFilePattern);
/*20 */   if(NULL == tokenBuff)
/*21 */   {
/*22 */     pantheios::log_ERROR(_T("Memory failure\""));
/*23 */     return;
/*24 */   }
/*25 */   else
/*26 */   {
/*27 */     for(token = _tcstok(tokenBuff, ";"); NULL != token; token = _tcstok(NULL, ";"))
/*28 */     {
/*29 */       ::lstrcpy(&szFind[cchDir], token);
/*30 */       hFind = ::FindFirstFile(szFind, &find);
/*31 */       if(INVALID_HANDLE_VALUE != hFind)
/*32 */       {
/*33 */         do
/*34 */         {
/*35 */           if(find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
/*36 */           {
/*37 */             continue;
/*38 */           }
/*39 */           ::lstrcpy(szPath, lpszDir); 
/*40 */           ::lstrcat(szPath, _T("\\"));
/*41 */           ::lstrcat(szPath, find.cFileName);
/*42 */           if(::DeleteFile(szPath)) 
/*43 */           {
/*44 */             pantheios::log_INFORMATIONAL( _T("Successfully deleted \"")
/*45 */                                         , szPath, _T("\""));
/*46 */             ::SHChangeNotify(SHCNE_DELETE, SHCNF_PATH, szPath, NULL);
/*47 */           }
/*48 */           else
/*49 */           {
/*50 */             pantheios::log_ERROR( _T("Unable to delete \""), szPath
/*51 */                       , _T("\": "), winstl::error_desc(::GetLastError()));
/*52 */           }
/*53 */         }
/*54 */         while(::FindNextFile(hFind,&find));
/*55 */         ::FindClose(hFind);
/*56 */       }
/*57 */     }
/*58 */     ::free(tokenBuff);
/*59 */   }
/*60 */ 
/*61 */   ::lstrcpy(szFind, lpszDir);
/*62 */   ::lstrcat(szFind, _T("\\*.*"));
/*63 */   hFind = ::FindFirstFile(szFind, &find);
/*64 */   if(INVALID_HANDLE_VALUE != hFind)
/*65 */   {
/*66 */     do
/*67 */     {
/*68 */       if( (find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
/*69 */           lstrcmp(find.cFileName, _T(".")) &&
/*70 */           lstrcmp(find.cFileName, _T("..")))
/*71 */       {
/*72 */         ::lstrcpy(szPath, lpszDir);
/*73 */         ::lstrcat(szPath, _T("\\"));
/*74 */         ::lstrcat(szPath, find.cFileName);
/*75 */         ClearDirectory(szPath, lpszFilePattern); 
/*76 */       }
/*77 */     }
/*78 */     while(::FindNextFile(hFind, &find));
/*79 */     ::FindClose(hFind);
/*80 */   }
/*81 */ }
#else /* ? 0 */
/* 1 */ void ClearDirectory(LPCTSTR lpszDir, LPCTSTR lpszFilePattern)
/* 2 */ {
/* 3 */   typedef winstl::basic_findfile_sequence<TCHAR>  ffs_t;
/* 4 */ 
/* 5 */   pantheios::log_DEBUG( _T("ClearDirectory(\""), lpszDir
/* 6 */                       , _T("\", \""), lpszFilePattern, _T("\")"));
/* 7 */   ffs_t files(lpszDir, lpszFilePattern, ';', ffs_t::files);
/* 8 */   { for(ffs_t::const_iterator b = files.begin(); b != files.end(); ++b)
/* 9 */   {
/*10 */     if(::DeleteFile(stlsoft::c_str_ptr(*b)))
/*11 */     {
/*12 */       pantheios::log_INFORMATIONAL(_T("Successfully deleted \""), *b, _T("\""));
/*13 */       ::SHChangeNotify(SHCNE_DELETE, SHCNF_PATH, stlsoft::c_str_ptr(*b), NULL); 
/*14 */     }
/*15 */     else
/*16 */     {
/*17 */       pantheios::log_ERROR(_T("Unable to delete \""), *b
/*18 */                             , _T("\": "), winstl::error_desc(::GetLastError()));
/*19 */     }
/*20 */   }}
/*21 */ 
/*22 */   ffs_t directories(lpszDir, _T("*.*"), ffs_t::directories | ffs_t::skipReparseDirs);
/*23 */   { for(ffs_t::const_iterator b = directories.begin(); b != directories.end(); ++b)
/*24 */   {
/*25 */     ClearDirectory(stlsoft::c_str_ptr(*b), lpszFilePattern);
/*26 */   }}
/*27 */ }
#endif /* 0 */

#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	{
		using winstl::findfile_sequence;

#if 0
		findfile_sequence					ffs(_TEXT("*.*"), findfile_sequence::includeDots);
#else /* ? 0 */
		findfile_sequence					ffs(_TEXT(".|*.*|h:/temp"), '|', findfile_sequence::includeDots);
#endif /* 0 */
		findfile_sequence::const_iterator	b	=	ffs.begin();
		findfile_sequence::const_iterator	b2;

		b2	=	b2;
		b	=	b;
		b2	=	b;
		b2	=	b2;
		b	=	b2;

		for(; b != ffs.end(); ++b)
		{
			findfile_sequence::value_type	v	=	*b;

			fprintf(stdout, "filename=%s; path=%s\n", v.get_filename(), v.c_str());
		}

		if(b == ffs.end())
		{
			return 0;
		}
	}

  /* . */
  ClearDirectory(_T("H:\\temp"), _T("*.tds;*.ilk;"));


    return 0;
}

int main(int argc, char *argv[])
{
#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemState    memState;
#endif /* _MSC_VER && _MSC_VER */
	int				iRet;

#if 0
  { for(size_t i = 0; i < 0xffffffff; ++i){} }
#endif /* 0 */

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemCheckpoint(&memState);
#endif /* _MSC_VER && _MSC_VER */

  try
  {
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
    puts("findfirstfile_sequence_motivation_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */


    iRet = main_(argc, argv);
  }
  catch(std::exception &x)
  {
    fprintf(stderr, "Unhandled error: %s\n", x.what());
	iRet = EXIT_FAILURE;
  }
  catch(...)
  {
    fprintf(stderr, "Unhandled unknown error\n");
	iRet = EXIT_FAILURE;
  }

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemDumpAllObjectsSince(&memState);
#endif /* _MSC_VER && _MSC_VER */

  return iRet;
}

/* ////////////////////////////////////////////////////////////////////////// */
