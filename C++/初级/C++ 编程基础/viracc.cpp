#include <iostream>

class Base
{
public:
  void PublicNonVirtual(){cout << "Base::PublicNonVirtual" << endl;};
  virtual void PublicVirtual(){cout << "Base::PublicVirtual" << endl;};

protected:
  void ProtectedNonVirtual(){cout << "Base::ProtectedNonVirtual" << endl;};
  virtual void ProtectedVirtual(){cout << "Base::ProtectedVirtual" << endl;};

private:
  void PrivateNonVirtual(){cout << "Base::PrivateNonVirtual" << endl;};
  virtual void PrivateVirtual(){cout << "Base::PrivateVirtual" << endl;};

public:
  void BaseTest();

};

class Derived : public Base
{
public:
  void PublicNonVirtual(){cout << "Derived::PublicNonVirtual" << endl;};
  virtual void PublicVirtual(){cout << "Derived::PublicVirtual" << endl;};

protected:
  void ProtectedNonVirtual(){cout << "Derived::ProtectedNonVirtual" << endl;};
  virtual void ProtectedVirtual(){cout << "Derived::ProtectedVirtual" << endl;};

private:
  void PrivateNonVirtual(){cout << "Derived::PrivateNonVirtual" << endl;};
  virtual void PrivateVirtual(){cout << "Derived::PrivateVirtual" << endl;};

public:
  void DerivedTest();
};


void Base::BaseTest()
{
  Derived DerivedObject;

  cout << "Base Test" << endl;
  DerivedObject.PublicNonVirtual();
//DerivedObject.ProtectedNonVirtual();
//DerivedObject.PrivateNonVirtual();

  PublicVirtual();
  ProtectedVirtual();
  PrivateVirtual();

  cout << endl;
}

void Derived::DerivedTest()
{
  Base* x = new Base;

  cout << "Derived Test" << endl;

  Base::PublicNonVirtual();
  Base::ProtectedNonVirtual();
//Base::PrivateNonVirtual();

  PublicVirtual();
  ProtectedVirtual();
  PrivateVirtual();

  x->ProtectedVirtual();

  cout << endl;
}

main()
{
  Base* BaseBase = new Base;
  Base* DerivedBase = new Derived;
  Derived* DerivedDerived = new Derived;

  cout << endl;
  BaseBase->BaseTest();
  DerivedBase->BaseTest();
  DerivedDerived->DerivedTest();
}

