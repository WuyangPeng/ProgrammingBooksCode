/////////////////////////////////////////////////////////////////////////
// BinaryConversion.cpp
// by Dustin Clingman  1/14/04
//
// Purpose: This program demonstrates one way to convert numbers from binary 
//          decimel and vice versa
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <math.h>
using namespace std;

void showSelection();
void binarytoDecimal();
void decimaltoBinary();


int main()
{
    char choice;

    showSelection();
    cin>>choice;

    while(choice != 'q')
    {
      switch(choice)
       {
           case 'b':
                 binarytoDecimal();
                 break;
           case 'd':
                 decimaltoBinary();
                 break;
           default:
           cout<<"That is not a valid selection, Please try again.";
           break;
       }
      showSelection();
      cin>>choice;
     }//end while

 cout<<"Thanks for converting numbers!\n";
 return 0;
}

void showSelection()
     {
      cout<<"\n";
      cout<<"Welcome to The Binary Decimal Convertor!\n";
      cout<<"Would you like to convert a number from:\n"; 
      cout<<"[b]inary to decimal or [d]ecimal to binary]n";
      cout<<"Please enter q to quit\n";
	  cout<<"\n";
    }
 
 //This function will take up to a 8 bit binary number and convert it to decimal value.
void binarytoDecimal()
    {
    //the value is set low for better accuracy, go ahead and bump it to a higher value if you like
    //but remember there is a reason we don't code like this. :)

      char tobeconverted[9];
      int finalvalue =0;
      int powerval = 0;
           
      cout<<"Please enter a binary value (8 bits max) beginning with the most significant bit.\n";
      cin>>tobeconverted;

      //run from 0-7 = 8 bits total
      for(int j = 0; j<=7; j++)
       {
         //we have to reverse the power so the ordering is MSB first, then work down
         powerval = pow(2,(7-j));

         //test for a "1", otherwise it must be a zero. ALWAYS error trap these sort of things.
         if(tobeconverted[j] == '1')
            finalvalue = finalvalue + powerval;  
                
       }
     
       cout<<"The number converted from binary to decimal is "<<finalvalue<<"\n";
     }

//This function takes a valid integet and prints out a 32 bit binary representation 
//of the int. The output is 32 bits regardless of the size of the int. Feel free to
//tinker with this to suit your needs. 
void decimaltoBinary()
    {
      int tobeconverted;
      int binaryplaceholder[32];

      cout<<"Please enter a binary number consisting of ones and zeros\n";
      cin>>tobeconverted;
    
      //loop through the integer array looking at the number to be converted
      for(int i =0;i<32;i++)
       {
         //take the number and process modulus to retun a 1 or 0
         binaryplaceholder[i] = tobeconverted%2;
         
         //then we divide the number by two and revisit the number.
         tobeconverted = tobeconverted/2;
       }

   cout<<"Your decimal number converted to binary is: \n";
       //To make sure we are outputting in the proper order,
       //we print the array backwards.

       for(int j = 31; j>=0;j--)
        {
          cout<<binaryplaceholder[j];
        }
     
    }

//end BinaryConversion.cpp