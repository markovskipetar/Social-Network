#pragma once
#include "../../Headers/Commands/Create.h"

void Create::execute() const
{
	std::cout << "---------" << std::endl;

	const User* user = usersRepository->getLoggedUserConst();

	if (!GlobalFunctions::userLogged(user))
	{
		return;
	}

	const Theme* theme = readTheme(user->getId());

	if (theme)
	{
		themesRepository->addTheme(*theme);
		delete theme;
	}

	std::cout << "Theme added successfully!" << std::endl << std::endl;
}

const Theme* Create::readTheme(unsigned creatorId) const
{
	try
	{
		std::cout << "Title: ";
		char title[64];
		std::cin.getline(title, 64);

		std::cout << "Description: ";
		char description[256];
		std::cin.getline(description, 256);

		// if a theme already exists, nothing will happen (redirecting to existing theme)
		if (themesRepository->find(title))
		{
			return nullptr;
		}

		return new Theme(title, description, creatorId);
	}
	catch (const std::invalid_argument& exception)
	{
		std::cout << exception.what() << std::endl;
		return nullptr;
	}
}
