#pragma once

#include <string_view>
#include <type_traits>
#include <initializer_list>

#define HASH(MSG) FORCE_CONST_EVAL(hash_string(MSG))
#define FORCE_CONST_EVAL(expr) (std::integral_constant<decltype(expr), (expr)>::value)

static constexpr size_t default_hash_seed = 0xdddad34ed82471d2;

// Adapted from https://github.com/serge-sans-paille/frozen/blob/1f006e45adf600280bd3924513b80023e8dfdc80/include/frozen/bits/hash_string.h#L19
// Roughly implements https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
constexpr size_t hash_strings(std::initializer_list<std::string_view> strings, size_t seed = default_hash_seed)
{
	size_t d = (0xcbf29ce484222325 ^ seed) * static_cast<size_t>(0x100000001B3);

	for (const auto& s : strings)
	{
		for (char c : s)
		{
			d = (d ^ static_cast<size_t>(c)) * static_cast<size_t>(0x01000193);
		}
	}

	return d >> 8;
}

constexpr size_t hash_string(std::string_view str, size_t seed = default_hash_seed)
{
	return hash_strings({ str }, seed);
}
