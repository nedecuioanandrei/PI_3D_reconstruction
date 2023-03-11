/*
  (づ ￣ ³￣)づ
*/
#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <argparse/argparse.hpp>
#include <jsoncpp/json/json.h>
#include <fstream>
using ll = long long;
using ull = unsigned long long;
using lld = long double;
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).begin(),(x).end()
using namespace std;
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
using ll = long long;
using ull = unsigned long long; 


void test_case() {
    
}

signed main(int argc, char** argv) {
    argparse::ArgumentParser program("3D_reconstruction");
    program.add_argument("left")
        .help("Provide the left image (Path to file).")
        .required();
    program.add_argument("right")
        .help("Provide the right image (Path to file).")
        .required();
    program.add_argument("params")
        .help("Path to params file (json) format.")
        .required();
    
    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }
    
    string left_image_path = program.get<string>("left");
    string right_image_path = program.get<string>("right");
    string param_file_path = program.get<string>("params");

    debug() << imie(left_image_path);
    debug() << imie(right_image_path);
    debug() << imie(param_file_path);

    //Mat left_image = imread(left_image_path, IMREAD_GRAYSCALE);
    //Mat right_image = imread(right_image_path, IMREAD_GRAYSCALE);
    std::ifstream params_file(param_file_path.c_str(), std::ifstream::binary);
    Json::Value param_values;
    params_file >> param_values;

    //std::cout << param_values["f"] << std::endl;
    
    return 0x0;
}
