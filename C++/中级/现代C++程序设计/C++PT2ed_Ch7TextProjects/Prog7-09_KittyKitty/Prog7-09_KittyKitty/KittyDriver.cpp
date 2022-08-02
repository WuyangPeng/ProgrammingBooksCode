//File: KittyKitty.cpp

//This program demonstrates how to use 
//pointers and references with objects.

#include "Kitty.h"

//prototypes, one with a pointer,
//one with a reference
void FillCatInfo(Kitty *pCat);  
void FillCatInfo(Kitty &rCat); 

void PrintCatInfo(Kitty *pCat);
void PrintCatInfo(Kitty &rCat); 

int main()
{
    Kitty meow, yowl;

    cout << "The Kitty-Cat Program \n";
	
	//we pass the address to a pointer
    FillCatInfo(&meow);	
	
	//we pass the reference here
    FillCatInfo(yowl);

	PrintCatInfo(&meow);	//pointer
	PrintCatInfo(yowl);		//reference

	cout << "\n\nNo more kitties for you.  \n";                                              
    return 0;
}

void FillCatInfo(Kitty * pCat)  //pointer use ->
{
    pCat->SetBreed("Alley Cat");   
    pCat->SetName("Thomas" );
    pCat->SetFavFood("Milk");
}

void FillCatInfo(Kitty & rCat)   //reference use .
{
    rCat.SetBreed("Siamese" ); 
    rCat.SetName("Comehere Kitty");
    rCat.SetFavFood("Fresh birdies");
}           

void PrintCatInfo(Kitty *pCat)
{	
	pCat->PrintCatInfo();
}

void PrintCatInfo(Kitty &rCat)
{
	rCat.PrintCatInfo();
}


                                           