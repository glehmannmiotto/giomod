cmake_minimum_required(VERSION 3.12)
project(giomod)

find_package(cetlib REQUIRED)
find_package(folly REQUIRED)

##############################################################################
point_build_to( doc )
# (No action taken, doc/CMakeLists.txt was empty)

##############################################################################
point_build_to( include )  
set(LIB_DIRS ${CMAKE_CURRENT_BINARY_DIR}/src)

##############################################################################
point_build_to( src )

add_library(giomod_HelloModule_duneDAQModule src/HelloModule.cpp)
target_link_libraries(giomod_HelloModule_duneDAQModule Folly::folly)

add_library(giomod_GoodbyeModule_duneDAQModule src/GoodbyeModule.cpp)
target_link_libraries(giomod_GoodbyeModule_duneDAQModule Folly::folly)

