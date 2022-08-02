#ifdef _AFXDLL
#define BEGIN_MESSAGE_MAP_FOR_TEMPLATE(theTemplate, theClass, baseClass) \
	template <class theTemplate> \
	const AFX_MSGMAP* PASCAL theClass::GetThisMessageMap() \
		{ \
		return &theClass::messageMap; \
	} \
	template <class theTemplate> \
	const AFX_MSGMAP* theClass::GetMessageMap() const \
	{ \
		return &theClass::messageMap; \
	} \
	template <class theTemplate> \
	AFX_COMDAT const AFX_MSGMAP theClass::messageMap = \
	{ \
		&baseClass::GetThisMessageMap, &theClass::_messageEntries[0] \
	}; \
	template <class theTemplate> \
	AFX_COMDAT const AFX_MSGMAP_ENTRY theClass::_messageEntries[] = \
	{ \

#else
	#define BEGIN_MESSAGE_MAP_FOR_TEMPLATE(theTemplate, theClass, baseClass) \
		template <class theTemplate> \
		const AFX_MSGMAP* theClass::GetMessageMap() const \
		{ \
			return &theClass::messageMap; \
		} \
		template <class theTemplate> \
		AFX_COMDAT const AFX_MSGMAP theClass::messageMap = \
		{ \
			&baseClass::messageMap, &theClass::_messageEntries[0] \
		}; \
		template <class theTemplate> \
		AFX_COMDAT const AFX_MSGMAP_ENTRY theClass::_messageEntries[] = \
		{ \

#endif