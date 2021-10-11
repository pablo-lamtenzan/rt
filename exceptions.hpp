# pragma once

# include <rt.hpp>
# include <exception>

namespace NAMESPACE_RT
{
    struct ExceptionDivByZero : std::exception { const char* what() { return "Cannot divide by 0"; } };
}
