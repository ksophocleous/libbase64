#include "base64/base64.h"

#include <iostream>
#include <cassert>

std::vector<uint8_t> convert_from_string(const std::string& input) {
	return std::vector<uint8_t>(input.data(), input.data() + input.size());
}

bool compare_vec(const std::vector<uint8_t>& left, const std::vector<uint8_t>& right) {
	if (left.size() != right.size())
		return false;

	for (size_t i = 0; i < left.size(); i++)
		if (left[i] != right[i])
			return false;

	return true;
}

void check_encode_output(std::string input, std::string expected_output) {
	auto vec = convert_from_string(input);
	auto expout = convert_from_string(expected_output);
	auto outstr = base64::encode(vec);
	auto out = convert_from_string(outstr);
	if (compare_vec(out, expout) == false) {
		std::cout << "failed on in " << input << " got '" << outstr << "' but expected '" << expected_output << "'" << std::endl;
		assert(false);
	}
}

void check_decode_output(std::string input, std::string expected_output) {
	auto out = base64::decode(input);
	auto strout = std::string(out.data(), out.data() + out.size());
	if (strout.compare(expected_output) != 0) {
		std::cout << "failed on in " << input << " got '" << strout << "' but expected '" << expected_output << "'" << std::endl;
		assert(false);
	}
}

int main(int argc, char* argv[]) {
	check_encode_output("hi buddy", "aGkgYnVkZHk=");
	check_encode_output("a", "YQ==");
	check_encode_output("end it once and for all.", "ZW5kIGl0IG9uY2UgYW5kIGZvciBhbGwu");

	check_decode_output("aGkgYnVkZHk=", "hi buddy");
	check_decode_output("YQ==", "a");
	check_decode_output("ZW5kIGl0IG9uY2UgYW5kIGZvciBhbGwu", "end it once and for all.");

	std::string somethinglong = "sao5ntlkjauefdvpoauhwiv53pmqc94hyt3oiq4cuhtm;bmoqhvcloiwhefliUQHLIEULIU5RTHQ3LIGCMELRHUQWLIU45HNOL2GCTQKXP[WEFP;WEFK;ERKTKVMW;BJ64OV]\x02\x03\x06\x07";
	auto data = convert_from_string(somethinglong);
	auto encodeout = base64::encode(data);
	auto decodeout = base64::decode(encodeout);
	assert(compare_vec(data, decodeout));

	return 0;
}
