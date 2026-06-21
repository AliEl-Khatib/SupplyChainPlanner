cmake_minimum_required(VERSION 3.20)
project(SupplyChainPlanner)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost REQUIRED)

add_executable(planner
    src/main.cpp
    src/Node.cpp
    src/Factory.cpp
    src/Warehouse.cpp
    src/Store.cpp
    src/Route.cpp
    src/Algorithm.cpp
    src/Dijkstra.cpp
    src/SupplyChainNetwork.cpp
    src/api.cpp
)

target_include_directories(planner PRIVATE include)
target_link_libraries(planner PRIVATE Boost::boost pthread)