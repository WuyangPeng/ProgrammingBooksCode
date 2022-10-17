#pragma once

int in(int value)
{
    return value;
}

void out(int, int)
{
}

void wait(int)
{
}

class Thermometer
{
public:
    int Read()
    {
        return 0;
    }
};

class Heater
{
public:
    void Engage()
    {
    }

    void Disengage()
    {
    }
};