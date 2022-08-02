//DISPLAY 15.13 More Inheritance with Virtual Functions
//Program to illustrate use of a virtual function
//to defeat the slicing problem.

#include <string>
#include <iostream>
using namespace std;

class Pet
{
public:
    virtual void print();
    string name;
};

class Dog : public Pet
{
public:
    virtual void print();//Keyword virtual not needed, but put
                         //here for clarity. (It is also good style!)

string breed;
};

int main()
{
    Dog vDog;
    Pet vPet;

    vDog.name = "Tiny";
    vDog.breed = "Great Dane";
    vPet = vDog;

    //vPet.breed; is illegal since class Pet has no member named breed

    Dog *pDog;
    pDog = new Dog;
    pDog->name = "Tiny";
    pDog->breed = "Great Dane";

    Pet *pPet;
    pPet = pDog;
    pPet->print(); // These two print the same output:
    pDog->print(); // name: Tiny breed: Great Dane

    //The following, which accesses member variables directly
    //rather than via virtual functions, would produce an error:
    //cout << "name: " << pPet->name << "  breed: "
    //     << pPet->breed << endl;
    //generates an error message: 'class Pet' has no member
    //named 'breed' .
    //See Pitfall section "Not Using Virtual Member Functions"
    //for more discussion on this.

    return 0;
}

void Dog::print()
{
    cout << "name: " << name << endl;
    cout << "breed: " << breed << endl;
}

void Pet::print()

{
    cout << "name: " << endl;//Note no breed mentioned
}
