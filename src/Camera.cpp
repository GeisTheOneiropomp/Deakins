#include "Camera.h"
#include <math.h>
using namespace deakins_math;

//50 mm camera
// aperture 
Camera::Camera(Point3 lookFrom, Point3 lookAt, Vec3 upVec, double verticalFieldOfView,
    double aspectRatio, double aperture, double focusDistance,
    double time0, double time1, double tilt, double shift, bool useVignette) {

    auto theta = DegreesToRadians(verticalFieldOfView);
    auto height = tan(theta/2);
    auto viewportHeight = 2.0 * height;
    auto viewportWidth = aspectRatio * viewportHeight;

    w = UnitVector(lookFrom - lookAt);
    u = UnitVector(Cross(upVec, w));
    v = Cross(w, u);

    origin = lookFrom;
    lensCenter = lookAt;
    horizontal = focusDistance * viewportWidth * u;
    vertical = focusDistance * viewportHeight * v;
    lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - focusDistance*w;
    lensRadius = aperture / 2;
    this->time0 = time0;
    this->time1 = time1; 
    this->tilt = tilt;
    this->shift = shift;
    this->vignetteOption = useVignette;
}

Ray Camera::getRay(double s, double t) const
{
    auto randomTime = WeightedExponential(RandomDouble(time0, time1), 5);
    auto randomTilt = interpolateTilt(randomTime);
    auto randomShift = interpolateShift(randomTime);
    Vec3 rd = lensRadius * RandomInUnitDisk();
    Vec3 offset = u * rd.x() + v * rd.y();
    return Ray(origin + offset, 
        lowerLeftCorner + (s * (horizontal + Vec3(randomShift, 0, 0))) + (t * vertical + Vec3(0, randomTilt, 0)) - origin - offset,
        randomTime);
}

MonochromaticRay Camera::getDiffractionRay(double s, double t, double wavelength) const {

    auto randomTime = WeightedExponential(RandomDouble(time0, time1), 5);
    auto randomTilt = interpolateTilt(randomTime);
    auto randomShift = interpolateShift(randomTime);
    Vec3 rd = lensRadius * RandomOnUnitDesk();
    Vec3 offset = u * rd.x() + v * rd.y();

    Vec3 actualOrgin = origin + offset;
    Vec3 opticalAxis = lensCenter - origin;
    Vec3 rayDirection = lowerLeftCorner + (s * (horizontal + Vec3(randomShift, 0, 0))) + (t * vertical + Vec3(0, randomTilt, 0)) - origin - offset;
    Vec3 chiefRay = -rayDirection;

    double diffAngle = Angle(opticalAxis, chiefRay);
    double intensity = getDiffractionIntensity(diffAngle, wavelength);
    return MonochromaticRay(origin + offset,
        lowerLeftCorner + (s * (horizontal + Vec3(randomShift, 0, 0))) + (t * vertical + Vec3(0, randomTilt, 0)) - origin - offset,
      randomTime, wavelength, intensity);

}

double Camera::getDiffractionIntensity(double theta, double wavelength) const {

    auto unitWavelength = wavelength * (0.000001);
    auto waveNumber = 2 * pi / unitWavelength;
    auto beta = (waveNumber * lensRadius / 50 * sin(theta));
    if (beta == 0.0f) {
        return 0.0;
    }
    return pow((sin(beta)/beta),2);
}

double Camera::vignetteFactor(double s, double t) const {

    if (vignetteOption) {
        auto randomTime = WeightedExponential(RandomDouble(time0, time1), 5);
        auto randomTilt = interpolateTilt(randomTime);
        auto randomShift = interpolateShift(randomTime);

        Vec3 opticalAxis = lensCenter - origin;
        Vec3 chiefRay = lensCenter - (lowerLeftCorner + (s * (horizontal + Vec3(randomShift, 0, 0)) + (t * (vertical + Vec3(0, randomTilt, 0)))));
        return pow(CosAngle(opticalAxis, chiefRay), 4);
    }
    else {
        return 1;
    }

}

double Camera::interpolateTilt(double randomVar) const {
   
    auto timeFactor = randomVar * (time1 - time0);
    return timeFactor * tilt;

}

double Camera::interpolateShift(double randomVar) const {

    auto timeFactor = randomVar * (time1 - time0);
    return timeFactor * shift;
}
