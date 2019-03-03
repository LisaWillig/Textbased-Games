#include "highScoreFile.h"

void readScoreFromFile(std::vector<std::string> &temp) {
	std::ifstream infile;
	infile.open("../highScore.txt");

	if (infile.fail()) {
		std::ofstream file;
		file.open("../highScore.txt");
		file << "#Playername\t Number of letteres\t Score(Number of tries)\nTest\t 3\t 20\n";
		file.close();
		return;
	}

	std::string line;
	while (std::getline(infile, line)) {
		if (line[0] != '#') {
			temp.push_back(line);
		}
	}

	infile.close();
}


int readScore(int nbLetters) {
	std::vector<std::string> myScore;
	readScoreFromFile(myScore);
	int i = 0;
	while (i < myScore.size()) {
		std::cout << myScore[i] << " ";
		i++;
	}
	return 0;
}