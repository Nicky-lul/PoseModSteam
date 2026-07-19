#include <windows.h>
#include <tlhelp32.h>
#include <fstream>
#include <string>


DWORD FindProcess(const wchar_t* processName)
{
    PROCESSENTRY32W entry{};
    entry.dwSize = sizeof(entry);

    HANDLE snapshot = CreateToolhelp32Snapshot(
        TH32CS_SNAPPROCESS,
        0
    );

    if (snapshot == INVALID_HANDLE_VALUE)
        return 0;

    if (Process32FirstW(snapshot, &entry))
    {
        do
        {
            if (_wcsicmp(entry.szExeFile, processName) == 0)
            {
                CloseHandle(snapshot);
                return entry.th32ProcessID;
            }

        } while (Process32NextW(snapshot, &entry));
    }

    CloseHandle(snapshot);
    return 0;
}


std::string GetSteamAppID()
{
    std::ifstream file("steam_appid.txt");

    if (!file)
        return "";

    std::string appID;
    std::getline(file, appID);

    return appID;
}


bool InjectDLL(DWORD pid, const char* dllPath)
{
    HANDLE process = OpenProcess(
        PROCESS_ALL_ACCESS,
        FALSE,
        pid
    );

    if (!process)
        return false;


    void* memory = VirtualAllocEx(
        process,
        nullptr,
        strlen(dllPath) + 1,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_READWRITE
    );

    if (!memory)
    {
        CloseHandle(process);
        return false;
    }


    if (!WriteProcessMemory(
        process,
        memory,
        dllPath,
        strlen(dllPath) + 1,
        nullptr))
    {
        CloseHandle(process);
        return false;
    }


    HMODULE kernel32 = GetModuleHandleA("kernel32.dll");

    FARPROC loadLibrary = GetProcAddress(
        kernel32,
        "LoadLibraryA"
    );


    HANDLE thread = CreateRemoteThread(
        process,
        nullptr,
        0,
        (LPTHREAD_START_ROUTINE)loadLibrary,
        memory,
        0,
        nullptr
    );


    if (!thread)
    {
        CloseHandle(process);
        return false;
    }


    WaitForSingleObject(thread, INFINITE);

    CloseHandle(thread);
    CloseHandle(process);

    return true;
}


int WINAPI WinMain(
    HINSTANCE,
    HINSTANCE,
    LPSTR,
    int
)
{
    std::string appID = GetSteamAppID();

    if (appID.empty())
        return 1;


    std::string steamURL =
        "steam://rungameid/" + appID;


    ShellExecuteA(
        nullptr,
        "open",
        steamURL.c_str(),
        nullptr,
        nullptr,
        SW_SHOWNORMAL
    );


    DWORD pid = 0;


    while (pid == 0)
    {
        Sleep(1000);

        pid = FindProcess(
            L"YandereSimulator.exe"
        );
    }


    InjectDLL(
        pid,
        "PoseMod/Modules/pmmono64.dll"
    );


    return 0;
}