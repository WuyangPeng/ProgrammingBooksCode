using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;

namespace Ch26Ex02Contracts
{
   [ServiceContract(SessionMode = SessionMode.Required)]
   public interface IAwardService
   {
      [OperationContract(IsOneWay = true, IsInitiating = true)]
      void SetPassMark(int passMark);

      [OperationContract]
      Person[] GetAwardedPeople(Person[] peopleToTest);
   }
}
