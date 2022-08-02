
//Listing 7-5

  extern int Answer;

  void *task1(void *X)
  {
     Answer = Answer * 32;
  }

  void *task2(void *X)
  {
     Answer = Answer / 2;
  }

  void *task3(void *X)
  {
     Answer = Answer + 5;
  }
