using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FunWithLinqExpressions
{
    #region Sample class for LINQ queries
    class ProductInfo
    {
        public string Name { get; set; }
        public string Description { get; set; }
        public int NumberInStock { get; set; }

        public override string ToString()
        {
            return string.Format("Name={0}, Description={1}, Number in Stock={2}",
              Name, Description, NumberInStock);
        }
    }
    #endregion 

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Fun with Query Expressions *****\n");

            // This array will be the basis of our testing...
            ProductInfo[] itemsInStock = new[] {
                new ProductInfo{ Name = "Mac's Coffee", Description = "Coffee with TEETH", NumberInStock = 24},
                new ProductInfo{ Name = "Milk Maid Milk", Description = "Milk cow's love", NumberInStock = 100},
                new ProductInfo{ Name = "Pure Silk Tofu", Description = "Bland as Possible", NumberInStock = 120},
                new ProductInfo{ Name = "Cruchy Pops", Description = "Cheezy, peppery goodness", NumberInStock = 2},
                new ProductInfo{ Name = "RipOff Water", Description = "From the tap to your wallet", NumberInStock = 100},
                new ProductInfo{ Name = "Classic Valpo Pizza", Description = "Everyone loves pizza!", NumberInStock = 73}
            };

            // We will call various methods here!
            SelectEverything(itemsInStock);
            Console.WriteLine();
            
            ListProductNames(itemsInStock);
            Console.WriteLine();

            Console.WriteLine();

            GetOverstock(itemsInStock);
            Console.WriteLine();

            GetNamesAndDescriptions(itemsInStock);
            Console.WriteLine();

            Array objs = GetProjectedSubset();
            foreach (object o in objs)
            {
                Console.WriteLine(o);  // Calls ToString() on each anonymous object.
            }
            Console.WriteLine();

            AlphabetizeProductNames(itemsInStock);
            Console.WriteLine();

            GetCountFromQuery();
            Console.WriteLine();

            DisplayConcat();
            Console.WriteLine();

            DisplayConcatNoDups();
            Console.WriteLine(); 
            
            DisplayDiff();
            Console.WriteLine(); 
            
            DisplayIntersection();
            Console.WriteLine(); 
            
            DisplayUnion();
            Console.WriteLine();

            AggregateOps();
            Console.WriteLine();

            Console.ReadLine();
        }

        #region Basic selections
        static void SelectEverything(ProductInfo[] products)
        {
            // Get everything.
            Console.WriteLine("All product details:");
            var allProducts = from p in products select p;
            foreach (var prod in allProducts)
            {
                Console.WriteLine(prod.ToString());
            }
        }

        static void ListProductNames(ProductInfo[] products)
        {
            // Now get only the names of the products.
            Console.WriteLine("Only product names:");
            var names = from p in products select p.Name;

            foreach (var n in names)
            {
                Console.WriteLine("Name: {0}", n);
            }
        }
        #endregion

        #region Orderby
        static void AlphabetizeProductNames(ProductInfo[] products)
        {
            // Get names of products, alphabetized.
            var subset = from p in products orderby p.Name descending select p;

            Console.WriteLine("Ordered by Name:");
            foreach (var p in subset)
            {
                Console.WriteLine(p.ToString());
            }
        }
        #endregion

        #region Subsets with where
        static void GetOverstock(ProductInfo[] products)
        {
            Console.WriteLine("The overstock items!");
            // Get only the items where we have more than
            // 25 in stock.
            var overstock = from p in products where p.NumberInStock > 25 select p;

            foreach (ProductInfo c in overstock)
            {
                Console.WriteLine(c.ToString());
            }
        }
        #endregion

        #region Projections
        static void GetNamesAndDescriptions(ProductInfo[] products)
        {
            Console.WriteLine("Names and Descriptions:");
            var nameDesc = from p in products select new { p.Name, p.Description };
            foreach (var item in nameDesc)
            {
                // Could also use Name and Description properties directly.
                Console.WriteLine(item.ToString());
            }
        }

        static Array GetProjectedSubset()
        {
            ProductInfo[] products = new[] {
                new ProductInfo{ Name = "Mac's Coffee", Description = "Coffee with TEETH", NumberInStock = 24},
                new ProductInfo{ Name = "Milk Maid Milk", Description = "Milk cow's love", NumberInStock = 100},
                new ProductInfo{ Name = "Pure Silk Tofu", Description = "Bland as Possible", NumberInStock = 120},
                new ProductInfo{ Name = "Cruchy Pops", Description = "Cheezy, peppery goodness", NumberInStock = 2},
                new ProductInfo{ Name = "RipOff Water", Description = "From the tap to your wallet", NumberInStock = 100},
                new ProductInfo{ Name = "Classic Valpo Pizza", Description = "Everyone loves pizza!", NumberInStock = 73}
            };

            var nameDesc = from p in products select new { p.Name, p.Description };
            return nameDesc.ToArray();
        }
        #endregion

        #region Get the Count
        static void GetCountFromQuery()
        {
            string[] currentVideoGames = {"Morrowind", "BioShock",
                    "Half Life 2: Episode 1", "The Darkness",
                    "Daxter", "System Shock 2"};

            // Get count from the query.
            int numb = (from g in currentVideoGames
                        where g.Length > 6
                        orderby g
                        select g).Count();

            // numb is the value 5.
            Console.WriteLine("{0} items honor the LINQ query.", numb);
        }
        #endregion

        #region Reversing
        static void ReverseEverything(ProductInfo[] products)
        {
            // Get everything.
            Console.WriteLine("Product in reverse:");
            var allProducts = from p in products select p;
            foreach (var prod in allProducts.Reverse())
            {
                Console.WriteLine(prod.ToString());
            }
        }
        #endregion

        #region Venn diagram type extension methods
        static void DisplayDiff()
        {
            List<string> myCars = new List<String> { "Yugo", "Aztec", "BMW" };
            List<string> yourCars = new List<String> { "BMW", "Saab", "Aztec" };

            var carDiff = (from c in myCars select c)
              .Except(from c2 in yourCars select c2);

            Console.WriteLine("Here is what you don't have, but I do:");
            foreach (string s in carDiff)
                Console.WriteLine(s);  // Prints Yugo.
        }

        static void DisplayIntersection()
        {
            List<string> myCars = new List<String> { "Yugo", "Aztec", "BMW" };
            List<string> yourCars = new List<String> { "BMW", "Saab", "Aztec" };

            // Get the common members.
            var carIntersect = (from c in myCars select c)
              .Intersect(from c2 in yourCars select c2);

            Console.WriteLine("Here is what we have in common:");
            foreach (string s in carIntersect)
                Console.WriteLine(s);  // Prints BMW and Aztec.
        }

        static void DisplayUnion()
        {
            List<string> myCars = new List<String> { "Yugo", "Aztec", "BMW" };
            List<string> yourCars = new List<String> { "BMW", "Saab", "Aztec" };

            // Get the union of these containers. 
            var carUnion = (from c in myCars select c)
              .Union(from c2 in yourCars select c2);

            Console.WriteLine("Here is everything:");
            foreach (string s in carUnion)
                Console.WriteLine(s);  // Prints all common members 
            // (Saab, BMW, Aztec, Yugo).
        }

        static void DisplayConcat()
        {
            List<string> myCars = new List<String> { "Yugo", "Aztec", "BMW" };
            List<string> yourCars = new List<String> { "BMW", "Saab", "Aztec" };

            // Prints:
            // Yugo, Aztec, BMW, BMW, Saab, Aztec.
            var carConcat = (from c in myCars select c)
              .Concat(from c2 in yourCars select c2);

            foreach (string s in carConcat)
                Console.WriteLine(s);
        }

        static void DisplayConcatNoDups()
        {
            List<string> myCars = new List<String> { "Yugo", "Aztec", "BMW" };
            List<string> yourCars = new List<String> { "BMW", "Saab", "Aztec" };

            var carConcat = (from c in myCars select c)
              .Concat(from c2 in yourCars select c2);

            // Prints:
            // Yugo Aztec BMW Saab Aztec.
            foreach (string s in carConcat.Distinct())
                Console.WriteLine(s);
        }

        #endregion

        #region Aggregation Examples
        static void AggregateOps()
        {
            double[] winterTemps = { 2.0, -21.3, 8, -4, 0, 8.2 };

            // Various aggregation examples. 
            Console.WriteLine("Max temp: {0}", (from t in winterTemps
                                                select t).Max());
            Console.WriteLine("Min temp: {0}", (from t in winterTemps
                                                select t).Min());
            Console.WriteLine("Avarage temp: {0}", (from t in winterTemps
                                                    select t).Average());
            Console.WriteLine("Sum of all temps: {0}", (from t in winterTemps
                                                        select t).Sum());
        }

        #endregion
    }
}
