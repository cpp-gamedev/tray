add_executable(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_sources(${PROJECT_NAME} PRIVATE
  src/tray/hit.cpp
  src/tray/hit.hpp
  src/tray/image.cpp
  src/tray/image.hpp
  src/tray/io.cpp
  src/tray/io.hpp
  src/tray/light.hpp
  src/tray/nvec3.hpp
  src/tray/ray.hpp
  src/tray/rgb.hpp
  src/tray/sphere.hpp
  src/tray/vec.hpp
  src/tray/viewport.hpp

  src/main.cpp
)

if(CMAKE_CXX_COMPILER_ID STREQUAL Clang OR CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra -Wpedantic -Wconversion -Werror=return-type -Wunused
  )
endif()
