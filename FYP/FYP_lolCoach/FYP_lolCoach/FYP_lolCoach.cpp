// FYP_lolCoach.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <string>
#include "TestHeader.h"
#include "SystemMain.h"


void test()
{
    string command = "python hello.py";
    system(command.c_str());
}
int main()
{
    std::cout << "This is gonna be my FYP!\n";
    //TestHeader t1;
    //t1.ReadJsonMethod();
    SystemMain h1;
    h1.EngineMain();
    
   /* thread pthyonthreadcall(test);
    std::cout << "Still running\n";
    test();
    pthyonthreadcall.join();*/

}