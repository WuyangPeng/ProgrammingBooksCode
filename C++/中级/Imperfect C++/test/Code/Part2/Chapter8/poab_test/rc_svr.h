/* /////////////////////////////////////////////////////////////////////////////
 * File:        rc_svr.h
 *
 * Purpose:     Portable (POAB) Ref-counted Interface Test
 *
 * Created:     6th December 2003       
 * Updated:     4th March 2004
 *
 * Copyright:   Synesis Software Pty Ltd, (c) 2003. All rights reserved.
 *
 * Home:        www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////////// */


#include <MIRefCnt.h>

#include <SWrn001u.h>

__SYNSOFT_GEN_USING(::SynesisStd::IRefCounter)

/*
// interface IThing
 */
struct IThing;
struct IThingVTable
{
    /* IRefCounter */
    void    (__SYNSOFT_MOD_CALLCONV_VDECL *AddRef)(struct IThing *obj);
    void    (__SYNSOFT_MOD_CALLCONV_VDECL *Release)(struct IThing *obj);
    /* IThing */
    char const *(__SYNSOFT_MOD_CALLCONV_VDECL *GetBuildCompiler)(struct IThing const *obj);
    char const *(__SYNSOFT_MOD_CALLCONV_VDECL *GetClientCompiler)(struct IThing const *obj);
};
struct IThing
#ifdef __cplusplus
    : public IRefCounter
#endif /* __cplusplus */
{
#ifndef __cplusplus
    struct IThingVTable *const      vtable;
#else /* ? !__cplusplus */
public:
    typedef IThing                  Interface;
protected:
    typedef struct IThingVTable     vtable_t;

    vtable_t *get_vtable_()
    {
        return (vtable_t*)IRefCounter::get_vtable_();
    }
    vtable_t const *get_vtable_() const
    {
        return (vtable_t*)IRefCounter::get_vtable_();
    }

protected:
    IThing(struct IThingVTable *vt)
        : IRefCounter((IRefCounter::vtable_t*)vt)
    {}
    ~IThing()
    {}
public:
    /* IRefCounter */
    inline void __SYNSOFT_MOD_CALLCONV_VDECL AddRef()
    {
        SyAssert(NULL != get_vtable_());
        get_vtable_()->AddRef(this);
    }
    inline void __SYNSOFT_MOD_CALLCONV_VDECL Release()
    {
        SyAssert(NULL != get_vtable_());
        get_vtable_()->Release(this);
    }
    /* IThing */
    inline char const *__SYNSOFT_MOD_CALLCONV_VDECL GetBuildCompiler() const
    {
        SyAssert(NULL != get_vtable_());
        return get_vtable_()->GetBuildCompiler(this);
    }
    inline char const *__SYNSOFT_MOD_CALLCONV_VDECL GetClientCompiler() const
    {
        SyAssert(NULL != get_vtable_());
        return get_vtable_()->GetClientCompiler(this);
    }

private:
    IThing(IThing const &rhs);
    IThing &operator =(IThing const &rhs);
#endif /* __cplusplus */
};

#ifdef __cplusplus
# ifdef POAB_COMPILER_HAS_COMPATIBLE_VTABLES
typedef IThing  IThing_;
# else /* ? POAB_COMPILER_HAS_COMPATIBLE_VTABLES */
struct IThing_
    : public IThing
{
public:
    typedef IThing_             class_type;
private:
    typedef IThing::vtable_t    vtable_t;

public:
    IThing_()
        : IThing(GetVTable())
    {}
    IThing_(class_type const &/* rhs */)
        : IThing(GetVTable())
    {}
    IThing_ &operator =(class_type const &/* rhs */)
    {
        return *this;
    }

// IThing
public:
    virtual void        __SYNSOFT_MOD_CALLCONV_VDECL AddRef() = 0;
    virtual void        __SYNSOFT_MOD_CALLCONV_VDECL Release() = 0;
    virtual char const  *__SYNSOFT_MOD_CALLCONV_VDECL GetBuildCompiler() const = 0;
    virtual char const  *__SYNSOFT_MOD_CALLCONV_VDECL GetClientCompiler() const = 0;

private:
    static void __SYNSOFT_MOD_CALLCONV_VDECL AddRef_(IThing *this_)
    {
        static_cast<class_type*>(this_)->AddRef();
    }
    static void __SYNSOFT_MOD_CALLCONV_VDECL Release_(IThing *this_)
    {
        static_cast<class_type*>(this_)->Release();
    }
    static char const *__SYNSOFT_MOD_CALLCONV_VDECL GetBuildCompiler_(IThing const *this_)
    {
        return static_cast<class_type const*>(this_)->GetBuildCompiler();
    }
    static char const *__SYNSOFT_MOD_CALLCONV_VDECL GetClientCompiler_(IThing const *this_)
    {
        return static_cast<class_type const*>(this_)->GetClientCompiler();
    }

    static vtable_t MakeVTable()
    {
        vtable_t vt = { AddRef_, Release_, GetBuildCompiler_, GetClientCompiler_ };

        return vt;
    }
    static vtable_t *const GetVTable()
    {
        static vtable_t s_vt = MakeVTable();

        return &s_vt;
    }
};
# endif /* !POAB_COMPILER_HAS_COMPATIBLE_VTABLES */
#endif /* __cplusplus */

#include <SWrn001o.h>

