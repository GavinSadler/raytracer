
#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record {
	point3 p;		 // Point of hit
	vec3 normal;	 // Normal at point of hit
	double t;		 // For the ray which hit the object, the t at which that ray hit it
	bool front_face; // Whether or not the ray hit the front face of an object, or its back face

	// Checks to see if the normal and ray are pointing opposite in the same direction
	// If opposite, we flag it and flip the normal
	inline void set_face_normal(const ray& r, const vec3& outward_normal) {
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal; // Flip the normal if we hit a back face
	}
};

class hittable {
	public:
		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif // !HITTABLE_H

