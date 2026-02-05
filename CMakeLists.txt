cmake_minimum_required(VERSION 3.10)
project(SpaceShooter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set SFML directory
set(SFML_DIR "C:/SFML/SFML-2.6.0/lib/cmake/SFML")
set(SFML_ROOT "C:/SFML/SFML-2.6.0")

# Find SFML
find_package(SFML 2.6 COMPONENTS system window graphics audio REQUIRED)

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

# Copy assets to build directory (if they exist)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets")
    file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/config.ini")
    file(COPY config.ini DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

# Set compiler options
if(MSVC)
    target_compile_options(SpaceShooter PRIVATE /W4)
else()
    target_compile_options(SpaceShooter PRIVATE -Wall -Wextra)
endif()