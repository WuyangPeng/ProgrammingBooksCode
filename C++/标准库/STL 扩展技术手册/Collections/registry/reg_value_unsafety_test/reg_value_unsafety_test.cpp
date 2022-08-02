/* /////////////////////////////////////////////////////////////////////////////
 * File:        reg_value_unsafety_test.cpp
 *
 * Purpose:     Implementation file for the reg_value_unsafety_test project.
 *
 * Created:     9th January 2006
 * Updated:     12th February 2006
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2006, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              This source code is placed into the public domain 2006
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
#include <winstl/registry/reg_key.hpp>
#include <winstl/registry/reg_key_sequence.hpp>
#include <winstl/registry/reg_value.hpp>
#include <winstl/registry/reg_value_sequence.hpp>

#include <MWRegFns.h>

/* Standard C++ Header Files */
#include <exception>
#if 0
#include <algorithm>
#include <iterator>
#include <list>
#include <string>
#include <vector>
#endif /* 0 */

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
#include <stdio.h>
#include <stdlib.h>

#if defined(_MSC_VER) && \
    defined(_DEBUG)
# include <crtdbg.h>
#endif /* _MSC_VER) && _DEBUG */

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

#if 0
typedef std::string     string_t;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

static void usage(int bExit, char const *reason, int iInvalidArg, int argc, char **argv);
static void recreate_test_keys();

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int argc, char *argv[])
{
    int                 iRet        =   EXIT_SUCCESS;
    int                 bVerbose    =   true;

    { for(int i = 1; i < argc; ++i)
    {
        const char  *const  arg =   argv[i];

        if(arg[0] == '-')
        {
            if(arg[1] == '-')
            {
                /* -- arguments */
                usage(1, "Invalid argument(s) specified", i, argc, argv);
            }
            else
            {
                /* - arguments */
                switch(arg[1])
                {
                    case    '?':
                        usage(1, NULL, -1, argc, argv);
                        break;
                    case    's':
                        bVerbose    =   false;
                        break;
                    case    'v':
                        bVerbose    =   true;
                        break;
                    default:
                        usage(1, "Invalid argument(s) specified", i, argc, argv);
                        break;
                }
            }
        }
        else
        {
            /* other arguments */
            usage(1, "Invalid argument(s) specified", i, argc, argv);
        }
    }}

    /* . */
    {
        recreate_test_keys();

        winstl::reg_key     key(HKEY_CURRENT_USER, "SOFTWARE\\XSTL");
        winstl::reg_key     subKey  =   key.open_sub_key("Vol1\\test\\EII\\Registry");

        {
            printf("\nUnprotected enumeration (long-hand)\n");

            HKEY                        key     =   subKey.get_key_handle();
            DWORD                       index   =   0;
            stlsoft::auto_buffer<char>  buff(4);

            for(;; )
            {
                DWORD n   = buff.size();
                LONG  res = ::RegEnumKeyEx(key, index, &buff[0], &n, NULL, NULL, NULL, NULL);

                if(ERROR_MORE_DATA == res)
                {
                    buff.resize(2 * buff.size());
                }
                else if(ERROR_SUCCESS == res)
                {
                    printf( "subkey[%u] name=%.*s\n", index
                        ,   static_cast<int>(buff.size()), buff.data());
                    ++index;
                }
                else if(ERROR_NO_MORE_ITEMS == res)
                {
                    break; // No more data
                }
                else
                {
                    return EXIT_FAILURE; // Report error and stop further processing
                }
            }
        }

        {
            printf("\nProtected enumeration (long-hand)\n");

            HKEY                        key     =   subKey.get_key_handle();
            DWORD                       index   =   0;
            stlsoft::auto_buffer<char>  buff(4);
            winstl::event               hev(true, false);

            ::RegNotifyChangeKeyValue(  key
                                    ,   true
                                    ,   REG_NOTIFY_CHANGE_NAME /* | REG_NOTIFY_CHANGE_LAST_SET */
                                    ,   hev.get()
                                    ,   true);

            for(;; )
            {
                DWORD n   = buff.size();
                LONG  res = ::RegEnumKeyEx(key, index, &buff[0], &n, NULL, NULL, NULL, NULL);

                if(ERROR_MORE_DATA == res)
                {
                    buff.resize(2 * buff.size());
                }
                else if(ERROR_SUCCESS == res)
                {
                    printf( "subkey[%u] name=%.*s\n", index
                        ,   static_cast<int>(buff.size()), buff.data());
                    ++index;
                }
                else if(ERROR_NO_MORE_ITEMS == res)
                {
                    break; // No more data
                }
                else
                {
                    return EXIT_FAILURE; // Report error and stop further processing
                }

                if(WAIT_OBJECT_0 == ::WaitForSingleObject(hev.handle(), 0))
                {
                    printf("External interruption!\n");
#if 0
                    break;
#else /* ? 0 */
					hev.reset();
            ::RegNotifyChangeKeyValue(  key
                                    ,   true
                                    ,   REG_NOTIFY_CHANGE_NAME /* | REG_NOTIFY_CHANGE_LAST_SET */
                                    ,   hev.get()
                                    ,   true);
#endif /* 0 */
                }
            }
        }


        {
#if 0
            winstl::reg_value_sequence  values(subKey);

            { for(winstl::reg_value_sequence::const_iterator b = values.begin(); b != values.end(); ++b)
            {
                fprintf(stdout, "%s=%s\n", (*b).name().c_str(), (*b).value_sz().c_str());
            }}

            { for(winstl::reg_value_sequence::const_reverse_iterator b = values.rbegin(); b != values.rend(); ++b)
            {
                fprintf(stdout, "%s=%s\n", (*b).name().c_str(), (*b).value_sz().c_str());
            }}
#else /* ? 0 */
            winstl::reg_key_sequence    keys(subKey);

            { for(winstl::reg_key_sequence::const_iterator b = keys.begin(); b != keys.end(); ++b)
            {
                fprintf(stdout, "%s\n", (*b).name().c_str());
            }}
#endif /* 0 */
        }

//      subkey.create_value
    }

    return iRet;
}

int main(int argc, char *argv[])
{
    int             iRet;

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemState    memState;
#endif /* _MSC_VER && _MSC_VER */

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemCheckpoint(&memState);
#endif /* _MSC_VER && _MSC_VER */

#if 0
    { for(size_t i = 0; i < 0xffffffff; ++i){} }
#endif /* 0 */

    try
    {
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
        puts("reg_value_unsafety_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

        SynesisWin::Reg_Init();

        iRet = main_(argc, argv);

        SynesisWin::Reg_Uninit();
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
#endif /* _MSC_VER) && _DEBUG */

    return iRet;
}

/* ////////////////////////////////////////////////////////////////////////// */

static void usage(int bExit, char const *reason, int iInvalidArg, int argc, char **argv)
{

    fprintf(stderr, "\n");
    fprintf(stderr, "  reg_value_unsafety_test\n\n");
    fprintf(stderr, "\n");

    if(NULL != reason)
    {
        fprintf(stderr, "  Error: %s\n", reason);
        fprintf(stderr, "\n");
    }

#if 0
    fprintf(stderr, "  USAGE: reg_value_unsafety_test [{-w | -p<root-paths> | -h}] [-u] [-d] [{-v | -s}] <search-spec>\n");
    fprintf(stderr, "    where:\n\n");
    fprintf(stderr, "    -w             - searches from the current working directory. The default\n");
    fprintf(stderr, "    -p<root-paths> - searches from the given root path(s), separated by \';\',\n");
    fprintf(stderr, "                     eg.\n");
    fprintf(stderr, "                       -p\"c:\\windows;x:\\bin\"\n");
    fprintf(stderr, "    -r             - deletes readonly files\n");
    fprintf(stderr, "    -h             - searches from the roots of all drives on the system\n");
    fprintf(stderr, "    -d             - displays the path(s) searched\n");
    fprintf(stderr, "    -u             - do not act recursively\n");
    fprintf(stderr, "    -v             - verbose output. Prints time, attributes, size and path. (default)\n");
    fprintf(stderr, "    -s             - succinct output. Prints path only\n");
    fprintf(stderr, "    <search-spec>  - one or more file search specifications, separated by \';\',\n");
    fprintf(stderr, "                     eg.\n");
    fprintf(stderr, "                       \"*.exe\"\n");
    fprintf(stderr, "                       \"myfile.ext\"\n");
    fprintf(stderr, "                       \"*.exe;*.dll\"\n");
    fprintf(stderr, "                       \"*.xl?;report.*\"\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "  Contact %s\n", _nameSynesisSoftware);
    fprintf(stderr, "    at \"%s\",\n", _wwwSynesisSoftware_SystemTools);
    fprintf(stderr, "    or, via email, at \"%s\"\n", _emailSynesisSoftware_SystemTools);
    fprintf(stderr, "\n");
#endif /* 0 */

    if(bExit)
    {
        exit(EXIT_FAILURE);
    }
}

/* ////////////////////////////////////////////////////////////////////////// */

static void recreate_test_keys()
{
    winstl::reg_key SOFTWARE(HKEY_CURRENT_USER, "Software");
    winstl::reg_key EII         =   SOFTWARE.create_sub_key("XSTL\\Vol1\\test\\EII");

    // Clear out all things in "Registry" by deleting it.

    SynesisWin::Reg_DeleteKey(EII.get(), "Registry", true);

    // Create the key and its sub-keys

    winstl::reg_key Registry    =   EII.create_sub_key("Registry");

    Registry.create_sub_key("Key#1");
    Registry.create_sub_key("Key#2");
    Registry.create_sub_key("Key#3");
    Registry.create_sub_key("Key#4");
    Registry.create_sub_key("Key#5");
}

/* ////////////////////////////////////////////////////////////////////////// */
