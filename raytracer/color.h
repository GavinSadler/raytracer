
#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel) {
	// Since a pixel's color is the sum of the samples for the given pixel, the range of each color component may exceed the expected max value of 1
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	// Divide each color component by the number of samples
	auto scale = 1.0 / samples_per_pixel;
	r *= scale;
	g *= scale;
	b *= scale;

	// Now our pixels should be in the range of [0.0, 1.0], just clamp the values before casting to make sure we stay below 256
	out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif
