#define _CRT_SECURE_NO_WARNINGS
#include "General_system.h"
#include <iostream>
#include <stdio.h>

using namespace std;

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( NORMAL_BLOCK ,FILE_ , _LINE_ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

void work()
{
    General_System system;
    system.Generator();
}


int main()
{

    work();
    _CrtDumpMemoryLeaks();
    cout << "Leaks: " << _CrtDumpMemoryLeaks() << endl;
    return 0;
}

