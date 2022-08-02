using System;
using System.IO;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using Windows.ApplicationModel.DataTransfer;
using Windows.Graphics.Imaging;
using Windows.Storage.Streams;
using Windows.System;
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;

namespace FingerPaint
{
    public sealed partial class MainPage : Page
    {
        int pastedPixelWidth, pastedPixelHeight;
        byte[] pastedPixels;

        void InitializeSharing()
        {
            // Initialize the Paste button and provide for updates
            CheckForPasteEnable();
            Clipboard.ContentChanged += OnClipboardContentChanged;

            // Watch for accelerator keys for Copy and Paste
            Window.Current.CoreWindow.Dispatcher.AcceleratorKeyActivated += 
                                                                    OnAcceleratorKeyActivated;

            // Hook into the Share pane for providing data
            DataTransferManager.GetForCurrentView().DataRequested += OnDataTransferDataRequested;
        }

        async void OnDataTransferDataRequested(DataTransferManager sender, DataRequestedEventArgs args)
        {
            DataRequestDeferral deferral = args.Request.GetDeferral();

            // Get a stream reference and hand it over
            RandomAccessStreamReference reference = await GetBitmapStream(bitmap);
            args.Request.Data.SetBitmap(reference);
            args.Request.Data.Properties.Title = "Finger Paint";
            args.Request.Data.Properties.Description = "Share this painting with another app";

            deferral.Complete();
        }

        void OnClipboardContentChanged(object sender, object args)
        {
            CheckForPasteEnable();
        }

        void CheckForPasteEnable()
        {
            pasteAppBarButton.IsEnabled = CheckClipboardForBitmap();
        }

        bool CheckClipboardForBitmap()
        {
            DataPackageView dataView = Clipboard.GetContent();
            return dataView.Contains(StandardDataFormats.Bitmap);
        }

        async void OnCopyAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            DataPackage dataPackage = new DataPackage
            {
                 RequestedOperation = DataPackageOperation.Move,
            };
            dataPackage.SetBitmap(await GetBitmapStream(bitmap));

            Clipboard.SetContent(dataPackage);
            this.BottomAppBar.IsOpen = false;
        }

        async Task<RandomAccessStreamReference> GetBitmapStream(WriteableBitmap bitmap)
        {
            // Get a pixels array for this bitmap
            byte[] pixels = new byte[4 * bitmap.PixelWidth * bitmap.PixelHeight];
            Stream stream = bitmap.PixelBuffer.AsStream();
            await stream.ReadAsync(pixels, 0, pixels.Length);

            // Create a BitmapEncoder associated with a memory stream
            InMemoryRandomAccessStream memoryStream = new InMemoryRandomAccessStream();
            BitmapEncoder encoder = await BitmapEncoder.CreateAsync(BitmapEncoder.PngEncoderId, 
                                                                    memoryStream);

            // Set the pixels into that encoder
            encoder.SetPixelData(BitmapPixelFormat.Bgra8, BitmapAlphaMode.Premultiplied,
                                 (uint)bitmap.PixelWidth, (uint)bitmap.PixelHeight, 96, 96, pixels);
            await encoder.FlushAsync();

            // Return a RandomAccessStreamReference
            return RandomAccessStreamReference.CreateFromStream(memoryStream);
        }

        async void OnPasteAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            // Temporarily disable the Paste button
            Button button = sender as Button;
            button.IsEnabled = false;

            // Get the Clipboard contents and check for a bitmap
            DataPackageView dataView = Clipboard.GetContent();

            if (dataView.Contains(StandardDataFormats.Bitmap))
            {
                // Get the stream reference and a stream
                RandomAccessStreamReference streamRef = await dataView.GetBitmapAsync();
                IRandomAccessStreamWithContentType stream = await streamRef.OpenReadAsync();

                // Create a BitmapDecoder for reading the bitmap
                BitmapDecoder decoder = await BitmapDecoder.CreateAsync(stream);
                BitmapFrame bitmapFrame = await decoder.GetFrameAsync(0);
                PixelDataProvider pixelProvider = 
                    await bitmapFrame.GetPixelDataAsync(BitmapPixelFormat.Bgra8, 
                                                        BitmapAlphaMode.Premultiplied, 
                                                        new BitmapTransform(),
                                                        ExifOrientationMode.RespectExifOrientation, 
                                                        ColorManagementMode.ColorManageToSRgb);

                // Save information sufficient for creating WriteableBitmap
                pastedPixelWidth = (int)bitmapFrame.PixelWidth;
                pastedPixelHeight = (int)bitmapFrame.PixelHeight;
                pastedPixels = pixelProvider.DetachPixelData();

                // Check if it's OK to replace the current painting
                await CheckIfOkToTrashFile(FinishPasteBitmapAndPixelArray);
            }

            // Re-enable the button and close the app bar
            button.IsEnabled = true;
            this.BottomAppBar.IsOpen = false;
        }

        async Task FinishPasteBitmapAndPixelArray()
        {
            bitmap = new WriteableBitmap(pastedPixelWidth, pastedPixelHeight);
            pixels = pastedPixels;

            // Transfer pixels to bitmap, among other chores
            await InitializeBitmap();

            // Set AppSettings properties for new image
            appSettings.LoadedFilePath = null;
            appSettings.LoadedFilename = null;
            appSettings.IsImageModified = false;
        }

        void OnAcceleratorKeyActivated(CoreDispatcher sender, AcceleratorKeyEventArgs args)
        {
            if ((args.EventType == CoreAcceleratorKeyEventType.SystemKeyDown ||
                 args.EventType == CoreAcceleratorKeyEventType.KeyDown) &&
                (args.VirtualKey == VirtualKey.C || args.VirtualKey == VirtualKey.V))
            {
                CoreWindow window = Window.Current.CoreWindow;
                CoreVirtualKeyStates down = CoreVirtualKeyStates.Down;

                // Only want case where Ctrl is down
                if ((window.GetKeyState(VirtualKey.Shift) & down) == down ||
                    (window.GetKeyState(VirtualKey.Control) & down) != down ||
                    (window.GetKeyState(VirtualKey.Menu) & down) == down)
                {
                    return;
                }

                if (args.VirtualKey == VirtualKey.C)
                {
                    OnCopyAppBarButtonClick(null, null);   
                }
                else if (args.VirtualKey == VirtualKey.V)
                {
                    OnPasteAppBarButtonClick(pasteAppBarButton, null);
                }
            }
        }
    }
}
