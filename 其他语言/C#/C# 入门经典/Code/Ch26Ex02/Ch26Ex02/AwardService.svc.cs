using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using Ch26Ex02Contracts;

namespace Ch26Ex02
{
   // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "AwardService" in code, svc and config file together.
   public class AwardService : IAwardService
   {
      private int passMark;

      public void SetPassMark(int passMark)
      {
         this.passMark = passMark;
      }

      public Person[] GetAwardedPeople(Person[] peopleToTest)
      {
         List<Person> result = new List<Person>();
         foreach (Person person in peopleToTest)
         {
            if (person.Mark > passMark)
            {
               result.Add(person);
            }
         }
         return result.ToArray();
      }
   }
}
