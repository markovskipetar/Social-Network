#pragma once
#include "../../Headers/Commands/PostOpen.h"

void PostOpen::execute() const
{
	Theme* openedTheme = themesRepository->getOpenedTheme();

	if (!GlobalFunctions::userLogged(usersRepository->getLoggedUserConst()) ||
		!GlobalFunctions::openedTheme(openedTheme))
	{
		return;
	}

	std::cout << "---------" << std::endl;

	std::cout << "Id: ";
	char idText[16];
	std::cin.getline(idText, 16);

	int postId = GlobalFunctions::ParseId(idText);

	if (postId < 0 || !openedTheme->openPost(postId))
	{
		std::cout << "Post with such id does not exist!" << std::endl << std::endl;
	}
}