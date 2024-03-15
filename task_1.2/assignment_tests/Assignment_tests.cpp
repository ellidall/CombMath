#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../Assignment/FindMinGroup.h"

using namespace std;

SCENARIO("FindMinGroup")
{
	WHEN("Ñorrect input data")
	{
		Skills requiredSkills = {3, 4, 6};
		const People people = InitializePeople();
		std::vector<int> expectedVector = { 2, 4 };

		THEN("Ñorrect execution of the program")
		{
			auto subgroup = FindMinGroup(requiredSkills, InitializePeople());
			std::vector<int> vector = subgroup.value();
			REQUIRE(vector == expectedVector);
		}
	}
}

SCENARIO("ReadSkills")
{
	WHEN("Empty input")
	{
		const std::string inputFileName = "skills_empty.txt";

		THEN("Error in qutput")
		{
			REQUIRE_THROWS_AS(ReadSkills(inputFileName), invalid_argument);
		}
	}
}