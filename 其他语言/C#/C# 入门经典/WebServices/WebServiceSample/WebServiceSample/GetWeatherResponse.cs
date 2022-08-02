using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace WebServiceSample
{
    public enum TemparatureCondition
    {
        Rainy,
        Sunny,
        Cloudy,
        Thunderstorm
    }

    public class GetWeatherResponse
    {
        public TemparatureCondition Condition;
        public int Temperature;
    }
}