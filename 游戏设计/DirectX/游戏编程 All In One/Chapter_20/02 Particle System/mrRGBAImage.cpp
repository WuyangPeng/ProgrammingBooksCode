 /* 'mrRGBAImage.cpp' */

 /* Complement header file */
#include "mrRGBAImage.h"

 /* Default constructor */
mrRGBAImage::mrRGBAImage (void)
{
 m_iWidth        = 0;
 m_iHeight       = 0;
 m_piImageBuffer = NULL;
}

 /* Default destructor */
mrRGBAImage::~mrRGBAImage (void)
{
 m_iWidth        = 0;
 m_iHeight       = 0;

  /* If memory was allocated, release it */
 if (NULL != m_piImageBuffer)
 {
  delete [] m_piImageBuffer;
  m_piImageBuffer = NULL;
 }
}

 /* Copy this image to another */
mrRGBAImage & mrRGBAImage::operator = (mrRGBAImage & rkImage)
{
 m_iWidth  = rkImage.GetWidth ();
 m_iHeight = rkImage.GetHeight ();
 SetImageBuffer (rkImage.GetImageBuffer ());

  /* Return an instance of this class */
 return * this;
}

 /* Load image from a windows bitmap file */
mrError32 mrRGBAImage::LoadFromBitmap (LPSTR lpszFilename)
{
 fstream      kBitmap;

 kBitmap.open (lpszFilename, ios::binary | ios::in);

	if (kBitmap.is_open ())
	{
		mrUInt16     iType;
		kBitmap.read ((char *) &iType, sizeof (mrUInt16));

			/* Get bitmap signature */
		if (0x4D42 != iType)
		{
			return mrErrorNotBitmapFile;
		}

			/* Ignore eight bytes */
		kBitmap.seekg (8, ios::cur);

			/* Get the position of the start of the bitmap buffer */
		mrUInt32     iStartBuffer;
		kBitmap.read ((char *) &iStartBuffer, sizeof (mrUInt32));

			/* Ignore four bytes */
		kBitmap.seekg (4, ios::cur);

			/* Get width and height of bitmap */
		kBitmap.read ((char *) &m_iWidth, sizeof (mrUInt32));
		kBitmap.read ((char *) &m_iHeight, sizeof (mrUInt32));
 
			/* Ignore two bytes */
		kBitmap.seekg (2, ios::cur);

			/* Get bit count */
		mrUInt16     iBitCount;
		kBitmap.read ((char *) &iBitCount, sizeof (mrUInt16));

			/* If not 24 mode not supported, return error */
		if (iBitCount != 24)
		{
			return mrErrorBitmapNotSupported;
		}
			/* Get compression */
		mrUInt32     iCompression;
		kBitmap.read ((char *) &iCompression, sizeof (mrUInt32));

			/* If compressed not supported, return error */
		if (iCompression != BI_RGB)
		{
			return mrErrorBitmapNotSupported;
		}
 
			/* Move to bitmap buffer */
		kBitmap.seekg (iStartBuffer, ios::beg);

			/* Read image buffer from file */
		mrUInt8 * piBuffer = new mrUInt8 [m_iWidth * m_iHeight * 3];
		kBitmap.read ((char *) piBuffer, m_iWidth * m_iHeight * 3 * 
																sizeof (mrUInt8));

			/* Allocate memory for image buffer */
		if (NULL != m_piImageBuffer)
		{
			delete [] m_piImageBuffer;
		}
		m_piImageBuffer = new mrUInt32 [m_iWidth * m_iHeight];

			/* Get each pixel color components and fill image buffer */ 
		mrUInt32 iX, iY;

		for (iY = 0; iY < m_iHeight; iY++)
		{
			for (iX = 0; iX < m_iWidth; iX++)
			{
					/* Needs to be flipped */
				if (m_iHeight > 0)
				{
						m_piImageBuffer [iX + (m_iHeight - 1 - iY) * (m_iWidth)] = 255 |
												(piBuffer [(iX + iY * (m_iWidth)) * 3 + 0] << 8) |
												(piBuffer [(iX + iY * (m_iWidth)) * 3 + 1] << 16) |
												(piBuffer [(iX + iY * (m_iWidth)) * 3 + 2] << 24);
				}
					/* Doesn't need to be flipped */
				else
				{
					m_piImageBuffer [iX + (iY * m_iWidth)] =  255 |
												(piBuffer [iX + (iY * m_iWidth) * 3 + 0] << 8) |
												(piBuffer [iX + (iY * m_iWidth) * 3 + 1] << 16) |
												(piBuffer [iX + (iY * m_iWidth) * 3 + 2] << 24);
				}
			}
		}

			/* Close file, release memory and return no error */
		if (NULL != piBuffer)
		{
			delete [] piBuffer;
		}

		kBitmap.close ();
	}

 return mrNoError;
}

 /* Load image from TARGA file */
mrError32 mrRGBAImage::LoadFromTarga (LPSTR lpszFilename)
{
 fstream      kTarga;

 kTarga.open (lpszFilename, ios::binary | ios::in);
	
	if (kTarga.is_open ())
	{
			/* Read field description size */
		mrUInt8      iFieldDescSize;
		kTarga.read ((char *) &iFieldDescSize, sizeof (mrUInt8));

			/* Ignore one byte */
		kTarga.seekg (1, ios::cur);

			/* Read image color code */
		mrUInt8      iImageCode;
		kTarga.read ((char *) &iImageCode, sizeof (mrUInt8));

		if (2 != iImageCode)
		{
			return mrErrorTargaNotSupported;
		}

			/* Ignore two bytes */
		kTarga.seekg (2, ios::cur);

			/* Read color map */
		mrUInt16      iMapLength;
		kTarga.read ((char *) &iMapLength, sizeof (mrUInt16));

			/* Ignore one byte */
		kTarga.seekg (1, ios::cur);

			/* Read image start positions */
		mrUInt16      iXStart;
		kTarga.read ((char *) &iXStart, sizeof (mrUInt16));
		mrUInt16      iYStart;
		kTarga.read ((char *) &iYStart, sizeof (mrUInt16));

			/* Read image size */
		mrUInt16      iWidth;
		kTarga.read ((char *) &iWidth, sizeof (mrUInt16));
		mrUInt16      iHeight;
		kTarga.read ((char *) &iHeight, sizeof (mrUInt16));

		m_iWidth  = iWidth;
		m_iHeight = iHeight;

			/* Read image bit depth */
		mrUInt8      iImageBits;

		kTarga.read ((char *) &iImageBits, sizeof (mrUInt8));
		if (32 != iImageBits)
		{
			return mrErrorTargaNotSupported;
		}

			/* Read image description */
		mrUInt8      iImageDesc;
		kTarga.read ((char *) &iImageDesc, sizeof (mrUInt8));
 
			/* Ignore field description */
		kTarga.seekg (iFieldDescSize, ios::cur);
			/* Ignore color map */
		kTarga.seekg (iMapLength * 4, ios::cur);
 
			/* Read image buffer from file */
		mrUInt32 * piBuffer = new mrUInt32 [m_iWidth * m_iHeight];
		kTarga.read ((char *) piBuffer, m_iWidth * m_iHeight * 4 * 
																sizeof (mrUInt8));

			/* Allocate memory for image buffer */
		if (NULL != m_piImageBuffer)
		{
			delete [] m_piImageBuffer;
		}
		m_piImageBuffer = new mrUInt32 [m_iWidth * m_iHeight];

		mrUInt8  iRed, iGreen, iBlue, iAlpha;
		mrUInt32 iColor;

			/* Get each pixel color components and fill image buffer */ 
		mrUInt32 iX, iY;

		for (iY = 0; iY < m_iHeight; iY++)
		{
			for (iX = 0; iX < m_iWidth; iX++)
			{
					/* Doens't need to be flipped */
				if ((iImageDesc & 1) << 4)
				{
						/* Get color components */
					iColor = piBuffer [iX + (iY * m_iWidth)];

					iAlpha = (mrUInt8)((iColor & 0xFF000000) >> 24);
					iRed   = (mrUInt8)((iColor & 0x00FF0000) >> 16);
					iGreen = (mrUInt8)((iColor & 0x0000FF00) >> 8);
					iBlue  = (mrUInt8)((iColor & 0x000000FF));

						/* Copy flipped position */
					m_piImageBuffer [iX + (iY * m_iWidth)] = 
												iAlpha << 0 | iBlue << 8 | iGreen << 16 | iRed << 24;
				}
					/* Needs to be flipped */
				else
				{
						/* Get color components */
					iColor = piBuffer [iX + (iY * m_iWidth)];

					iAlpha = (mrUInt8)((iColor & 0xFF000000) >> 24);
					iRed   = (mrUInt8)((iColor & 0x00FF0000) >> 16);
					iGreen = (mrUInt8)((iColor & 0x0000FF00) >> 8);
					iBlue  = (mrUInt8)((iColor & 0x000000FF));

						/* Copy position */
					m_piImageBuffer [iX + (m_iHeight - 1 - iY) * (m_iWidth)] = 
												iAlpha << 0 | iBlue << 8 | iGreen << 16 | iRed << 24;
				}
			}
		}

			/* Close file, release memory and return no error */
		if (NULL != piBuffer)
		{
			delete [] piBuffer;
		}

		kTarga.close ();
		}

 return mrNoError;

}


 /* Set image color key for rendering */
void mrRGBAImage::SetColorKey (mrUInt8 iRed, mrUInt8 iGreen, 
                               mrUInt8 iBlue)
{
  /* Get each pixel color components and set color key */ 
 mrUInt32 iX, iY;
 mrUInt8 iOriRed, iOriGreen, iOriBlue;

 for (iY = 0; iY < m_iHeight; iY++)
 {
  for (iX = 0; iX < m_iWidth; iX++)
  {
   iOriRed   = (mrUInt8)((m_piImageBuffer [iX + (iY * m_iWidth)] 
                         & 0xFF000000) >> 24);
   iOriGreen = (mrUInt8)((m_piImageBuffer [iX + (iY * m_iWidth)] 
                         & 0x00FF0000) >> 16);
   iOriBlue  = (mrUInt8)((m_piImageBuffer [iX + (iY * m_iWidth)] 
                         & 0x0000FF00) >> 8);

    /* If color matches, set alpha to 0 */
   if ( (iOriRed == iRed) && (iOriGreen == iGreen) && (iOriBlue == iBlue))
   {
    m_piImageBuffer [iX + (iY * m_iWidth)] = iOriRed   << 24 | 
                                             iOriGreen << 16 | 
                                             iOriBlue  << 8  | 
																																													0;
   }
  }
 }
}

 /* Set image width */
void mrRGBAImage::SetWidth (mrUInt32 iWidth)
{
 m_iWidth = iWidth;
}

 /* Set image height */
void mrRGBAImage::SetHeight (mrUInt32 iHeight)
{
 m_iHeight = iHeight;
}

 /* Set color at given position */
void mrRGBAImage::SetColor (mrUInt32 iX, mrUInt32 iY, mrUInt8 iRed, 
																												mrUInt8 iGreen, mrUInt8 iBlue, 
																												mrUInt8 iAlpha)
{
	mrUInt32 iColor;
	iColor = D3DCOLOR_RGBA (iRed, iGreen, iBlue, iAlpha);

 m_piImageBuffer [iX + (iY * m_iWidth - 1)] = iColor;
}

 /* Set the image buffer */
void mrRGBAImage::SetImageBuffer (mrUInt32 * pImage)
{
 if (NULL != m_piImageBuffer)
 {
  delete [] m_piImageBuffer;
 }
 m_piImageBuffer = new mrUInt32 [m_iWidth * m_iHeight];

 memcpy (m_piImageBuffer, pImage, 
         sizeof (mrUInt32) * m_iWidth * m_iHeight);
}

 /* Returns image width */
mrUInt32 mrRGBAImage::GetWidth (void)
{
 return m_iWidth;
}

 /* Returns image height */
mrUInt32 mrRGBAImage::GetHeight (void)
{
 return m_iHeight;
}

 /* Returns image color at a point */
mrUInt32 mrRGBAImage::GetColor (mrUInt32 iX, mrUInt32 iY)
{
 return m_piImageBuffer [iX + iY * m_iWidth];
}

 /* Returns image buffer */
mrUInt32 * mrRGBAImage::GetImageBuffer (void)
{
 return m_piImageBuffer;
}
