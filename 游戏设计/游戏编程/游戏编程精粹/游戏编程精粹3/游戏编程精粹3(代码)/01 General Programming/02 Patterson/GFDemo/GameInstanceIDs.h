/* Copyright (C) Scott Patterson, 2002. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Scott Patterson, 2002"
 */


// InstanceIDs.h

#ifndef INSTANCEIDS_H
#define INSTANCEIDS_H

// AVLayer IDs
enum {
	INSTANCE_ID_AVLAYER_INTRO,
	INSTANCE_ID_AVLAYER_STARTMENU,
	INSTANCE_ID_AVLAYER_GAMECONFIG,
	INSTANCE_ID_AVLAYER_GAME,
	INSTANCE_ID_AVLAYER_GAMEHUD,
	INSTANCE_ID_AVLAYER_GAMEPAUSE,
	INSTANCE_ID_AVLAYER_SYSTEMCONFIG,
	INSTANCE_ID_AVLAYER_GAMEWIN,
	INSTANCE_ID_AVLAYER_GAMELOSE,
	INSTANCE_ID_AVLAYER_GAMEVIEWER,
	INSTANCE_ID_AVLAYER_GAMEEDITOR,
	INSTANCE_ID_AVLAYER_COUNT
};

// LogicLayer IDs
enum {
	INSTANCE_ID_LOGICLAYER_INTRO,
	INSTANCE_ID_LOGICLAYER_STARTMENU,
	INSTANCE_ID_LOGICLAYER_GAMECONFIG,
	INSTANCE_ID_LOGICLAYER_GAME,
	INSTANCE_ID_LOGICLAYER_GAMEPAUSE,
	INSTANCE_ID_LOGICLAYER_SYSTEMCONFIG,
	INSTANCE_ID_LOGICLAYER_GAMEWIN,
	INSTANCE_ID_LOGICLAYER_GAMELOSE,
	INSTANCE_ID_LOGICLAYER_GAMEVIEWER,
	INSTANCE_ID_LOGICLAYER_GAMEEDITOR,
	INSTANCE_ID_LOGICLAYER_COUNT
};

// Task IDs
enum {
	INSTANCE_ID_TASK_START_APP,
	INSTANCE_ID_TASK_CHANGE_DRIVER,
	INSTANCE_ID_TASK_INTRO,
	INSTANCE_ID_TASK_GAME,
	INSTANCE_ID_TASK_GAMECONFIG,
	INSTANCE_ID_TASK_SYSTEMCONFIG,
	INSTANCE_ID_TASK_COUNT
};

#endif