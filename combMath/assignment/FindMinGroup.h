#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <optional>

using Skills = std::unordered_set<int>;
using SkillsHashTable = std::unordered_map<int, std::vector<int>>;
using People = std::unordered_map<int, Skills>;

People InitializePeople();
SkillsHashTable CreateSkillsHashTable(const People& people);
Skills ReadSkills(const std::string& fileName);
std::optional<std::vector<int>> FindMinGroup(Skills& requiredSkills, const People& people);
void PrintMinGroup(const std::vector<int>& people);