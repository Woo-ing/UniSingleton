# UniSingleton For C++

## Project Description
A simple can easily encapsulate normal C++ classes into singleton classes, can support both classes with and without instance() function, and with several singleton instance management functions. Some usage examples are provided in main.cpp.

## How to compile

+ For Linux systems

1. Go to the project directory and execute:

    ``` bash
    cmake -B./build
    ```
2. Go to the build directory and run the following command:

    ``` bash
    ./UniSignleton
    ```

+ For Windows systems

1. Go to the project directory in the console and execute:

    ``` bash
    cmake -B./build -G"Visual Studio 17 2022"
    ```
2. Go to the build directory in the file browser and double-click UniSingleton.sln;
3. Use Visual Studio to compile the project.