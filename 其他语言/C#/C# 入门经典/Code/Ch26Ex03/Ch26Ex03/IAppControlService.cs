﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace Ch26Ex03
{
   // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IAppControlService" in both code and config file together.
   [ServiceContract]
   public interface IAppControlService
   {
      [OperationContract]
      void SetRadius(int radius, string foreTo, int seconds);
   }
}
