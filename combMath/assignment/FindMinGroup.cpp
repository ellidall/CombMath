#include "FindMinGroup.h"

constexpr const int BEST_PERSON_ID_INITIAL_VALUE = -1;

void EraseUnnecessarySkills(Skills& requiredSkills, const Skills& personSkills)
{
	for (int skill : personSkills)
	{
		requiredSkills.erase(skill);
	}
}

People InitializePeople()
{
	return People{
		{ 10, { 1, 2 } },
		{ 1, { 2, 3 } },
		{ 2, { 3, 4 } },
		{ 3, { 4, 5 } },
		{ 4, { 5, 6 } },
	};
}

SkillsHashTable CreateSkillsHashTable(const People& people)
{
	SkillsHashTable skillToPerson;

	for (const auto person : people)
	{
		for (int skill : person.second)
		{
			skillToPerson[skill].push_back(person.first);
		}
	}

	return skillToPerson;
}

void FindPersonWithMaxSuitableSkillsNumber(const std::vector<int>& personIds,
	const People& people, const Skills& requiredSkills, int& maxCommonSkills, int& bestPersonId)
{
	for (int personId : personIds)
	{
		int commonSkills = 0;
		auto it = people.find(personId);
		if (it == people.end())
		{
			throw std::runtime_error("Error when executing the program");
		}
		const Skills& skills = it->second;
		for (const auto s : skills)
		{
			if (requiredSkills.find(s) != requiredSkills.end())
			{
				commonSkills++;
			}
		}
		if (commonSkills > maxCommonSkills)
		{
			maxCommonSkills = commonSkills;
			bestPersonId = personId;
		}
	}
}

Skills ReadSkills(const std::string& fileName)
{
	std::ifstream input(fileName);
	if (!input.is_open())
	{
		throw std::invalid_argument("Unable to open file " + fileName);
	}

	Skills skills;
	std::string line;
	while (std::getline(input, line))
	{
		std::istringstream iss(line);
		int num;
		while (iss >> num)
		{
			skills.insert(num);
		}
	}
	if (skills.empty())
	{
		throw std::invalid_argument("The skill set should not be empty");
	}

	return skills;
}

std::optional<std::vector<int>> FindMinGroup(Skills& requiredSkills, const People& people)
{
	SkillsHashTable skillToPerson = CreateSkillsHashTable(people);
	std::vector<int> subgroup;

	while (!requiredSkills.empty())
	{
		int bestPersonId = BEST_PERSON_ID_INITIAL_VALUE;
		int maxCommonSkills = 0;

		const auto skill = *requiredSkills.begin();
		if (skillToPerson.find(skill) == skillToPerson.end())
		{
			return std::nullopt;
		}

		FindPersonWithMaxSuitableSkillsNumber(skillToPerson[skill],
			people, requiredSkills, maxCommonSkills, bestPersonId);

		const auto bestPersonSkills = people.find(bestPersonId);
		if (bestPersonSkills == people.end())
		{
			throw std::runtime_error("Error when executing the program");
		}
		EraseUnnecessarySkills(requiredSkills, bestPersonSkills->second);
		subgroup.push_back(bestPersonId);
	}

	return subgroup;
}

void PrintMinGroup(const std::vector<int>& people)
{
	std::cout << "Min group (People): ";
	for (int person : people)
	{
		std::cout << person << " ";
	}
	std::cout << "\n";
}