#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include <iostream>
#include <string>

using namespace std;

class Product
{
public:
   /**
      Constructs a product with zero price and score.
   */
   Product();

   /**
      Reads in this product object.
   */   
   void read();

   /**
      Compares two product objects.
      @param b the object to compare with this object
      @retur true if this object is better than b
   */
   bool is_better_than(Product b) const;

   /**
      Print this product object
   */
   void print() const;
private:
   string name;
   double price;
   int score;
};

Product::Product()
{  
   price = 0;
   score = 0;
}

void Product::read()
{  
   cout << "Please enter the model name: ";
   getline(cin, name);
   cout << "Please enter the price: ";
   cin >> price;
   cout << "Please enter the score: ";
   cin >> score;
   string remainder; /* read remainder of line */
   getline(cin, remainder);
}

bool Product::is_better_than(Product b) const
{  
   if (price == 0) return false;
   if (b.price == 0) return true;
   return score / price > b.score / b.price;
}

void Product::print() const
{  
   cout << name
      << " Price: " << price
      << " Score: " << score << "\n";
}

int main()
{  
   vector<Product> products;

   Product best_product;
   int best_index = -1;

   bool more = true;
   while (more)
   {  
      Product next_product;
      next_product.read();
      products.push_back(next_product);

      if (next_product.is_better_than(best_product))
      {  
         best_index = products.size() - 1;
         best_product = next_product;
      }     

      cout << "More data? (y/n) ";
      string answer;
      getline(cin, answer);
      if (answer != "y") more = false;
   }

   for (int i = 0; i < products.size(); i++)
   {
      if (i == best_index) cout << "best value => ";
      products[i].print();
   }

   return 0;
}
