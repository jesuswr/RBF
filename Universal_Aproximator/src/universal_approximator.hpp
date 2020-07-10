#ifndef _UNIVERSAL_APPROXIMATOR_HPP
#define _UNIVERSAL_APPROXIMATOR_HPP

#include <armadillo>
#include <vector>
#include <math.h>

using namespace arma;
using namespace std;

class universal_approximator {
    double sigma;
    vector<long double> w;
    vector<long double> G;
public:
    universal_approximator(const vector<double> &x, const vector<double> &y,
                           double lambda);

    double gaussian(double xi, double xj);

    double get_output(double x);

    vector<double> test(const vector<double> &x);
};









#endif