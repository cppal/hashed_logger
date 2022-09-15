#include "../common/logger_defs.h"

#include <fstream>
#include <string>



int main()
{
	std::ifstream ifs{ "../encoded_log.txt" };
	std::ofstream ofs{ "../decoded_log.txt" };

	std::string line_str;

	while (ifs)
	{
		std::getline(ifs, line_str);
		if (!line_str.empty())
		{
			const auto decoded_line = decode_log_line(line_str);
			ofs << decoded_line << '\n';
		}
	}

	return 0;
}