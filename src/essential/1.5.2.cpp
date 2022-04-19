/**
 * c 风格字符串
 * Created by mason on 2022/4/19.
 */

#include <cstring>
#include <iomanip>
#include <iostream>
int main() {
	const int nm_size = 128;
	char input[nm_size];
	std::cout << "please input something" << std::endl;
	std::cin >> std::setw(nm_size) >> input;
	if (strlen(input) < 2) {
		std::cout << "invalid info" << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "you input: " << input << std::endl;

	return EXIT_SUCCESS;
}