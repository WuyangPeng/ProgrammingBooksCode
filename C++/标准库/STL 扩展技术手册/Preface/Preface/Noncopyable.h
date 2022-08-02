#pragma once

class Noncopyable
{
public:  // Member Types
    typedef Noncopyable class_type;
    // ...
private:  // Not to be implemented
    Noncopyable(class_type const&);
    class_type& operator=(class_type const&);
};