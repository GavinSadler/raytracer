
#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>

color ray_color(const ray& r, const hittable& world) {

	hit_record rec;

	if (world.hit(r, 0, infinity, rec)) {
		// Color any hit object as the normal vector, which we map from [-1, 1] to [0, 1]
		return 0.5 * (rec.normal + color(1, 1, 1));
	}

	vec3 unit_direction = unit_vector(r.direction());

	// Because unit_direction is a unit form of r, unit_direction's y component is bounded by [-1.0, 1.0]
	// The following line will add one, changing the bound to [0.0, 2.0], then multiplies by 0.5, or divides by 2, making t bounded by [0.0, 1.0]
	auto t = 0.5 * (unit_direction.y() + 1.0);

	// Here we perform a lerp. At t=0.0, the color (1.0, 1.0, 1.0), which is white, is displayed
	// When t=1.0, the color (0.5, 0.7, 1.0), which is a sky blue, is displayed
	// Valus between 0.0 and 1.0 will interpolate these colors linearly
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {

	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 800;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;

	camera cam;

	// World
	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	// Rendering

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; j--) {
		std::cerr << "\nScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) {

			color pixel_color(0, 0, 0);

			for (int s = 0; s < samples_per_pixel; s++)
			{
				auto u = (i + random_double()) / (image_width - 1);
				auto v = (j + random_double()) / (image_height - 1);

				ray r = cam.get_ray(u, v);

				pixel_color += ray_color(r, world);
			}

			write_color(std::cout, pixel_color, samples_per_pixel);

		}
	}

	std::cerr << "\nDone\n";

}
