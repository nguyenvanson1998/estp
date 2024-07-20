#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm>
#include "commons.hpp"

namespace fs = std::filesystem;

int main() {
    std::ofstream f_out("output/table2.txt");
    if (!f_out.is_open()) {
        std::cerr << "Unable to open output file." << std::endl;
        return 1;
    }

    const std::string data_path = "data/OR-LIBRARY";
    std::vector<std::string> files;

    // Đọc tất cả các file trong thư mục
    for (const auto & entry : fs::directory_iterator(data_path)) {
        std::string filename = entry.path().filename().string();
        if (filename.find("opt") == std::string::npos) {
            files.push_back(filename);
        }
    }

    // Sắp xếp tên file
    std::sort(files.begin(), files.end());

    // Xử lý từng file
    for (const auto & file : files) {
        std::string full_path = data_path + "/" + file;
        std::string label = file.substr(6, file.length() - 10); // Loại bỏ 'estein' và '.txt'
        process_file(full_path, label, f_out, 10);
    }

    f_out.close();
    return 0;
}