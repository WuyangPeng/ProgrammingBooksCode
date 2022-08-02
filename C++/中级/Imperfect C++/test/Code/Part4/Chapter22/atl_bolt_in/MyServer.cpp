// MyServer.cpp : Implementation of MyServer
#include "stdafx.h"
#include "atl_bolt_in.h"
#include "MyServer.h"

/////////////////////////////////////////////////////////////////////////////
// MyServer

void fn()
{
    new MyServer;
    new CComObject<MyServer>;

    MyServer                    ms;
    CComObjectStack<MyServer>   so;
}
