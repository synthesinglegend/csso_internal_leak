#include <string>
#include <Windows.h>
#include <psapi.h>

#define InRange(x,a,b)  (x >= a && x <= b)
#define GetBits(x)    (InRange((x & (~0x20)),'A','F') ? ((x & (~0x20)) - 'A' + 0xA) : (InRange(x,'0','9') ? x - '0' : 0))
#define GetBytes(x)    (GetBits(x[0]) << 4 | GetBits(x[1]))

namespace Memory
{
    inline DWORD PatternScan(std::string moduleName, std::string pattern)
    {
        const char* pat = pattern.c_str();
        DWORD firstMatch = 0;
        DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
        MODULEINFO miModInfo;
        GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
        DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
        for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
        {
            if (!*pat)
                return firstMatch;

            if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == GetBytes(pat))
            {
                if (!firstMatch)
                    firstMatch = pCur;

                if (!pat[2])
                    return firstMatch;

                if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
                    pat += 3;

                else
                    pat += 2;
            }
            else
            {
                pat = pattern.c_str();
                firstMatch = 0;
            }
        }

        return NULL;
    }
}
