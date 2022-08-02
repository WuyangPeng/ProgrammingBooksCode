//
//  main.cpp
//  DispatchPerformance
//
//  Created by Phillip Voyle on 14/04/15.
//  Copyright (c) 2015 PV. All rights reserved.
//

#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

enum DispatchID
{
    ONE,
    TWO,
    THREE,
    FOUR
};

class CDispatch
{
    DispatchID dispid;
public:

    DispatchID get_dispid()
    {
        return dispid;
    }
    
    CDispatch(DispatchID disp):dispid(disp)
    {
    }

    virtual int test_me_virtual() = 0;
};

template<DispatchID disp>
class CDispatchImpl: public CDispatch
{
public:
    CDispatchImpl():CDispatch(disp)
    {
    }
    
    int test_me();
    
    int test_me_nonvirtual()
    {
        return test_me();
    }
    
    int test_me_virtual()
    {
        return test_me();
    }
};

template<>
int CDispatchImpl<ONE>::test_me()
{
    return 1;
}

template<>
int CDispatchImpl<TWO>::test_me()
{
    return 2;
}

template<>
int CDispatchImpl<THREE>::test_me()
{
    return 3;
}

template<>
int CDispatchImpl<FOUR>::test_me()
{
    return 4;
}

int test_me_switch(CDispatch* disp)
{
    switch (disp->get_dispid()) {
    case ONE:
        return ((CDispatchImpl<ONE>*) disp)->test_me_nonvirtual();
    case TWO:
        return ((CDispatchImpl<TWO>*) disp)->test_me_nonvirtual();
    case THREE:
        return ((CDispatchImpl<THREE>*) disp)->test_me_nonvirtual();;
    case FOUR:
        return ((CDispatchImpl<FOUR>*) disp)->test_me_nonvirtual();
    }
}

const int SIZE = 1000;
const int ITERATIONS = 1000000;

std::vector<std::shared_ptr<CDispatch>> setup()
{
    std::vector<std::shared_ptr<CDispatch>> parameters(SIZE);
    for(int a = 0; a < SIZE; a++)
    {
        switch (rand() % 4) {
        case 0:
            parameters[a] = std::make_shared<CDispatchImpl<ONE>>();
            break;
        case 1:
            parameters[a] = std::make_shared<CDispatchImpl<TWO>>();
            break;
        case 2:
            parameters[a] = std::make_shared<CDispatchImpl<THREE>>();
            break;
        case 3:
            parameters[a] = std::make_shared<CDispatchImpl<FOUR>>();
            break;
        }
    }
    return parameters;
}

  using namespace std;


void execute_1(std::vector<int>& results, const std::vector<std::shared_ptr<CDispatch>>& parameters)
{
    clock_t begin = clock();
    for(int b = 0; b < ITERATIONS; b++)
    {
        for(int a = 0; a < SIZE; a++)
        {
            results[a] = test_me_switch(parameters[a].get());
        }
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "elapsed:" << elapsed_secs << std::endl;
}

void execute_2(std::vector<int>& results, const std::vector<std::shared_ptr<CDispatch>>& parameters)
{
    clock_t begin = clock();

    for(int b = 0; b < ITERATIONS; b++)
    {
        for(int a = 0; a < SIZE; a++)
        {
            results[a] = parameters[a]->test_me_virtual();
        }
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "elapsed:" << elapsed_secs << std::endl;
}


int main(int argc, const char * argv[])
{
    std::cout << "setting up...." << std::endl;
    std::vector<std::shared_ptr<CDispatch>> parameters = setup();

    std::cout << "initialising..." << std::endl;
    std::vector<int> results(SIZE);
   
    std::cout << "executing nonvirtual..." << std::endl;
    execute_1(results, parameters);
    std::cout << "executing virtual..." << std::endl;
    execute_2(results, parameters);
    return 0;
}
