﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BegVCSharp_23_15_SetOperators
{
    class Customer
    {
        public string ID { get; set; }
        public string City { get; set; }
        public string Country { get; set; }
        public string Region { get; set; }
        public decimal Sales { get; set; }
    }
    class Order
    {
        public string ID { get; set; }
        public decimal Amount { get; set; }
    }
    class Program
    {
        static void Main(string[] args)
        {
            List<Order> orders = new List<Order> {
              new Order { ID="P", Amount=100 },
              new Order { ID="Q", Amount=200 },
              new Order { ID="R", Amount=300 },
              new Order { ID="S", Amount=400 },
              new Order { ID="T", Amount=500 },
              new Order { ID="U", Amount=600 },
              new Order { ID="V", Amount=700 },
              new Order { ID="W", Amount=800 },
              new Order { ID="X", Amount=900 },
              new Order { ID="Y", Amount=1000 },
              new Order { ID="Z", Amount=1100 }
            };
            List<Customer> customers = new List<Customer> {
              new Customer { ID="A", City="New York", Country="USA", Region="North America", Sales=9999},
              new Customer { ID="B", City="Mumbai", Country="India", Region="Asia", Sales=8888},
              new Customer { ID="C", City="Karachi", Country="Pakistan", Region="Asia", Sales=7777},
              new Customer { ID="D", City="Delhi", Country="India", Region="Asia", Sales=6666},
              new Customer { ID="E", City="São Paulo", Country="Brazil", Region="South America", Sales=5555 },
              new Customer { ID="F", City="Moscow", Country="Russia", Region="Europe", Sales=4444 },
              new Customer { ID="G", City="Seoul", Country="Korea", Region="Asia", Sales=3333 },
              new Customer { ID="H", City="Istanbul", Country="Turkey", Region="Asia", Sales=2222 },
              new Customer { ID="I", City="Shanghai", Country="China", Region="Asia", Sales=1111 },
              new Customer { ID="J", City="Lagos", Country="Nigeria", Region="Africa", Sales=1000 },
              new Customer { ID="K", City="Mexico City", Country="Mexico", Region="North America", Sales=2000 },
              new Customer { ID="L", City="Jakarta", Country="Indonesia", Region="Asia", Sales=3000 },
              new Customer { ID="M", City="Tokyo", Country="Japan", Region="Asia", Sales=4000 },
              new Customer { ID="N", City="Los Angeles", Country="USA", Region="North America", Sales=5000 },
              new Customer { ID="O", City="Cairo", Country="Egypt", Region="Africa", Sales=6000 },
              new Customer { ID="P", City="Tehran", Country="Iran", Region="Asia", Sales=7000 },
              new Customer { ID="Q", City="London", Country="UK", Region="Europe", Sales=8000 },
              new Customer { ID="R", City="Beijing", Country="China", Region="Asia", Sales=9000 },
              new Customer { ID="S", City="Bogotá", Country="Colombia", Region="South America", Sales=1001 },
              new Customer { ID="T", City="Lima", Country="Peru", Region="South America", Sales=2002 }
           };

            var customerIDs =
               from c in customers
               select c.ID
               ;
            var orderIDs =
               from o in orders
               select o.ID
               ;
            var customersWithOrders = customerIDs.Intersect(orderIDs);
            Console.WriteLine("Customers with Orders:");
            foreach (var item in customersWithOrders)
            {
                Console.Write("{0} ", item);
            }
            Console.WriteLine();

            Console.WriteLine("Orders with no customers:");
            var ordersNoCustomers = orderIDs.Except(customerIDs);
            foreach (var item in ordersNoCustomers)
            {
                Console.Write("{0} ", item);
            }
            Console.WriteLine();

            Console.WriteLine("All Customer and Order IDs:");
            var allCustomerOrderIDs = orderIDs.Union(customerIDs);
            foreach (var item in allCustomerOrderIDs)
            {
                Console.Write("{0} ", item);
            } 
            Console.WriteLine();

            Console.Write("Program finished, press Enter/Return to continue:");
            Console.ReadLine();
        }
    }

}