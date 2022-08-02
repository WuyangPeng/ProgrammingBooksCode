/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Tue Jan 14 17:25:25 2003
 */
/* Compiler settings for atl_bolt_in.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __atl_bolt_in_h__
#define __atl_bolt_in_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMyServer_FWD_DEFINED__
#define __IMyServer_FWD_DEFINED__
typedef interface IMyServer IMyServer;
#endif  /* __IMyServer_FWD_DEFINED__ */


#ifndef __MyServer_FWD_DEFINED__
#define __MyServer_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyServer MyServer;
#else
typedef struct MyServer MyServer;
#endif /* __cplusplus */

#endif  /* __MyServer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IMyServer_INTERFACE_DEFINED__
#define __IMyServer_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMyServer
 * at Tue Jan 14 17:25:25 2003
 * using MIDL 3.01.75
 ****************************************/
/* [object][unique][helpstring][uuid] */ 



EXTERN_C const IID IID_IMyServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("83382C08-6CD0-43F3-8AD4-BE2F02893F4A")
    IMyServer : public IUnknown
    {
    public:
    };
    
#else   /* C style interface */

    typedef struct IMyServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMyServer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMyServer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMyServer __RPC_FAR * This);
        
        END_INTERFACE
    } IMyServerVtbl;

    interface IMyServer
    {
        CONST_VTBL struct IMyServerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyServer_QueryInterface(This,riid,ppvObject)   \
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyServer_AddRef(This)  \
    (This)->lpVtbl -> AddRef(This)

#define IMyServer_Release(This) \
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif  /* C style interface */




#endif  /* __IMyServer_INTERFACE_DEFINED__ */



#ifndef __ATL_BOLT_INLib_LIBRARY_DEFINED__
#define __ATL_BOLT_INLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: ATL_BOLT_INLib
 * at Tue Jan 14 17:25:25 2003
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_ATL_BOLT_INLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_MyServer;

class DECLSPEC_UUID("E6E002E2-0284-49D8-A555-FBEB9E389A6A")
MyServer;
#endif
#endif /* __ATL_BOLT_INLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
