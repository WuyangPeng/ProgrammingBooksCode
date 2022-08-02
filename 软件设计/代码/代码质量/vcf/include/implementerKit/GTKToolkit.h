/**
*Copyright (c) 2000-2001, Jim Crafton
*All rights reserved.
*Redistribution and use in source and binary forms, with or without
*modification, are permitted provided that the following conditions
*are met:
*	Redistributions of source code must retain the above copyright
*	notice, this list of conditions and the following disclaimer.
*
*	Redistributions in binary form must reproduce the above copyright
*	notice, this list of conditions and the following disclaimer in 
*	the documentation and/or other materials provided with the distribution.
*
*THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
*AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS
*OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
*PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
*PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
*LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
*NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
*SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*NB: This software will not save the world.
*/

#ifndef _GTKTOOLKIT_H__
#define _GTKTOOLKIT_H__


#include "GTKPeer.h"
#include "UIToolkit.h"
#include <map>

namespace VCF {

class Color;

class GTKToolkit {

public:
	GTKToolkit();

	virtual ~GTKToolkit();

	virtual Color* getSystemColor( const unsigned long& systemColor );
	
	virtual ApplicationPeer* createApplicationPeer();
	
	virtual TextPeer* createTextPeer( TextControl* component, ComponentType componentType=CT_DEFAULT);

	virtual TreePeer* createTreePeer( TreeControl* component, ComponentType componentType=CT_DEFAULT);

	virtual ListBoxPeer* createListboxPeer( ListBoxControl* component, ComponentType componentType=CT_DEFAULT);

	virtual ListviewPeer* createListViewPeer( ListViewControl* component, ComponentType componentType=CT_DEFAULT);

	virtual DialogPeer* createDialogPeer( Frame* owner, Dialog* component, ComponentType componentType=CT_DEFAULT );

	virtual DialogPeer* createDialogPeer();
	
	virtual MenuItemPeer* createMenuItemPeer( MenuItem* item );

	virtual MenuBarPeer* createMenuBarPeer( MenuBar* menuBar );

	virtual PopupMenuPeer* createPopupMenuPeer( PopupMenu* popupMenu );

	virtual ComboBoxPeer* createComboBoxPeer( ComboBoxControl* component, ComponentType componentType=CT_DEFAULT);

	virtual ButtonPeer* createButtonPeer( CommandButton* component, ComponentType componentType);

	virtual ContextPeer* createContextPeer( Control* component );

	virtual CommonFileDialogPeer* createCommonFileOpenDialogPeer( Control* owner );

	virtual CommonFileDialogPeer* createCommonFileSaveDialogPeer( Control* owner );

	virtual CommonColorDialogPeer* createCommonColorDialogPeer( Control* owner );

	virtual CommonFolderBrowseDialogPeer* createCommonFolderBrowseDialogPeer( Control* owner );

	virtual CommonFontDialogPeer* createCommonFontDialogPeer( Control* owner );

	virtual DragDropPeer* createDragDropPeer(); 

	virtual DataObjectPeer* createDataObjectPeer();

	virtual DropTargetPeer* createDropTargetPeer();

private:
	void loadSystemColors();
	std::map<unsigned long,Color*> m_systemColors;

};

}; //end of namespace VCF

#endif //_GTKTOOLKIT_H__