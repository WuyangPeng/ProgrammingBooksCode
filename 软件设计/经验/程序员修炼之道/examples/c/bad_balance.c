/**
  * From "How to Balance Resources", illustrate bad resource balancing
  */

#include <stdio.h>

typedef struct {
  double balance;
} Customer;

FILE *cFile;

//START:code
void readCustomer(const char *fName, Customer *cRec) {
  
  cFile = fopen(fName, "r+");
  fread(cRec, sizeof(*cRec), 1, cFile);
}

void writeCustomer(Customer *cRec) {

  rewind(cFile);
  fwrite(cRec, sizeof(*cRec), 1, cFile);
  fclose(cFile);
}

void updateCustomer(const char *fName, double newBalance) {

  Customer cRec;
  
  readCustomer(fName, &cRec);

  cRec.balance = newBalance;

  writeCustomer(&cRec);
}
//END:code

#ifdef NEVER
//START:new_update
void updateCustomer(const char *fName, double newBalance) {

  Customer cRec;
  
  readCustomer(fName, &cRec);

  if (newBalance >= 0.0) {
    cRec.balance = newBalance;

    writeCustomer(&cRec);
  }
}
//END:new_update

//START:bad_update
void updateCustomer(const char *fName, double newBalance) {

  Customer cRec;
  
  readCustomer(fName, &cRec);

  if (newBalance >= 0.0) {
    cRec.balance = newBalance;

    writeCustomer(&cRec);
  }
  else
    fclose(cFile);
}
//END:bad_update
#endif

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
