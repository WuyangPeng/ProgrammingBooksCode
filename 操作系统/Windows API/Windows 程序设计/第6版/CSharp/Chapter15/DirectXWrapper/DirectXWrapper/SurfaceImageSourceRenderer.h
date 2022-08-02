#pragma once

namespace DirectXWrapper
{
    public ref class SurfaceImageSourceRenderer sealed
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
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> solidColorBrush;
        Microsoft::WRL::ComPtr<ID2D1StrokeStyle> strokeStyle;
        bool needsUpdate;

    public:
        SurfaceImageSourceRenderer(
                Windows::UI::Xaml::Media::Imaging::SurfaceImageSource^ surfaceImageSource, 
                int width, int height);
        void Clear(Windows::UI::Color color);
        void DrawLine(Windows::Foundation::Point pt1, Windows::Foundation::Point pt2, 
                      Windows::UI::Color color, double thickness);
        void Update();

    private:
        ID2D1RenderTarget * CreateRenderTarget(Microsoft::WRL::ComPtr<IDXGISurface> pSurface);
        D2D1::ColorF ConvertColor(Windows::UI::Color color);
    };
}
