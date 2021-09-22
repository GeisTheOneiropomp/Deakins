#include "Skybox.h"
#include "RTWeekendUtil.h"
#include "Vec3Util.h"
using namespace rtweekend_math;

Skybox::Skybox()
{
}

Skybox::Skybox(string input)
{
	texturePointers.push_back(make_shared<ImageTexture>(input + "Tsuruta.jpg"));
}

Color Skybox::getValue(const Vec3 vector) const
{

	Vec3 unit = UnitVector(vector);


	auto theta = acos(-unit.y());
	auto phi = atan2(-unit.z(), unit.x()) + pi;

	auto u = phi / (2 * pi);
	auto v = (theta / pi);

	return texturePointers[0]->value(u, v, unit);

}