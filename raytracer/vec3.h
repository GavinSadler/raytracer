
#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3
{
	public:
		vec3() : e{ 0, 0, 0 } {}
		vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

		// Returns a vector3 with values ranging from [-1, 1]
		inline static vec3 random() {
			return vec3(random_double(), random_double(), random_double());
		}

		// Returns a vector3 with values ranging from [min, max]
		inline static vec3 random(double min, double max) {
			return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
		}

		double x() const { return e[0]; }
		double y() const { return e[1]; }
		double z() const { return e[2]; }

		vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

		// One of these gives a copy of a double, whereas the other gives a reference to the double
		double operator[](int i) const { return e[i]; }
		double& operator[](int i) { return e[i]; }

		vec3& operator += (const vec3& v) {
			e[0] += v.e[0];
			e[1] += v.e[1];
			e[2] += v.e[2];
			return *this;
		}

		vec3& operator *= (const double t) {
			e[0] *= t;
			e[1] *= t;
			e[2] *= t;
			return *this;
		}

		vec3& operator /= (const double t) {
			return *this *= 1 / t;
		}

		double length_squared() const {
			return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
		}

		double length() const {
			return sqrt(length_squared());
		}

		// This is the array container which holds the 3 numbers in the vector
		double e[3];
};

// Utility functions/operators for vectors

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v){
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v){
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v){
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(const vec3& u, double t){
	return vec3(u.e[0] * t, u.e[1] * t, u.e[2] * t);
}

inline vec3 operator*(double t, const vec3& u){
	return u * t;
}

// V does not have to be a reference since we don't have to directly access any of its members in this function, thanks to the multiplicaiton overloads above
inline vec3 operator/(vec3 v, double t){
	return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
	return u.e[0] * v.e[0]
		 + u.e[1] * v.e[1]
		 + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
				u.e[2] * v.e[0] - u.e[0] * v.e[2],
				u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 u) {
	return u / u.length();
}

vec3 random_in_unit_sphere()
{
	while (true) {
		auto p = vec3::random(-1, 1);

		if (p.length_squared() >= 1) continue;

		return p;
	}
}

// Type aliases
using point3 = vec3;
using color = vec3;

#endif // !VEC3_H
