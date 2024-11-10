# Fake_pacman
A simple remake of the pac-man game in c++ SFML and CMake
![pacmanScreenshot](https://github.com/user-attachments/assets/a461a92c-ec0e-4808-85c5-8cf03fd4a94d)
![mapEditor](https://github.com/user-attachments/assets/38139ad1-6bd6-4905-ac5c-4b615d2aa322)
### Requirements
- SFML and SFML-devel
- CMake
- C++
### How to build it
This is a cmake project, so to build it, go to the build directory and type
```bash
cd build
rm CMakeCache.txt
cmake ..
make
```
Then you can run it by going to the parent directory and running the .elf/.exe file from there
```bash
./build/pacman_game
```
### Features
* It's just your avarage pacman clone
* You can change the map in the "options" menu, and create new ones with the maze_builder.py python editor.

### Todo
- [x] A GUI
- [x] beautify the walls
- [x] Ability to change (and create) maps

