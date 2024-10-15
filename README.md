# Fake_pacman
A simple remake of the pac-man game in c++ SFML and CMake
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

