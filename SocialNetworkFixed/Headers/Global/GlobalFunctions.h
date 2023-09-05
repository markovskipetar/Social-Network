#pragma once
#include "../Global/GlobalFunctions.h"
#include "../Entities/Theme.h"
#include <string>

class GlobalFunctions
{
public:
	static bool userLogged(const User* user)
	{
		if (!user)
		{
			std::cout << "No user is logged!" << std::endl << std::endl;
			return false;
		}

		return true;
	}

	static bool openedTheme(const Theme* theme)
	{
		if (!theme)
		{
			std::cout << "No theme is loaded!" << std::endl << std::endl;
			return false;
		}

		return true;
	}

	static bool postOpened(const Post* post)
	{
		if (!post)
		{
			std::cout << "No post is opened!" << std::endl << std::endl;
			return false;
		}

		return true;
	}

	static int ParseId(const char* idText)
	{
		int id;
		size_t processedCharacters;

		try
		{
			id = std::stoi(idText, &processedCharacters);
		}
		catch (const std::invalid_argument&)
		{
			return -1;
		}

		if (idText[processedCharacters])
		{
			return -1;
		}

		return id;
	}
};

