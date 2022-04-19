/**
 * c++ 风格字符串
 * Created by mason on 2022/4/17.
 */
#include <iostream>
#include <string>

int main() {
	std::string input;
	std::cout << "please input something" << std::endl;
	std::cin >> input;
	if (input.size() < 2) {
		std::cout << "invalid info" << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "you input: " << input << std::endl;

	return EXIT_SUCCESS;
}