cmake_minimum_required(VERSION 3.0...4.1)

project(raylib_box2d_debugdraw C)

option(RAYLIB_BOX2D_DEBUGDRAW_SHARED "Build raylib_box2d_debugdraw as a shared library" ${BUILD_SHARED_LIBS})


if(RAYLIB_BOX2D_DEBUGDRAW_SHARED)
  set(RAYLIB_BOX2D_DEBUGDRAW_LIBRARY_TYPE SHARED)
else()
  set(RAYLIB_BOX2D_DEBUGDRAW_LIBRARY_TYPE STATIC)
endif()

add_library(raylib_box2d_debugdraw ${RAYLIB_BOX2D_DEBUGDRAW_LIBRARY_TYPE}
  "raylib_box2d_debugdraw.c"
  "raylib_box2d_debugdraw.h"
)

# In case Raylib is being compiled via CMake, link it directly
if(TARGET raylib)
  target_link_libraries(raylib_box2d_debugdraw PUBLIC raylib)
else()
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(RAYLIB REQUIRED raylib)
  target_include_directories(raylib_box2d_debugdraw PUBLIC ${RAYLIB_INCLUDE_DIRS})
  target_link_libraries(raylib_box2d_debugdraw PRIVATE ${RAYLIB_LINK_LIBRARIES})
endif()

# In case Box2D is being compiled via CMake, link it directly
if(TARGET box2d)
  target_link_libraries(raylib_box2d_debugdraw PUBLIC box2d)
else()
  find_package(box2d 3.0 REQUIRED)
  target_include_directories(raylib_box2d_debugdraw PUBLIC ${BOX2D_INCLUDE_DIRS})
  target_link_libraries(raylib_box2d_debugdraw PRIVATE box2d::box2d)
endif()
