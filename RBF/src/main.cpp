#include <iostream>
#include <armadillo>
#include <vector>
#include "rbf.hpp"

using namespace arma;
using namespace std;

const double LAMBDA = 0.01;

int main() {
    FILE *input = fopen("../../Spectra100.csv", "r");

    vector<double> xs, ys;
    double a, b;
    while ( fscanf(input, "%lF,%lF", &a, &b) != EOF ) {
        xs.push_back(a), ys.push_back(b);
    }
    fclose(input);

    rbf my_rbf(xs, ys, LAMBDA);

    vector<double> all_xs;
    for ( double i = 0; i <= 5; i += 0.01 )
        all_xs.push_back(i);

    vector<double> fxs = my_rbf.test(all_xs);

    int n = fxs.size();
    for (int i = 0; i < n; ++i) {
        printf("%lF,%lF\n", all_xs[i], fxs[i]);
    }

    return 0;
}