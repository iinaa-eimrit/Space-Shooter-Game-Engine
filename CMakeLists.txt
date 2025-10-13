cmake_minimum_required(VERSION 3.10)
project(SpaceShooter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

# Set source files
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
    src/Bullet.cpp
    src/Enemy.cpp
    src/EnemyTypes.cpp
    src/BossEnemy.cpp
    src/PowerUp.cpp
    src/ParticleSystem.cpp
    src/Background.cpp
    src/SoundManager.cpp
    src/Config.cpp
    src/HighScoreManager.cpp
)

# Create executable
add_executable(SpaceShooter ${SOURCES})

# Link SFML
target_link_libraries(SpaceShooter sfml-system sfml-window sfml-graphics sfml-audio)

# Copy assets to build directory
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY config.ini DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Set compiler options
if(MSVC)
    target_compile_options(SpaceShooter PRIVATE /W4)
else()
    target_compile_options(SpaceShooter PRIVATE -Wall -Wextra)
endif()