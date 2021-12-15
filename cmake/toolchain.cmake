# Sample toolchain file for building for Windows.

set(CMAKE_SYSTEM_NAME Windows)
set(MINGW_PATH C:/mingw64)

# cross compilers to use for C, C++ and Fortran
set(CMAKE_C_COMPILER ${MINGW_PATH}/bin/gcc.exe)
set(CMAKE_CXX_COMPILER ${MINGW_PATH}/bin/g++.exe)
#set(CMAKE_Fortran_COMPILER ${MINGW_PATH}/bin/gfortran.exe)
#set(CMAKE_RC_COMPILER ${MINGW_PATH}/bin/windres.exe)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

# target environment on the build host system
set(CMAKE_FIND_ROOT_PATH ${MINGW_PATH}/x86_64-w64-mingw32)

# modify default behavior of FIND_XXX() commands
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
