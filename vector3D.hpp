
# pragma once

# include <types.hpp>
# include <exceptions.hpp>

# include <cmath>
# include <iostream>

// rvalues: https://stackoverflow.com/questions/1116641/is-returning-by-rvalue-reference-more-efficient

namespace NAMESPACE_RT
{
	/**
	 * 	@brief Represent a point in a 3 dimensinal space
	 *
	 * 	@method: normalize
	 * 	@method: dot product
	 * 	@method: cross product
	 * 	@method: rotate
	 * 	@method: distance
	 * 
	 * 	@operators: =, +, +=, -, -=, *, *=, /, /=, %, %=, ==, !==, <<
	*/
    class Vector3D
    {
        f64 x;
        f64 y;
        f64 z;

        Vector3D() = default;

        public:

        Vector3D(f64 axisX, f64 axisY, f64 axisZ)
        noexcept
        : x(axisX), y(axisY), z(axisZ)
        { }

        Vector3D(const Vector3D& other)
        noexcept
        { *this = other; }

        Vector3D(const Vector3D&& other)
        noexcept
        { *this = other; }

        ~Vector3D() { }

        f64 getX() const noexcept { return this->x; }
        f64 getY() const noexcept { return this->y; }
        f64 getZ() const noexcept { return this->z; }

        f64
        normalize() const
        noexcept
        { return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2) + std::pow(this->z, 2));  }

        f64
        dotProduct(const Vector3D& other) const
        noexcept
        { return (this->x * other.getX()) + (this->y * other.getY()) + (this->z * other.getZ()); }

        
        Vector3D
        getCrossProduct(const Vector3D& other) const
        noexcept
        {
            return Vector3D(
                this->y * other.getZ() - this->z * other.getY(),
                this->z * other.getX() - this->x * other.getZ(),
                this->x * other.getY() - this->y * other.getX()
            );
        }

        Vector3D&
        setCrossProduct(const Vector3D& other)
        noexcept
        { return *this = this->getCrossProduct(other); }

		///NOTE: radVec is *= PI /= 180
        Vector3D
        getRotate(Vector3D& radVec) const
		noexcept
        {
            Vector3D res(*this);

            (radVec *= M_PI) /= 180.0;

			// X rotation
			res.y = res.y * cos(radVec.getX()) - res.z * sin(radVec.getX());
			res.z = res.y * sin(radVec.getX()) + res.z * cos(radVec.getX());

			// Y rotation
			res.x = res.x * cos(radVec.getY()) + res.z * sin(radVec.getY());
			res.z = -res.x * sin(radVec.getY()) + res.z * cos(radVec.getY());

			// Z rotation
			res.x = res.x * cos(radVec.getZ()) - res.y * sin(radVec.getZ());
			res.y = res.x * sin(radVec.getZ()) + res.y * cos(radVec.getZ());

			return res;
        }

		///NOTE: radVec is *= PI /= 180
		Vector3D&
		setRotate(Vector3D& radVec)
		noexcept
		{ return *this = this->getRotate(radVec); }

		f64
		distance(const Vector3D& other) const
		noexcept 
		{
			return std::sqrt(std::pow(this->x - other.getX(), 2)
			+ std::pow(this->y - other.getY(), 2) + std::pow(this->z - other.getZ(), 2));
		}

        Vector3D&
        operator=(const Vector3D& other)
        noexcept
        {
            if (this != &other)
            {
                this->x = other.x;
                this->y = other.y;
                this->z = other.z;
            }
            return *this;
        }

        Vector3D
        operator+(const Vector3D&& other) const
        noexcept
        { return Vector3D(this->x + other.x, this->y + other.y, this->z + other.z); }

        Vector3D
        operator-(const Vector3D&& other) const
        noexcept
        { return Vector3D(this->x - other.x, this->y - other.y, this->z - other.z); }

        Vector3D&
        operator+=(const Vector3D& other)
        noexcept
        {
            if (this != &other)
            {
                this->x += other.x;
                this->y += other.y;
                this->z += other.z;
            }
            return *this;
        }

        Vector3D&
        operator-=(const Vector3D& other)
        noexcept
        {
            if (this != &other)
            {
                this->x -= other.x;
                this->y -= other.y;
                this->z -= other.z;
            }
            return *this;
        }

        Vector3D
        operator*(f64 scale) const
        throw(ExceptionDivByZero)
        { return Vector3D(this->x * scale, this->y * scale, this->z * scale); }

        Vector3D
        operator*(const Vector3D& other) const
        noexcept
        { return Vector3D(this->x * other.getX(), this->y * other.getY(), this->z * other.getZ()); }

        Vector3D&
        operator*=(f64 scale)
        noexcept
        {
            this->x *= scale;
            this->y *= scale;
            this->z *= scale;
            
            return *this;
        }

        Vector3D&
        operator*=(const Vector3D& other)
        noexcept
        {
            this->x *= other.getX();
            this->y *= other.getY();
            this->z *= other.getZ();

            return *this;
        }

        Vector3D
        operator/(f64 divisor) const
        throw(ExceptionDivByZero) /** TODO: Update to modern C++ */
        {
            if (divisor == FZERO)
                throw ExceptionDivByZero();
            return Vector3D(this->x / divisor, this->y / divisor, this->z / divisor);
        }

        Vector3D
        operator/(const Vector3D& other) const
        throw(ExceptionDivByZero) /** TODO: Update to modern C++ */
        {
            if (other.getX() == FZERO || other.getY() == FZERO || other.getZ() == FZERO)
                throw ExceptionDivByZero();
            return Vector3D(this->x / other.getX(), this->y / other.getY(), this->z / other.getZ());
        }

        Vector3D&
        operator/=(f64 divisor)
        throw(ExceptionDivByZero) /** TODO: Update to modern C++ */
        {
            if (divisor == FZERO)
                throw ExceptionDivByZero();
            this->x /= divisor;
            this->y /= divisor;
            this->z /= divisor;
            
            return *this;
        }

        Vector3D&
        operator/=(const Vector3D& other)
        throw(ExceptionDivByZero) /** TODO: Update to modern C++ */
        {
            if (other.getX() == FZERO || other.getY() == FZERO
            || other.getZ() == FZERO)
                throw ExceptionDivByZero();
            this->x /= other.getX();
            this->y /= other.getY();
            this->z /= other.getZ();

            return *this;
        }

        Vector3D
        operator%(f64 modulo) const
        noexcept
        { return Vector3D(std::fmod(this->x, modulo), std::fmod(this->x, modulo), std::fmod(this->x, modulo)); }

        Vector3D
        operator%(const Vector3D& other) const
        noexcept
        { return Vector3D(std::fmod(this->x, other.getX()), std::fmod(this->y, other.getY()), std::fmod(this->z, other.getZ())); }

        Vector3D&
        operator%=(f64 modulo)
        noexcept
        {
            this->x = std::fmod(this->x, modulo);
            this->y = std::fmod(this->y, modulo);
            this->z = std::fmod(this->z, modulo);

            return *this;
        }

        Vector3D&
        operator%=(const Vector3D& other)
        noexcept
        {
            this->x = std::fmod(this->x, other.getX());
            this->y = std::fmod(this->y, other.getY());
            this->z = std::fmod(this->z, other.getZ());

            return *this;
        }

        friend bool operator==(const Vector3D& lhs, const Vector3D& rhs);
        friend bool operator!=(const Vector3D& lhs, const Vector3D& rhs);
    };

    inline bool
    operator==(const Vector3D& lhs, const Vector3D& rhs)
    { return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY() && lhs.getZ() == rhs.getZ(); }

    inline bool
    operator!=(const Vector3D& lhs, const Vector3D& rhs)
    { return !(lhs == rhs); }

    std::ostream&
    operator<<(std::ostream& os, const Vector3D& vec)
    { return os << "Vector [ " << &vec << " ]: { "<< vec.getX()
    << ", " << vec.getY() << ", " << vec.getZ() << " }"; }
}
    