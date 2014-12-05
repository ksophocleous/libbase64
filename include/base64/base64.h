#ifndef LIBBASE64_H
#define LIBBASE64_H

#include <string>

namespace base64 {
	std::string encode(const std::string& input);
	std::string decode(const std::string& input);
}

#endif // LIBBASE64_H
