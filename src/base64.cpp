#include "base64/base64.h"
#include "base64.h"

#include <stdexcept>

namespace base64 {
	std::string encode(const std::vector<uint8_t>& input) {
		size_t len = BASE64_LENGTH(input.size());
		std::string output;
		output.resize(len);

		base64_encode(reinterpret_cast<const char*>(input.data()), input.size(), reinterpret_cast<char*>(&output[0]), output.size() + 1);

		return output;
	}

	std::vector<uint8_t> decode(const std::string& input) {
		std::vector<uint8_t> output;
		size_t outlen = input.size();
		output.resize(outlen);
		if (input.size() > 0) {
			bool result = base64_decode(reinterpret_cast<const char*>(input.data()), input.size(), reinterpret_cast<char*>(&output[0]), &outlen);
			if (result == false)
				throw std::runtime_error("invalid base64 input given to base64::decode");
			output.resize(outlen);
		}

		return output;
	}
}
