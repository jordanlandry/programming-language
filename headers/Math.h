#pragma once
class Math {
public:
    float pow(float num, int exp) {
        float result = num;
        for (int i = 0; i < exp; i++) {
            result *= num;
        }
        return result;
    }

	float sqrt(float num) {
		// Binary search
		float low = 0;
		float high = num / 2;
		float guess = high;
		float minDistance = 0.0000000000001;
		if (num == 1) return 1;
		if (num < 0) return NAN;
		while (guess * guess < (num - minDistance) || guess * guess > (num + minDistance)) {
			if (guess * guess > num + minDistance) high = guess;
			else low = guess;

			guess = (high - low) / 2 + low;
		}
		return guess;
	}

	float nthroot(float num, int root) {
		float low = 0;
		float high = num / 2;
		float guess = high;
		float minDistance = 0.00000000001;
		if (num == 1) return 1;
		if (num < 0) return NAN;
		while (this->pow(guess, root) < (num - minDistance) || this->pow(guess, root) > (num + minDistance)) {
			if (this->pow(guess, root) > num + minDistance) high = guess;
			else low = guess;

			guess = (high - low) / 2 + low;
		}
		return guess;
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

