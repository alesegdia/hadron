cmake_minimum_required(VERSION 2.6)
project(hadron)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin)

if(WIN32)
	list(APPEND CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -g -static-libgcc")
endif()

# CORE LIBRARY ################################
file(GLOB_RECURSE HADRON_SOURCES src/lib/**/*.cpp src/lib/**/*.h)
add_library(hadron ${HADRON_SOURCES})
set_target_properties(hadron PROPERTIES
        COMPILE_FLAGS "-std=c++11"
        LINK_FLAGS "-g -ftest-coverage -fprofile-arcs"
        INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/src
)

message("\nBEGIN LIST OF HADRON SOURCES ========")
message("${HADRON_SOURCES}")
message("END OF LIST OF HADRON SOURCES =======\n")

# TESTS ########################################

set(INCLUDE_TESTS 0)
if(INCLUDE_TESTS)

    find_package(Allegro REQUIRED)
    add_subdirectory(module/alligator)

    add_subdirectory(module/xstf)

    function(add_alligator_test EXEC-NAME)
            message("\nBEGIN SOURCES FOR ${EXEC-NAME} =============")
            message("${ARGN}")
            message("END SOURCES FOR ${EXEC-NAME} ================\n")
            add_executable(${EXEC-NAME} ${HADRON_SOURCES} ${ARGN})
            target_link_libraries(${EXEC-NAME} alligator)
            target_link_libraries(${EXEC-NAME} ${ALLEGRO_LIBRARIES})
            target_include_directories(${EXEC-NAME} PUBLIC src/lib/)
            target_include_directories(${EXEC-NAME} PUBLIC module/alligator/src)
            target_include_directories(${EXEC-NAME} PUBLIC ${ALLEGRO_INCLUDE_DIR})
            set_target_properties(${EXEC-NAME} PROPERTIES
                    COMPILE_FLAGS "-std=c++11"
                    LINK_FLAGS "-g -ftest-coverage -fprofile-arcs"
            )
    endfunction(add_alligator_test)


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

    file(GLOB_RECURSE TESTBED_SOURCES
            src/test/graphics/*.cpp
            src/test/graphics/*.h)


    message(${TESTBED_SOURCES})

    add_alligator_test(testbed ${TESTBED_SOURCES})

    message("BEGIN LIST OF UNIT TESTS ===========")

    file(GLOB XSTF_UNIT_TESTS "src/test/unit/*.cpp")
    foreach(file ${XSTF_UNIT_TESTS})
            get_filename_component(TEST_WE ${file} NAME_WE)
            message("Test found: [" ${TEST_WE} "]")
            add_xstf_test(${TEST_WE} ${file})
    endforeach()

    message("END LIST OF UNIT TESTS ===========\n")

endif(INCLUDE_TESTS)
