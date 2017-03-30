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
add_subdirectory(module/alligator)
add_subdirectory(module/xstf)


function(add_alligator_test EXEC-NAME SRCS)
	message("BEGIN LIST OF SOURCES ========")
	message(${SRCS})
	message("END OF LIST OF SOURCES =======")
	add_executable(${EXEC-NAME} ${HADRON_SOURCES} ${SRCS})
	target_link_libraries(${EXEC-NAME} alligator)
	target_link_libraries(${EXEC-NAME} ${ALLEGRO_LIBRARIES})
	target_include_directories(${EXEC-NAME} PUBLIC src/)
	target_include_directories(${EXEC-NAME} PUBLIC module/alligator/src)
	target_include_directories(${EXEC-NAME} PUBLIC ${ALLEGRO_INCLUDE_DIR})
	set_target_properties(${EXEC-NAME} PROPERTIES
		COMPILE_FLAGS "-std=c++11"
		LINK_FLAGS "-g -ftest-coverage -fprofile-arcs"
	)
endfunction(add_alligator_test)


file(GLOB TESTBED_SOURCES "src/test/**/*.cpp")
add_alligator_test(letest ${TESTBED_SOURCES})



#[[
function(add_xstf_test EXEC-NAME SRCS)
    add_executable(${EXEC-NAME} ${HADRON_SOURCES} ${SRCS})
    target_link_libraries(${EXEC-NAME} xstf)
    target_include_directories(${EXEC-NAME} PUBLIC src/lib)
    target_include_directories(${EXEC-NAME} PUBLIC module/xstf/src)
    set_target_properties(${EXEC-NAME} PROPERTIES
            COMPILE_FLAGS "-std=c++11"
            LINK_FLAGS "-g -ftest-coverage -fprofile-arcs"
    )
endfunction(add_xstf_test)

file(GLOB GRAPHIC_TESTBED_FILES "src/test/graphics/*.cpp")
foreach(file ${GRAPHIC_TESTBED_FILES})
    get_filename_component(TEST_WE ${file} NAME_WE)
    add_alligator_testbed(${TEST_WE} ${file})
endforeach()

file(GLOB XSTF_TEST_FILES "src/test/unit/*.cpp")
foreach(file ${XSTF_TEST_FILES})
    get_filename_component(TEST_WE ${file} NAME_WE)
    add_xstf_test(${TEST_WE} ${file})
endforeach()
]]
