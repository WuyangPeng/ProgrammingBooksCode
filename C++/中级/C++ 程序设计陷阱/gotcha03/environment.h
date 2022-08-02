#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

class Environment { // Singleton
  public:
    static Environment &instance();
    virtual void op1() = 0;
    // other operations...
  protected:
    Environment();
    virtual ~Environment();
  private:
    static Environment *instance_;
	// member data...
	friend class Destroyer;
};

#endif
