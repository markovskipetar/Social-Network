#pragma once
#include "../../Headers/Commands/Search.h"

void Search::execute() const
{
	if (!GlobalFunctions::userLogged(usersRepository->getLoggedUserConst()))
	{
		return;
	}

	std::cout << "---------" << std::endl;

	std::cout << "Pattern: ";
	char pattern[64];
	std::cin.getline(pattern, 64);

	printMatches(pattern, themesRepository->getThemes());
}

void Search::printMatches(const char* pattern, const std::vector<Theme>& themes) const
{
	if (!pattern[0])
	{
		std::cout << "Pattern cannot be empty string!" << std::endl;
		return;
	}

	unsigned themesCount = themes.size();

	for (size_t i = 0; i < themesCount; i++)
	{
		if (isMatch(themes[i].getTitle(), pattern))
		{
			std::cout << themes[i].getTitle() << " {id: " << themes[i].getId() << "}" << std::endl;
		}
	}

	std::cout << std::endl;
}

bool Search::isMatch(const MyString& title, const char* pattern) const
{
	unsigned titleIndex = 0;
	unsigned patternIndex = 0;

	while (true)
	{
		if (!pattern[patternIndex])
		{
			return true;
		}

		if (!title[titleIndex])
		{
			return false;
		}

		if (title[titleIndex] == pattern[patternIndex])
		{
			patternIndex++;
		}
		else
		{
			patternIndex = 0;
		}

		titleIndex++;
	}
}