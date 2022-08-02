
atl_bolt_inps.dll: dlldata.obj atl_bolt_in_p.obj atl_bolt_in_i.obj
	link /dll /out:atl_bolt_inps.dll /def:atl_bolt_inps.def /entry:DllMain dlldata.obj atl_bolt_in_p.obj atl_bolt_in_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del atl_bolt_inps.dll
	@del atl_bolt_inps.lib
	@del atl_bolt_inps.exp
	@del dlldata.obj
	@del atl_bolt_in_p.obj
	@del atl_bolt_in_i.obj
