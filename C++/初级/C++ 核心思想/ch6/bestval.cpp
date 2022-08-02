#include <iostream>
#include <string>

using namespace std;

int main()
{  
   string best_name = "";
   double best_price = 1;
   int best_score = 0;

   bool more = true;
   while (more)
   {  
      string next_name;
      double next_price;
      int next_score;

      cout << "Please enter the model name: ";
      getline(cin, next_name);
      cout << "Please enter the price: ";
      cin >> next_price;
      cout << "Please enter the score: ";
      cin >> next_score;
      string remainder; /* read remainder of line */
      getline(cin, remainder); 

      if (next_score / next_price > best_score / best_price)
      {  
         best_name = next_name;
         best_score = next_score;
         best_price = next_price;
      }     

      cout << "More data? (y/n) ";
      string answer;
      getline(cin, answer);
      if (answer != "y") more = false;
   }

   cout << "The best value is " << best_name
      << " Price: " << best_price 
      << " Score: " << best_score << "\n";

   return 0;
}
