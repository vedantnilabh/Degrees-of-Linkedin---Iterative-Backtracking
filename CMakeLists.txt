cmake_minimum_required(VERSION 3.14)
project(22su_PA03)

set(CMAKE_CXX_STANDARD 17)

# The configure_file statements below ensure that files are copied into the data
# folder that will be created in the build folder.
configure_file(data/links.txt data/links.txt NEWLINE_STYLE UNIX)


# This target is for the main project.  Add in any additional files you need or that you're copying
# over from a previous project.
add_executable(22su_PA03 main.cpp DSVector.h DSString.cpp DSString.h ListNode.h LinkedList.h Person.h Person.cpp AdjList.h AdjList.cpp DegreesofLinkedin.cpp DegreesofLinkedin.h)

# this is the testing target.  Don't include your main driver.cpp file in this target.
add_executable(22su_PA03_tests DSVector.h catch.hpp catch_setup.cpp DataStructure_Tests.cpp catch_setup.h ListNode.h LinkedList.cpp LinkedList.h AdjList.cpp AdjList.h Person.h Person.cpp sample_tests.cpp DSString.cpp DSString.h)
