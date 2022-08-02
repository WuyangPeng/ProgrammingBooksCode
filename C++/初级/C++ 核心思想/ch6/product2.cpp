#include <iostream>
#include <string>

using namespace std;

class Product
{
public:
   /**
      Constructs a product with score 0 and price 1.
   */
   Product();

   /**
      Reads in this product object.
   */   
   void read();

   /**
      Compares two product objects.
      @param b the object to compare with this object
      @return true if this object is better than b
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
   price = 1;
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
   if (b.price == 0) return false;
   if (price == 0) return true;
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
   Product best;

   bool more = true;
   while (more)
   {  
      Product next;
      next.read();
      if (next.is_better_than(best)) best = next;

      cout << "More data? (y/n) ";
      string answer;
      getline(cin, answer);
      if (answer != "y") more = false;
   }

   cout << "The best value is ";
   best.print();

   return 0;
}
