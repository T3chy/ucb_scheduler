cmake_minimum_required(VERSION 3.10)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()


project("Berk_Scheduler")

# file(GLOB SOURCES "*.cpp")
add_executable("${PROJECT_NAME}" "main.cpp" "Schedule.cpp")
set_property(TARGET "${PROJECT_NAME}" PROPERTY CXX_STANDARD 17)


# install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
# install(FILES "main.cpp" DESTINATION src)
# relative to cmake install path
