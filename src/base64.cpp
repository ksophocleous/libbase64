#include "base64/base64.h"
#include "base64.h"

#include <stdexcept>

namespace base64 {
	std::string encode(const std::string& input) {
		size_t len = BASE64_LENGTH(input.size());
		std::string output;
		output.resize(len);

		base64_encode(input.data(), input.size(), &output[0], output.size() + 1);

		return output;
	}

	std::string decode(const std::string& input) {
		std::string output;
		size_t outlen = input.size();
		output.resize(outlen);
		if (input.size() > 0) {
			bool result = base64_decode(input.data(), input.size(), &output[0], &outlen);
			if (result == false)
				throw std::runtime_error("invalid base64 input given to base64::decode");
			output.resize(outlen);
		}

		return output;
	}
}
