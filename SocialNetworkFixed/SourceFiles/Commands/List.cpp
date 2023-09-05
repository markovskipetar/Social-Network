#pragma once
#include "../../Headers/Commands/List.h"

void List::execute() const
{
	const Theme* openedTheme = themesRepository->getOpenedThemeConst();

	if (!GlobalFunctions::userLogged(usersRepository->getLoggedUserConst()) ||
		!GlobalFunctions::openedTheme(openedTheme))
	{
		return;
	}

	std::cout << "---------" << std::endl;

	openedTheme->printPosts();

	std::cout << std::endl;

}