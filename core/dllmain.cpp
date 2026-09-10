#include "pch.h"

bool DllMain(HMODULE hModule, DWORD reasonCalled, void *lpReserved)
{
    switch (reasonCalled)
    {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return true;
}

