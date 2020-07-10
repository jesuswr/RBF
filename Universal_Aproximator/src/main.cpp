#include <iostream>
#include <armadillo>
#include <vector>
#include "universal_approximator.hpp"

using namespace arma;
using namespace std;

const double LAMBDA = 0.001;
const double SIGMA = 0.5;

int main() {
    FILE *input = fopen("../../Spectra20.csv", "r");

    vector<double> xs, ys;
    double a, b;
    while ( fscanf(input, "%lF,%lF", &a, &b) != EOF ) {
        xs.push_back(a), ys.push_back(b);
    }

    fclose(input);

    universal_approximator my_approx(xs, ys, LAMBDA, SIGMA);

    vector<double> all_xs;
    for ( double i = 0; i <= 5; i += 0.01 )
        all_xs.push_back(i);

    vector<double> fxs = my_approx.test(all_xs);

    int n = fxs.size();
    for (int i = 0; i < n; ++i) {
        printf("%lF,%lF\n", all_xs[i], fxs[i]);

    }

    return 0;
}