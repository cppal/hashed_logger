# hashed_logger
demo of logger with hashed log messages, as presented at CppCon and Core C++

This demo contains a Visual Studio solution with 2 projects:
- production - emulates production code, outputs obfuscated log entries
- decoder - creates decoder tool

Usage:
- Run production code, observe encoded log file encoded_log.txt being produced.
- Run decoder code, observe decoded log file decoded_log.txt: with src.cpp included in the decoder project logs are successfully decoded, without it decoding fails. In either case the decoder tool is successfully built and executed.
