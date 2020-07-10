#ifndef _RBF_HPP
#define _RBF_HPP

#include <armadillo>
#include <vector>
#include <math.h>

using namespace arma;
using namespace std;

class rbf {
    double sigma;
    vector<double> w;
    vector<double> g;
public:
    rbf(vector<double> &x, vector<double> &y,
                           double lambda);

    double gaussian(double xi, double xj);

    double get_output(double x);

    vector<double> test(const vector<double> &x);
};









#endif