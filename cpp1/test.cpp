#include <iostream>
#include <fstream>
#include <string>
#include "point.hpp" 
void print_points(const std::vector<Point*>& S) {
    for (const auto& p : S) {
        for (size_t i = 0; i < p->axes.size(); ++i) {
            std::cout << p->axes[i];
            if (i < p->axes.size() - 1) {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
}
int main() {
    std::ifstream file("./build2/data/OR-LIBRARY/estein10.txt");  // Adjust the file path if necessary
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    int test_cases;
    file >> test_cases;
        std::cout << "Num test case " << test_cases << std::endl;

    for (int i = 0; i < test_cases; i++) {
                std::cout << "huhuhu " <<std::endl;
                int length = 0;
                file >> length;
                std::cout<< "length =" << length <<std::endl;
                std::vector<Point*> X(length);
                for (int i = 0; i < length; ++i) {
                    std::vector<double> coords(2);
                    for (int j = 0; j < 2; ++j) {
                        file >> coords[j];
                    }
                    X[i] = new Point(coords);
                }
                print_points(X);
    }
    file.close();
    return 0;
}
