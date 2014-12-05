#include "base64/base64.h"

#include <iostream>
#include <cassert>

void check_encode_output(std::string input, std::string expected_output) {
	auto out = base64::encode(input);
	std::cout << "check_encode_output() -- in: " << input << " out: " << out << " expected: " << expected_output << std::endl;
	if (out.compare(expected_output) != 0) {
		std::cerr << "base64 encode of '" << input << "' gave back '" << out << "' but we are expecting '" << expected_output << "'" << std::endl;
		//exit(-1);
	}
	assert(out.compare(expected_output) == 0);
}

void check_decode_output(std::string input, std::string expected_output) {
	auto out = base64::decode(input);
	std::cout << "check_decode_output() -- in: " << input << " out: " << out << " expected: " << expected_output << std::endl;
	if (out.compare(expected_output) != 0) {
		std::cerr << "base64 decode of '" << input << "' gave back '" << out << "' but we are expecting '" << expected_output << "'" << std::endl;
		exit(-1);
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
	auto encodeout = base64::encode(somethinglong);
	auto decodeout = base64::decode(encodeout);
	assert(somethinglong.compare(decodeout) == 0);

	return 0;
}
