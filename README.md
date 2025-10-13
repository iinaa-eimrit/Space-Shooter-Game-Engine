# Space Shooter

A complete 2D space shooter game built in C++ with SFML over a 30-day development journey.

## Features

- **Wave-based gameplay** with increasing difficulty
- **Multiple enemy types** with unique behaviors:
  - Basic enemies
  - Fast enemies with oscillating movement
  - Tank enemies with high health
  - Shooter enemies with rapid fire
  - Epic boss battles every 5 waves
- **Power-up system**:
  - Rapid fire
  - Shield protection
  - Extra lives
  - Score boosts
- **Advanced visual effects**:
  - Particle explosions
  - Trail effects
  - Screen shake
  - Parallax star field background
- **Persistent high score system**
- **Configurable game settings**
- **Frame-independent movement**
- **Sound effects and background music**

## Requirements

- C++17 compatible compiler
- SFML 2.5.1 or later
- CMake 3.10 or later

## Building the Game

### Linux/Mac
```bash
mkdir build
cd build
cmake ..
make -j4
./SpaceShooter
```

### Windows
```bash
mkdir build
cd build
cmake ..
cmake --build .
SpaceShooter.exe
```