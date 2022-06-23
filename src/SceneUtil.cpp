#include "SceneUtil.h"
#include "Lambertian.h"
#include "Sphere.h"
#include "Metal.h"
#include "Dielectric.h"
#include "MovingSphere.h"
#include "NoiseTexture.h"
#include "ImageTexture.h"
#include "HittableList.h"
#include "FileResources.h"
#include "NoiseImageTexture.h"

using namespace deakins_math;

HittableList TwoPerlinSpheres() {
    HittableList objects;

    auto pertext = make_shared<NoiseTexture>(10);
    objects.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(pertext)));
    objects.add(make_shared<Sphere>(Point3(0, 2, 0), 2, make_shared<Lambertian>(pertext)));

    return objects;
}

HittableList SingleSphere() {
    HittableList world;

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3(0, 0, 0), 1.0, material1));

    return world;
}


HittableList RandomScene() {
    HittableList world;
    auto pertext = make_shared<NoiseTexture>(13);
    world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(pertext)));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = RandomDouble();
            Point3 center(a + 0.9 * RandomDouble(), 0.2 +RandomInt(-3,3), b + 0.9 * RandomDouble());

            if ((center - Point3(4, 0.2, 0)).Length() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < .7) {
                    // diffuse
                    auto albedo = random() * random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    auto center2 = center + Vec3(0, RandomDouble(0, 0.5), 0);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random() * random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                if (choose_mat < 0.1) {
                    // metal
                    auto albedo = random(0.5, 1);
                    auto fuzz = RandomDouble(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2 + RandomDouble(-.1, .4), sphere_material));
                }
                else if (choose_mat < 0.2) {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2 + RandomDouble(-.1, .4), sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3(0, 0, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}