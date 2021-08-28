
#ifndef RAY_H
#define RAY_H

#include "vec3.h"

/*
	Represents the function for a ray in 3D space
	Basically, the equation of a line

	P(t) = A + tB

		A - The origin of the ray, a 3D point
		B - The direction of the ray, a 3 component vector
		t - The movement along the ray
*/

class ray {
	public:
		ray() {}
		ray(const point3& origin, const vec3& direction)
			: orig(origin), dir(direction)
		{}

		point3 origin() const { return orig; }
		vec3 direction() const { return dir; }

		point3 at(double t) const {
			return orig + t * dir;
		}

		point3 orig;
		vec3 dir;
};

#endif // !RAY_H
