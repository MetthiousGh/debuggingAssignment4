#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

std::vector<int> readInts(const std::string& filename) {
    std::ifstream fin(filename);
    std::vector<int> v;
    int x;
    while (fin >> x) v.push_back(x);
    return v;
}

// BUG #1: logic bug (integer division)
double mean_BUG(const std::vector<int>& v) {
    long long sum = 0;
    for (int x : v) sum += x;
    return (v.empty()) ? 0.0 : (sum / v.size());
}

// BUG #2: out-of-bounds (ASan should catch)
int countAbove_BUG(const std::vector<int>& v, int threshold) {
    int cnt = 0;
    for (size_t i = 0; i <= v.size(); i++) {
        if (v[i] > threshold) cnt++;
    }
    return cnt;
}

// BUG #3: use-after-free
int* maxPtr_BUG(const std::vector<int>& v) {
    if (v.empty()) return nullptr;
    int* p = new int(*std::max_element(v.begin(), v.end()));
    delete p;
    return p;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file> [threshold]\n";
        return 1;
    }
    int threshold = (argc >= 3) ? std::stoi(argv[2]) : 50;

    std::vector<int> nums = readInts(argv[1]);
    std::cout << "N=" << nums.size() << "\n";
    std::cout << "Mean=" << mean_BUG(nums) << "\n";

    int* pMax = maxPtr_BUG(nums);
    if (pMax) std::cout << "Max=" << *pMax << "\n";

    std::cout << "Count(>" << threshold << ")="
              << countAbove_BUG(nums, threshold) << "\n";
    return 0;
}

