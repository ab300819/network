//
// Created by mason on 2022/4/21.
//

#include <iostream>
#include <vector>

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

int main() {
	std::vector<int> num_list = {2, 4, 1, 3, 5, 8, 6, 9};
	for (int i = 0; i < num_list.size(); ++i) {
		for (int j = 0; j < num_list.size(); ++j) {
			if (num_list[i] < num_list[j]) {
				swap(num_list[i], num_list[j]);
			}
		}
	}

	for (int i = 0; i < num_list.size(); ++i) {
		std::cout << num_list[i] << std::endl;
	}

	return EXIT_SUCCESS;
}