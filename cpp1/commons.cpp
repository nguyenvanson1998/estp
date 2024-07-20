#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cmath>
#include "point.hpp" // Giả sử bạn có file header cho class Point
#include "tree.hpp" // Giả sử bạn có file header cho class Tree
#include "prim.hpp" // Giả sử bạn có file header cho function MST
#include "local_search.hpp" // Giả sử bạn có file header cho function local_search

double percent_reduction(double l_T, double l_MST) {
    return 100.0 * (l_MST - l_T) / l_MST;
}

std::vector<Point*> read_input(std::ifstream& f_inp) {
    int length;
    f_inp >> length;
    std::cout<< "length =" << length;
    std::vector<Point*> X(length);
    for (int i = 0; i < length; ++i) {
        std::vector<double> coords(3);
        for (int j = 0; j < 3; ++j) {
            f_inp >> coords[j];
        }
        X[i] = new Point(coords);
    }
    return X;
}

std::pair<double, double> read_optimal(std::ifstream& f_opt) {
    double opt, mst;
    f_opt >> opt >> mst;
    int steiner_cnt;
    f_opt >> steiner_cnt;
    for (int i = 0; i < steiner_cnt; i++) {
        std::string dummy;
        std::getline(f_opt, dummy);
    }
    return {opt, mst};
}

std::tuple<double, double, double> run_instance(std::ifstream& f_inp, int run_times) {
    std::cout<< "huhu";
    auto X = read_input(f_inp);
    double mst = MST(X).l();

    double best_phi = 0.0;
    double avg_phi = 0.0;
    double avg_time = 0.0;

    for (int i = 0; i < run_times; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        auto [T, S] = local_search(X);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        double phi = percent_reduction(std::round(T.l() * 1e9) / 1e9, mst);
        best_phi = std::max(best_phi, phi);
        avg_phi += phi;
        avg_time += elapsed.count();
    }

    avg_phi /= run_times;
    avg_time /= run_times;

    for (auto p : X) delete p;

    return {best_phi, avg_phi, avg_time};
}

double get_phi(const std::vector<Point*>& X, double mst, double p) {
    auto [T, S] = local_search(X, p, p);
    return percent_reduction(std::round(T.l() * 1e9) / 1e9, mst);
}

// Parallel version not implemented here as it requires additional libraries

void process_file(const std::string& path, const std::string& label, std::ofstream& f_out, int run_count) {
    std::vector<double> results(3, 0.0);

    std::ifstream f_inp(path);
    if (f_inp.is_open()) {
        std::cout << path << std::endl;
        int test_cases;
        f_inp >> test_cases;
        for (int i = 0; i < test_cases; i++) {
                int length = 0;
                f_inp >> length;
                std::vector<Point*> X(length);
                for (int i = 0; i < length; ++i) {
                    // std::vector<double> coords(3);
                    std::vector<double> coords(2);
                    for (int j = 0; j < 2; ++j) {
                        f_inp >> coords[j];
                    }
                    X[i] = new Point(coords);
                }
                // auto X = read_input(f_inp);
                double mst = MST(X).l();

                double best_phi = 0.0;
                double avg_phi = 0.0;
                double avg_time = 0.0;

                for (int i = 0; i < run_count; i++) {
                    auto start = std::chrono::high_resolution_clock::now();
                    auto [T, S] = local_search(X);
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> elapsed = end - start;

                    double phi = percent_reduction(std::round(T.l() * 1e9) / 1e9, mst);
                    best_phi = std::max(best_phi, phi);
                    avg_phi += phi;
                    avg_time += elapsed.count();
                }

                avg_phi /= run_count;
                avg_time /= run_count;

                // for (auto p : X) delete p;
            // auto [best_phi, avg_phi, avg_time] = run_instance(f_inp, run_count);
            results[0] += best_phi;
            results[1] += avg_phi;
            results[2] += avg_time;
        }

        for (auto& res : results) res /= test_cases;

        f_out << label << " ";
        for (const auto& res : results) {
            f_out << std::round(res * 100) / 100 << " ";
        }
        f_out << "\n";

        f_inp.close();
    } else {
        std::cerr << "Unable to open file: " << path << std::endl;
    }
}