# UniSingleton For C++

## 项目描述
一个可以方便将普通的 C++ 类封装成单例类，可同时支持带 instance() 函数和不带 instance() 函数的对象类，并带有一定的单例对象管理功能，在 main.cpp 中给出了详细的几种调用方式。

## 如何编译

对于 linux 系统

1. 进入工程目录，执行:

    ``` bash
    cmake -B./build
    ```
2. 进入build目录，执行:

    ``` bash
    ./UniSignleton
    ```

对于 windows 系统

1. 在控制台中进入工程目录，执行:

    ``` bash
    cmake -B./build -G"Visual Studio 17 2022"
    ```
2. 在文件浏览器中进入build目录，双击 UniSingleton.sln;
3. 使用 Visual Studio 编译工程。