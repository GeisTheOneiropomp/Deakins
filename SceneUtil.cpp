#include "SceneUtil.h"
#include "Lambertian.h"
#include "Sphere.h"
#include "Metal.h"
#include "Dielectric.h"
#include "ImproperLambert.h"
#include "LommelSeeliger.h"
#include "MovingSphere.h"
using namespace rtweekend_math;

HittableList RandomScene() {
    srand(time(NULL));
    HittableList world;

    auto ground_material = make_shared<Lambertian>(Color(0.0, 0.4, 0.7));
    world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = RandomDouble();
            Point3 center(a + 0.9 * RandomDouble(), 0.2, b + 0.9 * RandomDouble());

            if ((center - Point3(4, 0.2, 0)).Length() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.4) {
                    // diffuse
                    auto albedo = random() * random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    auto center2 = center + Vec3(0, RandomDouble(0, 0.5), 0);
                    world.add(make_shared<MovingSphere>(center, center2, 0.0, 1.0, 0.2, sphere_material));
                }

                else if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random() * random();
                    sphere_material = make_shared<LommelSeeliger>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random(0.5, 1);
                    auto fuzz = RandomDouble(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}