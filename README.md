# CatchTheRain
A Simple C++ SFML Game (My very first game). I've provided with the default sfml-app that I built. If you want to build one yourself, follow the steps below. Please also note that, I've was using the Mac version of SFML, so variations may occur.


To build and run an SFML (Simple and Fast Multimedia Library) application in C++, you'll need to follow these general steps:

Install SFML:
Make sure you have SFML installed on your system. You can download it from the official website (https://www.sfml-dev.org/) and follow the installation instructions specific to your platform.

Create a C++ source file:
Copy and paste your C++ code into a .cpp file, for example, main.cpp.

Write a CMakeLists.txt file (for CMake users):
If you're using CMake to manage your project, create a CMakeLists.txt file in the same directory as your source file. Here's a minimal CMakeLists.txt file for an SFML project:

cmake_minimum_required(VERSION 3.0)

project(SFMLApp)

find_package(SFML 2.5 REQUIRED system window graphics audio)

add_executable(SFMLApp main.cpp)

target_link_libraries(SFMLApp sfml-system sfml-window sfml-graphics sfml-audio)

Build your application:
Open a terminal or command prompt and navigate to the directory containing your source code and CMakeLists.txt file. Run the following commands:

mkdir build
cd build
cmake ..
make

This will generate the executable for your SFML application.

Run your SFML application:
After building your application, you can run it by executing the generated executable from the terminal:

./SFMLApp

Replace "SFMLApp" with the desired name for your application.

Please note that the above steps assume you have a working C++ development environment set up with SFML properly installed. Adjust the CMakeLists.txt file and build process as needed for your specific development environment and project structure.
