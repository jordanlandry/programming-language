#pragma once
class Math {
public:
    int pow(int num, int exp) {
        int result = num;
        for (int i = 0; i < exp; i++) {
            result *= num;
        }
        return result;
    }

	double sqrt(double num) {
		return 1;
	}

	double round(double num) {
		return 1;
	}

	float round(float num) {
		return 1;
	}

	double floor(double num) {
		return 1;
	}

	float floor(float num) {
		return 1;
	}

	double ceil(double num) {
		return 1;
	}

	float ceil(float num) {
		return 1;
	}
};

