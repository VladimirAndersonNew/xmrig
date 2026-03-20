# XMRig DLL Build

This fork allows you to build XMRig as a **DLL** instead of an executable.

---

## Build Instructions

### 1. Download Dependencies

Download the pre-built dependency archive from [xmrig-deps](https://github.com/xmrig/xmrig-deps) and extract it to `C:\xmrig-deps`.

The folder structure should look like this:

```
C:\xmrig-deps
└── msvc2022
    └── x64
        ├── include
        └── lib
```

---

### 2. Clone the Repository

```bash
git clone https://github.com/VladimirAndersonNew/xmrig-dll
cd xmrig
```

---

### 3. Configure with CMake

Create a build folder and run CMake:

```bash
mkdir build && cd build
```

Choose the command that matches your toolchain:

**Visual Studio 2022 (x64):**

```bash
cmake .. -G "Visual Studio 17 2022" -A x64 -DXMRIG_DEPS="C:\xmrig-deps\msvc2022\x64"
```

**Visual Studio 2019 (x64):**

```bash
cmake .. -G "Visual Studio 16 2019" -A x64 -DXMRIG_DEPS="C:\xmrig-deps\msvc2019\x64"
```

**MSYS2 / MinGW (x64):**

```bash
cmake .. -G "Unix Makefiles" -DXMRIG_DEPS="C:/xmrig-deps/gcc/x64"
```

**MSYS2 / MinGW (x86):**

```bash
cmake .. -G "Unix Makefiles" -DXMRIG_DEPS="C:/xmrig-deps/gcc/x86"
```

---

### 4. Build

```bash
cmake --build . --config Release
```

The resulting DLL will be located at:

```
build/Release/xmrig.dll
```
### 5. Run 

Loader example using two exported functions: `xmrig_start` and `xmrig_stop`.

```c
#include <windows.h>
#include <stdio.h>

typedef int (*StartFunc)(int argc, char** argv);
typedef void (*StopFunc)();

DWORD WINAPI MinerThread(LPVOID lpParam) {
    StartFunc start = (StartFunc)lpParam;
    char* argv[] = { "xmrig", "--config", "config.json" };
    int argc = 3;
    int ret = start(argc, argv);
    printf("[DEBUG] xmrig_start returned: %d\n", ret);
    return 0;
}

int main(int argc, char* argv[]) {
    // Usage: loader.exe <dll_path> [config_path]
    if (argc < 2) {
        printf("Usage: %s <xmrig.dll> [config.json]\n", argv[0]);
        return 1;
    }

    const char* dllPath = argv[1];
    const char* configPath = (argc >= 3) ? argv[2] : "config.json";

    HMODULE hDll = LoadLibraryA(dllPath);
    if (!hDll) {
        printf("[ERROR] Failed to load %s. Error: %lu\n", dllPath, GetLastError());
        return 1;
    }

    StartFunc start = (StartFunc)GetProcAddress(hDll, "xmrig_start");
    StopFunc stop = (StopFunc)GetProcAddress(hDll, "xmrig_stop");

    if (!start || !stop) {
        printf("[ERROR] Functions not found.\n");
        FreeLibrary(hDll);
        return 1;
    }

    printf("[INFO] DLL loaded. Starting miner...\n");
    HANDLE hThread = CreateThread(NULL, 0, MinerThread, (LPVOID)start, 0, NULL);
    if (!hThread) {
        printf("[ERROR] Failed to create thread. Error: %lu\n", GetLastError());
        FreeLibrary(hDll);
        return 1;
    }
    printf("[INFO] Miner is running. Press Enter to stop...\n");
    getchar();

    stop();
    printf("[INFO] Stop signal sent.\n");

    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    FreeLibrary(hDll);
    printf("[INFO] Cleanup done.\n");

    return 0;
}
```

---

## Donation Settings

By default, the donation to the original XMRig developer is **disabled** in this fork.

If you wish to re-enable it, edit `src/donate.h` and set:

```cpp
constexpr const int kDefaultDonateLevel = 1;
constexpr const int kMinimumDonateLevel = 1;
```

---

## By me a coffee : )

If you find this fork useful, consider donating:

**XMR:**

```
47kgGV3Mt5cjEiRqBTdDagZ34NhDJL62Y5aJgUdjLsgjMkYPnNoMdg9Wo9Lgk9T2AxbKovx4tZXz4Aws9aZxStYSRrQ6Pbv
```
