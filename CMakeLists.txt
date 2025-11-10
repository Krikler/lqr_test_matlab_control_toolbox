cmake_minimum_required(VERSION 3.14)
project(lqr_compare CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Find MATLAB
if(NOT Matlab_ROOT_DIR AND DEFINED ENV{MATLAB_ROOT})
  set(Matlab_ROOT_DIR $ENV{MATLAB_ROOT})
endif()

# Eigen
find_package(Eigen3 REQUIRED)

# Manual MATLAB configuration
set(Matlab_INCLUDE_DIRS "${Matlab_ROOT_DIR}/extern/include")
set(Matlab_ENGINE_LIBRARY "${Matlab_ROOT_DIR}/extern/bin/glnxa64/libMatlabEngine.so")
set(Matlab_DATAARRAY_LIBRARY "${Matlab_ROOT_DIR}/extern/bin/glnxa64/libMatlabDataArray.so")

if(NOT EXISTS ${Matlab_ENGINE_LIBRARY})
	message(FATAL_ERROR "Matlab Engine lib not found: ${Matlab_ENGINE_LIBRARY}")
endif()
if(NOT EXISTS ${Matlab_DATAARRAY_LIBRARY})
	message(FATAL_ERROR "Matlab DataArray lib not found: ${Matlab_DATAARRAY_LIBRARY}")
endif()

# Control Toolbox (ETH Zurich) -- require core and optcon components explicitly
find_package(ct_core REQUIRED)
find_package(ct_optcon REQUIRED)

include_directories(${Matlab_INCLUDE_DIRS})


add_library(matlab_lqr src/matlab_lqr.cpp include/lqr_matlab.hpp)
 target_include_directories(matlab_lqr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
 target_link_libraries(matlab_lqr PRIVATE Eigen3::Eigen ${Matlab_ENGINE_LIBRARY} ${Matlab_DATAARRAY_LIBRARY})

add_library(ct_lqr src/ct_lqr.cpp include/lqr_ct.hpp)
 target_include_directories(ct_lqr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
 target_link_libraries(ct_lqr PRIVATE Eigen3::Eigen ct_core ct_optcon)

add_executable(test_lqr src/test_lqr.cpp)
 target_link_libraries(test_lqr PRIVATE matlab_lqr ct_lqr Eigen3::Eigen ${Matlab_ENGINE_LIBRARY} ${Matlab_DATAARRAY_LIBRARY})
