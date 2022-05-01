//
// Created by mason on 2022/4/21.
//

#include <iostream>
#include <vector>
const std::vector<int>* fibon_seq(int size) {
	const int max_size = 1024;

	if (size <= 0 || size > max_size) {
		std::cerr << "error param" << std::endl;
		return 0;
	}

	static std::vector<int> elems;
	for (int index = elems.size(); index < size; ++index) {
		if (index == 0 || index == 1) {
			elems.push_back(1);
		} else {
			elems.push_back(elems[index - 1] + elems[index - 2]);
		}
	}

	return &elems;
}

int main() {
	const std::vector<int>* one = fibon_seq(10);

	const std::vector<int>* two = fibon_seq(25);

	return EXIT_SUCCESS;
}