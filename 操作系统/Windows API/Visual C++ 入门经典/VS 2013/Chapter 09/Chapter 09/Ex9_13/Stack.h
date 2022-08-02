#pragma once
class CBox;                           // Forward class declaration
class CStack
{
private:
  // Defines items to store in the stack
  struct CItem
  {
    CBox* pBox;                       // Pointer to the object in this node
    CItem* pNext;                     // Pointer to next item in the stack or null

    // Constructor
    CItem(CBox* pB, CItem* pN) : pBox{ pB }, pNext{ pN } {}
  };

  CItem* pTop{};                     // Pointer to item that is at the top

public:
  CStack() = default;                   // Constructor

  // Inhibit copy construction and assignment
  CStack(const CStack& stack) = delete;
  CStack& operator=(const CStack& stack) = delete;

  // Push a Box object onto the stack
  void push(CBox* pBox)
  {
    pTop = new CItem(pBox, pTop);     // Create new item and make it the top
  }

  // Pop an object off the stack
  CBox* pop()
  {
    if (!pTop)                         // If the stack is empty
      return nullptr;                 // return null

    CBox* pBox = pTop->pBox;          // Get box from item
    CItem* pTemp = pTop;              // Save address of the top item
    pTop = pTop->pNext;               // Make next item the top
    delete pTemp;                     // Delete old top item from the heap
    return pBox;
  }

  // Destructor
  virtual ~CStack()
  {
    CItem* pTemp{};
    while (pTop)                       // While pTop not null
    {
      pTemp = pTop;
      pTop = pTop->pNext;
      delete pTemp;
    }
  }
};
