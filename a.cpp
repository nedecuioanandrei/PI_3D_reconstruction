/*
  (づ ￣ ³￣)づ
*/
#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <argparse/argparse.hpp>
#include <jsoncpp/json/json.h>
#include <opencv4/opencv2/opencv.hpp>
#include <fstream>
using ll = long long;
using ull = unsigned long long;
using lld = long double;
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).begin(),(x).end()
using namespace std;
using namespace cv;
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
const int inf = (int)(1e9);


bool is_inside(int x, int y, int max_n, int max_m) {
    return x >= 0 && y >= 0 && max_n > x && max_m > y;
}


int compute_disparity(int posx, int posy, Mat& a, Mat& b, int limit, int window_size) {
    const int n = (int)a.rows;
    const int m = (int)a.cols;
    int ans = 0;
    int score = inf;
    for (int offset = 0 ; offset < limit ; ++offset) {
        int sad = 0;
        int wso2 = window_size / 2;
        for (int i = posx - wso2 ; i <= posx + wso2 ; ++i) {
            for (int j = posy - wso2 ; j <= posy + wso2 ; ++j) {
                if (is_inside(i, j, n, m) && is_inside(i + offset, j + offset, n, m)) {
                    int abs_diff = (int)abs(a.at<uchar>(i + offset, j + offset) - b.at<uchar>(i, j));
                    sad += abs_diff * abs_diff; 
                }
            }
        }
        if (sad < score) {
            ans = offset;
            score = sad;
        }
    }
    return ans;
}


void test_case(Mat& left, Mat& right, Json::Value par) {
    const double f = par["f"].asDouble();
    const double xc = par["xC"].asDouble(); 
    const double yc = par["yC"].asDouble();
    
    const double xcl = par["XCl"].asDouble();
    const double ycl = par["YCl"].asDouble();
    const double zcl = par["ZCl"].asDouble();
    
    const double xcr = par["XCr"].asDouble(); 
    const double ycr = par["YCr"].asDouble();
    const double zcr = par["ZCr"].asDouble();

    debug() << imie(f);
    debug() << imie(xc);
    debug() << imie(yc);
    debug() << imie(xcl);
    debug() << imie(ycl);
    debug() << imie(zcl);
    debug() << imie(xcr);
    debug() << imie(ycr);
    debug() << imie(zcr);
    
    // 3D reconstruction implementation
    const int n = (int)left.rows;
    const int m = (int)left.cols;
    
    Mat ans = left.clone();

    int maxima = 0;
    for (int i = 0 ; i < n ; ++i) {
        for (int j = 0 ; j < m ; ++j) {
            int d = compute_disparity(i, j, right, left, 128, 9);
            int value = f * abs(xcl - xcr) / d;
            debug() << imie(d);
            maxima =  max(maxima, value);
            ///debug() << imie(value);
            ans.at<uchar>(i, j) = d;
        }
    } 

    imwrite("./test_case_output.jpg", ans);
    
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

    std::cout << param_values["f"] << std::endl;
    Mat left = imread(left_image_path, IMREAD_GRAYSCALE); 
    Mat right = imread(right_image_path, IMREAD_GRAYSCALE);

    test_case(left, right, param_values);
    return 0x0;
}
