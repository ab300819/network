#include <assert.h>

double sqrt(double x) {
	assert(x > 0.0);
	return 0.0;
}

int main(void) {
    sqrt(-9.0);
	static_assert(sizeof(int) >= 4,
				  "Integer should have at least 4 bytes length.");
	return 0;
}