#ifndef CBRIDGE_H
#define CBRIDGE_H

class Cimpl;

class C {
  public:
    C( int val );
    ~C();
    int get_a() const;
    int get_b() const;
  private:
    Cimpl *impl_;
};

#endif
