
#include <iostream>
#include <fstream>

int main() {

	std::ofstream potok("test.txt");

	/*for (size_t i = 0; i < 33333; i++) {
		potok << "k " << 3 * i + 2 << " ";
		potok << "k " << 3 * i << " ";
		potok << "k " << 3 * i + 1 << " ";
	}

	for (size_t i = 1; i < 10000; i++) {
		potok << "m " << 3 * i << " ";
		potok << "n " << 3 * i << " ";
	}*/

	for (size_t i = 1; i < 10000; i++) {
		potok << 3 * i - 1 << " ";
		potok << 3 * i << " ";
	}
	printf("Test created\n");
}