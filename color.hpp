# pragma once

# include <types.hpp>
# include <exceptions.hpp>

# include <cmath>

namespace NAMESPACE_RT
{
    class Color
    {
        public:

        f64 r;
        f64 g;
        f64 b;
        f64 a;

        Color(f64 fr, f64 fg, f64 fb, f64 fa)
        : r(fr), g(fg), b(fb), a(fa)
        { }

        Color(u32 colorValue)
        : r(static_cast<f64>(colorValue & 0XFF)),
        g(static_cast<f64>((colorValue >> 8) & 0XFF)),
        b(static_cast<f64>((colorValue >> 16) & 0XFF)),
        a(static_cast<f64>((colorValue >> 24) & 0XFF))
        { }

        Color(const Color& other)
        { *this = other; }

        Color(const Color&& other)
        { *this = other; }

        ~Color()
        { }

        u32
        getColorValue() const
        noexcept
        {
            return static_cast<u32>(std::fmax(0.0, std::fmin(255.0, this->r)))
            | (static_cast<u32>(std::fmax(0.0, std::fmin(255.0, this->g))) << 8)
            | (static_cast<u32>(std::fmax(0.0, std::fmin(255.0, this->b))) << 16)
            | (static_cast<u32>(std::fmax(0.0, std::fmin(255.0, this->a))) << 24);
        }

        Color&
        operator=(const Color& other)
        noexcept
        {
            if (this != &other)
            {
                this->r = other.r;
                this->g = other.g;
                this->b = other.b;
                this->a = other.a;
            }
            return *this;
        }

        Color
        operator+(const Color& other) const
        noexcept
        {
            return Color(
                this->r + other.r,
                this->g + other.g,
                this->b + other.b,
                this->a + other.a
            );
        }

        Color&
        operator+=(const Color& other)
        noexcept
        {
            this->r += other.r;
            this->g += other.g;
            this->b += other.b;
            this->a += other.a;

            return *this;
        }

        Color
        operator-(const Color& other) const
        noexcept
        {
            return Color(
                this->r - other.r,
                this->g - other.g,
                this->b - other.b,
                this->a - other.a
            );
        }

        Color&
        operator-=(const Color& other)
        noexcept
        {
            this->r -= other.r;
            this->g -= other.g;
            this->b -= other.b;
            this->a -= other.a;

            return *this;
        }

        Color
        operator*(f64 scale) const
        noexcept
        {
            return Color(
                this->r * scale,
                this->g * scale,
                this->b * scale,
                this->a * scale
            );
        }

        Color&
        operator*=(f64 scale)
        noexcept
        {
            this->r *= scale;
            this->g *= scale;
            this->b *= scale;
            this->a *= scale;

            return *this;
        }

        Color
        operator/(f64 divisor) const
        throw(ExceptionDivByZero)
        {
            if (divisor == 0)
                throw ExceptionDivByZero();

            return Color(
                this->r / divisor,
                this->g / divisor,
                this->b / divisor,
                this->a / divisor
            );
        }

        Color&
        operator/=(f64 divisor)
        throw(ExceptionDivByZero)
        {
            if (divisor == 0)
                throw ExceptionDivByZero();

            this->r /= divisor;
            this->g /= divisor;
            this->b /= divisor;
            this->a /= divisor;

            return *this;
        }
    };
}
