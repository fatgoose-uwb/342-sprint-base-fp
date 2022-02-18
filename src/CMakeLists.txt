add_executable(${PROJECT_NAME} main.cpp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

FILE(GLOB ProblemSource *.cpp) # problem 2 template files don't need to be compiled here
add_library(homework_functions STATIC ${ProblemSource})

target_link_libraries(${PROJECT_NAME} homework_functions)

add_test(
        NAME
        main
        COMMAND
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
)