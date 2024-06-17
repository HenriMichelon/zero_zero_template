# ZeroZero template

Starter project for the [ZeroZero engine](https://henrimichelon.github.io/ZeroZero/)

**Building tools needed**
 - GCC 11+ (for example, [MingW64 13.x, 64bits, win32 threads, MSVCRT](https://github.com/niXman/mingw-builds-binaries))
 - [CMake 3.29+](https://cmake.org/download/) with a [build tool](https://github.com/ninja-build/ninja/releases)
 - [Vulkan SDK 1.3.28x+](https://vulkan.lunarg.com/)

 **How to use**
 - Clone this repository and the [ZeroZero repository](https://github.com/HenriMichelon/zero_zero)
 - Create a `.env.cmake` file in your project with a variable called `Z0_PROJECT_DIR` to reference the ZeroZero cloned directory, for example : 
 `set(Z0_PROJECT_DIR "C:/Users/MyUser/Documents/GitHub/zero_zero")`
 - If needed adjust the `CMakeLists.txt` settings to your needs
 - `cmake -B build -G Ninja -D CMAKE_BUILD_TYPE=Release` (adapt to your build tool)
 - `cmake --build build`

    
