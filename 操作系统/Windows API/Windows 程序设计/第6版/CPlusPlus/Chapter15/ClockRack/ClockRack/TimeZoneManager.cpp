#include "pch.h"
#include "TimeZoneManager.h"
#include "TimeZoneDisplayInfo.h"

using namespace ClockRack;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Globalization;

bool TimeZoneManager::areDisplayStringsInitialized = false;
Map<String^, String^>^ TimeZoneManager::displayStrings = ref new Map<String^, String^>();

TimeZoneManager::TimeZoneManager()
{
    if (!areDisplayStringsInitialized)
    {
        displayStrings->Insert("Dateline Standard Time", "(UTC-12:00) International Date Line West");
        displayStrings->Insert("UTC-11", "(UTC-11:00) Coordinated Universal Time-11");
        displayStrings->Insert("Hawaiian Standard Time", "(UTC-10:00) Hawaii");
        displayStrings->Insert("Alaskan Standard Time", "(UTC-09:00) Alaska");
        displayStrings->Insert("Pacific Standard Time (Mexico)", "(UTC-08:00) Baja California");
        displayStrings->Insert("Pacific Standard Time", "(UTC-08:00) Pacific Time (US & Canada)");
        displayStrings->Insert("US Mountain Standard Time", "(UTC-07:00) Arizona");
        displayStrings->Insert("Mountain Standard Time (Mexico)", "(UTC-07:00) Chihuahua, La Paz, Mazatlan");
        displayStrings->Insert("Mountain Standard Time", "(UTC-07:00) Mountain Time (US & Canada)");
        displayStrings->Insert("Central America Standard Time", "(UTC-06:00) Central America");
        displayStrings->Insert("Central Standard Time", "(UTC-06:00) Central Time (US & Canada)");
        displayStrings->Insert("Central Standard Time (Mexico)", "(UTC-06:00) Guadalajara, Mexico City, Monterrey");
        displayStrings->Insert("Canada Central Standard Time", "(UTC-06:00) Saskatchewan");
        displayStrings->Insert("SA Pacific Standard Time", "(UTC-05:00) Bogota, Lima, Quito");
        displayStrings->Insert("Eastern Standard Time", "(UTC-05:00) Eastern Time (US & Canada)");
        displayStrings->Insert("US Eastern Standard Time", "(UTC-05:00) Indiana (East)");
        displayStrings->Insert("Venezuela Standard Time", "(UTC-04:30) Caracas");
        displayStrings->Insert("Paraguay Standard Time", "(UTC-04:00) Asuncion");
        displayStrings->Insert("Atlantic Standard Time", "(UTC-04:00) Atlantic Time (Canada)");
        displayStrings->Insert("Central Brazilian Standard Time", "(UTC-04:00) Cuiaba");
        displayStrings->Insert("SA Western Standard Time", "(UTC-04:00) Georgetown, La Paz, Manaus, San Juan");
        displayStrings->Insert("Pacific SA Standard Time", "(UTC-04:00) Santiago");
        displayStrings->Insert("Newfoundland Standard Time", "(UTC-03:30) Newfoundland");
        displayStrings->Insert("E. South America Standard Time", "(UTC-03:00) Brasilia");
        displayStrings->Insert("Argentina Standard Time", "(UTC-03:00) Buenos Aires");
        displayStrings->Insert("SA Eastern Standard Time", "(UTC-03:00) Cayenne, Fortaleza");
        displayStrings->Insert("Greenland Standard Time", "(UTC-03:00) Greenland");
        displayStrings->Insert("Montevideo Standard Time", "(UTC-03:00) Montevideo");
        displayStrings->Insert("Bahia Standard Time", "(UTC-03:00) Salvador");
        displayStrings->Insert("UTC-02", "(UTC-02:00) Coordinated Universal Time-02");
        displayStrings->Insert("Mid-Atlantic Standard Time", "(UTC-02:00) Mid-Atlantic");
        displayStrings->Insert("Azores Standard Time", "(UTC-01:00) Azores");
        displayStrings->Insert("Cape Verde Standard Time", "(UTC-01:00) Cape Verde Is.");
        displayStrings->Insert("Morocco Standard Time", "(UTC) Casablanca");
        displayStrings->Insert("Coordinated Universal Time", "(UTC) Coordinated Universal Time");
        displayStrings->Insert("GMT Standard Time", "(UTC) Dublin, Edinburgh, Lisbon, London");
        displayStrings->Insert("Greenwich Standard Time", "(UTC) Monrovia, Reykjavik");
        displayStrings->Insert("W. Europe Standard Time", "(UTC+01:00) Amsterdam, Berlin, Bern, Rome, Stockholm, Vienna");
        displayStrings->Insert("Central Europe Standard Time", "(UTC+01:00) Belgrade, Bratislava, Budapest, Ljubljana, Prague");
        displayStrings->Insert("Romance Standard Time", "(UTC+01:00) Brussels, Copenhagen, Madrid, Paris");
        displayStrings->Insert("Central European Standard Time", "(UTC+01:00) Sarajevo, Skopje, Warsaw, Zagreb");
        displayStrings->Insert("W. Central Africa Standard Time", "(UTC+01:00) West Central Africa");
        displayStrings->Insert("Namibia Standard Time", "(UTC+01:00) Windhoek");
        displayStrings->Insert("Jordan Standard Time", "(UTC+02:00) Amman");
        displayStrings->Insert("GTB Standard Time", "(UTC+02:00) Athens, Bucharest");
        displayStrings->Insert("Middle East Standard Time", "(UTC+02:00) Beirut");
        displayStrings->Insert("Egypt Standard Time", "(UTC+02:00) Cairo");
        displayStrings->Insert("Syria Standard Time", "(UTC+02:00) Damascus");
        displayStrings->Insert("South Africa Standard Time", "(UTC+02:00) Harare, Pretoria");
        displayStrings->Insert("FLE Standard Time", "(UTC+02:00) Helsinki, Kyiv, Riga, Sofia, Tallinn, Vilnius");
        displayStrings->Insert("Turkey Standard Time", "(UTC+02:00) Istanbul");
        displayStrings->Insert("Jerusalem Standard Time", "(UTC+02:00) Jerusalem");
        displayStrings->Insert("E. Europe Standard Time", "(UTC+02:00) Nicosia");
        displayStrings->Insert("Arabic Standard Time", "(UTC+03:00) Baghdad");
        displayStrings->Insert("Kaliningrad Standard Time", "(UTC+03:00) Kaliningrad, Minsk");
        displayStrings->Insert("Arab Standard Time", "(UTC+03:00) Kuwait, Riyadh");
        displayStrings->Insert("E. Africa Standard Time", "(UTC+03:00) Nairobi");
        displayStrings->Insert("Iran Standard Time", "(UTC+03:30) Tehran");
        displayStrings->Insert("Arabian Standard Time", "(UTC+04:00) Abu Dhabi, Muscat");
        displayStrings->Insert("Azerbaijan Standard Time", "(UTC+04:00) Baku");
        displayStrings->Insert("Russian Standard Time", "(UTC+04:00) Moscow, St. Petersburg, Volgograd");
        displayStrings->Insert("Mauritius Standard Time", "(UTC+04:00) Port Louis");
        displayStrings->Insert("Georgian Standard Time", "(UTC+04:00) Tbilisi");
        displayStrings->Insert("Caucasus Standard Time", "(UTC+04:00) Yerevan");
        displayStrings->Insert("Afghanistan Standard Time", "(UTC+04:30) Kabul");
        displayStrings->Insert("Pakistan Standard Time", "(UTC+05:00) Islamabad, Karachi");
        displayStrings->Insert("West Asia Standard Time", "(UTC+05:00) Tashkent");
        displayStrings->Insert("India Standard Time", "(UTC+05:30) Chennai, Kolkata, Mumbai, New Delhi");
        displayStrings->Insert("Sri Lanka Standard Time", "(UTC+05:30) Sri Jayawardenepura");
        displayStrings->Insert("Nepal Standard Time", "(UTC+05:45) Kathmandu");
        displayStrings->Insert("Central Asia Standard Time", "(UTC+06:00) Astana");
        displayStrings->Insert("Bangladesh Standard Time", "(UTC+06:00) Dhaka");
        displayStrings->Insert("Ekaterinburg Standard Time", "(UTC+06:00) Ekaterinburg");
        displayStrings->Insert("Myanmar Standard Time", "(UTC+06:30) Yangon (Rangoon)");
        displayStrings->Insert("SE Asia Standard Time", "(UTC+07:00) Bangkok, Hanoi, Jakarta");
        displayStrings->Insert("N. Central Asia Standard Time", "(UTC+07:00) Novosibirsk");
        displayStrings->Insert("China Standard Time", "(UTC+08:00) Beijing, Chongqing, Hong Kong, Urumqi");
        displayStrings->Insert("North Asia Standard Time", "(UTC+08:00) Krasnoyarsk");
        displayStrings->Insert("Malay Peninsula Standard Time", "(UTC+08:00) Kuala Lumpur, Singapore");
        displayStrings->Insert("W. Australia Standard Time", "(UTC+08:00) Perth");
        displayStrings->Insert("Taipei Standard Time", "(UTC+08:00) Taipei");
        displayStrings->Insert("Ulaanbaatar Standard Time", "(UTC+08:00) Ulaanbaatar");
        displayStrings->Insert("North Asia East Standard Time", "(UTC+09:00) Irkutsk");
        displayStrings->Insert("Tokyo Standard Time", "(UTC+09:00) Osaka, Sapporo, Tokyo");
        displayStrings->Insert("Korea Standard Time", "(UTC+09:00) Seoul");
        displayStrings->Insert("Cen. Australia Standard Time", "(UTC+09:30) Adelaide");
        displayStrings->Insert("AUS Central Standard Time", "(UTC+09:30) Darwin");
        displayStrings->Insert("E. Australia Standard Time", "(UTC+10:00) Brisbane");
        displayStrings->Insert("AUS Eastern Standard Time", "(UTC+10:00) Canberra, Melbourne, Sydney");
        displayStrings->Insert("West Pacific Standard Time", "(UTC+10:00) Guam, Port Moresby");
        displayStrings->Insert("Tasmania Standard Time", "(UTC+10:00) Hobart");
        displayStrings->Insert("Yakutsk Standard Time", "(UTC+10:00) Yakutsk");
        displayStrings->Insert("Central Pacific Standard Time", "(UTC+11:00) Solomon Is., New Caledonia");
        displayStrings->Insert("Vladivostok Standard Time", "(UTC+11:00) Vladivostok");
        displayStrings->Insert("New Zealand Standard Time", "(UTC+12:00) Auckland, Wellington");
        displayStrings->Insert("UTC+12", "(UTC+12:00) Coordinated Universal Time+12");
        displayStrings->Insert("Fiji Standard Time", "(UTC+12:00) Fiji");
        displayStrings->Insert("Magadan Standard Time", "(UTC+12:00) Magadan");
        displayStrings->Insert("Kamchatka Standard Time", "(UTC+12:00) Petropavlovsk-Kamchatsky - Old");
        displayStrings->Insert("Tonga Standard Time", "(UTC+13:00) Nuku'alofa");
        displayStrings->Insert("Samoa Standard Time", "(UTC+13:00) Samoa");

        areDisplayStringsInitialized = true;
    }

    int index = 0;
    DYNAMIC_TIME_ZONE_INFORMATION* tzi = new DYNAMIC_TIME_ZONE_INFORMATION();
    displayInformation = ref new Vector<TimeZoneDisplayInfo^>();

    // Enumerate through the time zones
    while (0 == EnumDynamicTimeZoneInformation(index, tzi))
    {
        // Convert strings from DYNAMIC_TIME_ZONE_INFORMATION object
        wchar_t tziString[128];
        wcscpy_s(tziString, 128, tzi->TimeZoneKeyName);
        String^ timeZoneKeyName = ref new String(tziString);

        wcscpy_s(tziString, 128, tzi->StandardName);
        String^ standardName = ref new String(tziString);

        // Store in map by key name
        dynamicTzis[timeZoneKeyName] = tzi;

        // Create TimeZoneDisplayInfo for public property
        TimeZoneDisplayInfo^ displayInfo = ref new TimeZoneDisplayInfo();
        displayInfo->Bias = tzi->Bias;
        displayInfo->TimeZoneKey = timeZoneKeyName;

        // Look up the display string
        if (displayStrings->HasKey(timeZoneKeyName))
        {
            displayInfo->Display = displayStrings->Lookup(timeZoneKeyName);
        }
        else if (displayStrings->HasKey(standardName))
        {
            displayInfo->Display = displayStrings->Lookup(standardName);
        }
        // Or calculate one
        else
        {
            if (tzi->Bias == 0)
                displayInfo->Display = "(UTC) ";
            else
            {
                wchar_t display[32];
                swprintf(display, 32, L"(UTC%c%02i:%02i) ", tzi->Bias > 0 ? '-' : '+',
                                         abs(tzi->Bias) / 60,
                                         abs(tzi->Bias) % 60);
                displayInfo->Display += ref new String(display);
            }
            displayInfo->Display += timeZoneKeyName;
        }

        // Add to collection
        displayInformation->Append(displayInfo);

        // Prepare for next iteration
        index += 1;
        tzi = new DYNAMIC_TIME_ZONE_INFORMATION();
    }

    // Sort the display information items
    std::sort(begin(displayInformation), end(displayInformation), 
              [] (TimeZoneDisplayInfo^ info1, TimeZoneDisplayInfo^ info2)
    {
        return info1->Bias < info2->Bias;
    });

    // Create a Calendar to help with the conversions
    calendar = ref new Calendar();
    calendar->ChangeClock(ClockIdentifiers::TwentyFourHour);
}

DateTime TimeZoneManager::GetLocalTime(String^ timeZoneKey)
{
    SYSTEMTIME utcSysTime;
    GetSystemTime(&utcSysTime);

    // Convert to local time
    DYNAMIC_TIME_ZONE_INFORMATION* dtzi = dynamicTzis.at(timeZoneKey);
    TIME_ZONE_INFORMATION tzi;
    GetTimeZoneInformationForYear(utcSysTime.wYear, dtzi, &tzi);

    SYSTEMTIME localTime;
    SystemTimeToTzSpecificLocalTime(&tzi, &utcSysTime, &localTime);

    // Convert SYSTEMTIME to DateTime
    calendar->Year = localTime.wYear;
    calendar->Month = localTime.wMonth;
    calendar->Day = localTime.wDay;
    calendar->Hour = localTime.wHour;
    calendar->Minute = localTime.wMinute;
    calendar->Second = localTime.wSecond;
    calendar->Nanosecond = 1000000 * localTime.wMilliseconds;

    return calendar->GetDateTime();
}
