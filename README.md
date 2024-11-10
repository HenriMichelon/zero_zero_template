# ZeroZero template
********************************************************

Starter project for the [ZeroZero engine](https://henrimichelon.github.io/ZeroZero/)

[User documentation](https://henrimichelon.github.io/ZeroZero/)

 **How to use**
 - Clone this repository and the [ZeroZero repository](https://github.com/HenriMichelon/zero_zero)
 - Create a `.env.cmake` file in your project to set a variable called `Z0_PROJECT_DIR` with the **absolute** path to the ZeroZero directory, for example : 
 `set(Z0_PROJECT_DIR "C:/Users/MyUser/Documents/GitHub/zero_zero")`
 - `cmake -B build -G Ninja -D CMAKE_BUILD_TYPE=Release`
 - `cmake --build build`

    
