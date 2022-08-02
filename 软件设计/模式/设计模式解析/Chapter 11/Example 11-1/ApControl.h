#pragma once

#typedef enum { LOW, HIGH } Resolution;

class ApControl
{
public:
    ApControl(void);
    void doDraw();
    void doPrint();
public:
    ~ApControl(void);
private:
    Resolution myResolution;
};