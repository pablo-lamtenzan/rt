
# pragma once

# include <vector3D.hpp>

namespace NAMESPACE_RT  
{
    struct Ray
    {
        Vector3D pos;
        Vector3D dir;

        Ray(const Vector3D& rayPos, const Vector3D& rayDir)
        : pos(rayPos), dir(rayDir)
        { }

        ~Ray()
        { }
    };
}
