cmake_minimum_required(VERSION 3.20)
project(SupplyChainPlanner)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(planner
    src/main.cpp 
    src/Node.cpp 
    src/Factory.cpp 
    src/Warehouse.cpp 
    src/Store.cpp
    src/Route.cpp
    src/SupplyChainNetwork.cpp
    src/Algorithm.cpp
    src/Dijkstra.cpp
    )
target_include_directories(planner PRIVATE include)
