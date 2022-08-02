 /* 'mrTemplateSet.cpp' */

 /* Complement header file */
#include "mrTemplateSet.h"

 /* Default constructor */
mrTemplateSet::mrTemplateSet (void)
{
 m_pkTexture       = NULL;
 m_iTextureWidth   = 0;
 m_iTextureHeight  = 0;
 m_iCellWidth      = 0;
 m_iCellHeight     = 0;
}

 /* Default destructor */
mrTemplateSet::~mrTemplateSet (void)
{
 m_iTextureWidth   = 0;
 m_iTextureHeight  = 0;
 m_iCellWidth      = 0;
 m_iCellHeight     = 0;
 m_pkTexture       = NULL;
}

 /* Create the template set */
void mrTemplateSet::Create (mrTexture * pkTexture, 
                            mrUInt32 iTextureWidth, 
                            mrUInt32 iTextureHeight, 
                            mrUInt32 iCellWidth, 
                            mrUInt32 iCellHeight)
{
 m_iTextureWidth  = iTextureWidth;
 m_iTextureHeight = iTextureHeight;
 m_iCellWidth     = iCellWidth;
 m_iCellHeight    = iCellHeight;

 m_pkTexture      = pkTexture;
}

 /* Returns the texture UV rect for a given cell */
void mrTemplateSet::GetUV (mrCellID kPosition, mrRectText * pkUVRect)
{
 pkUVRect->m_fLeft   = (mrReal32)(1 + ((1 + m_iCellWidth) 
	 * kPosition.m_iX)) / m_iTextureWidth;
 pkUVRect->m_fRight  = (mrReal32)(1 + ((1 + m_iCellWidth) 
	 * kPosition.m_iX) + m_iCellWidth) / m_iTextureWidth;
 pkUVRect->m_fTop    = (mrReal32)(1 + ((1 + m_iCellHeight) 
	 * kPosition.m_iY)) / m_iTextureHeight;
 pkUVRect->m_fBottom = (mrReal32)(1 + ((1 + m_iCellHeight) 
	 * kPosition.m_iY) + m_iCellHeight) / m_iTextureHeight;
}

 /* Set as active texture */
void mrTemplateSet::SetActiveTexture (void)
{
 m_pkTexture->SetActiveTexture ();
}

 /* Returns texture width */
mrUInt32 mrTemplateSet::GetTextureWidth (void)
{
 return m_iTextureWidth;
}

 /* Returns texture height */
mrUInt32 mrTemplateSet::GetTextureHeight (void)
{
 return m_iTextureHeight;
}

 /* Returns cell width */
mrUInt32 mrTemplateSet::GetCellWidth (void)
{
 return m_iCellWidth;
}

 /* Returns cell height */
mrUInt32 mrTemplateSet::GetCellHeight (void)
{
 return m_iCellHeight;
}
