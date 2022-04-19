//
// Created by mason on 2022/4/19.
//
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
int main() {
	std::ifstream in_file(
		"/Users/mason/Project/unix-programming/cmake-build-debug/test1.txt");
	if (!in_file) {
		std::cerr << "oops!unable to open input file" << std::endl;
		return EXIT_FAILURE;
	}

	std::ofstream out_file(
		"/Users/mason/Project/unix-programming/cmake-build-debug/test2.txt");
	if (!out_file) {
		std::cerr << "oops!unable to create file" << std::endl;
	}

	std::string word;
	std::vector<std::string> text;
	while (in_file >> word) {
		text.push_back(word);
	}

	int ix;
	std::cout << "unsorted text" << std::endl;
	for (ix = 0; ix < text.size(); ++ix) {
		std::cout << text[ix] << ' ';
	}
	std::cout << std::endl;

	std::sort(text.begin(), text.end());
	out_file << "sorted text:\n";
	for (ix = 0; ix < text.size(); ++ix) {
		out_file << text[ix] << ' ';
	}
	out_file << std::endl;

	return EXIT_SUCCESS;
}