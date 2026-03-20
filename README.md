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
