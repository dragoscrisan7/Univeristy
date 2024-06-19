#include "windows.h"
#include <iostream>

static int a;

static void __stdcall iterator(LPVOID callingFiber)
{
    for (int i = 0; i < 10; ++i)
    {
        a = i * i;
        SwitchToFiber(callingFiber);
    }
    a = -1;
    SwitchToFiber(callingFiber);
}

int main()
{
    LPVOID thisFiber = ConvertThreadToFiber(nullptr);
    LPVOID iteratorFiber = CreateFiber(0x8000, &iterator, thisFiber);
    while (true)
    {
        SwitchToFiber(iteratorFiber);
        if (a == -1) break;
        std::cout << a << "\n";
    }
    DeleteFiber(iteratorFiber);
}