#include "NoiseTexture.h"

NoiseTexture::NoiseTexture()
{
	scale = 1;
}

NoiseTexture::NoiseTexture(double scale) : scale(scale)
{
}

Color NoiseTexture::value(double u, double v, const Point3& p) const
{
	return Color(1, 1, 1) *.5 * (1 + sin(scale*p.z() + 10* noise.Turbulence(p)));
}
