#include "pch.h"
#include "SurfaceImageSourceRenderer.h"

using namespace DirectXWrapper;

using namespace Microsoft::WRL;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI;
using namespace Windows::UI::Xaml::Media::Imaging;

SurfaceImageSourceRenderer::SurfaceImageSourceRenderer(SurfaceImageSource^ surfaceImageSource, 
                                                       int width, int height)
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
    IInspectable* sisInspectable = (IInspectable*) 
                                        reinterpret_cast<IInspectable*>(surfaceImageSource);
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

    // Create a SolidColorBrush for drawing lines
    bitmapRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &solidColorBrush);

    // Create StrokeStyle for drawing lines
    D2D1_STROKE_STYLE_PROPERTIES strokeStyleProperties = 
    {
        D2D1_CAP_STYLE_ROUND,
        D2D1_CAP_STYLE_ROUND,
        D2D1_CAP_STYLE_ROUND,
        D2D1_LINE_JOIN_ROUND,
        10,
        D2D1_DASH_STYLE_SOLID,
        0
    };

    hr = pFactory->CreateStrokeStyle(&strokeStyleProperties, nullptr, 0, &strokeStyle);

    if (!SUCCEEDED(hr))
        throw ref new COMException(hr);
}

void SurfaceImageSourceRenderer::Clear(Color color)
{
    bitmapRenderTarget->BeginDraw();
    bitmapRenderTarget->Clear(ConvertColor(color));
    bitmapRenderTarget->EndDraw();
    needsUpdate = true;
}

void SurfaceImageSourceRenderer::DrawLine(Point point1, Point point2, 
                                          Color color, double thickness)
{
    // Convert the points
    D2D1_POINT_2F pt1 = { (float)point1.X, (float)point1.Y };
    D2D1_POINT_2F pt2 = { (float)point2.X, (float)point2.Y };

    // Convert the color for the SolidColorBrush
    solidColorBrush->SetColor(ConvertColor(color));

    // Draw the line
    bitmapRenderTarget->BeginDraw();
    bitmapRenderTarget->DrawLine(pt1, pt2, solidColorBrush.Get(), 
                                           (float)thickness, 
                                           strokeStyle.Get());
    bitmapRenderTarget->EndDraw();
    needsUpdate = true;
}

void SurfaceImageSourceRenderer::Update()
{
    // Check if needs update
    if (!needsUpdate)
        return;

    needsUpdate = false;

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
    HRESULT hr = pFactory->CreateDxgiSurfaceRenderTarget(pSurface.Get(), 
                                                &properties, &pRenderTarget);

    if (!SUCCEEDED(hr))
        throw ref new COMException(hr);

    return pRenderTarget;
}

D2D1::ColorF SurfaceImageSourceRenderer::ConvertColor(Color color)
{
    D2D1::ColorF colorf(color.R / 255.0f,
                        color.G / 255.0f,
                        color.B / 255.0f,
                        color.A / 255.0f);
    return colorf;
}

