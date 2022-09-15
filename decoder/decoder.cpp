#include "decoder.h"

#include <map>
#include <string>
#include <cassert>

#include "../common/hash_utils.h"




namespace
{
	auto& getMessageRegistry()
	{
		static std::map<size_t, std::string> s_message_registry;
		return s_message_registry;
	};

	const char* getLogMessage(size_t msg_hash)
	{
		const auto& reg = getMessageRegistry();
		const auto it = reg.find(msg_hash);
		return (it != reg.end()) ? it->second.c_str() : "____";
	}
}



void register_log_message(std::string_view msg)
{
	auto& reg = getMessageRegistry();
	const auto key = hash_string(msg);
	assert((reg.find(key) == reg.end()) || ((reg.at(key) == msg.data()) || (reg.at(key).compare(msg) == 0)));
	reg.emplace(key, msg.data());
}

const char* decode_log_line(const std::string& line)
{
	return getLogMessage(std::stoll(line));
}
