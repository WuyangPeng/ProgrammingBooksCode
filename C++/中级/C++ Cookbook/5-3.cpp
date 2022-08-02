void f( ) {
  char* x = asctime(localtime(time(0)));
  wait_for_15_seconds( ); // do some long processing task 
  asctime(localtime(time(0)));
  cout << x << endl; // prints out the current time, not fifteen seconds ago
}
