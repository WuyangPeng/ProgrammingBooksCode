/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Mar 19 18:28:24 2000
 */
/* Compiler settings for C:\Polygon\Polygon.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IPolyCtl = {0x16F763AD,0x9F2E,0x11D3,{0xA7,0xE0,0x00,0x80,0xAE,0x00,0x00,0x01}};


const IID LIBID_POLYGONLib = {0x16F763A1,0x9F2E,0x11D3,{0xA7,0xE0,0x00,0x80,0xAE,0x00,0x00,0x01}};


const IID DIID__IPolyCtlEvents = {0x16F763AF,0x9F2E,0x11D3,{0xA7,0xE0,0x00,0x80,0xAE,0x00,0x00,0x01}};


const CLSID CLSID_PolyCtl = {0x16F763AE,0x9F2E,0x11D3,{0xA7,0xE0,0x00,0x80,0xAE,0x00,0x00,0x01}};


const CLSID CLSID_PolyProp = {0x7846CD41,0x9F37,0x11D3,{0xA7,0xE0,0x00,0x80,0xAE,0x00,0x00,0x01}};


#ifdef __cplusplus
}
#endif

