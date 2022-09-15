#pragma once

#ifdef ENCODE_LOGS
	#include "../common/hash_utils.h"
	#define LOG(MSG) ofs << HASH(MSG) << '\n'
#elif defined(DECODE_LOGS)
	#include "../decoder/do_on_init.h"
	#include "../decoder/decoder.h"
	#define LOG(MSG) DO_ON_INIT(register_log_message(MSG))
#endif
