
#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "ray.h"

class sphere : public hittable {
	public:
		sphere() {}
		sphere(point3 cen, double r) : center(cen), radius(r) {}

		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
		
		point3 center;
		double radius;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {

	auto oc = r.origin() - center;
	auto a = dot(r.direction(), r.direction());
	auto half_b = dot(r.direction(), oc);
	auto c = dot(oc, oc) - radius * radius;

	auto descriminant = half_b * half_b - a * c;

	if (descriminant < 0)
		return false;

	// Square root is expensive, so we precompute it
	auto sqrtd = sqrt(descriminant);

	// First, we try -b + sqrt(b^2 - 4ac) / 2a
	auto root = (-half_b - sqrtd) / a;
	if (root < t_min || root > t_max) {
		// If this is out of bounds, we can try -b - sqrt(b^2 - 4ac) / 2a
		root = (-half_b + sqrtd) / a;
		if (root < t_min || root > t_max)
			return false; // In this case, both computations for t were out of bounds, so we gotta get outta here
	}
	
	// When we assigned root above, we solved the quadratic equation for t in P(t)
	rec.t = root;

	// The point at which the ray hit the object
	rec.p = r.at(rec.t);

	// The normal is easy for a sphere, just the point intersected minus the center, and the normal should be a unit vector
	vec3 outward_normal = unit_vector(rec.p - center);
	rec.set_face_normal(r, outward_normal);

	return true;
}

#endif // !SPHERE_H
