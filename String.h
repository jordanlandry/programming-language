#pragma once
#include <string>

class String {
public:
	std::string value;
	int length() {
		return this->value.size();
	}
};

