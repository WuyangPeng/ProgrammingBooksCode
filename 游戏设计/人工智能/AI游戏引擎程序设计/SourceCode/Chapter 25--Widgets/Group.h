#pragma once
#include "Widgets/Common.h"
#include "Widgets/EventHandler.h"
#include "Widgets/ScrubberWidget.h"
// forward declarations
class OnOffButton;
class BasicButton;
class Widget;
class WidgetBank;
class RadioButton;

/********************************************************************
*	Group:		A Group represents an entry in the widget bank, and 
*				can house other groups or widgets. It contains a 
*				header which can be expanded/contracted to show/hide 
*				its child groups or child widgets, which are added with
*				subsequent calls to AddScrubber, AddOnOff, etc.
*
********************************************************************/
class Group : public CWnd {
public:
	// constructors
	Group( char * label, CWnd * pWin, const int level );
	virtual ~Group();

	// member methods
	virtual void Update();
	void OnClickHeader();
	
	bool IsExpanded(){ return m_status; }
	int GetHeight();
	int GetClientHeight();
	//int GetPrevPos(){ return m_prevPos; }
	//void SetPrevPos( int prevPos ){ m_prevPos = prevPos; }
	void SetWidgetBank( WidgetBank * wb ){ m_widgetBank = wb; }
	
	Group * AddGroup( char * label );

	ScrubberWidget<int> * AddScrubber( char * name, int & val ); 
	ScrubberWidget<float> * AddScrubber( char * name, float & val );
	ScrubberWidget<unsigned char> * AddScrubber( char * name, unsigned char & val );

	OnOffButton * AddOnOff(	char * name, bool & a, int ID1 = 0, EventHandler * h = 0 );
	
	void AddWatcher( char * caption, float & val );
	void AddWatcher( char * caption, int & val );

	void AddText( char * caption );
	RadioButton * AddRadio( char * groupName, char * leftName, char * rightName, 
		int & val, int id1 = 0, int id2 = 0, EventHandler * h = 0 );
	BasicButton * AddBasicButton(	char * filename, int id, EventHandler * h = NULL );

	int Draw( int y_pos );

	// MFC Overrides
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNcDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	// member variables
private:
	Group * m_childGroups[ MAX_CHILD_GROUPS ];
	Widget * m_childWidgets[ MAX_CHILD_WIDGETS ];
	WidgetBank * m_widgetBank;		// a pointer to the parent widget bank

	CButton m_header;
	COLORREF m_color;				// the color of this widget
	int m_top;						// position of the top of this widget in widget bank
	bool m_status;					// is this widget currently expanded?
	unsigned int m_numChildGroups;	// number of subgroups contained in this group
	unsigned int m_numChildWidgets;	// number of child widgets in this group
	int m_level;					// how many levels deep is this nested?
};