
# pragma once

# include <ray.hpp>
# include <color.hpp>

namespace NAMESPACE_RT
{

    struct IShape
    {
        Vector3D	pos;
		Color		color;

		IShape(const Vector3D& shapePos, const Color& shapeColor)
		: pos(shapePos), color(shapeColor)
		{ }

		~IShape()
		{ }

		virtual bool onCollision(const Ray& ray) = 0;
    };

	struct Plane
	: IShape
	{
		Vector3D dir;

		Plane(const Vector3D planePos, const Vector3D planeDir, const Color& planeColor)
		: IShape(planePos, planeColor), dir(planeDir)
		{ }

		~Plane()
		{ }

		bool onCollision(const Ray& Ray);
	};

	struct Sphere
	: IShape
	{
		u64 radius;

		Sphere(const Vector3D& pos, u64 rad, const Color& color)
		: IShape(pos, color), radius(rad)
		{ }

		~Sphere()
		{ }

		u64 diameter() const noexcept { return this->radius * 2; }

		bool onCollision(const Ray& Ray);
	};

	struct Cyclinder
	: IShape
	{
		Vector3D	dir;
		u64			radius;
		u64			height;

		Cyclinder(const Vector3D& pos, const Vector3D direc, u64 rad, u64 h, const Color &color)
		: IShape(pos, color), dir(direc), radius(rad), height(h)
		{ }

		~Cyclinder()
		{ }

		u64 diameter() const noexcept { return this->radius * 2; }

		bool onCollision(const Ray& Ray);
	};
}
