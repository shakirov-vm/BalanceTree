cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set (PROJECT BalancedTree)

project(${PROJECT})

add_executable(BalancedTree source/main.cpp)

enable_testing()

add_test(EazyTest BalancedTree ../source/Tests/input_1.txt ../source/Tests/answer_1.txt)
add_test(BigTest BalancedTree ../source/Tests/input_2.txt ../source/Tests/answer_2.txt)
add_test(BeforeBigTest BalancedTree ../source/Tests/input_3.txt ../source/Tests/answer_3.txt)

if (DEFINED U_TEST) 

	project(TreeTest)
	add_executable(TreeTest source/Tests/unit_test.cpp)
	SET(CMAKE_CXX_FLAGS  "-DU_TEST")

endif()