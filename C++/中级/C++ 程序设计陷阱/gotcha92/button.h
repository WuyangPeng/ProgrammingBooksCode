#ifndef BUTTON_H
#define BUTTON_H

#include <string>

class Action {
  public:
    virtual ~Action();
    virtual void operator ()() = 0;
    virtual Action *clone() const = 0;
};

class Button {
  public:
    Button( const char *label );
    ~Button();
    void press() const;
    void setAction( const Action * );
  private:
    std::string label_;
    Action *action_;
};

class NullAction : public Action {
  public:
    void operator ()()
        {}
    NullAction *clone() const
        { return new NullAction; }
};

#endif
