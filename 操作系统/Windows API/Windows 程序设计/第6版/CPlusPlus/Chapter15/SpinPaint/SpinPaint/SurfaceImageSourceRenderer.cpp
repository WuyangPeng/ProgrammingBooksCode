#include "pch.h"
#include "SurfaceImageSourceRenderer.h"

using namespace SpinPaint;

using namespace Microsoft::WRL;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI;
using namespace Windows::UI::Xaml::Media::Imaging;

SurfaceImageSourceRenderer::SurfaceImageSourceRenderer(SurfaceImageSource^ surfaceImageSource, int width, int height)
{
    // Save the image width and height
    this->width = width;
    this->height = height;

    // Create Factory
    D2D1_FACTORY_OPTIONS options = { D2D1_DEBUG_LEVEL_NONE };

    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
                                   __uuidof(ID2D1Factory),
                                   &options,
                                   &pFactory);    
    if (!SUCCEEDED(hr))
        throw ref new COMException(hr);

    // Create ISurfaceImageSourceNative object
    IInspectable* sisInspectable = (IInspectable*) reinterpret_cast<IInspectable*>(surfaceImageSource);
    sisInspectable->QueryInterface(__uuidof(ISurfaceImageSourceNative), (void **)&sisNative);

    // Create Device and Device Context
    D3D_FEATURE_LEVEL featureLevels[] = 
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    hr = D3D11CreateDevice(nullptr,
                           D3D_DRIVER_TYPE_HARDWARE,
                           0,
                           D3D11_CREATE_DEVICE_SINGLETHREADED | 
                                    D3D11_CREATE_DEVICE_BGRA_SUPPORT,
                           featureLevels,
                           ARRAYSIZE(featureLevels),
                           D3D11_SDK_VERSION,
                           &pd3dDevice,
                           nullptr,
                           &pd3dContext);

    if (!SUCCEEDED(hr))
        throw ref new COMException(hr);

    // Get DXGIDevice
    hr = pd3dDevice.As(&pDxgiDevice);

    if (!SUCCEEDED(hr))
        throw ref new COMException(hr);

    sisNative->SetDevice(pDxgiDevice.Get());

    // Begin drawing
    RECT update = { 0, 0, width, height };
    POINT offset;
    IDXGISurface * dxgiSurface;
    hr = sisNative->BeginDraw(update, &dxgiSurface, &offset);

    if (!SUCCEEDED(hr))
        throw ref new COMException(hr);

    ID2D1RenderTarget * pRenderTarget = CreateRenderTarget(dxgiSurface);

    // But only go far enough to create compatible BitmapRenderTarget 
    //      and get the Bitmap for updating the surface
    pRenderTarget->CreateCompatibleRenderTarget(&bitmapRenderTarget);
    bitmapRenderTarget->GetBitmap(&bitmap);

    // End drawing
    sisNative->EndDraw();
    pRenderTarget->Release();
    dxgiSurface->Release();
}

void SurfaceImageSourceRenderer::Update()
{
    // Begin drawing
    RECT update = { 0, 0, width, height };
    POINT offset;
    IDXGISurface * dxgiSurface;
    HRESULT hr = sisNative->BeginDraw(update, &dxgiSurface, &offset);

    if (!SUCCEEDED(hr))
        throw ref new COMException(hr);

    ID2D1RenderTarget * renderTarget = CreateRenderTarget(dxgiSurface);
    renderTarget->BeginDraw();

    // Draw the bitmap to the surface
    D2D1_RECT_F rect = { 0, 0, (float)width, (float)height };
    renderTarget->DrawBitmap(bitmap.Get(), &rect);

    // End drawing
    renderTarget->EndDraw();
    sisNative->EndDraw();

    // Release update resources
    renderTarget->Release();
    dxgiSurface->Release();
}

ID2D1RenderTarget * SurfaceImageSourceRenderer::CreateRenderTarget(ComPtr<IDXGISurface> pSurface)
{
    D2D1_PIXEL_FORMAT format = 
    {
        DXGI_FORMAT_UNKNOWN,
        D2D1_ALPHA_MODE_PREMULTIPLIED
    };

    float dpiX, dpiY;
    pFactory->GetDesktopDpi(&dpiX, &dpiY);

    D2D1_RENDER_TARGET_PROPERTIES properties = 
    {
        D2D1_RENDER_TARGET_TYPE_DEFAULT,
        format,
        dpiX,
        dpiY,
        D2D1_RENDER_TARGET_USAGE_NONE,
        D2D1_FEATURE_LEVEL_DEFAULT
    };

    ID2D1RenderTarget * pRenderTarget;
    HRESULT hr = pFactory->CreateDxgiSurfaceRenderTarget(pSurface.Get(), &properties, &pRenderTarget);

    if (!SUCCEEDED(hr))
        throw ref new COMException(hr);

    return pRenderTarget;
}

