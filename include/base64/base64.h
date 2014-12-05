#ifndef LIBBASE64_H
#define LIBBASE64_H

#include <string>
#include <vector>
#include <cstdint>

namespace base64 {
	std::string encode(const std::vector<uint8_t>& input);
	std::vector<uint8_t> decode(const std::string& input);
}

#endif // LIBBASE64_H
