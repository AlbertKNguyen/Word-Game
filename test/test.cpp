#include <igloo/igloo.h>
#include <game.h>

using namespace igloo;

game::Game gameTest;

std::vector<std::string> solution1;
std::vector<std::string> solution2;

bool containsOneNineLetterWord(std::vector<std::string> solution) {
	for (int i = 0; i < solution.size(); i++) {
		if (solution[i].size() == 9) {
			return true;
		}
	}
	return false;
}

bool doesNotContainTenLetterWord(std::vector<std::string> solution) {
	for (int i = 0; i < solution.size(); i++) {
		if (solution[i].size() >= 10) {
			return false;
		}
	}
	return true;
}

bool isDifferentSolution(std::vector<std::string> solution1, std::vector<std::string> solution2) {
	if (solution1.size() != solution2.size()) {
		return true;
	} else {
		for (int i = 0; i < solution1.size(); i++) {
			if (solution1[i] != solution2[i]) {
				return true;
			}
		}
	}
	return false;
}


Context(FunctionsOnEmptyGame) {
	Spec(CheckWord) {
		Assert::That(gameTest.check("A") && gameTest.check("E") && gameTest.check("U") && 
					 gameTest.check("O") && gameTest.check("I"), Equals(false));
	};

	Spec(HighscoreIsZero) {
		Assert::That(gameTest.getHighscore(), Equals(0));
	};
};

Context(NewGame) {
	Spec(NineLetterWordContainsVowel) {
		gameTest.generateList();
		Assert::That(gameTest.check("A") || gameTest.check("E") || gameTest.check("U") || 
					 gameTest.check("O") || gameTest.check("I"), Equals(true));
	};

	Spec(SolutionSizeIsWithinExpected) {
		std::vector<std::string> solution = gameTest.getSolution();
		solution1 = solution;
		Assert::That(solution.size() > 10 && solution.size() < 2000, Equals(true));
	};

	Spec(SolutionContainsOne9LetterWord) {
		std::vector<std::string> solution = gameTest.getSolution();
		Assert::That(containsOneNineLetterWord(solution), Equals(true));
	};

	Spec(SolutionDoesNotContain10LetterWord) {
		std::vector<std::string> solution = gameTest.getSolution();
		Assert::That(doesNotContainTenLetterWord(solution), Equals(true));
	};
};

Context(AnotherGame) {
	Spec(NineLetterWordContainsVowel) {
		gameTest.generateList();
		Assert::That(gameTest.check("A") || gameTest.check("E") || gameTest.check("U") || 
					 gameTest.check("O") || gameTest.check("I"), Equals(true));
	};

	Spec(SolutionSizeIsWithinExpected) {
		std::vector<std::string> solution = gameTest.getSolution();
		solution2 = solution;
		Assert::That(solution.size() > 10 && solution.size() < 2000, Equals(true));
	};

	Spec(SolutionContainsOne9LetterWord) {
		std::vector<std::string> solution = gameTest.getSolution();
		Assert::That(containsOneNineLetterWord(solution), Equals(true));
	};

	Spec(SolutionDoesNotContain10LetterWord) {
		std::vector<std::string> solution = gameTest.getSolution();
		Assert::That(doesNotContainTenLetterWord(solution), Equals(true));
	};

	Spec(SolutionDifferentFromPrevGame) {
		std::vector<std::string> solution = gameTest.getSolution();
		Assert::That(isDifferentSolution(solution, solution1), Equals(true));
	};
};

Context(AnotherAnotherGame) {
	Spec(NineLetterWordContainsVowel) {
		gameTest.generateList();
		Assert::That(gameTest.check("A") || gameTest.check("E") || gameTest.check("U") || 
					 gameTest.check("O") || gameTest.check("I"), Equals(true));
	};

	Spec(SolutionSizeIsWithinExpected) {
		std::vector<std::string> solution = gameTest.getSolution();
		Assert::That(solution.size() > 10 && solution.size() < 2000, Equals(true));
	};

	Spec(SolutionContainsOne9LetterWord) {
		std::vector<std::string> solution = gameTest.getSolution();
		Assert::That(containsOneNineLetterWord(solution), Equals(true));
	};

	Spec(SolutionDoesNotContain10LetterWord) {
		std::vector<std::string> solution = gameTest.getSolution();
		Assert::That(doesNotContainTenLetterWord(solution), Equals(true));
	};

	Spec(SolutionDifferentFromPrevGame) {
		std::vector<std::string> solution = gameTest.getSolution();
		Assert::That(isDifferentSolution(solution, solution2), Equals(true));
	};

	Spec(SolutionDifferentFromPrevPrevGame) {
		std::vector<std::string> solution = gameTest.getSolution();
		Assert::That(isDifferentSolution(solution, solution1), Equals(true));
	};
};

Context(SetAndGetHighscore) {
	Spec(SetAndGetHighscoreTo1) {
		gameTest.setHighscore(1);
		Assert::That(gameTest.getHighscore(), Equals(1));
	};
	
	Spec(SetAndGetHighscoreTo99999) {
		gameTest.setHighscore(99999);
		Assert::That(gameTest.getHighscore(), Equals(99999));
	};

	Spec(SetAndGetHighscoreTo10000000) {
		gameTest.setHighscore(10000000);
		Assert::That(gameTest.getHighscore(), Equals(10000000));
	};
};


int main() {
	// Run all the tests defined above
	return TestRunner::RunAllTests();
}
