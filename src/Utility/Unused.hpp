#ifndef MONOSCRIPT_UNUSED_HPP
#define MONOSCRIPT_UNUSED_HPP

#define UNUSED(...) priv::unused(__VA_ARGS__)

namespace monoscript
{
namespace priv
{
template <typename... Args>
constexpr void unused(Args&&... args)
{
	(static_cast<void>(std::forward<Args>(args)), ...);
}
}
}

#endif // MONOSCRIPT_UNUSED_HPP
