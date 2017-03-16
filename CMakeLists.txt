cmake_minimum_required(VERSION 2.6)
project(hadron)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin)

if(WIN32)
	list(APPEND CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc")
endif()

# CORE LIBRARY ################################
file(GLOB_RECURSE HADRON_SOURCES **/*.cpp **/*.h)
add_library(hadron ${HADRON_SOURCES})
set_target_properties(hadron PROPERTIES
        COMPILE_FLAGS "-std=c++11"
        LINK_FLAGS "-g -ftest-coverage -fprofile-arcs"
        INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# TESTS ########################################

find_package(Allegro REQUIRED)

function(add_alligator_test EXEC-NAME SRCS)
	add_executable(${EXEC-NAME} ${HADRON_SOURCES} ${SRCS})
	target_link_libraries(${EXEC-NAME} alligator)
	target_link_libraries(${EXEC-NAME} ${ALLEGRO_LIBRARIES})
	target_include_directories(${EXEC-NAME} PUBLIC module/alligator/src)
	target_include_directories(${EXEC-NAME} PUBLIC ${ALLEGRO_INCLUDE_DIR})
	set_target_properties(${EXEC-NAME} PROPERTIES
		COMPILE_FLAGS "-std=c++11"
		LINK_FLAGS "-g -ftest-coverage -fprofile-arcs"
	)
endfunction(add_alligator_test)

add_subdirectory(module/alligator)
set(TEST_SOURCES src/test/testbed.cpp src/test/testbed.h)
add_executable(letest ${TEST_SOURCES})
target_link_libraries(letest ${ALLEGRO_LIBRARIES})
target_link_libraries(letest alligator)
