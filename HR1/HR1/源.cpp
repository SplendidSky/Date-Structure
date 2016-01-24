#include <set>

using namespace std;

template<class T>
T& stat(double t, const vector<double> &rec, T& out) {
	set<double> absolute_error;
	double sum = 0;
	for (int i = 0; i < rec.size(); i++) {
		absolute_error.insert(rec[i] - t);
		sum += rec[i] - t;
	}
	return out << absolute_error[0] << absolute_error[absolute_error.size() - 1] << sum / rec.size();
}
