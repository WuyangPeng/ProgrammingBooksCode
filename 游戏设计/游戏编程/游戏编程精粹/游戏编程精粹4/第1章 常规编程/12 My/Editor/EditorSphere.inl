//--------------------------------------------------------------------------------------------------------------------//
//                                                EDITOR SPHERE CLASS                                                 //
// written by Frederic My                                                                                             //
// fmy@fairyengine.com                                                                                                //
//--------------------------------------------------------------------------------------------------------------------//

#ifndef   _GPG4_EDITORSPHERE_INL_
#define   _GPG4_EDITORSPHERE_INL_

//----------------------------------------------- INCLUDES -----------------------------------------------------------//

#include  "ImgMenu.h"

namespace GPG4
{

//--------------------------------------------------------------------------------------------------------------------//
//                                                CONSTRUCTORS / DESTRUCTOR                                           //
//--------------------------------------------------------------------------------------------------------------------//

INLINE CEditorSphere::CEditorSphere()
  {}

INLINE CEditorSphere::~CEditorSphere()
  {}

//--------------------------------------------------------------------------------------------------------------------//
//                                                GET/SET                                                             //
//--------------------------------------------------------------------------------------------------------------------//

INLINE CStdString CEditorSphere::GetDefaultName() const
  {
  return "sphere";
  }

INLINE u32 CEditorSphere::GetIcon() const
  {
  return CImgMenu::GetImgID("_IMG_SPHERE_");
  }

INLINE u32 CEditorSphere::GetMenu() const
  {
  return CImgMenu::GetMenuID("_MENU_SPHERE_");
  }

//--------------------------------------------------------------------------------------------------------------------//

} // namespace

#endif // _GPG4_EDITORSPHERE_INL_
