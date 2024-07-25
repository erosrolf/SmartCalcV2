cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "CalcCore")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

set(SOURCES 
  calc_graph.cc
  lexems.cc
  shanting_yard.cc
  polish_calc.cc
  expression.cc
  dll_interface.cc
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
