#include "FindMinGroup.h"
#define BOOST_TIMER_ENABLE_DEPRECATED
#include <boost/timer.hpp>

struct Args
{
	std::string inputSkillSet;
};

 Args ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument("Invalid argument count\nUsage: assignment.exe <inputSkillSetFile>");
	}

	Args args;
	args.inputSkillSet = argv[1];

	return args;
}

int main(int argc, char* argv[])
{
	boost::timer t;
	t.restart();

	try
	{
		Args args = ParseArgs(argc, argv);
		Skills requiredSkills = ReadSkills(args.inputSkillSet);
		auto subgroup = FindMinGroup(requiredSkills, InitializePeople());
		if (subgroup.has_value())
		{
			PrintMinGroup(subgroup.value());
		}
		else
		{
			std::cout << "Minimum group cannot be made up: people's skills are not suitable\n";
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "Program execution time: " << t.elapsed() << "\n";
	return EXIT_SUCCESS;
}