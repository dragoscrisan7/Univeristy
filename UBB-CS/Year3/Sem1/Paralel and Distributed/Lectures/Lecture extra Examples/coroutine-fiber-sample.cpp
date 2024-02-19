#include "windows.h"
#include <iostream>

static int a;

LPVOID coro_main;
LPVOID coro1;
LPVOID coro2;

static void __stdcall func1(LPVOID )
{
    std::cout << "func1() begin\n";
    SwitchToFiber(coro2);
    std::cout << "func1() end\n";
    SwitchToFiber(coro_main);
}

static void __stdcall func2(LPVOID callingFiber)
{
    std::cout << "func2() begin\n";
    SwitchToFiber(coro_main);
    std::cout << "func2() end\n";
    SwitchToFiber(coro_main);
}

int main()
{
    coro_main = ConvertThreadToFiber(nullptr);
    coro1 = CreateFiber(0x8000, &func1, nullptr);
    coro2 = CreateFiber(0x8000, &func2, nullptr);

    std::cout << "Msg 1\n";
    SwitchToFiber(coro1);
    std::cout << "Msg 2\n";
    SwitchToFiber(coro2);
    std::cout << "Msg 3\n";
    SwitchToFiber(coro1);
    std::cout << "Msg 4\n";

    DeleteFiber(coro1);
    DeleteFiber(coro2);
    ConvertFiberToThread();
}