cmake_minimum_required(VERSION 3.0)
set(CMAKE_DEBUG_TRY_COMPILE ON)

set(MY_VARIABLE "Hello, World!")
message("Variable value: ${MY_VARIABLE}")
# 打印出所有可能影响 find_package 的变量

project(Star7)
#set(ENV{PKG_CONFIG_PATH} "/usr/local/Cellar/sdl2_image/2.0.5/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")

# 设置C标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_SYSTEM_PREFIX_PATH "${CMAKE_SYSTEM_PREFIX_PATH};/usr/local/Cellar/sdl2_image/2.8.2_1/lib/pkgconfig")
# set(CMAKE_LIBRARY_PATH "/usr/local/Cellar/sdl2_image/2.8.2_1/lib")
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
message(STATUS "CMAKE_SYSTEM_PREFIX_PATH: ${CMAKE_SYSTEM_PREFIX_PATH}")
message(STATUS "CMAKE_INCLUDE_PATH: ${CMAKE_INCLUDE_PATH}")
message(STATUS "CMAKE_LIBRARY_PATH: ${CMAKE_LIBRARY_PATH}")
message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
message(STATUS "PKG_CONFIG_PATH: ENV{PKG_CONFIG_PATH}")

# 查找SDL2包
find_package(SDL2_image REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)


if(NOT ${SDL2_image_FOUND})
  message(STATUS "SDL2_image not found")
else()
  message(STATUS "SDL2_image found: ${SDL2_IMAGE_INCLUDE_DIRS}")
endif()

message(STATUS "SDL2_INCLUDE_DIRS found ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_LIBRARIES found ${SDL2_LIBRARIES}")

set(SDL2_IMAGE_INCLUDE_DIRS "/usr/local/opt/sdl2_image/include")
set(SDL2_IMAGE_LIBRARIES "SDL2_image::SDL2_image")

message(STATUS "SDL2_IMAGE_INCLUDE_DIRS found ${SDL2_IMAGE_INCLUDE_DIRS}")
message(STATUS "SDL2_IMAGE_LIBRARIES found ${SDL2_IMAGE_LIBRARIES}")


set(SDL2_TTF_INCLUDE_DIRS "//usr/local/opt/sdl2_ttf/include")
set(SDL2_TTF_LIBRARIES "SDL2_ttf::SDL2_ttf")

# find_package(SDL2_image REQUIRED)

# 包含SDL2头文件目录
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})




# 添加可执行文件
#add_executable(kukuImage test_image.cpp)
add_executable(Star7 main.cpp)
target_link_libraries(Star7 ${SDL2_LIBRARIES}  ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
#target_link_libraries(kukuImage ${SDL2_LIBRARIES}  ${SDL2_IMAGE_LIBRARIES})


#  add_executable(KuGame main.cpp)
# 链接SDL2库
#target_link_libraries(KuGame ${SDL2_LIBRARIES}  ${SDL2_IMAGE_LIBRARIES})
