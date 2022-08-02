#ifndef _MESSAGEMAPSFORTEMPLATES_
#define _MESSAGEMAPSFORTEMPLATES_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _AFXDLL
#define DECLARE_MESSAGE_MAP_FOR_TEMPLATE() \
private: \
 static /*const*/ AFX_MSGMAP_ENTRY _messageEntries[]; \

protected: \
 static AFX_DATA /*const*/ AFX_MSGMAP messageMap; \
 static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
 virtual const AFX_MSGMAP* GetMessageMap() const; \

#else
#define DECLARE_MESSAGE_MAP_FOR_TEMPLATE() \
private: \
 static /*const*/ AFX_MSGMAP_ENTRY _messageEntries[]; \
protected: \
 static AFX_DATA /*const*/ AFX_MSGMAP messageMap; \
 virtual const AFX_MSGMAP* GetMessageMap() const; \

#endif

#ifdef _AFXDLL
#define BEGIN_MESSAGE_MAP_FOR_TEMPLATE(theClass, baseClass) \
 template <class baseClass> const AFX_MSGMAP* PASCAL theClass::_GetBaseMessageMap() \
  { return &baseClass::messageMap; } \
 template <class baseClass> const AFX_MSGMAP* theClass::GetMessageMap() const \
  { return &theClass::messageMap; } \
 template <class baseClass> AFX_COMDAT AFX_DATADEF /*const*/ AFX_MSGMAP theClass::messageMap = \
  { &theClass::_GetBaseMessageMap, &theClass::_messageEntries[0] }; \
 template <class baseClass> AFX_COMDAT /*const*/ AFX_MSGMAP_ENTRY theClass::_messageEntries[] = \
  { \

#else
#define BEGIN_MESSAGE_MAP_FOR_TEMPLATE(theClass, baseClass) \
 template <class baseClass> const AFX_MSGMAP* theClass::GetMessageMap() const \
  { return &theClass::messageMap; } \
 template <class baseClass> AFX_COMDAT AFX_DATADEF /*const*/ AFX_MSGMAP theClass::messageMap = \
  { &baseClass::messageMap, &theClass::_messageEntries[0] }; \
 template <class baseClass> AFX_COMDAT /*const*/ AFX_MSGMAP_ENTRY theClass::_messageEntries[] = \
  { \

#endif
#define END_MESSAGE_MAP_FOR_TEMPLATE() END_MESSAGE_MAP()

#endif 
