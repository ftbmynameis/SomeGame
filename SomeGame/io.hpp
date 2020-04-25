#pragma once

#include <iostream>

namespace util
{
	template <typename Arg>
	inline std::ostream& concat(std::ostream& out, Arg&& arg)
	{
		return out << arg;
	}

	template <typename Arg, typename... Args>
	inline std::ostream& concat(std::ostream& out, Arg&& arg, Args&&... args)
	{
		return concat(out << arg, std::forward<Args>(args)...);
	}
} // namespace util