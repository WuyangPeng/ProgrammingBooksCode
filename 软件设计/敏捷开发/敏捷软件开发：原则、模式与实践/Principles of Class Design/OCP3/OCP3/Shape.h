#pragma once

class Shape
{
public:
    virtual void Draw() const = 0;
    bool Precedes(const Shape&) const;

    bool operator<(const Shape& s)
    {
        return Precedes(s);
    }

private:
    static const char* typeOrderTable[];
};