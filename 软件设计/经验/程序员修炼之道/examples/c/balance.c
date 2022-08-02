/**
  * From "How to Balance Resources", illustrate better resource balancing.
  */

#include <stdio.h>

typedef struct {
  double balance;
} Customer;


//START:code
void readCustomer(FILE *cFile, Customer *cRec) {
  fread(cRec, sizeof(*cRec), 1, cFile);
}

void writeCustomer(FILE *cFile, Customer *cRec) {
  rewind(cFile);
  fwrite(cRec, sizeof(*cRec), 1, cFile);
}

void updateCustomer(const char *fName, double newBalance) {
  FILE *cFile;
  Customer cRec;
  
  cFile = fopen(fName, "r+");        // >---
  readCustomer(cFile, &cRec);        //     |
  if (newBalance >= 0.0) {           //     |
    cRec.balance = newBalance;       //     |
    writeCustomer(cFile, &cRec);     //     |
  }                                  //     |
  fclose(cFile);                     // <---
}
//END:code

int main(int argc, char **argv) {

  if (argc > 1) {
    updateCustomer(argv[1], -1.0);
    updateCustomer(argv[1], 0.0);
    updateCustomer(argv[1], 1.0);
  }
  else
    fprintf(stderr, "Missing file name\n");

  return 0;
}
