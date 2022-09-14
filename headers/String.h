#pragma once
#include <string>

class String {
public:
	std::string value;
	int length() {
		return this->value.size();
	}

	bool includes(std::string s) {
		return this->value.find(s) != std::string::npos;
	}
};