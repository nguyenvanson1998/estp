#!/bin/bash

# Biên dịch project
g++ -std=c++17 -Wall -Wextra -pedantic main_total.cpp point.cpp tree.cpp prim.cpp weiszfeld.cpp steiner_topology_recovery.cpp local_optimization.cpp edge_insertion.cpp cleanup_procedure.cpp local_search.cpp -o main

# Kiểm tra xem biên dịch có thành công không
if [ $? -eq 0 ]; then
    echo "Biên dịch thành công. Đang chạy chương trình..."
    # Chạy chương trình
    ./main
else
    echo "Biên dịch thất bại."
fi