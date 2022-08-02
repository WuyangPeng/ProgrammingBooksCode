#include <iostream>
#include "environment.h"

class OfficialEnv : public Environment {
  public:
	void op1()
		{ std::cout << "OfficialEnv::op1" << std::endl; }
};

Environment::Environment()
	{ std::cout << "Created" << std::endl; }

Environment::~Environment()
	{ std:: cout << "Destroyed" << std:: endl; }

Environment *Environment::instance_ = 0;

Environment &Environment::instance() {
    if( !instance_ )
        instance_ = new OfficialEnv;
    return *instance_;
}

// Simple mechanism for Singleton cleanup.  Often works,
// but is far from foolproof.
class Destroyer {
  public:
	~Destroyer() { delete Environment::instance_; }
};
namespace {
Destroyer d;
}
