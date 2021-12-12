cmake_minimum_required(VERSION 3.8)

project("opengl-3d-egg-model")

include_directories("include")
add_executable("main" "src/main.cpp" "src/Color.cpp" "src/Egg.cpp" "src/Vertex3d.cpp")

target_link_libraries("main" -lGL -lglut -lGLU)