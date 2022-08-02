// MyServer.h : Declaration of the MyServer

#ifndef __MYSERVER_H_
#define __MYSERVER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// MyServer
class ATL_NO_VTABLE MyServer
    : public IMyServer
    , public CComObjectRootEx<CComSingleThreadModel>
{
public:
    MyServer()
    {}

DECLARE_REGISTRY_RESOURCEID(IDR_MYSERVER)

BEGIN_COM_MAP(MyServer)
    COM_INTERFACE_ENTRY(IMyServer)
END_COM_MAP()

// IMyServer
public:
};

#endif //__MYSERVER_H_
