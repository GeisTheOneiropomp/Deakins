#include <iostream>
#include <fstream>

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
#include "Config.h"

using namespace deakins_math;

int main() {

    //world
    auto R = cos(pi / 4);

    HittableList world;
    auto skybox = new Skybox(SKYBOX_FILE);
    Point3 lookfrom(13, 2, 3);
    Point3 lookat(0, 0, 0);
    Vec3 vup(0, 1, 0);

    switch (ScenePath) {
    case SCENEPATH::BASESCENE :
    default:
        world = SingleSphere();    
        lookfrom = Point3(3, 1, 0);
        lookat = Point3(0, 0, 0);
        break;
    case 2:
        world = TwoPerlinSpheres();
        lookfrom = Point3(13, 2, 3);
        lookat = Point3(0, 0, 0);
        break;
    }

    Camera cam(lookfrom, lookat, vup, FieldOfView, AspectRatio, Aperture, DistToFocus, 0.0, 1.0, TiltFactor, ShiftFactor, UseVignette);
    // Render

    std::ofstream outfile;
    outfile.open(OUTPUT);

    outfile << "P3\n" << ImageWidth << ' ' << ImageHeight << "\n255\n";

    for (int j = ImageHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < ImageWidth; ++i) {
            Color normal_pixel_color(0, 0, 0);
            for (int s = 0; s < SamplesPerPixel; ++s) {
                auto u = (i + RandomDouble()) /  (double (ImageWidth - 1.0));
                auto v = (j + RandomDouble()) /  (double (ImageHeight - 1.0));
                if (RandomDouble(0, 1) < 1 - DiffractionRatio) {
                    Ray r = cam.getRay(u, v);
                    normal_pixel_color +=  RayColorWithBackground(r, skybox, world, MaxDepth) *cam.vignetteFactor(u, v, VignetteFactor);
                }
                else {
                    MonochromaticRay mr = cam.getDiffractionRay(u, v, RandomDouble(380.00, 750.00));
                    normal_pixel_color +=  DiffractionRayColorWithBackground(mr, skybox, world, MaxDepth) * cam.vignetteFactor(u, v, VignetteFactor);
                }
            }
            ColorUtil::WriteColor(outfile, normal_pixel_color, SamplesPerPixel);
        }
    }
    outfile.close();
    std::cerr << "\nDone.\n";
}