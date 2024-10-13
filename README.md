# Fake_pacman
A simple remake of the pac-man game in c++ SFML with cmake for building
### Requirements
- SFML and SFML-devel
- CMake
- c++
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
### Todo
- [x] A GUI
- [x] beautify the walls
- [ ] Ability to change (and create) maps

