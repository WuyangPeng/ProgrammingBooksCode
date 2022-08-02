using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Windows.Storage.Streams;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace WordFreq
{
    public sealed partial class MainPage : Page
    {
        // Project Gutenberg ebook of Herman Melville's "Moby-Dick" 
        Uri uri = new Uri("http://www.gutenberg.org/ebooks/2701.txt.utf-8");
        CancellationTokenSource cts;

        public MainPage()
        {
            this.InitializeComponent();
        }

        async void OnStartButtonClick(object sender, RoutedEventArgs args)
        {
            stackPanel.Children.Clear();
            progressBar.Value = 0;
            errorText.Text = "";
            startButton.IsEnabled = false;
            IOrderedEnumerable<KeyValuePair<string, int>> wordList = null;

            try
            {
                RandomAccessStreamReference streamRef = RandomAccessStreamReference.CreateFromUri(uri);

                using (IRandomAccessStream raStream = await streamRef.OpenReadAsync())
                {
                    using (Stream stream = raStream.AsStream())
                    {
                        cancelButton.IsEnabled = true;
                        cts = new CancellationTokenSource();

                        wordList = await GetWordFrequenciesAsync(stream, cts.Token,
                                                        new Progress<double>(ProgressCallback));

                        cancelButton.IsEnabled = false;
                    }
                }
            }
            catch (OperationCanceledException)
            {
                progressBar.Value = 0;
                cancelButton.IsEnabled = false;
                startButton.IsEnabled = true;
                return;
            }
            catch (Exception exc)
            {
                progressBar.Value = 0;
                cancelButton.IsEnabled = false;
                startButton.IsEnabled = true;
                errorText.Text = "Error: " + exc.Message;
                return;
            }

            // Transfer the list of word and counts to the StackPanel
            foreach (KeyValuePair<string, int> word in wordList)
            {
                if (word.Value > 1)
                {
                    TextBlock txtblk = new TextBlock
                    {
                        FontSize = 24,
                        Text = word.Key + " \x2014 " + word.Value.ToString()
                    };
                    stackPanel.Children.Add(txtblk);
                }

                await Task.Yield();
            }

            startButton.IsEnabled = true;
        }

        void OnCancelButtonClick(object sender, RoutedEventArgs args)
        {
            cts.Cancel();
        }

        void ProgressCallback(double progress)
        {
            progressBar.Value = progress;
        }

        Task<IOrderedEnumerable<KeyValuePair<string, int>>> GetWordFrequenciesAsync(Stream stream, 
                                                                CancellationToken cancellationToken, 
                                                                IProgress<double> progress)
        {
            return Task.Run(async () =>
                {
                    Dictionary<string, int> dictionary = new Dictionary<string, int>();

                    using (StreamReader streamReader = new StreamReader(stream))
                    {
                        // Read the first line
                        string line = await streamReader.ReadLineAsync();

                        while (line != null)
                        {
                            cancellationToken.ThrowIfCancellationRequested();
                            progress.Report(100.0 * stream.Position / stream.Length);

                            string[] words = line.Split(' ', ',', '.', ';', ':');

                            foreach (string word in words)
                            {
                                string charWord = word.ToLower();

                                while (charWord.Length > 0 && !Char.IsLetter(charWord[0]))
                                    charWord = charWord.Substring(1);

                                while (charWord.Length > 0 && 
                                                !Char.IsLetter(charWord[charWord.Length - 1]))
                                    charWord = charWord.Substring(0, charWord.Length - 1);

                                if (charWord.Length == 0)
                                    continue;

                                if (dictionary.ContainsKey(charWord))
                                    dictionary[charWord] += 1;
                                else
                                    dictionary.Add(charWord, 1);
                            }
                            line = await streamReader.ReadLineAsync();
                        }
                    }

                    // Return the dictionary sorted by Value (the word count)
                    return dictionary.OrderByDescending(i => i.Value);
                }, cancellationToken);
        }
    }
}
