using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace ClockRack
{
    public partial class TimeZoneManager
    {
        [StructLayout(LayoutKind.Sequential)]
        struct SYSTEMTIME
        {
            public ushort wYear;
            public ushort wMonth;
            public ushort wDayOfWeek;
            public ushort wDay;
            public ushort wHour;
            public ushort wMinute;
            public ushort wSecond;
            public ushort wMilliseconds;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        struct TIME_ZONE_INFORMATION
        {
            public int Bias;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
            public string StandardName;
            public SYSTEMTIME StandardDate;
            public int StandardBias;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
            public string DaylightName;
            public SYSTEMTIME DaylightDate;
            public int DaylightBias;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        struct DYNAMIC_TIME_ZONE_INFORMATION
        {
            public int Bias;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
            public string StandardName;
            public SYSTEMTIME StandardDate;
            public int StandardBias;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
            public string DaylightName;
            public SYSTEMTIME DaylightDate;
            public int DaylightBias;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]
            public string TimeZoneKeyName;
            public byte DynamicDaylightTimeDisabled;
        }

        [DllImport("Advapi32.dll")]
        static extern uint EnumDynamicTimeZoneInformation(uint index, 
                                            ref DYNAMIC_TIME_ZONE_INFORMATION dynamicTzi);

        [DllImport("kernel32.dll")]
        static extern byte GetTimeZoneInformationForYear(ushort year, 
                                            ref DYNAMIC_TIME_ZONE_INFORMATION dtzi, 
                                            out TIME_ZONE_INFORMATION tzi);

        [DllImport("kernel32.dll")]
        static extern byte SystemTimeToTzSpecificLocalTime(ref TIME_ZONE_INFORMATION tzi, 
                                            ref SYSTEMTIME utc, out SYSTEMTIME local);

        // Internal dictionary for looking up DYNAMIC_TIME_ZONE_INFORMATION values from keys
        Dictionary<string, DYNAMIC_TIME_ZONE_INFORMATION> dynamicTzis = 
                                        new Dictionary<string, DYNAMIC_TIME_ZONE_INFORMATION>();

        public TimeZoneManager()
        {
            uint index = 0;
            DYNAMIC_TIME_ZONE_INFORMATION tzi = new DYNAMIC_TIME_ZONE_INFORMATION();
            List<TimeZoneDisplayInfo> displayInformation = new List<TimeZoneDisplayInfo>();

            // Enumerate through time zones
            while (0 == EnumDynamicTimeZoneInformation(index, ref tzi))
            {
                dynamicTzis.Add(tzi.TimeZoneKeyName, tzi);

                // Create TimeZoneDisplayInfo for public property
                TimeZoneDisplayInfo displayInfo = new TimeZoneDisplayInfo 
                { 
                    Bias = tzi.Bias, 
                    TimeZoneKey = tzi.TimeZoneKeyName 
                };

                // Look up the display string
                if (displayStrings.ContainsKey(tzi.TimeZoneKeyName))
                {
                    displayInfo.Display = displayStrings[tzi.TimeZoneKeyName];
                }
                else if (displayStrings.ContainsKey(tzi.StandardName))
                {
                    displayInfo.Display = displayStrings[tzi.StandardName];
                }
                // Or calculate one
                else
                {
                    if (tzi.Bias == 0)
                        displayInfo.Display = "(UTC) ";
                    else
                        displayInfo.Display = String.Format("(UTC{0}{1:D2}:{2:D2}) ", 
                                                            tzi.Bias > 0 ? '-' : '+', 
                                                            Math.Abs(tzi.Bias) / 60, 
                                                            Math.Abs(tzi.Bias) % 60);
                    displayInfo.Display += tzi.TimeZoneKeyName;
                }

                // Add to collection
                displayInformation.Add(displayInfo);

                // Prepare for next iteration
                index += 1;
                tzi = new DYNAMIC_TIME_ZONE_INFORMATION();
            }

            // Sort the display information items
            displayInformation.Sort((TimeZoneDisplayInfo info1, TimeZoneDisplayInfo info2) =>
                {
                    return info2.Bias.CompareTo(info1.Bias);
                });

            // Set to the publicly available property
            this.DisplayInformation = displayInformation;
        }

        // Public interface
        public IList<TimeZoneDisplayInfo> DisplayInformation { protected set; get; }

        public DateTime GetLocalTime(string timeZoneKey, DateTime utc)
        {
            // Convert to Win32 SYSTEMTIME
            SYSTEMTIME utcSysTime = new SYSTEMTIME
            {
                wYear = (ushort)utc.Year,
                wMonth = (ushort)utc.Month,
                wDay = (ushort)utc.Day,
                wHour = (ushort)utc.Hour,
                wMinute = (ushort)utc.Minute,
                wSecond = (ushort)utc.Second,
                wMilliseconds = (ushort)utc.Millisecond
            };

            // Convert to local time
            DYNAMIC_TIME_ZONE_INFORMATION dtzi = dynamicTzis[timeZoneKey];
            TIME_ZONE_INFORMATION tzi = new TIME_ZONE_INFORMATION();
            GetTimeZoneInformationForYear((ushort)utc.Year, ref dtzi, out tzi);

            SYSTEMTIME localSysTime = new SYSTEMTIME();
            SystemTimeToTzSpecificLocalTime(ref tzi, ref utcSysTime, out localSysTime);

            // Convert SYSTEMTIME to DateTime
            return new DateTime(localSysTime.wYear, localSysTime.wMonth, localSysTime.wDay, 
                                localSysTime.wHour, localSysTime.wMinute, 
                                localSysTime.wSecond, localSysTime.wMilliseconds);
        }
    }
}
