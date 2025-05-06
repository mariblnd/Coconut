cmake_minimum_required(VERSION 3.11)
cmake_policy(SET CMP0072 NEW)
cmake_policy(SET CMP0079 NEW)

project(coconut)

# Set the folder where the executable will be created
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Libraries
find_package(OpenGL REQUIRED)

# GLAD configuration first (since others depend on it)
add_library(glad STATIC third_party/glad/src/glad.c)
target_include_directories(glad PUBLIC third_party/glad/include)

# GLFW configuration
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(third_party/glfw)

# GLBasimac configuration
add_subdirectory(third_party/glbasimac)
target_include_directories(glbasimac PUBLIC third_party/glad/include)
target_link_libraries(glbasimac PUBLIC glad)

# Create executable
add_executable(${PROJECT_NAME} 
src/main.cpp
src/Tile.cpp
src/Map.cpp)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)


# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    glfw
    glbasimac
)