cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set (PROJECT BalancedTree)

project(${PROJECT})

add_executable(${PROJECT} source/main.cpp source/tree/dump.cpp source/tree/tree.cpp)

enable_testing()

add_test(EazyTest ${PROJECT} ../source/Tests/input_1.txt ../source/Tests/answer_1.txt)
add_test(BigTest ${PROJECT} ../source/Tests/input_2.txt ../source/Tests/answer_2.txt)
add_test(BeforeBigTest ${PROJECT} ../source/Tests/input_3.txt ../source/Tests/answer_3.txt)