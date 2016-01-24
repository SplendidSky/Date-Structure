class CIRCLE {
private:
	double r;
	double area;
	double length;
	double pi;
public:
	CIRCLE() : r(1), area(pi * r * r), length(2 * pi * r), pi(3.14) {}
	CIRCLE(double pi) : pi(pi) {}
	double get_r() const { return r; }
	double get_pi() const { return pi; }
	double cal_area() { return pi * r * r; }
	double cal_length() { return 2 * pi * r; }
};
