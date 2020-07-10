#include "universal_approximator.hpp"

universal_approximator::universal_approximator(const vector<double> &x,
        const vector<double> &y, double lambda, double sigma) : sigma(sigma) {

    int n = x.size();
    mat m(n, n);
    mat d = y;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            m(i, j) = gaussian(x[i], x[j]);
        }
    }

    m = m + lambda * eye(n, n);
    // solve m * w = d
    mat ans = inv(m) * d;

    for (int i = 0; i < n; ++i) {
        w.push_back( ans(i, 0) );
        G.push_back( x[i] );
    }
}

double universal_approximator::gaussian(double xi, double xj) {
    double num = (xi - xj) * (xi - xj) ;
    double den = 2 * sigma * sigma;
    return exp( -num / den );
}

double universal_approximator::get_output(double x) {
    int n = w.size();
    double fx = 0;

    for (int i = 0; i < n; ++i) {
        fx += gaussian(x, G[i]) * w[i];
    }

    return fx;
}

vector<double> universal_approximator::test(const vector<double> &xs) {

    vector<double> fxs;
    int n = xs.size();

    for (int i = 0; i < n; ++i) {
        fxs.push_back( get_output( xs[i] ) );
    }

    return fxs;
}
