#include "Camera.h"

Camera::Camera(Point3 lookFrom, Point3 lookAt, Vec3 upVec, double verticalFieldOfView,
    double aspectRatio, double aperture, double focusDistance) {
    auto theta = degrees_to_radians(verticalFieldOfView);
    auto height = tan(theta/2);
    auto viewportHeight = 2.0 * height;
    auto viewportWidth = aspectRatio * viewportHeight;
    auto focalLength = 1.0;

    w = unit_vector(lookFrom - lookAt);
    u = unit_vector(cross(upVec, w));
    v = cross(w, u);

    origin = lookFrom;
    horizontal = focusDistance * viewportWidth * u;
    vertical = focusDistance * viewportHeight * v;
    lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - focusDistance*w;
    lensRadius = aperture / 2;
}

Ray Camera::getRay(double s, double t) const
{
    Vec3 rd = lensRadius * randomInUnitDisk();
    Vec3 offset = u * rd.x() + v * rd.y();
    return Ray(origin + offset, 
        lowerLeftCorner + s * horizontal + t * vertical - origin - offset);
}