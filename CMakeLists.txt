cmake_minimum_required(VERSION 3.12)

project(game)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройка компилятора LLVM/Clang (если это действительно необходимо)
set(CMAKE_C_COMPILER "/usr/local/opt/llvm/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/local/opt/llvm/bin/clang++")

# Добавление исполняемого файла
add_executable(game main.cpp gamescene.cpp player.cpp bullet.cpp enemy.cpp 
map.cpp helth.cpp camera.cpp aim.cpp text.cpp menu.cpp)

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2.5 REQUIRED COMPONENTS graphics)

target_include_directories(game PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(game PUBLIC cxx_std_17)
target_compile_definitions(game PRIVATE SFML_STATIC)

# Установка стандарта C++17 для цели
set_target_properties(game PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(game PRIVATE sfml-graphics)
