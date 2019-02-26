#include "readInput.h"

void readVectorFromFile(std::vector<std::string> &temp) {
	std::ifstream infile;
	infile.open("../WordSource/10k_englishWords.txt");

	if (infile.fail()) {
		std::cout << "Could not open file numbers." << "\n";
		return;
	}

	std::string line;
	while (std::getline(infile, line)) {
		temp.push_back(line);
	}
	infile.close();
}

