#pragma once

namespace SpinPaint
{
    ref class SurfaceImageSourceRenderer sealed
    {
    private:
        int width, height;
        Microsoft::WRL::ComPtr<ID2D1Factory> pFactory;
        Microsoft::WRL::ComPtr<ID3D11Device> pd3dDevice;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> pd3dContext;
        Microsoft::WRL::ComPtr<ISurfaceImageSourceNative> sisNative;
        Microsoft::WRL::ComPtr<IDXGIDevice> pDxgiDevice;
        Microsoft::WRL::ComPtr<ID2D1BitmapRenderTarget> bitmapRenderTarget;
        Microsoft::WRL::ComPtr<ID2D1Bitmap> bitmap;

    public:
        SurfaceImageSourceRenderer(Windows::UI::Xaml::Media::Imaging::SurfaceImageSource^ surfaceImageSource, int width, int height);
        void Update();
        
    internal:
        // Allows program to access ID2D1Factory for creating stroke style
        property Microsoft::WRL::ComPtr<ID2D1Factory> Factory
        {
            Microsoft::WRL::ComPtr<ID2D1Factory> get() { return pFactory; }
        }

        // Allows program to access ID2D1BitmapRenderTarget for creating brush and drawing lines
        property Microsoft::WRL::ComPtr<ID2D1BitmapRenderTarget> RenderTarget
        {
            Microsoft::WRL::ComPtr<ID2D1BitmapRenderTarget> get() { return bitmapRenderTarget; }
        }

    private:
        ID2D1RenderTarget * CreateRenderTarget(Microsoft::WRL::ComPtr<IDXGISurface> pSurface);
    };
}
