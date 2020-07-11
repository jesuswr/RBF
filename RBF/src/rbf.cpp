#include "rbf.hpp"

const int MEANS_SIZE = 20;

rbf::rbf(vector<double> &x,
         vector<double> &y, double lambda) {
	int n = x.size();
	mat data(&x.front(), 1, n);
	mat means;
	mat d = y;

	if ( !kmeans(means, data, MEANS_SIZE, random_subset, 10, false) ) {
		printf("Error in kmeans\n");
		exit(-1);
	}

	double dmax = 0;
	for (int i = 0; i < MEANS_SIZE; ++i) {
		for (int j = i + 1; j < MEANS_SIZE; ++j) {
			dmax = max(fabs(means(0, i) - means(0, j)), dmax);
		}
	}
	sigma = dmax / (2*MEANS_SIZE);

	mat G(n, MEANS_SIZE);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < MEANS_SIZE; ++j) {
			G(i, j) = gaussian(x[i], means(0, j));
		}
	}

	mat G0(MEANS_SIZE, MEANS_SIZE);
	for (int i = 0; i < MEANS_SIZE; ++i) {
		for (int j = 0; j < MEANS_SIZE; ++j) {
			G0(i, j) = gaussian(means(0, i), means(0, j));
		}
	}

	// solve ( t(G)*G + lambda*G0)W = t(G)*d
	mat ans = inv(G.t() * G + lambda * G0) * G.t() * d;

	for (int i = 0; i < MEANS_SIZE; ++i) {
		w.push_back(ans(i, 0));
		g.push_back(means(0, i));
	}
}

double rbf::gaussian(double xi, double xj) {
	double num = (xi - xj) * (xi - xj) ;
	double den = sigma;
	return exp( -num / den );
}

double rbf::get_output(double x) {
	int n = w.size();
	double fx = 0;

	for (int i = 0; i < n; ++i) {
		fx += gaussian(x, g[i]) * w[i];
	}

	return fx;
}

vector<double> rbf::test(const vector<double> &xs) {
	vector<double> fxs;
	int n = xs.size();

	for (int i = 0; i < n; ++i) {
		fxs.push_back( get_output( xs[i] ) );
	}

	return fxs;
}
