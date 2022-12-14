#ifndef __MESSAGEENUMS_H
#define __MESSAGEENUMS_H

enum EMessageType
{
	MT_UPDATE,
	MT_OBJECT_CREATED,
	MT_ALL_OBJECTS_CREATED,
	MT_COMMAND,
	MT_LOOK,
	MT_DESCRIBE_OBJECT,
	MT_DESCRIBE_CHARACTER,
	MT_USE,
	MT_EXAMINE,
	MT_EXAMINE_INVENTORY,
	MT_SET_INVENTORY_ITEM_POS,
	MT_BE_PICKED_UP,
	MT_PICK_UP,
	MT_PICK_UP_SUCCESSFUL,
	MT_HIDE,
	MT_SHOW,
	MT_EVENT,
	MT_TELL_ROOM,
	NUM_MESSAGE_TYPES
};

enum EMessageResult
{
	MR_FALSE,
	MR_TRUE,
	MR_IGNORED,
	MR_ERROR
};

#endif //__MESSAGEENUMS_H