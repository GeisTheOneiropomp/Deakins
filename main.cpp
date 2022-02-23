#include <iostream>
#include "ColorUtil.h"
#include "Ray.h"
#include "vec3.h"
#include "Vec3Util.h"
#include "D_util.h"

#include "HittableList.h"
#include "sphere.h"
#include "Camera.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "SceneUtil.h"
#include "RayColorUtil.h"
#include "ImageTexture.h"
#include "NoiseTexture.h"
#include "math.h"
#include "Skybox.h"
#include "D_Util.h"
#include "FileResources.h"

using namespace deakins_math;

int main() {

    // Image
    auto kAspectRatio = 16.0 / 9.0;
    int kImageWidth = 1600;
    int kImageHeight = static_cast<int> (kImageWidth / kAspectRatio);
    int samplesPerPixel = 100;
    int maxDepth = 30;

    //world
    auto R = cos(pi / 4);

    HittableList world;
    auto skybox = new Skybox(TSURUTA_FILE);
    Point3 lookfrom(13, 2, 3);
    Point3 lookat(0, 0, 0);
    Vec3 vup(0, 1, 0);
    auto distToFocus = 10;
    auto aperture = 0.0;
    double fieldOfView = 100;
    double tilt0 = 0;
    double shift0 = 0;
    double tilt1 = 0;
    double shift1 = 0;
    double diffractionRatio = 0;
    bool useVignette = 0;
    Color background(0, 0, 0);

    switch (0) {
    case 1:
    default:
        world = RandomScene();    
        samplesPerPixel = 100;
        lookfrom = Point3(3, 2, 3);
        background = Color(0.70, 0.80, 1.00);
        lookat = Point3(0, 0, 0);
        fieldOfView = 100;
        diffractionRatio = .1;
        useVignette = 1;
        aperture = 0.1;
        tilt1 = 1;
        shift1 = 1;
        break;
    case 2:
        world = two_perlin_spheres();
        background = Color(0.90, 0.60, 0.60);
        lookfrom = Point3(13, 2, 3);
        lookat = Point3(0, 0, 0);
        fieldOfView = 20.0;
        break;
    }

    Camera cam(lookfrom, lookat, vup, fieldOfView, kAspectRatio, aperture, distToFocus, 0.0, 1.0, tilt0, shift0, tilt1, shift1, useVignette);
    // Render

    std::cout << "P3\n" << kImageWidth << ' ' << kImageHeight << "\n255\n";

    for (int j = kImageHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < kImageWidth; ++i) {
            Color normal_pixel_color(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; ++s) {
                auto u = (i + RandomDouble()) /  (double (kImageWidth - 1.0));
                auto v = (j + RandomDouble()) /  (double (kImageHeight - 1.0));
                if (RandomDouble(0, 1) < 1 - diffractionRatio) {
                    Ray r = cam.getRay(u, v);
                    normal_pixel_color +=  RayColorWithBackground(r, skybox, world, maxDepth) *cam.vignetteFactor(u, v);
                }
                else {
                    MonochromaticRay mr = cam.getDiffractionRay(u, v, RandomDouble(380.00, 750.00));
                    normal_pixel_color +=  DiffractionRayColorWithBackground(mr, skybox, world, maxDepth) * cam.vignetteFactor(u, v);
                }
            }
            
            ColorUtil::WriteColor(std::cout, normal_pixel_color, samplesPerPixel);
        }
    }
    std::cerr << "\nDone.\n";
}