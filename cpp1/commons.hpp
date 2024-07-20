#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <string>
#include <tuple>
#include <fstream>
#include "point.hpp"
#include "tree.hpp"

// Tính phần trăm giảm
double percent_reduction(double l_T, double l_MST);

// Đọc dữ liệu đầu vào
std::vector<Point*> read_input(std::ifstream& f_inp);

// Đọc giá trị tối ưu
std::pair<double, double> read_optimal(std::ifstream& f_opt);

// Chạy một instance
std::tuple<double, double, double> run_instance(std::ifstream& f_inp, int run_times);

// Tính phi
double get_phi(const std::vector<Point*>& X, double mst, double p);

// Xử lý file
void process_file(const std::string& path, const std::string& label, std::ofstream& f_out, int run_count);

#endif // COMMON_H