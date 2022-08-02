// Ex8_09A.cpp Creeping inefficiencies eliminated
#include <iostream>
#include <cstring>
#include <utility>
using std::cout;
using std::endl;

class CText
{
private:
  char* pText;

public:
  // Function to display text
  void showIt() const
  {
    cout << pText << endl;
  }

  // Constructor
  CText(const char* pStr = "No text")
  {
    cout << "CText constructor called." << endl;
    size_t len{ strlen(pStr) + 1 };
    pText = new char[len];                                 // Allocate space for text
    strcpy_s(pText, len, pStr);                            // Copy text to new memory
  }

  // Copy constructor definition
  CText(const CText& txt)
  {
    cout << "CText copy constructor called." << endl;
    size_t len{ strlen(txt.pText) + 1 };
    pText = new char[len];
    strcpy_s(pText, len, txt.pText);
  }

  // Move constructor definition
  CText(CText&& txt)
  {
    cout << "CText move constructor called." << endl;
    pText = txt.pText;
    txt.pText = nullptr;
  }

  // Destructor to free memory allocated by new
  ~CText()
  {
    cout << "CText destructor called." << endl;            // Just to track what happens
    delete[] pText;                                        // Free memory
  }

  // Assignment operator for CText objects
  CText& operator=(const CText& txt)
  {
    cout << "CText assignment operator function called." << endl;
    if (this != &txt)                                      // Check addresses not equal
    {
      delete[] pText;                                      // Release memory for 1st operand
      size_t length{ strlen(txt.pText) + 1 };
      pText = new char[length];

      // Copy 2nd operand string to 1st
      strcpy_s(this->pText, length, txt.pText);
    }
    return *this;                                          // Return a reference to 1st operand
  }

  // Move assignment operator for CText objects
  CText& operator=(CText&& txt)
  {
    cout << "CText move assignment operator function called." << endl;
    delete[] pText;                                        // Release memory for 1st operand
    pText = txt.pText;
    txt.pText = nullptr;
    return *this;                                          // Return a reference to 1st operand
  }

  // Overloaded addition operator
  CText operator+(const CText& txt) const
  {
    cout << "CText add operator function called." << endl;
    size_t length{ strlen(pText) + strlen(txt.pText) + 1 };
    CText aText;
    aText.pText = new char[length];
    strcpy_s(aText.pText, length, pText);
    strcat_s(aText.pText, length, txt.pText);
    return aText;
  }
};

class CMessage
{
private:
  CText m_Text;                    // Object text string

public:
  // Function to display a message
  void showIt() const
  {
    m_Text.showIt();
  }

  // Overloaded addition operator
  CMessage operator+(const CMessage& aMess) const
  {
    cout << "CMessage add operator function called." << endl;
    CMessage message;
    message.m_Text = m_Text + aMess.m_Text;
    return message;
  }

  // Copy assignment operator for CMessage objects
  CMessage& operator=(const CMessage& aMess)
  {
    cout << "CMessage copy assignment operator function called." << endl;
    if (this != &aMess)               // Check addresses not equal
    {
      m_Text = aMess.m_Text;
    }
    return *this;                    // Return a reference to 1st operand
  }

  // Move assignment operator for CMessage objects
  CMessage& operator=(CMessage&& aMess)
  {
    cout << "CMessage move assignment operator function called." << endl;
    m_Text = std::move(aMess.m_Text);
    return *this;                    // Return a reference to 1st operand
  }

  // Constructor definition
  CMessage(const char* str = "Default message")
  {
    cout << "CMessage constructor called." << endl;
    m_Text = CText(str);
  }

  // Copy constructor definition
  CMessage(const CMessage& aMess)
  {
    cout << "CMessage copy constructor called." << endl;
    m_Text = aMess.m_Text;
  }

  // Move constructor definition
  CMessage(CMessage&& aMess)
  {
    cout << "CMessage move constructor called." << endl;
    m_Text = std::move(aMess.m_Text);
  }
};

int main()
{
  CMessage motto1{ "The devil takes care of his own. " };
  CMessage motto2{ "If you sup with the devil use a long spoon.\n" };

  cout << endl << " Executing: CMessage motto3(motto1+motto2); " << endl;
  CMessage motto3{ motto1 + motto2 };
  cout << " Done!! " << endl << endl << "motto3 contains:" << endl;
  motto3.showIt();
  CMessage motto4;
  cout << " Executing: motto4 = motto3 + motto2; " << endl;
  motto4 = motto3 + motto2;
  cout << " Done!! " << endl << endl << "motto4 contains:" << endl;
  motto4.showIt();

  return 0;
}
