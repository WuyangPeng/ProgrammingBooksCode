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
	 /* Copy the entire array from the other image to this one */
 memcpy (m_piImageBuffer, rkImage.GetImageBuffer (), 
		       (m_iWidth * m_iHeight) * sizeof (mrUInt32));

	 /* Return an instance of this class */
	return * this;
}


 /* Load image from a windows bitmap file */
mrError32 mrRGBAImage::LoadFromBitmap (LPSTR lpszFilename)
{
	fstream						kBitmap;

	kBitmap.open (lpszFilename, ios::binary | ios::in);

	mrUInt16					iType;
	kBitmap.read ((char *) &iType, sizeof (mrUInt16));

	 /* Get bitmap signature */
	if (0x4D42 != iType)
	{
		return mrErrorNotBitmapFile;
	}

	 /* Ignore eight bytes */
	kBitmap.seekg (8, ios::cur);

	 /* Get the position of the start of the bitmap buffer */
	mrUInt32					iStartBuffer;
	kBitmap.read ((char *) &iStartBuffer, sizeof (mrUInt32));

	 /* Ignore four bytes */
	kBitmap.seekg (4, ios::cur);

	 /* Get width and height of bitmap */
	kBitmap.read ((char *) &m_iWidth, sizeof (mrUInt32));
	kBitmap.read ((char *) &m_iHeight, sizeof (mrUInt32));
	
	 /* Ignore two bytes */
	kBitmap.seekg (2, ios::cur);

	 /* Get bit count */
	mrUInt16					iBitCount;
	kBitmap.read ((char *) &iBitCount, sizeof (mrUInt16));

	 /* If not mode not supported return error */
	if (iBitCount != 24)
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
	 			m_piImageBuffer [iX + (m_iHeight - 1 - iY) * (m_iWidth)] = 
				       (piBuffer [(iX + iY * (m_iWidth)) * 3 + 0] << 8) |
					      (piBuffer [(iX + iY * (m_iWidth)) * 3 + 1] << 16) |
					      (piBuffer [(iX + iY * (m_iWidth)) * 3 + 2] << 24);
			}
			 /* Doesn't need to be flipped */
			else
			{
				m_piImageBuffer [iX + (iY * m_iWidth - 1)] = 
					      (piBuffer [iX + (iY * m_iWidth - 1) * 3 + 0] << 8) |
					      (piBuffer [iX + (iY * m_iWidth - 1) * 3 + 1] << 16) |
					      (piBuffer [iX + (iY * m_iWidth - 1) * 3 + 2] << 24);
			}
		}
	}

	 /* Close file, release memory and return no error */
	if (NULL != piBuffer)
	{
		delete [] piBuffer;
	}

	kBitmap.close ();

	return mrNoError;
}

 /* Return image width */
mrUInt32 mrRGBAImage::GetWidth (void)
{
 return m_iWidth;
}

 /* Return image height */
mrUInt32 mrRGBAImage::GetHeight (void)
{
 return m_iHeight;
}

 /* Return image color at a point */
mrUInt32 mrRGBAImage::GetColor (mrUInt32 iX, mrUInt32 iY)
{
 return m_piImageBuffer [iX + iY * m_iWidth];
}

 /* Return image buffer */
mrUInt32 * mrRGBAImage::GetImageBuffer (void)
{
 return m_piImageBuffer;
}
