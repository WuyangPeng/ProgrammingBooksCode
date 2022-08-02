//--------------------------------------------------------------------------------------
// File: ClipMapPS20.cpp
//
// This sample shows an example of clipmapped rendering.
//
//--------------------------------------------------------------------------------------
#include "dxstdafx.h"
#include "resource.h"

//#define DEBUG_VS   // Uncomment this line to debug vertex shaders
//#define DEBUG_PS   // Uncomment this line to debug pixel shaders


//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
ID3DXFont*              g_pFont = NULL;         // Font for drawing text
ID3DXSprite*            g_pSprite = NULL;       // Sprite for batching draw text calls
bool                    g_bShowHelp = true;     // If true, it renders the UI control text
CModelViewerCamera      g_Camera;               // A model viewing camera
ID3DXEffect*            g_pEffect = NULL;       // D3DX effect interface
ID3DXMesh*              g_pMesh = NULL;         // Mesh object
IDirect3DTexture9*      g_pMeshTexture = NULL;  // Mesh texture
CDXUTDialogResourceManager g_DialogResourceManager; // manager for shared resources of dialogs
CD3DSettingsDlg         g_SettingsDlg;          // Device settings dialog
CDXUTDialog             g_HUD;                  // manages the 3D UI
CDXUTDialog             g_SampleUI;             // dialog for sample specific controls
bool                    g_bEnablePreshader;     // if TRUE, then D3DXSHADER_NO_PRESHADER is used when compiling the shader
D3DXMATRIXA16           g_mCenterWorld;


//--------------------------------------------------------------------------------------
// UI control IDs
//--------------------------------------------------------------------------------------
#define IDC_TOGGLEFULLSCREEN    1
#define IDC_TOGGLEREF           3
#define IDC_CHANGEDEVICE        4
#define IDC_ENABLE_PRESHADER    5
#define IDC_CLIPMAP_MODE        6
#define IDC_CLIPMAP_X           7
#define IDC_CLIPMAP_Y           8
#define IDC_CLIPMAP_X_LABEL     9
#define IDC_CLIPMAP_Y_LABEL     10

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
bool    CALLBACK IsDeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext );
bool    CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps, void* pUserContext );
HRESULT CALLBACK OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
HRESULT CALLBACK OnResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
void    CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext );
void    CALLBACK OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext );
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext );
void    CALLBACK KeyboardProc( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext );
void    CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext );
void    CALLBACK OnLostDevice( void* pUserContext );
void    CALLBACK OnDestroyDevice( void* pUserContext );

void    InitApp();
HRESULT LoadMesh( IDirect3DDevice9* pd3dDevice, WCHAR* strFileName, ID3DXMesh** ppMesh );
void    RenderText( double fTime );

#define AssertFatal(cond, msg) if(!(cond)) { printf("Assertion: " msg); OutputDebugStringA("Assertion: " msg); exit(1); }

// TGA Loader - 16/11/04 Codehead
// Gotten from http://gpwiki.org/index.php/LoadTGACpp - all rights are theirs.

#include <iostream>
#include <fstream>
#include <memory.h>

#define IMG_OK              0x1
#define IMG_ERR_NO_FILE     0x2
#define IMG_ERR_MEM_FAIL    0x4
#define IMG_ERR_BAD_FORMAT  0x8
#define IMG_ERR_UNSUPPORTED 0x40

class TGAImg
{
public:
   TGAImg();
   ~TGAImg();
   int Load(char* szFilename);
   int GetBPP();
   int GetWidth();
   int GetHeight();
   unsigned char* GetImg();       // Return a pointer to image data
   unsigned char* GetPalette();   // Return a pointer to VGA palette

   void BGRtoRGB();

private:
   short int iWidth,iHeight,iBPP;
   unsigned long lImageSize;
   char bEnc;
   unsigned char *pImage, *pPalette, *pData;

   // Internal workers
   int ReadHeader();
   int LoadRawData();
   int LoadTgaRLEData();
   int LoadTgaPalette();
   void FlipImg();
};


TGAImg::TGAImg()
{ 
   pImage=pPalette=pData=NULL;
   iWidth=iHeight=iBPP=bEnc=0;
   lImageSize=0;
}


TGAImg::~TGAImg()
{
   if(pImage)
   {
      delete [] pImage;
      pImage=NULL;
   }

   if(pPalette)
   {
      delete [] pPalette;
      pPalette=NULL;
   }

   if(pData)
   {
      delete [] pData;
      pData=NULL;
   }
}


int TGAImg::Load(char* szFilename)
{
   using namespace std;
   ifstream fIn;
   unsigned long ulSize;
   int iRet;

   // Clear out any existing image and palette
   if(pImage)
   {
      delete [] pImage;
      pImage=NULL;
   }

   if(pPalette)
   {
      delete [] pPalette;
      pPalette=NULL;
   }

   // Open the specified file
   fIn.open(szFilename,ios::binary);

   if(fIn==NULL)
      return IMG_ERR_NO_FILE;

   // Get file size
   fIn.seekg(0,ios_base::end);
   ulSize=fIn.tellg();
   fIn.seekg(0,ios_base::beg);

   // Allocate some space
   // Check and clear pDat, just in case
   if(pData)
      delete [] pData; 

   pData=new unsigned char[ulSize];

   if(pData==NULL)
   {
      fIn.close();
      return IMG_ERR_MEM_FAIL;
   }

   // Read the file into memory
   fIn.read((char*)pData,ulSize);

   fIn.close();

   // Process the header
   iRet=ReadHeader();

   if(iRet!=IMG_OK)
      return iRet;

   switch(bEnc)
   {
   case 1: // Raw Indexed
      {
         // Check filesize against header values
         if((lImageSize+18+pData[0]+768)>ulSize)
            return IMG_ERR_BAD_FORMAT;

         // Double check image type field
         if(pData[1]!=1)
            return IMG_ERR_BAD_FORMAT;

         // Load image data
         iRet=LoadRawData();
         if(iRet!=IMG_OK)
            return iRet;

         // Load palette
         iRet=LoadTgaPalette();
         if(iRet!=IMG_OK)
            return iRet;

         break;
      }

   case 2: // Raw RGB
      {
         // Check filesize against header values
         if((lImageSize+18+pData[0])>ulSize)
            return IMG_ERR_BAD_FORMAT;

         // Double check image type field
         if(pData[1]!=0)
            return IMG_ERR_BAD_FORMAT;

         // Load image data
         iRet=LoadRawData();
         if(iRet!=IMG_OK)
            return iRet;

         BGRtoRGB(); // Convert to RGB
         break;
      }

   case 9: // RLE Indexed
      {
         // Double check image type field
         if(pData[1]!=1)
            return IMG_ERR_BAD_FORMAT;

         // Load image data
         iRet=LoadTgaRLEData();
         if(iRet!=IMG_OK)
            return iRet;

         // Load palette
         iRet=LoadTgaPalette();
         if(iRet!=IMG_OK)
            return iRet;

         break;
      }

   case 10: // RLE RGB
      {
         // Double check image type field
         if(pData[1]!=0)
            return IMG_ERR_BAD_FORMAT;

         // Load image data
         iRet=LoadTgaRLEData();
         if(iRet!=IMG_OK)
            return iRet;

         BGRtoRGB(); // Convert to RGB
         break;
      }

   default:
      return IMG_ERR_UNSUPPORTED;
   }

   // Check flip bit
   if((pData[17] & 0x20)==0) 
      FlipImg();

   // Release file memory
   delete [] pData;
   pData=NULL;

   return IMG_OK;
}


int TGAImg::ReadHeader() // Examine the header and populate our class attributes
{
   short ColMapStart,ColMapLen;
   short x1,y1,x2,y2;

   if(pData==NULL)
      return IMG_ERR_NO_FILE;

   if(pData[1]>1)    // 0 (RGB) and 1 (Indexed) are the only types we know about
      return IMG_ERR_UNSUPPORTED;

   bEnc=pData[2];     // Encoding flag  1 = Raw indexed image
   //                2 = Raw RGB
   //                3 = Raw greyscale
   //                9 = RLE indexed
   //               10 = RLE RGB
   //               11 = RLE greyscale
   //               32 & 33 Other compression, indexed

   if(bEnc>11)       // We don't want 32 or 33
      return IMG_ERR_UNSUPPORTED;


   // Get palette info
   memcpy(&ColMapStart,&pData[3],2);
   memcpy(&ColMapLen,&pData[5],2);

   // Reject indexed images if not a VGA palette (256 entries with 24 bits per entry)
   if(pData[1]==1) // Indexed
   {
      if(ColMapStart!=0 || ColMapLen!=256 || pData[7]!=24)
         return IMG_ERR_UNSUPPORTED;
   }

   // Get image window and produce width & height values
   memcpy(&x1,&pData[8],2);
   memcpy(&y1,&pData[10],2);
   memcpy(&x2,&pData[12],2);
   memcpy(&y2,&pData[14],2);

   iWidth=(x2-x1);
   iHeight=(y2-y1);

   if(iWidth<1 || iHeight<1)
      return IMG_ERR_BAD_FORMAT;

   // Bits per Pixel
   iBPP=pData[16];

   // Check flip / interleave byte
   if(pData[17]>32) // Interleaved data
      return IMG_ERR_UNSUPPORTED;

   // Calculate image size
   lImageSize=(iWidth * iHeight * (iBPP/8));

   return IMG_OK;
}


int TGAImg::LoadRawData() // Load uncompressed image data
{
   short iOffset;

   if(pImage) // Clear old data if present
      delete [] pImage;

   pImage=new unsigned char[lImageSize];

   if(pImage==NULL)
      return IMG_ERR_MEM_FAIL;

   iOffset=pData[0]+18; // Add header to ident field size

   if(pData[1]==1) // Indexed images
      iOffset+=768;  // Add palette offset

   memcpy(pImage,&pData[iOffset],lImageSize);

   return IMG_OK;
}


int TGAImg::LoadTgaRLEData() // Load RLE compressed image data
{
   short iOffset,iPixelSize;
   unsigned char *pCur;
   unsigned long Index=0;
   unsigned char bLength,bLoop;

   // Calculate offset to image data
   iOffset=pData[0]+18;

   // Add palette offset for indexed images
   if(pData[1]==1)
      iOffset+=768; 

   // Get pixel size in bytes
   iPixelSize=iBPP/8;

   // Set our pointer to the beginning of the image data
   pCur=&pData[iOffset];

   // Allocate space for the image data
   if(pImage!=NULL)
      delete [] pImage;

   pImage=new unsigned char[lImageSize];

   if(pImage==NULL)
      return IMG_ERR_MEM_FAIL;

   // Decode
   while(Index<lImageSize) 
   {
      if(*pCur & 0x80) // Run length chunk (High bit = 1)
      {
         bLength=*pCur-127; // Get run length
         pCur++;            // Move to pixel data  

         // Repeat the next pixel bLength times
         for(bLoop=0;bLoop!=bLength;++bLoop,Index+=iPixelSize)
            memcpy(&pImage[Index],pCur,iPixelSize);

         pCur+=iPixelSize; // Move to the next descriptor chunk
      }
      else // Raw chunk
      {
         bLength=*pCur+1; // Get run length
         pCur++;          // Move to pixel data

         // Write the next bLength pixels directly
         for(bLoop=0;bLoop!=bLength;++bLoop,Index+=iPixelSize,pCur+=iPixelSize)
            memcpy(&pImage[Index],pCur,iPixelSize);
      }
   }

   return IMG_OK;
}


int TGAImg::LoadTgaPalette() // Load a 256 color palette
{
   unsigned char bTemp;
   short iIndex,iPalPtr;

   // Delete old palette if present
   if(pPalette)
   {
      delete [] pPalette;
      pPalette=NULL;
   }

   // Create space for new palette
   pPalette=new unsigned char[768];

   if(pPalette==NULL)
      return IMG_ERR_MEM_FAIL;

   // VGA palette is the 768 bytes following the header
   memcpy(pPalette,&pData[pData[0]+18],768);

   // Palette entries are BGR ordered so we have to convert to RGB
   for(iIndex=0,iPalPtr=0;iIndex!=256;++iIndex,iPalPtr+=3)
   {
      bTemp=pPalette[iPalPtr];               // Get Blue value
      pPalette[iPalPtr]=pPalette[iPalPtr+2]; // Copy Red to Blue
      pPalette[iPalPtr+2]=bTemp;             // Replace Blue at the end
   }

   return IMG_OK;
}


void TGAImg::BGRtoRGB() // Convert BGR to RGB (or back again)
{
   unsigned long Index,nPixels;
   unsigned char *bCur;
   unsigned char bTemp;
   short iPixelSize;

   // Set ptr to start of image
   bCur=pImage;

   // Calc number of pixels
   nPixels=iWidth*iHeight;

   // Get pixel size in bytes
   iPixelSize=iBPP/8;

   for(Index=0;Index!=nPixels;Index++)  // For each pixel
   {
      bTemp=*bCur;      // Get Blue value
      *bCur=*(bCur+2);  // Swap red value into first position
      *(bCur+2)=bTemp;  // Write back blue to last position

      bCur+=iPixelSize; // Jump to next pixel
   }

}


void TGAImg::FlipImg() // Flips the image vertically (Why store images upside down?)
{
   unsigned char bTemp;
   unsigned char *pLine1, *pLine2;
   int iLineLen,iIndex;

   iLineLen=iWidth*(iBPP/8);
   pLine1=pImage;
   pLine2=&pImage[iLineLen * (iHeight - 1)];

   for( ;pLine1<pLine2;pLine2-=(iLineLen*2))
   {
      for(iIndex=0;iIndex!=iLineLen;pLine1++,pLine2++,iIndex++)
      {
         bTemp=*pLine1;
         *pLine1=*pLine2;
         *pLine2=bTemp;       
      }
   } 

}


int TGAImg::GetBPP() 
{
   return iBPP;
}


int TGAImg::GetWidth()
{
   return iWidth;
}


int TGAImg::GetHeight()
{
   return iHeight;
}


unsigned char* TGAImg::GetImg()
{
   return pImage;
}


unsigned char* TGAImg::GetPalette()
{
   return pPalette;
}

// ClipMap Management Class
class ClipMap
{
public:
   const static int csmLayerCount = 5;
   const static int csmClipMapSize = 256;
   const static int csmClipMapShift = 8; // log2 of csmClipMapSize;
   const static int csmSourceImageSize = 4096;
   const static int csmSourceImageMipCount = 12; // log2 of csmSourceImageSize

   // Total storage for the raw image we'll be clipmapping.
   unsigned char *mRawImage;

   // Pointers to each mip level of the image.
   unsigned char *mRawMips[12];

   // Simple integer-coordinate point.
   struct Point2I
   {
      Point2I()
      {
      }

      Point2I(int inX, int inY)
         : x(inX), y(inY)
      {
      }

      int x,y;

      Point2I  operator-(const Point2I &_rSub) const
      {
         return Point2I(x - _rSub.x, y - _rSub.y);
      }
   };

   // Simple integer-coordinate rectangle.
   struct RectI
   {
      RectI()
      {
      }

      RectI(Point2I p, Point2I e)
      {
         point = p;
         extent = e;
      }

      Point2I point, extent;

      bool isValidRect() const { return (extent.x > 0 && extent.y > 0); }
      
      bool intersect(const RectI &clipRect)
      {
         Point2I bottomL;
         bottomL.x = min(point.x + extent.x - 1, clipRect.point.x + clipRect.extent.x - 1);
         bottomL.y = min(point.y + extent.y - 1, clipRect.point.y + clipRect.extent.y - 1);

         point.x = max(point.x, clipRect.point.x);
         point.y = max(point.y, clipRect.point.y);

         extent.x = bottomL.x - point.x + 1;
         extent.y = bottomL.y - point.y + 1;

         return isValidRect();
      }

      bool overlaps(RectI R) const
      {
         return R.intersect (* this);
      }

      bool contains(const RectI& R) const
      {
         if (point.x <= R.point.x && point.y <= R.point.y)
            if (R.point.x + R.extent.x <= point.x + extent.x)
               if (R.point.y + R.extent.y <= point.y + extent.y)
                  return true;
         return false;
      }

   };

   // Each layer of the clipmap stack is represented by one of these structures.
   struct ClipStackEntry
   {
      // The top-left coordinate in the virtualized image that this entry
      // currently stores. It's referred to as the toroidal offset because 
      // this modulo clipmapsize indicates where the seams in the toroidal
      // image buffer is.
      Point2I mToroidalOffset;

      /// The texture coordinate scale factor for this level.
      float mScale;
      
      /// Centerpoint of this layer in UV coordinates.
      float mCenterX, mCenterY;

      /// The actual texture resource this stack entry owns.
      IDirect3DTexture9 *mTex;

      ClipStackEntry()
      {
         mToroidalOffset.x = mToroidalOffset.y = 0;
         mCenterX = mCenterY = 0;
         mScale = 1.f;
         mTex = NULL;
      }
   };

   ClipStackEntry mLayer[csmLayerCount];

   ClipMap()
   {
      // Fill in some default information for all layers.
      for(int i=0; i<csmLayerCount; i++)
      {
         // Set up a centered position.
         mLayer[i].mCenterX = 0.5f;
         mLayer[i].mCenterY = 0.5f; 
         mLayer[i].mToroidalOffset.x = ((csmClipMapSize/2) << i) - csmClipMapSize/2;
         mLayer[i].mToroidalOffset.y = ((csmClipMapSize/2) << i) - csmClipMapSize/2;
         mLayer[i].mScale = float(1<<i);
      }

      mRawImage = NULL;
   }

   void reset()
   {
      for(int i=0; i<csmLayerCount; i++)
      {
         if(mLayer[i].mTex)
         {
            mLayer[i].mTex->Release();
            mLayer[i].mTex = NULL;
         }
      }

      bindTextures();
   }

   void alloc(IDirect3DDevice9 *device)
   {
      // Just to be safe...
      reset();

      // Recreate appropriate textures to upload into.
      HRESULT hr;
      for(int i=0; i<csmLayerCount; i++)
      {
         V(device->CreateTexture(csmClipMapSize,csmClipMapSize,0,D3DUSAGE_DYNAMIC|D3DUSAGE_AUTOGENMIPMAP,
                                 D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&mLayer[i].mTex, NULL));
      }

      bindTextures();
      fillWithTextureData();
   }

   ~ClipMap()
   {
      reset();
      if(mRawImage)
      {
         delete[] mRawImage;
         mRawImage = NULL;
      }
   }

   void bindTextures()
   {
      if(!g_pEffect)
         return;

      HRESULT hr;

      V( g_pEffect->SetTexture( "clipTexture0", mLayer[0].mTex) );
      V( g_pEffect->SetTexture( "clipTexture1", mLayer[1].mTex) );
      V( g_pEffect->SetTexture( "clipTexture2", mLayer[2].mTex) );
      V( g_pEffect->SetTexture( "clipTexture3", mLayer[3].mTex) );
      V( g_pEffect->SetTexture( "clipTexture4", mLayer[4].mTex) );
   }

   void updateEffectParams()
   {
      if(!g_pEffect)
         return;

      HRESULT hr;

      D3DXHANDLE h;
      h = g_pEffect->GetParameterByName(NULL, "g_clipLayerAndCenter");

      float clipArray[csmLayerCount*3];

      for(int i=0; i<csmLayerCount; i++)
      {
         clipArray[i*3+0] = mLayer[i].mCenterX * mLayer[i].mScale;
         clipArray[i*3+1] = mLayer[i].mCenterY * mLayer[i].mScale;
         clipArray[i*3+2] = mLayer[i].mScale;
      }

      V( g_pEffect->SetFloatArray(h, clipArray, 5*3) );
   }

   void generateMip32Bit(unsigned char *srcLevel, int srcSize, unsigned char *outLevel)
   {
      int r,g,b,a,offset;

      int halfSrcSize = srcSize >> 1;
      for(int x=0; x<halfSrcSize; x++)
      {
         for(int y=0; y<halfSrcSize; y++)
         {
            // Sample the four source pixels and average them to generate
            // out pixel.
            offset = (2*x*srcSize+2*y)*4;
            r = srcLevel[offset + 0];
            g = srcLevel[offset + 1];
            b = srcLevel[offset + 2];
            a = srcLevel[offset + 3];

            offset += 4;
            r += srcLevel[offset + 0];
            g += srcLevel[offset + 1];
            b += srcLevel[offset + 2];
            a += srcLevel[offset + 3];

            offset += srcSize*4;
            r += srcLevel[offset + 0];
            g += srcLevel[offset + 1];
            b += srcLevel[offset + 2];
            a += srcLevel[offset + 3];

            offset += 4;
            r += srcLevel[offset + 0];
            g += srcLevel[offset + 1];
            b += srcLevel[offset + 2];
            a += srcLevel[offset + 3];

            // Now average down.
            r >>= 2;
            g >>= 2;
            b >>= 2;
            a >>= 2;

            // And store
            offset = (x*halfSrcSize+y)*4;
            outLevel[offset+0] = r;
            outLevel[offset+1] = g;
            outLevel[offset+2] = b;
            outLevel[offset+3] = a;
         }
      }
   }

   void fillSourceData()
   {
      // Only fill it once.
      if(mRawImage)
         return;

      // Allocate storage for an RGBA image with mips. We also note what
      // the offset from the image base will be for each mip level so that
      // we just have to add the image base offset to the contents of mRawMips.
      int storageSize = 0;
      int storageDim = csmSourceImageSize;
      int mipCount = 0;
      while(storageDim > 1)
      {
         mRawMips[mipCount++] = (unsigned char*)storageSize;
         storageSize += storageDim * storageDim * 4;
         storageDim >>= 1;
      }

      mRawImage = new unsigned char[storageSize];

      for(int i=0; i<csmSourceImageMipCount; i++)
         mRawMips[i] = mRawMips[i] + (int)mRawImage;

#if 0
      // Now walk the array filling with a test pattern.
      unsigned char *ptr = mRawImage;

      for(int i=0; i<csmSourceImageSize; i++)
      {
         for(int j=0; j<csmSourceImageSize; j++)
         {
            // Generate a fill pattern.
            (*ptr++) = unsigned char(i & 0xFF);
            (*ptr++) = unsigned char(j & 0xFF);
            (*ptr++) = unsigned char(((i+j) & 0x0F) << 4);
            (*ptr++) = unsigned char(0);
         }
      }
#else
      TGAImg image;
      int res = image.Load("texture.tga");

      if(res != IMG_OK)
      {
         AssertFatal(false, "Image 'texture.tga' failed to load.");
      }

      // We need to flip endianness. :)
      image.BGRtoRGB();

      // This will be 24bpp, so have to swizzle it into our buffer.
      unsigned char *imgBits = image.GetImg();

      unsigned char *outBits = mRawImage;
      unsigned char *outBitsEnd = mRawImage + (csmSourceImageSize * csmSourceImageSize * 4);

      while(outBits != outBitsEnd)
      {
         *(outBits++) = *(imgBits++);
         *(outBits++) = *(imgBits++);
         *(outBits++) = *(imgBits++);
         *(outBits++) = 0;
      }
#endif

      // Great - the base mip is filled with data but we need to generate
      // the mip levels so we can copy out of them for clipmap updates.
      
      // Let's do something simple - braindead box filter.
      for(int i=0; i<csmSourceImageMipCount-1; i++)
         generateMip32Bit(mRawMips[i], csmSourceImageSize >> i, mRawMips[i+1]);

      // And we're done.
   }

   void clipAgainstGrid(const int gridSpacing, const RectI &rect, int *outCount, RectI *outBuffer)
   {
      // Check against X grids...
      const int startX = rect.point.x;
      const int endX   = rect.point.x + rect.extent.x;

      const int gridMask = ~(gridSpacing-1);
      const int startGridX = startX & gridMask;
      const int endGridX   = endX   & gridMask;

      RectI buffer[2];
      int rectCount = 0;

      // Check X...
      if(startGridX != endGridX && endX - endGridX > 0)
      {
         // We have a clip! Split against the grid multiple and store.
         rectCount = 2;
         buffer[0].point.x  = startX;
         buffer[0].point.y  = rect.point.y;
         buffer[0].extent.x = endGridX - startX;
         buffer[0].extent.y = rect.extent.y;

         buffer[1].point.x  = endGridX;
         buffer[1].point.y  = rect.point.y;
         buffer[1].extent.x = endX - endGridX;
         buffer[1].extent.y = rect.extent.y;
      }
      else
      {
         // Copy it in.
         rectCount = 1;
         buffer[0] = rect;
      }

      // Now, check Y for the one or two rects we have from above.
      *outCount = 0;
      for(int i=0; i<rectCount; i++)
      {
         // Figure our extent and grid information.
         const int startY = buffer[i].point.y;
         const int endY   = buffer[i].point.y + rect.extent.y;
         const int startGridY = startY & gridMask;
         const int endGridY   = endY   & gridMask;

         if(startGridY != endGridY && endY - endGridY > 0)
         {
            // We have a clip! Split against the grid multiple and store.
            RectI *buffA = outBuffer + *outCount;
            RectI *buffB = buffA + 1;
            (*outCount) += 2;

            buffA->point.x  = buffer[i].point.x;
            buffA->point.y  = startY;
            buffA->extent.x = buffer[i].extent.x;
            buffA->extent.y = endGridY - startY;

            buffB->point.x  = buffer[i].point.x;
            buffB->point.y  = endGridY;
            buffB->extent.x = buffer[i].extent.x;
            buffB->extent.y = endY - endGridY;
         }
         else
         {
            // Copy it in.
            outBuffer[*outCount] = buffer[i];
            (*outCount)++;
         }      
      }
   }

   void calculateModuloDeltaBounds(const RectI &oldData, const RectI &newData, 
      RectI *outRects, int *outRectCount)
   {
      // Sanity checking.
      AssertFatal(oldData.point.x >= 0 && oldData.point.y >= 0 && oldData.isValidRect(),
         "ClipMap::calculateModuloDeltaBounds - negative oldData origin or bad rect!");

      AssertFatal(newData.point.x >= 0 && newData.point.y >= 0 && newData.isValidRect(),
         "ClipMap::calculateModuloDeltaBounds - negative newData origin or bad rect!");

      AssertFatal(newData.extent.x == oldData.extent.x && newData.extent.y == oldData.extent.y, 
         "ClipMap::calculateModuloDeltaBounts - mismatching extents, can only work with matching extents!");

      // Easiest case - if they're the same then do nothing.
      if(oldData.point.x == newData.point.x && oldData.point.y == newData.point.y)
      {
         *outRectCount = 0;
         return;
      }

      // Easy case - if there's no overlap then it's all new!
      if(!oldData.overlaps(newData))
      {
         // Clip out to return buffer, and we're done.
         clipAgainstGrid(csmClipMapSize, newData, outRectCount, outRects);
         return;
      }

      // Calculate some useful values for both X and Y. Delta is used a lot
      // in determining bounds, and the boundary values are important for
      // determining where to start copying new data in.
      const int xDelta = newData.point.x - oldData.point.x;
      const int yDelta = newData.point.y - oldData.point.y;

      const int xBoundary = (oldData.point.x + oldData.extent.x) % csmClipMapSize;
      const int yBoundary = (oldData.point.y + oldData.extent.y) % csmClipMapSize;

      AssertFatal(xBoundary % csmClipMapSize == oldData.point.x % csmClipMapSize, 
         "ClipMap::calculateModuleDeltaBounds - we assume that left and "
         "right of the dataset are identical (ie, it's periodical on size of clipmap!) (x)");

      AssertFatal(yBoundary % csmClipMapSize == oldData.point.y % csmClipMapSize, 
         "ClipMap::calculateModuleDeltaBounds - we assume that left and "
         "right of the dataset are identical (ie, it's periodical on size of clipmap!) (y)");

      // Now, let's build up our rects. We have one rect if we are moving
      // on the X or Y axis, two if both. We dealt with the no-move case
      // previously.
      if(xDelta == 0)
      {
         // Moving on Y! So generate and store clipped results.
         RectI yRect;

         if(yDelta < 0)
         {
            // We need to generate the box from right of old to right of new.
            yRect.point = newData.point;
            yRect.extent.x = csmClipMapSize;
            yRect.extent.y = -yDelta;
         }
         else
         {
            // We need to generate the box from left of old to left of new.
            yRect.point.x = newData.point.x; // Doesn't matter which rect we get this from.
            yRect.point.y = (oldData.point.y + oldData.extent.y);
            yRect.extent.x = csmClipMapSize;
            yRect.extent.y = yDelta;
         }

         // Clip out to return buffer, and we're done.
         clipAgainstGrid(csmClipMapSize, yRect, outRectCount, outRects);

         return;
      }
      else if(yDelta == 0)
      {
         // Moving on X! So generate and store clipped results.
         RectI xRect;

         if(xDelta < 0)
         {
            // We need to generate the box from right of old to right of new.
            xRect.point = newData.point;
            xRect.extent.x = -xDelta;
            xRect.extent.y = csmClipMapSize;
         }
         else
         {
            // We need to generate the box from left of old to left of new.
            xRect.point.x = (oldData.point.x + oldData.extent.x);
            xRect.point.y = newData.point.y; // Doesn't matter which rect we get this from.
            xRect.extent.x = xDelta;
            xRect.extent.y = csmClipMapSize;
         }

         // Clip out to return buffer, and we're done.
         clipAgainstGrid(csmClipMapSize, xRect, outRectCount, outRects);

         return;
      }
      else
      {
         // Both! We have an L shape. So let's do the bulk of it in one rect,
         // and the remainder in the other. We'll choose X as the dominant axis.
         //
         // a-----b---------c   going from e to a.
         // |     |         |
         // |     |         |
         // d-----e---------f   So the dominant rect is abgh and the passive
         // |     |         |   rect is bcef. Obviously depending on delta we
         // |     |         |   have to switch things around a bit.
         // |     |         |          y+ ^
         // |     |         |             |  
         // g-----h---------i   x+->      |

         RectI xRect, yRect;

         if(xDelta < 0)
         {
            // Case in the diagram.
            xRect.point = newData.point;
            xRect.extent.x = -xDelta;
            xRect.extent.y = csmClipMapSize;

            // Set up what of yRect we know, too.
            yRect.point.x = xRect.point.x + xRect.extent.x;
            yRect.extent.x = csmClipMapSize - abs(xDelta); 
         }
         else
         {
            // Opposite of case in diagram!
            xRect.point.x = oldData.point.x + oldData.extent.x;
            xRect.point.y = newData.point.y;
            xRect.extent.x = xDelta;
            xRect.extent.y = csmClipMapSize;

            // Set up what of yRect we know,  too.
            yRect.point.x = (xRect.point.x + xRect.extent.x )- csmClipMapSize;
            yRect.extent.x = csmClipMapSize - xRect.extent.x;
         }

         if(yDelta < 0)
         {
            // Case in the diagram.
            yRect.point.y = newData.point.y;
            yRect.extent.y = -yDelta;
         }
         else
         {
            // Opposite of case in diagram!
            yRect.point.y = oldData.point.y + oldData.extent.y;
            yRect.extent.y = yDelta;
         }

         // Make sure we don't overlap.
         AssertFatal(!yRect.overlaps(xRect), 
            "ClipMap::calculateModuloDeltaBounds - have overlap in result rects!");

         // Ok, now run them through the clipper.
         int firstCount;
         clipAgainstGrid(csmClipMapSize, xRect, &firstCount, outRects);
         clipAgainstGrid(csmClipMapSize, yRect, outRectCount, outRects + firstCount);
         *outRectCount += firstCount;

         // All done!
         return;
      }
   }

   int clamp(int val, int min, int max)
   {
           if(val < min) return min;
      else if(val > max) return max;
      else               return val;
   }

   void uploadToTexture(int level, RectI srcRegion, RectI dstRegion)
   {
      // Lock dstRegion in the texture.
      RECT inR;
      D3DLOCKED_RECT lockRect;

      inR.top = dstRegion.point.x;
      inR.bottom = dstRegion.point.x + dstRegion.extent.x;

      inR.left = dstRegion.point.y;
      inR.right = dstRegion.point.y + dstRegion.extent.y;

      HRESULT hr;
      V(mLayer[level].mTex->LockRect(0, &lockRect, &inR, 0));

#if 0
      // Fill region with a debug color.
      static char debugCol = 0;
      debugCol = rand();
      for(int i=0; i<dstRegion.extent.x; i++)
         memset((char*)lockRect.pBits + i * lockRect.Pitch, debugCol, 4 * dstRegion.extent.y);
#else
      // Fill region with data from the source texture - so first make sure
      // it's loaded!
      fillSourceData();

      // Now, blt some data over. Note we have to do some x/y swaps to get thing
      // to work out properly. Also the mip level we upload from is based on the
      // specified CSE level - so we have to adjust from clip layers into source
      // image mips. This is a row-wise copy - one memcpy per row of data.

      const int selectedMip = csmLayerCount - level - 1;
      const unsigned char *mipLayer = mRawMips[selectedMip];

      for(int i=0; i<dstRegion.extent.x; i++)
         memcpy(
            (char*)lockRect.pBits + i * lockRect.Pitch,
            mipLayer + ((srcRegion.point.x + i) * (csmSourceImageSize>>selectedMip) + srcRegion.point.y) * 4,
            4 * dstRegion.extent.y
         );
#endif

      // Unlock!
      V(mLayer[level].mTex->UnlockRect(0));
   }

   void recenter(float centerX, float centerY)
   {

      // Ok, we're going to do toroidal updates on each entry of the clipstack
      // (except for the cap, which covers the whole texture), based on this
      // new center point.

      // For each texture...
      for(int i=csmLayerCount-1; i>=0; i--)
      {
         // Calculate new center point for this texture.
         float texelCenterFX = centerX * float(csmClipMapSize) * mLayer[i].mScale;
         float texelCenterFY = centerY * float(csmClipMapSize) * mLayer[i].mScale;

         const int texelMin = csmClipMapSize/2;
         const int texelMax = int(float(csmClipMapSize) * mLayer[i].mScale) - texelMin;

         Point2I texelTopLeft(
            clamp(int(floor(texelCenterFY)), texelMin, texelMax) - texelMin,
            clamp(int(floor(texelCenterFX)), texelMin, texelMax) - texelMin);

         // This + current toroid offset tells us what regions have to be blasted.
         RectI oldData(mLayer[i].mToroidalOffset,  Point2I(csmClipMapSize, csmClipMapSize));
         RectI newData(texelTopLeft,         Point2I(csmClipMapSize, csmClipMapSize));

         // This would be a good place to check if data is available (if you
         // implement paging) and abort if it's not present.

         // Alright, determine the set of data we actually need to upload.
         RectI buffer[8];
         int   rectCount = 0;

         calculateModuloDeltaBounds(oldData, newData, buffer, &rectCount);
         AssertFatal(rectCount < 8, "ClipMap::recenter - got too many rects back!");

         mLayer[i].mToroidalOffset = texelTopLeft;
         mLayer[i].mCenterX = centerX;
         mLayer[i].mCenterY = centerY;

         /*     if(rectCount)
         printf("    issuing %d updates to clipmap level %d (offset=%dx%d)", 
         rectCount, i, texelTopLeft.x, texelTopLeft.y); */

         if(rectCount)
         {
            //printf("layer %x, %d updates", &cse,  rectCount);

            // And GO!
            for(int j=0; j<rectCount; j++)
            {
               AssertFatal(buffer[j].isValidRect(),"ClipMap::recenter - got invalid rect!");

               // Note the rect, so we can then wrap and let the image cache do its thing.
               RectI srcRegion = buffer[j];
               buffer[j].point.x = srcRegion.point.x % csmClipMapSize;
               buffer[j].point.y = srcRegion.point.y % csmClipMapSize;

               AssertFatal(newData.contains(srcRegion), 
                  "ClipMap::recenter - got update buffer outside of expected new data bounds.");

               // Upload new data to the texture.
               uploadToTexture(i, srcRegion, buffer[j]);

               // This is where you'd update the number of texels uploaded.
            }
         }

         // If you were doing texel budgeting, this is where you'd abort on
         // overrun of budget.
      }
   }

   /// This is called when we want to completely fill every layer; for instance
   /// for the first frame or as part of a device reset.
   void fillWithTextureData()
   {
      // For each texture...
      for(int i=csmLayerCount-1; i>=0; i--)
      {
         // This + current toroid offset tells us what regions have to be blasted.
         RectI desiredData(mLayer[i].mToroidalOffset,  Point2I(csmClipMapSize, csmClipMapSize));

         // Alright, determine the set of data we actually need to upload.
         RectI buffer[8];
         int   rectCount = 0;

         clipAgainstGrid(csmClipMapSize, desiredData, &rectCount, buffer);
         AssertFatal(rectCount < 8, "ClipMap::fillWithTextureData - got too many rects back!");

         /*     if(rectCount)
         printf("    issuing %d updates to clipmap level %d (offset=%dx%d)", 
         rectCount, i, texelTopLeft.x, texelTopLeft.y); */

         if(rectCount)
         {
            //printf("layer %x, %d updates", &cse,  rectCount);

            // And GO!
            for(int j=0; j<rectCount; j++)
            {
               AssertFatal(buffer[j].isValidRect(),"ClipMap::fillWithTextureData - got invalid rect!");

               // Note the rect, so we can then wrap and let the image cache do its thing.
               RectI srcRegion = buffer[j];
               buffer[j].point.x = srcRegion.point.x % csmClipMapSize;
               buffer[j].point.y = srcRegion.point.y % csmClipMapSize;

               // Upload new data to the texture.
               uploadToTexture(i, srcRegion, buffer[j]);

               // This is where you'd update the number of texels uploaded.
            }
         }
      }
   }
} gClipMap;


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    // Set the callback functions. These functions allow DXUT to notify
    // the application about device changes, user input, and windows messages.  The
    // callbacks are optional so you need only set callbacks for events you're interested
    // in. However, if you don't handle the device reset/lost callbacks then the sample
    // framework won't be able to reset your device since the application must first
    // release all device resources before resetting.  Likewise, if you don't handle the
    // device created/destroyed callbacks then DXUT won't be able to
    // recreate your device resources.
    DXUTSetCallbackDeviceCreated( OnCreateDevice );
    DXUTSetCallbackDeviceReset( OnResetDevice );
    DXUTSetCallbackDeviceLost( OnLostDevice );
    DXUTSetCallbackDeviceDestroyed( OnDestroyDevice );
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackKeyboard( KeyboardProc );
    DXUTSetCallbackFrameRender( OnFrameRender );
    DXUTSetCallbackFrameMove( OnFrameMove );

    // Show the cursor and clip it when in full screen
    DXUTSetCursorSettings( true, true );

    InitApp();

    // Initialize DXUT and create the desired Win32 window and Direct3D
    // device for the application. Calling each of these functions is optional, but they
    // allow you to set several options which control the behavior of the framework.
    DXUTInit( true, true, true ); // Parse the command line, handle the default hotkeys, and show msgboxes
    DXUTCreateWindow( L"ClipMapPS20" );
    DXUTCreateDevice( D3DADAPTER_DEFAULT, true, 640, 480, IsDeviceAcceptable, ModifyDeviceSettings );

    // Pass control to DXUT for handling the message pump and
    // dispatching render calls. DXUT will call your FrameMove
    // and FrameRender callback when there is idle time between handling window messages.
    DXUTMainLoop();

    // Perform any application-level cleanup here. Direct3D device resources are released within the
    // appropriate callback functions and therefore don't require any cleanup code here.

    return DXUTGetExitCode();
}


//--------------------------------------------------------------------------------------
// Initialize the app
//--------------------------------------------------------------------------------------
void InitApp()
{
    g_bEnablePreshader = true;

    // Initialize dialogs
    g_SettingsDlg.Init( &g_DialogResourceManager );
    g_HUD.Init( &g_DialogResourceManager );
    g_SampleUI.Init( &g_DialogResourceManager );

    g_HUD.SetCallback( OnGUIEvent ); int iY = 10;
    g_HUD.AddButton( IDC_TOGGLEFULLSCREEN, L"Toggle full screen", 35, iY, 125, 22 );
    g_HUD.AddButton( IDC_TOGGLEREF, L"Toggle REF (F3)", 35, iY += 24, 125, 22 );
    g_HUD.AddButton( IDC_CHANGEDEVICE, L"Change device (F2)", 35, iY += 24, 125, 22, VK_F2 );

    CDXUTComboBox *box = NULL;
    g_HUD.AddComboBox( IDC_CLIPMAP_MODE, 35, iY += 24, 125, 22, 0, false, &box);

    box->AddItem( L"Normal ClipMap", (void*)1);
    box->AddItem( L"Debug ClipMap", (void*)0);

    g_HUD.AddStatic( IDC_CLIPMAP_X_LABEL, L"X Center:", -40, iY+24, 70, 22, 0);
    g_HUD.AddSlider( IDC_CLIPMAP_X, 35, iY += 24, 125, 22, 0, 1024, 512);
    g_HUD.AddStatic( IDC_CLIPMAP_Y_LABEL, L"Y Center:", -40, iY+24, 70, 22, 0);
    g_HUD.AddSlider( IDC_CLIPMAP_Y, 35, iY += 24, 125, 22, 0, 1024, 512);

    g_SampleUI.SetCallback( OnGUIEvent ); iY = 10;
}


//--------------------------------------------------------------------------------------
// Called during device initialization, this code checks the device for some
// minimum set of capabilities, and rejects those that don't pass by returning E_FAIL.
//--------------------------------------------------------------------------------------
bool CALLBACK IsDeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat,
                                  D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
{
    // No fallback defined by this app, so reject any device that
    // doesn't support at least ps1.1
    if( pCaps->PixelShaderVersion < D3DPS_VERSION(1,1) )
        return false;

    // Skip backbuffer formats that don't support alpha blending
    IDirect3D9* pD3D = DXUTGetD3DObject();
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                    AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
                    D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;

    return true;
}


//--------------------------------------------------------------------------------------
// This callback function is called immediately before a device is created to allow the
// application to modify the device settings. The supplied pDeviceSettings parameter
// contains the settings that the framework has selected for the new device, and the
// application can make any desired changes directly to this structure.  Note however that
// DXUT will not correct invalid device settings so care must be taken
// to return valid device settings, otherwise IDirect3D9::CreateDevice() will fail.
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps, void* pUserContext )
{
    // If device doesn't support HW T&L or doesn't support 1.1 vertex shaders in HW
    // then switch to SWVP.
    if( (pCaps->DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
         pCaps->VertexShaderVersion < D3DVS_VERSION(1,1) )
    {
        pDeviceSettings->BehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
    }

    // Debugging vertex shaders requires either REF or software vertex processing
    // and debugging pixel shaders requires REF.
#ifdef DEBUG_VS
    if( pDeviceSettings->DeviceType != D3DDEVTYPE_REF )
    {
        pDeviceSettings->BehaviorFlags &= ~D3DCREATE_HARDWARE_VERTEXPROCESSING;
        pDeviceSettings->BehaviorFlags &= ~D3DCREATE_PUREDEVICE;
        pDeviceSettings->BehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
    }
#endif
#ifdef DEBUG_PS
    pDeviceSettings->DeviceType = D3DDEVTYPE_REF;
#endif
    // For the first device created if its a REF device, optionally display a warning dialog box
    static bool s_bFirstTime = true;
    if( s_bFirstTime )
    {
        s_bFirstTime = false;
        if( pDeviceSettings->DeviceType == D3DDEVTYPE_REF )
            DXUTDisplaySwitchingToREFWarning();
    }

    return true;
}


//--------------------------------------------------------------------------------------
// This callback function will be called immediately after the Direct3D device has been
// created, which will happen during application initialization and windowed/full screen
// toggles. This is the best location to create D3DPOOL_MANAGED resources since these
// resources need to be reloaded whenever the device is destroyed. Resources created
// here should be released in the OnDestroyDevice callback.
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
    HRESULT hr;

    V_RETURN( g_DialogResourceManager.OnCreateDevice( pd3dDevice ) );
    V_RETURN( g_SettingsDlg.OnCreateDevice( pd3dDevice ) );
    // Initialize the font
    V_RETURN( D3DXCreateFont( pd3dDevice, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
                              OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                              L"Arial", &g_pFont ) );

    // Load the mesh
    V_RETURN( LoadMesh( pd3dDevice, L"heightfield.x", &g_pMesh ) );

    D3DXVECTOR3* pData;
    D3DXVECTOR3 vCenter;
    FLOAT fObjectRadius;
    V( g_pMesh->LockVertexBuffer( 0, (LPVOID*) &pData ) );
    V( D3DXComputeBoundingSphere( pData, g_pMesh->GetNumVertices(), D3DXGetFVFVertexSize( g_pMesh->GetFVF() ), &vCenter, &fObjectRadius ) );
    V( g_pMesh->UnlockVertexBuffer() );

    D3DXMatrixTranslation( &g_mCenterWorld, -vCenter.x, -vCenter.y, -vCenter.z );
    D3DXMATRIXA16 m;
    D3DXMatrixRotationY( &m, D3DX_PI );
    g_mCenterWorld *= m;
    D3DXMatrixRotationX( &m, D3DX_PI / 2.0f );
    g_mCenterWorld *= m;

    // Define DEBUG_VS and/or DEBUG_PS to debug vertex and/or pixel shaders with the
    // shader debugger. Debugging vertex shaders requires either REF or software vertex
    // processing, and debugging pixel shaders requires REF.  The
    // D3DXSHADER_FORCE_*_SOFTWARE_NOOPT flag improves the debug experience in the
    // shader debugger.  It enables source level debugging, prevents instruction
    // reordering, prevents dead code elimination, and forces the compiler to compile
    // against the next higher available software target, which ensures that the
    // unoptimized shaders do not exceed the shader model limitations.  Setting these
    // flags will cause slower rendering since the shaders will be unoptimized and
    // forced into software.  See the DirectX documentation for more information about
    // using the shader debugger.
    DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;

    #if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows
    // the shaders to be optimized and to run exactly the way they will run in
    // the release configuration of this program.
    dwShaderFlags |= D3DXSHADER_DEBUG;
    #endif

    #ifdef DEBUG_VS
        dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
    #endif
    #ifdef DEBUG_PS
        dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
    #endif

    // Preshaders are parts of the shader that the effect system pulls out of the
    // shader and runs on the host CPU. They should be used if you are GPU limited.
    // The D3DXSHADER_NO_PRESHADER flag disables preshaders.
    if( !g_bEnablePreshader )
        dwShaderFlags |= D3DXSHADER_NO_PRESHADER;

    // Read the D3DX effect file
    WCHAR str[MAX_PATH];
    V_RETURN( DXUTFindDXSDKMediaFileCch( str, MAX_PATH, L"ClipMapPS20.fx" ) );

    // If this fails, there should be debug output as to
    // why the .fx file failed to compile
    V_RETURN( D3DXCreateEffectFromFile( pd3dDevice, str, NULL, NULL, dwShaderFlags, NULL, &g_pEffect, NULL ) );

    // Create the mesh texture from a file
    V_RETURN( DXUTFindDXSDKMediaFileCch( str, MAX_PATH, L"misc\\linear.dds" ) );

    V_RETURN( D3DXCreateTextureFromFileEx( pd3dDevice, str, D3DX_DEFAULT, D3DX_DEFAULT,
                                       D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
                                       D3DX_DEFAULT, D3DX_DEFAULT, 0,
                                       NULL, NULL, &g_pMeshTexture ) );

    // Set effect variables as needed
    V_RETURN( g_pEffect->SetTexture( "clipTexture0", g_pMeshTexture) );
    V_RETURN( g_pEffect->SetTexture( "clipTexture1", g_pMeshTexture) );
    V_RETURN( g_pEffect->SetTexture( "clipTexture2", g_pMeshTexture) );
    V_RETURN( g_pEffect->SetTexture( "clipTexture3", g_pMeshTexture) );
    V_RETURN( g_pEffect->SetTexture( "clipTexture4", g_pMeshTexture) );

    // Setup the camera's view parameters
    D3DXVECTOR3 vecEye(0.0f, 0.0f, -15.0f);
    D3DXVECTOR3 vecAt (0.0f, 0.0f, -0.0f);
    g_Camera.SetViewParams( &vecEye, &vecAt );
    g_Camera.SetRadius( fObjectRadius*3.0f, fObjectRadius*0.5f, fObjectRadius*10.0f );

    // Initialize the clipmap.
    gClipMap.alloc(pd3dDevice);
    gClipMap.bindTextures();

    return S_OK;
}

//--------------------------------------------------------------------------------------
// This function loads the mesh and ensures the mesh has normals; it also optimizes the
// mesh for the graphics card's vertex cache, which improves performance by organizing
// the internal triangle list for less cache misses.
//--------------------------------------------------------------------------------------
HRESULT LoadMesh( IDirect3DDevice9* pd3dDevice, WCHAR* strFileName, ID3DXMesh** ppMesh )
{
    ID3DXMesh* pMesh = NULL;
    WCHAR str[MAX_PATH];
    HRESULT hr;

    // Load the mesh with D3DX and get back a ID3DXMesh*.  For this
    // sample we'll ignore the X file's embedded materials since we know
    // exactly the model we're loading.  See the mesh samples such as
    // "OptimizedMesh" for a more generic mesh loading example.
    V_RETURN( DXUTFindDXSDKMediaFileCch( str, MAX_PATH, strFileName ) );
    V_RETURN( D3DXLoadMeshFromX(str, D3DXMESH_MANAGED, pd3dDevice, NULL, NULL, NULL, NULL, &pMesh) );

    DWORD *rgdwAdjacency = NULL;

    // Make sure there are normals which are required for lighting
    if( !(pMesh->GetFVF() & D3DFVF_NORMAL) )
    {
        ID3DXMesh* pTempMesh;
        V( pMesh->CloneMeshFVF( pMesh->GetOptions(),
                                  pMesh->GetFVF() | D3DFVF_NORMAL,
                                  pd3dDevice, &pTempMesh ) );
        V( D3DXComputeNormals( pTempMesh, NULL ) );

        SAFE_RELEASE( pMesh );
        pMesh = pTempMesh;
    }

    // Optimize the mesh for this graphics card's vertex cache
    // so when rendering the mesh's triangle list the vertices will
    // cache hit more often so it won't have to re-execute the vertex shader
    // on those vertices so it will improve perf.
    rgdwAdjacency = new DWORD[pMesh->GetNumFaces() * 3];
    if( rgdwAdjacency == NULL )
        return E_OUTOFMEMORY;
    V( pMesh->GenerateAdjacency(1e-6f,rgdwAdjacency) );
    V( pMesh->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE, rgdwAdjacency, NULL, NULL, NULL) );
    delete []rgdwAdjacency;

    *ppMesh = pMesh;

    return S_OK;
}


//--------------------------------------------------------------------------------------
// This callback function will be called immediately after the Direct3D device has been
// reset, which will happen after a lost device scenario. This is the best location to
// create D3DPOOL_DEFAULT resources since these resources need to be reloaded whenever
// the device is lost. Resources created here should be released in the OnLostDevice
// callback.
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnResetDevice( IDirect3DDevice9* pd3dDevice,
                                const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
    HRESULT hr;

    gClipMap.reset();
    gClipMap.alloc(DXUTGetD3DDevice());

    V_RETURN( g_DialogResourceManager.OnResetDevice() );
    V_RETURN( g_SettingsDlg.OnResetDevice() );

    if( g_pFont )
        V_RETURN( g_pFont->OnResetDevice() );
    if( g_pEffect )
        V_RETURN( g_pEffect->OnResetDevice() );

    // Create a sprite to help batch calls when drawing many lines of text
    V_RETURN( D3DXCreateSprite( pd3dDevice, &g_pSprite ) );

    // Setup the camera's projection parameters
    float fAspectRatio = pBackBufferSurfaceDesc->Width / (FLOAT)pBackBufferSurfaceDesc->Height;
    g_Camera.SetProjParams( D3DX_PI/4, fAspectRatio, 2.0f, 4000.0f );
    g_Camera.SetWindow( pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height );
    g_Camera.SetButtonMasks( MOUSE_LEFT_BUTTON, MOUSE_WHEEL, MOUSE_MIDDLE_BUTTON );

    g_HUD.SetLocation( pBackBufferSurfaceDesc->Width-170, 0 );
    g_HUD.SetSize( 170, 170 );
    g_SampleUI.SetLocation( pBackBufferSurfaceDesc->Width-170, pBackBufferSurfaceDesc->Height-300 );
    g_SampleUI.SetSize( 170, 300 );

    return S_OK;
}


//--------------------------------------------------------------------------------------
// This callback function will be called once at the beginning of every frame. This is the
// best location for your application to handle updates to the scene, but is not
// intended to contain actual rendering calls, which should instead be placed in the
// OnFrameRender callback.
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    // Update the camera's position based on user input
    g_Camera.FrameMove( fElapsedTime );
}


//--------------------------------------------------------------------------------------
// This callback function will be called at the end of every frame to perform all the
// rendering calls for the scene, and it will also be called if the window needs to be
// repainted. After this function has returned, DXUT will call
// IDirect3DDevice9::Present to display the contents of the next buffer in the swap chain
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    // If the settings dialog is being shown, then
    // render it instead of rendering the app's scene
    if( g_SettingsDlg.IsActive() )
    {
        g_SettingsDlg.OnRender( fElapsedTime );
        return;
    }

    HRESULT hr;
    D3DXMATRIXA16 mWorldViewProjection;
    UINT iPass, cPasses;
    D3DXMATRIXA16 mWorld;
    D3DXMATRIXA16 mView;
    D3DXMATRIXA16 mProj;

    // Clear the render target and the zbuffer
    V( pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f,0.25f,0.25f,0.55f), 1.0f, 0) );

    // Render the scene
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
        // Get the projection & view matrix from the camera class
        mWorld = g_mCenterWorld * *g_Camera.GetWorldMatrix();
        mProj = *g_Camera.GetProjMatrix();
        mView = *g_Camera.GetViewMatrix();

        mWorldViewProjection = mWorld * mView * mProj;

        // Update the effect's variables.  Instead of using strings, it would
        // be more efficient to cache a handle to the parameter by calling
        // ID3DXEffect::GetParameterByName
        V( g_pEffect->SetMatrix( "g_mWorldViewProjection", &mWorldViewProjection ) );
        V( g_pEffect->SetMatrix( "g_mWorld", &mWorld ) );

        // Update clipmap state.

        CDXUTSlider *sliderX = g_HUD.GetSlider(IDC_CLIPMAP_X);
        CDXUTSlider *sliderY = g_HUD.GetSlider(IDC_CLIPMAP_Y);

        gClipMap.recenter(float(sliderX->GetValue()) / 1024.f, float(sliderY->GetValue()) / 1024.f);
        gClipMap.updateEffectParams();

        // Render the scene with this technique
        // as defined in the .fx file
        V( g_pEffect->SetTechnique( "RenderClipMapPS2" ) );

        // Apply the technique contained in the effect
        V( g_pEffect->Begin(&cPasses, 0) );

        for (iPass = 0; iPass < cPasses; iPass++)
        {
            V( g_pEffect->BeginPass(iPass) );

            // The effect interface queues up the changes and performs them
            // with the CommitChanges call. You do not need to call CommitChanges if
            // you are not setting any parameters between the BeginPass and EndPass.
            // V( g_pEffect->CommitChanges() );

            // Render the mesh with the applied technique
            V( g_pMesh->DrawSubset(0) );

            V( g_pEffect->EndPass() );
        }
        V( g_pEffect->End() );

        g_HUD.OnRender( fElapsedTime );
        g_SampleUI.OnRender( fElapsedTime );

        RenderText( fTime );

        V( pd3dDevice->EndScene() );
    }
}


//--------------------------------------------------------------------------------------
// Render the help and statistics text. This function uses the ID3DXFont interface for
// efficient text rendering.
//--------------------------------------------------------------------------------------
void RenderText( double fTime )
{
    // The helper object simply helps keep track of text position, and color
    // and then it calls pFont->DrawText( m_pSprite, strMsg, -1, &rc, DT_NOCLIP, m_clr );
    // If NULL is passed in as the sprite object, then it will work fine however the
    // pFont->DrawText() will not be batched together.  Batching calls will improves perf.
    CDXUTTextHelper txtHelper( g_pFont, g_pSprite, 15 );

    // Output statistics
    txtHelper.Begin();
    txtHelper.SetInsertionPos( 2, 0 );
    txtHelper.SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
    txtHelper.DrawTextLine( DXUTGetFrameStats() );
    txtHelper.DrawTextLine( DXUTGetDeviceStats() );

    txtHelper.SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    //txtHelper.DrawFormattedTextLine( L"fTime: %0.1f  sin(fTime): %0.4f", fTime, sin(fTime) );

    // Draw help
    if( g_bShowHelp )
    {
        const D3DSURFACE_DESC* pd3dsdBackBuffer = DXUTGetBackBufferSurfaceDesc();
        txtHelper.SetInsertionPos( 2, pd3dsdBackBuffer->Height-15*6 );
        txtHelper.SetForegroundColor( D3DXCOLOR(1.0f, 0.75f, 0.0f, 1.0f ) );
        txtHelper.DrawTextLine( L"Controls:" );

        txtHelper.SetInsertionPos( 20, pd3dsdBackBuffer->Height-15*5 );
        txtHelper.DrawTextLine( L"Rotate model: Left mouse button\n"
                                L"Zoom camera: Mouse wheel scroll\n" );

        txtHelper.SetInsertionPos( 250, pd3dsdBackBuffer->Height-15*5 );
        txtHelper.DrawTextLine( L"Hide help: F1\n"
                                L"Quit: ESC\n" );
    }
    else
    {
        txtHelper.SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
        txtHelper.DrawTextLine( L"Press F1 for help" );
    }
    txtHelper.End();
}


//--------------------------------------------------------------------------------------
// Before handling window messages, DXUT passes incoming windows
// messages to the application through this callback function. If the application sets
// *pbNoFurtherProcessing to TRUE, then DXUT will not process this message.
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext )
{
    // Always allow dialog resource manager calls to handle global messages
    // so GUI state is updated correctly
    *pbNoFurtherProcessing = g_DialogResourceManager.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;

    if( g_SettingsDlg.IsActive() )
    {
        g_SettingsDlg.MsgProc( hWnd, uMsg, wParam, lParam );
        return 0;
    }

    // Give the dialogs a chance to handle the message first
    *pbNoFurtherProcessing = g_HUD.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;
    *pbNoFurtherProcessing = g_SampleUI.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;

    // Pass all remaining windows messages to camera so it can respond to user input
    g_Camera.HandleMessages( hWnd, uMsg, wParam, lParam );

    return 0;
}


//--------------------------------------------------------------------------------------
// As a convenience, DXUT inspects the incoming windows messages for
// keystroke messages and decodes the message parameters to pass relevant keyboard
// messages to the application.  The framework does not remove the underlying keystroke
// messages, which are still passed to the application's MsgProc callback.
//--------------------------------------------------------------------------------------
void CALLBACK KeyboardProc( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext )
{
    if( bKeyDown )
    {
        switch( nChar )
        {
            case VK_F1: g_bShowHelp = !g_bShowHelp; break;
        }
    }
}


//--------------------------------------------------------------------------------------
// Handles the GUI events
//--------------------------------------------------------------------------------------
void CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext )
{

    switch( nControlID )
    {
        case IDC_TOGGLEFULLSCREEN: DXUTToggleFullScreen(); break;
        case IDC_TOGGLEREF:        DXUTToggleREF(); break;
        case IDC_CHANGEDEVICE:     g_SettingsDlg.SetActive( !g_SettingsDlg.IsActive() ); break;

        case IDC_ENABLE_PRESHADER:
        {
            g_bEnablePreshader = g_SampleUI.GetCheckBox( IDC_ENABLE_PRESHADER )->GetChecked();

            if( DXUTGetD3DDevice() != NULL )
            {
                OnLostDevice( NULL );
                OnDestroyDevice( NULL );
                OnCreateDevice( DXUTGetD3DDevice(), DXUTGetBackBufferSurfaceDesc(), NULL );
                OnResetDevice( DXUTGetD3DDevice(), DXUTGetBackBufferSurfaceDesc(), NULL );
            }
            break;
        }

        case IDC_CLIPMAP_MODE:
         {
            CDXUTComboBox *box = g_HUD.GetComboBox(IDC_CLIPMAP_MODE);
            HRESULT hr;
            if(box->GetSelectedItem()->pData == 0)
            {
               // Set to the debug texture
               V( g_pEffect->SetTexture( "clipTexture0", g_pMeshTexture) );
               V( g_pEffect->SetTexture( "clipTexture1", g_pMeshTexture) );
               V( g_pEffect->SetTexture( "clipTexture2", g_pMeshTexture) );
               V( g_pEffect->SetTexture( "clipTexture3", g_pMeshTexture) );
               V( g_pEffect->SetTexture( "clipTexture4", g_pMeshTexture) );
            }
            else
            {
               // Set to the clipmap textures
               gClipMap.alloc(DXUTGetD3DDevice());
               gClipMap.bindTextures();
            }
            break;
         }
    }
}


//--------------------------------------------------------------------------------------
// This callback function will be called immediately after the Direct3D device has
// entered a lost state and before IDirect3DDevice9::Reset is called. Resources created
// in the OnResetDevice callback should be released here, which generally includes all
// D3DPOOL_DEFAULT resources. See the "Lost Devices" section of the documentation for
// information about lost devices.
//--------------------------------------------------------------------------------------
void CALLBACK OnLostDevice( void* pUserContext )
{
    g_DialogResourceManager.OnLostDevice();
    g_SettingsDlg.OnLostDevice();
    CDXUTDirectionWidget::StaticOnLostDevice();
    if( g_pFont )
        g_pFont->OnLostDevice();
    if( g_pEffect )
        g_pEffect->OnLostDevice();
    SAFE_RELEASE(g_pSprite);

}


//--------------------------------------------------------------------------------------
// This callback function will be called immediately after the Direct3D device has
// been destroyed, which generally happens as a result of application termination or
// windowed/full screen toggles. Resources created in the OnCreateDevice callback
// should be released here, which generally includes all D3DPOOL_MANAGED resources.
//--------------------------------------------------------------------------------------
void CALLBACK OnDestroyDevice( void* pUserContext )
{
    g_DialogResourceManager.OnDestroyDevice();
    g_SettingsDlg.OnDestroyDevice();
    CDXUTDirectionWidget::StaticOnDestroyDevice();
    SAFE_RELEASE(g_pEffect);
    SAFE_RELEASE(g_pFont);
    SAFE_RELEASE(g_pMesh);
    SAFE_RELEASE(g_pMeshTexture);

    gClipMap.reset();
}



