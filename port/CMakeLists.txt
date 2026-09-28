# Fade port: generated game source (gen/, from tools/mkport.py) + hand fixups + SDL2 platform layer.
# Built by Gradle for Android (port/android); SDL2 comes from the source tree tools/android_build.sh fetches.
cmake_minimum_required(VERSION 3.18)
project(fade C)

set(SDL2_SRC "${CMAKE_CURRENT_LIST_DIR}/../build/third_party/SDL2-2.32.10" CACHE PATH "SDL2 source tree")
add_subdirectory(${SDL2_SRC} SDL2 EXCLUDE_FROM_ALL)

file(GLOB FIXUPS CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/fixups/*.c)
file(GLOB PLATFORM CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/src/*.c)
add_library(main SHARED gen/game.c gen/funcs.c ${FIXUPS} ${PLATFORM})
target_include_directories(main PRIVATE include src gen third_party)
# -fms-extensions: __ptr32 (32-bit game pointers). -fsigned-char: WinCE ARM char is signed (Android AArch64: unsigned). Loop-idiom recognition would turn the decompiled byte
# loops into memcpy on 32-bit address-space pointers, which the backend cannot lower.
target_compile_options(main PRIVATE -std=gnu11 -fms-extensions -O2 -w -fsigned-char -fno-strict-aliasing -fwrapv
  -Wno-error=int-conversion -Wno-error=incompatible-pointer-types -Wno-error=incompatible-function-pointer-types
)
target_link_libraries(main PRIVATE SDL2::SDL2 m)
# clang miscompiles narrow stores through __ptr32 pointers on AArch64: compile via IR + tools/ptr32fix.py
find_package(Python3 REQUIRED COMPONENTS Interpreter)
set_target_properties(main PROPERTIES C_COMPILER_LAUNCHER "${Python3_EXECUTABLE};${CMAKE_CURRENT_LIST_DIR}/../tools/ptr32cc.py")
if(ANDROID)
  target_link_libraries(main PRIVATE android log)
endif()
