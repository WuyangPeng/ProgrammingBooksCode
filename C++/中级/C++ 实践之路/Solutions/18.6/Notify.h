#if !defined (NOTIFY_H)
#define NOTIFY_H
// Bartosz Milewski (c) 2000
#include <cstddef>
#include <windows.h>

const UINT UM_MEMCLEAR = WM_USER;

class NotificationSink
{
public:
	virtual void AddItem (std::size_t id) = 0;
	virtual void UpdateItem (std::size_t id) = 0;
};

#endif
