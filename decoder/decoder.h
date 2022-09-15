#pragma once

#include <string_view>



void register_log_message(std::string_view msg);
const char* decode_log_line(const std::string& line);
