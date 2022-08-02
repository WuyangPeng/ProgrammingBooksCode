using System;
using System.Runtime.InteropServices;
using Windows.UI.Xaml.Controls;

namespace SystemInfoPInvoke
{
    public sealed partial class MainPage : Page
    {
        [StructLayout(LayoutKind.Sequential)]
        struct SystemInfo
        {
            public ushort wProcessorArchitecture;
            public byte wReserved;
            public uint dwPageSize;
            public IntPtr lpMinimumApplicationAddress;
            public IntPtr lpMaximumApplicationAddress;
            public IntPtr dwActiveProcessorMask;
            public uint dwNumberOfProcessors;
            public uint dwProcessorType;
            public uint dwAllocationGranularity;
            public ushort wProcessorLevel;
            public ushort wProcessorRevision;
        }

        [DllImport("kernel32.dll")]
        static extern void GetNativeSystemInfo(out SystemInfo systemInfo);

        enum ProcessorType
        {
            x86 = 0,
            ARM = 5,
            ia64 = 6,
            x64 = 9,
            Unknown = 65535
        };

        public MainPage()
        {
            this.InitializeComponent();

            SystemInfo systemInfo = new SystemInfo();
            GetNativeSystemInfo(out systemInfo);

            processorArchitecture.Text = 
                            ((ProcessorType)systemInfo.wProcessorArchitecture).ToString();
            pageSize.Text = systemInfo.dwPageSize.ToString();
            minAppAddr.Text = ((ulong)systemInfo.lpMinimumApplicationAddress).ToString("X");
            maxAppAddr.Text = ((ulong)systemInfo.lpMaximumApplicationAddress).ToString("X");
            activeProcessorMask.Text = ((ulong)systemInfo.dwActiveProcessorMask).ToString("X");
            numberProcessors.Text = systemInfo.dwNumberOfProcessors.ToString("X");
            allocationGranularity.Text = systemInfo.dwAllocationGranularity.ToString();
            processorLevel.Text = systemInfo.wProcessorLevel.ToString();
            processorRevision.Text = systemInfo.wProcessorRevision.ToString("X");
        }
    }
}
