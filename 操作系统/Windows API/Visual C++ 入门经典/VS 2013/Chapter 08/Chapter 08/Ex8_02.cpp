// Ex8_02.cpp
// Using a destructor to free memory
#include <iostream>          // For stream I/O
#include <cstring>           // For strlen() and strcpy()
using std::cout;
using std::endl;

class CMessage
{
private:
  char* m_pMessage;                   // Pointer to object text string

public:

  // Function to display a message
  void showIt() const
  {
    cout << m_pMessage << endl;
  }

  // Constructor definition
  CMessage(const char* text = "Default message")
  {
    size_t length{ strlen(text) + 1 };
    m_pMessage = new char[length + 1];        // Allocate space for text
    strcpy_s(m_pMessage, length + 1, text);   // Copy text to new memory
  }

  ~CMessage();                               // Destructor prototype
};

// Destructor to free memory allocated by new
CMessage::~CMessage()
{
  cout << "Destructor called." << endl;    // Just to track what happens
  delete[] m_pMessage;                       // Free memory assigned to pointer
}

int main()
{
  // Declare object
  CMessage motto{ "A miss is as good as a mile." };

  // Dynamic object
  CMessage* pM{ new CMessage{ "A cat can look at a queen." } };

  motto.showIt();            // Display 1st message
  pM->showIt();              // Display 2nd message

  delete pM;                // Manually delete object created with new
  return 0;
}
