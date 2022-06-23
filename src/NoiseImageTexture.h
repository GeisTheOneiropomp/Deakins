#pragma once
#include "Texture.h"
#include "Perlin.h"
#include "Vec3Util.h"
#include <string>
#include <iostream>

using std::string;

class NoiseImageTexture :
    public Texture
{
public:
	const static int bytes_per_pixel = 3;

	NoiseImageTexture();
	NoiseImageTexture(double scale, string fileName);
	virtual Color value(double u, double v, const Point3& p) const override;
	Perlin noise;
	double scale;
	~NoiseImageTexture();



private:
	unsigned char* data;
	int width, height;
	int bytes_per_scanline;
	Color valueOne(double u, double v, const Point3& p) const;
	Color valueTwo(double u, double v) const;
};

