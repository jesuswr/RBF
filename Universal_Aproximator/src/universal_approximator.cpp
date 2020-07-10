#include "universal_approximator.hpp"

universal_approximator::universal_approximator(const vector<double> &x,
        const vector<double> &y, double lambda) {

    int n = x.size();
    mat m(n, n);
    mat d = y;

    // set sigma value with max(x[i]-x[j]) / sqrt(size(x))
    double mx_d = 0;
    for (int i = 0; i < n - 1; ++i) {
        mx_d = max(fabs(x[i] - x[i + 1]), mx_d);
    }
    sigma = mx_d / sqrt(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            m(i, j) = gaussian(x[i], x[j]);
        }
    }

    // solve (m + lamda*I) * w = d
    m = m + lambda * eye(n, n);
    //cout << cond(m) << endl;
    mat ans = inv(m) * d;

    for (int i = 0; i < n; ++i) {
        w.push_back( ans(i, 0) );
        G.push_back( x[i] );
    }
}

double universal_approximator::gaussian(double xi, double xj) {
    double num = (xi - xj) * (xi - xj) ;
    double den = 2.0 * sigma * sigma;
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
