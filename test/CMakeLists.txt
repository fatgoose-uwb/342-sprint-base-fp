FILE(GLOB ProblemSource unit_test_*.cpp)
add_executable(${PROJECT_NAME}_unit_test main.cpp ${ProblemSource})

include_directories(${CMAKE_LIBRARY_PATH})

# gtest path for link (like -D)
link_directories(${LIBRARY_OUTPUT_PATH})

target_link_libraries(${PROJECT_NAME}_unit_test gtest homework_functions)
add_test(
        NAME
        unit_test
        COMMAND
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}_unit_test
)