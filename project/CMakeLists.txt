cmake_minimum_required (VERSION 2.6)
project (Image-Processor)

#############################
## Compiler and platform specific flags.
#############################
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  # Mac OS X specific code
  SET(OperatingSystem "Mac OS X")
  #Add -stdlib=libc++ for Mac OS X.
  #Assume Clang for now.
  list( APPEND CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++ -march=native -O2 -g -Wall ${CMAKE_CXX_FLAGS} ")
ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  #Assume Linux for now.
  #Try using link time optimization on GCC.
  IF(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    list( APPEND CMAKE_CXX_FLAGS "-pthread -std=c++0x -flto -march=native -O2 -g -Wall -Wl,--no-as-needed ${CMAKE_CXX_FLAGS} ")
  ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    list( APPEND CMAKE_CXX_FLAGS "-pthread -std=c++0x -march=native -O2 -g -Wall")
  ENDIF(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")


##########
# Src
##########

# For each subdirectory set the library name, add subdirectory and add header to includes.
#ADD_SUBDIRECTORY(src/aggregator)

# Buffers.
set (buffer_LIB buffer)
ADD_SUBDIRECTORY(src/buffers)
list (APPEND COMMON_INCLUDES src/buffers)

#ADD_SUBDIRECTORY(src/producers)
#ADD_SUBDIRECTORY(src/protocol)

ADD_SUBDIRECTORY(src/queues)
list (APPEND COMMON_INCLUDES src/queues)

#ADD_SUBDIRECTORY(src/workers)

# Utils.
set (thread_utils_LIB thread_utils)
ADD_SUBDIRECTORY(src/utils)
list (APPEND COMMON_INCLUDES src/utils)

####################
# Perf Testing with Hayai
####################
#ADD_SUBDIRECTORY(ext/hayai)
include_directories(ext/hayai/src)

####################
# Perf Tests.
####################
include_directories(${COMMON_INCLUDES})
ADD_SUBDIRECTORY(perf)


#####################
# Testing with Gtest-1.7
#####################
ADD_SUBDIRECTORY(ext/gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


###########################
# Unit tests
##########################
# Add custom ctest settings:
configure_file(../project/CTestCustom.cmake CTestCustom.cmake)

# Add test file
include_directories(${COMMON_INCLUDES})
add_executable( runUnitTests tests/buffer_test.cpp tests/ring_buffer_test.cpp)
# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests gtest gtest_main ${buffer_LIB})
add_test( runUnitTests runUnitTests )