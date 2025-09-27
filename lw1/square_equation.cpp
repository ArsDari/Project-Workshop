#include <cstdio>
#include <cmath>

float calculateDiscriminant(float a, float b, float c) {
	return b * b - 4 * a * c;
}

float findRoot(float a, float b, float discriminantRoot) {
	return (-b + discriminantRoot) / (2 * a);
}

int main() {
	std::puts("please enter a, b and c for `ax^2 + bx + c = 0`:");
	float a = 0;
	float b = 0;
	float c = 0;
	std::scanf("%f %f %f", &a, &b, &c);
	if (a == 0) {
		if (b == 0) {
			std::puts("wrong equation");
		}
		else {
			std::printf("solution: %f\n", -c / b);
		}
		return 0;
	}

	float discriminant = calculateDiscriminant(a, b, c);
	if (discriminant < 0) {
		std::printf("no solution");
		return 0;
	}

	float discriminantRoot = std::sqrt(discriminant);
	float result1 = findRoot(a, b, discriminantRoot);
	std::printf("solution: %f\n", result1);
	if (discriminant > 0) {
		float result2 = findRoot(a, b, -discriminantRoot);
		std::printf("%f\n", result2);
	}
	return 0;
}