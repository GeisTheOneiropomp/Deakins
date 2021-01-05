#pragma once
#include "Vec3.h"
class Perlin
{ 
public:
	Perlin();
	~Perlin();
	double Noise(const Point3& point) const;
private:
	static int* PerlinGeneratePerm();
	static void Permute(int* p, int n);
	static double TrilinearInterpolation(double c[2][2][2], double u, double v, double w);

	static const int point_count = 256;
	double* random_floats;
	int* perm_x;
	int* perm_y;
	int* perm_z;
};
