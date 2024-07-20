cmake_minimum_required(VERSION 3.10)
project(ESTP_Project)

set(CMAKE_CXX_STANDARD 17)

# Tìm kiếm các gói cần thiết
find_package(CGAL REQUIRED COMPONENTS Core)

# Danh sách các tệp nguồn
set(SOURCE_FILES
    plane_test.cpp
    commons.cpp
    point.cpp
    tree.cpp
    prim.cpp
    weiszfeld.cpp
    steiner_topology_recovery.cpp
    local_optimization.cpp
    edge_insertion.cpp
    cleanup_procedure.cpp
    local_search.cpp
)

# Thêm tệp nguồn
add_executable(estp_project ${SOURCE_FILES})

# Liên kết các thư viện CGAL
target_link_libraries(estp_project CGAL::CGAL CGAL::CGAL_Core)
