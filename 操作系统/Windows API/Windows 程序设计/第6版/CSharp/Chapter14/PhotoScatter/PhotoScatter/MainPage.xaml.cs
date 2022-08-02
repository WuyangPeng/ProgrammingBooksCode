using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using Windows.Graphics.Imaging;
using Windows.Storage;
using Windows.Storage.FileProperties;
using Windows.Storage.Streams;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;

namespace PhotoScatter
{
    public sealed partial class MainPage : Page
    {
        Random rand = new Random();

        public MainPage()
        {
            this.InitializeComponent();
            Loaded += OnMainPageLoaded;
        }

        void OnMainPageLoaded(object sender, RoutedEventArgs args)
        {
            StorageFolder storageFolder = KnownFolders.PicturesLibrary;
            BuildFolderListBox(storageFolder, 0);
            folderListBox.SelectedIndex = 0;
        }

        async void BuildFolderListBox(StorageFolder parentStorageFolder, int level)
        {
            FolderItem folderItem = new FolderItem
            {
                StorageFolder = parentStorageFolder,
                Level = level
            };
            folderListBox.Items.Add(folderItem);

            IReadOnlyList<StorageFolder> storageFolders = await parentStorageFolder.GetFoldersAsync();

            foreach (StorageFolder storageFolder in storageFolders)
                BuildFolderListBox(storageFolder, level + 1);
        }

        async void OnFolderListBoxSelectionChanged(object sender, SelectionChangedEventArgs args)
        {
            FolderItem folderItem = (sender as ListBox).SelectedItem as FolderItem;

            if (folderItem == null)
            {
                displayBorder.Child = null;
                return;
            }

            if (folderItem.DisplayGrid != null)
            {
                displayBorder.Child = folderItem.DisplayGrid;
                return;
            }

            Grid displayGrid = new Grid();
            folderItem.DisplayGrid = displayGrid;
            displayBorder.Child = displayGrid;

            StorageFolder storageFolder = folderItem.StorageFolder;
            IReadOnlyList<StorageFile> storageFiles = await storageFolder.GetFilesAsync();

            foreach (StorageFile storageFile in storageFiles)
            {
                StorageItemThumbnail thumbnail = 
                            await storageFile.GetThumbnailAsync(ThumbnailMode.SingleItem);
                BitmapSource bitmap = await LoadBitmapAsync(thumbnail);

                if (bitmap == null)
                    continue;

                // Create new Image element to display the thumbnail
                Image image = new Image
                    {
                        Source = bitmap,
                        Stretch = Stretch.None,
                        Tag = ImageType.Thumbnail
                    };

                // Create an initial CompositeTransform for the item
                CompositeTransform xform = new CompositeTransform();
                xform.TranslateX = (displayBorder.ActualWidth - bitmap.PixelWidth) / 2;
                xform.TranslateY = (displayBorder.ActualHeight - bitmap.PixelHeight) / 2;
                xform.TranslateX += 256 * (0.5 - rand.NextDouble());
                xform.TranslateY += 256 * (0.5 - rand.NextDouble());

                // Create the ManipulableContentControl for the Image
                ManipulableContentControl manipulableControl = new ManipulableContentControl(xform)
                {
                    Content = image,
                    Tag = storageFile
                };
                manipulableControl.ManipulationStarted += OnManipulableControlManipulationStarted;

                // Put it in the Grid
                displayGrid.Children.Add(manipulableControl);
            }
        }

        async void OnManipulableControlManipulationStarted(object sender, 
                                                           ManipulationStartedRoutedEventArgs args)
        {
            ManipulableContentControl manipulableControl = sender as ManipulableContentControl;
            Image image = manipulableControl.Content as Image;

            if ((ImageType)image.Tag == ImageType.Thumbnail)
            {
                // Set tag to transitioning
                image.Tag = ImageType.Transitioning;

                // Load the actual bitmap file
                StorageFile storageFile = manipulableControl.Tag as StorageFile;
                BitmapSource newBitmap = await LoadBitmapAsync(storageFile);

                // This is the case for a file that BitmapDecoder can't handle
                if (newBitmap != null)
                {
                    // Get the thumbnail from the Image element
                    BitmapSource oldBitmap = image.Source as BitmapSource;

                    // Find a ScaleTransform between old and new
                    double scale = 1;

                    if (oldBitmap.PixelWidth > oldBitmap.PixelHeight)
                        scale = (double)oldBitmap.PixelWidth / newBitmap.PixelWidth;
                    else
                        scale = (double)oldBitmap.PixelHeight / newBitmap.PixelHeight;

                    // Set properties on the Image element
                    image.Source = newBitmap;
                    image.RenderTransform = new ScaleTransform
                    {
                        ScaleX = scale,
                        ScaleY = scale,
                    };
                }
                image.Tag = ImageType.Full;
            }
        }

        async Task<BitmapSource> LoadBitmapAsync(StorageFile storageFile)
        {
            BitmapSource bitmapSource = null;

            // Open the StorageFile for reading
            using (IRandomAccessStreamWithContentType stream = await storageFile.OpenReadAsync())
            {
                bitmapSource = await LoadBitmapAsync(stream);
            }

            return bitmapSource;
        }

        async Task<BitmapSource> LoadBitmapAsync(StorageItemThumbnail thumbnail)
        {
            return await LoadBitmapAsync(thumbnail as IRandomAccessStream);
        }

        async Task<BitmapSource> LoadBitmapAsync(IRandomAccessStream stream)
        {
            WriteableBitmap bitmap = null;

            // Create a BitmapDecoder from the stream
            BitmapDecoder decoder = null;

            try
            {
                decoder = await BitmapDecoder.CreateAsync(stream);
            }
            catch
            {
                // Just skip ones that aren't valid
                return null;
            }

            // Get the first frame
            BitmapFrame bitmapFrame = await decoder.GetFrameAsync(0);

            // Get the pixels
            PixelDataProvider dataProvider =
                    await bitmapFrame.GetPixelDataAsync(BitmapPixelFormat.Bgra8,
                                                        BitmapAlphaMode.Premultiplied,
                                                        new BitmapTransform(),
                                                        ExifOrientationMode.RespectExifOrientation,
                                                        ColorManagementMode.ColorManageToSRgb);

            byte[] pixels = dataProvider.DetachPixelData();

            // Create WriteableBitmap and set the pixels
            bitmap = new WriteableBitmap((int)bitmapFrame.PixelWidth,
                                         (int)bitmapFrame.PixelHeight);

            using (Stream pixelStream = bitmap.PixelBuffer.AsStream())
            {
                pixelStream.Write(pixels, 0, pixels.Length);
            }

            bitmap.Invalidate();
            return bitmap;
        }
    }
}
