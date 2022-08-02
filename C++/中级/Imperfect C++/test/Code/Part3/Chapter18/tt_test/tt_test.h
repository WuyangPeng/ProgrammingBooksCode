/* /////////////////////////////////////////////////////////////////////////////
 * File:        tt_test.h
 *
 * Purpose:     Header file for the tt_test project.
 *
 * Created:     28th August 2003
 * Updated:     28th August 2003
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (C) 1999-2003, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              email:      software@synesis.com.au
 *
 *              This source code is placed into the public domain 2003
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


#ifdef __cplusplus

 stlsoft_gen_opaque(GameId_u)
 stlsoft_gen_opaque(GameInstanceId_u)
 typedef stlsoft_ns_qual(true_typedef)<long, GameId_u>          GameId_t;
 typedef stlsoft_ns_qual(true_typedef)<long, GameInstanceId_u>  GameInstanceId_t;
 typedef GameInstanceId_t                                       &REFGIID;

#else /* ? __cplusplus */

 typedef long                                                   GameId_t;
 typedef long                                                   GameInstanceId_t;
 typedef GameInstanceId_t                                       *REFGIID;

#endif /* __cplusplus */

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef __cplusplus
 extern "C" {
#else
#endif /* __cplusplus */

int __stdcall dump_instance(GameId_t gid, GameInstanceId_t giid);

GameInstanceId_t get_active_giid(GameId_t gid, REFGIID rgiid);

#ifdef __cplusplus
 } /* extern "C" */
#endif /* __cplusplus */

/* ////////////////////////////////////////////////////////////////////////// */
