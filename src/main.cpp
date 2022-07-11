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
#include "../extern/EasyBMP/EasyBMP.h"
using namespace deakins_math;

int main() {

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

    BMP outputImage;
    outputImage.SetSize(OutputImageWidth, OutputImageHeight);
    for (int j = OutputImageHeight - 1; j >= 0; --j) {
        std::cerr << "\rGenerating the Deakins Effect...\rCurrently Raytracing...Scanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < OutputImageWidth; ++i) {
            Color normal_pixel_color(0, 0, 0);
            for (int s = 0; s < SamplesPerPixel; ++s) {
                auto u = (i + RandomDouble()) /  (double (OutputImageWidth - 1.0));
                auto v = (j + RandomDouble()) /  (double (OutputImageHeight - 1.0));
                if (RandomDouble(0, 1) < 1 - DiffractionRatio) {
                    Ray r = cam.getRay(u, v);
                    normal_pixel_color +=  RayColorWithBackground(r, skybox, world, MaxDepth) *cam.vignetteFactor(u, v, VignetteFactor);
                }
                else {
                    MonochromaticRay mr = cam.getDiffractionRay(u, v, RandomDouble(380.00, 750.00));
                    normal_pixel_color +=  DiffractionRayColorWithBackground(mr, skybox, world, MaxDepth) * cam.vignetteFactor(u, v, VignetteFactor);
                }
            }
            ColorUtil::WriteColor(normal_pixel_color, SamplesPerPixel, &outputImage, i, OutputImageHeight - j - 1);
        }
    }
    outputImage.WriteToFile(OUTPUT.c_str());
    std::cerr << "\nDone. Output File to " << OUTPUT << "\n";
}