#pragma once
#include "../../Headers/Commands/AddComment.h"

void AddComment::execute() const
{
	const User* loggedUser = usersRepository->getLoggedUserConst();
	Theme* loadedTheme = themesRepository->getInstance()->getOpenedTheme();

	if (!GlobalFunctions::userLogged(loggedUser) ||
		!GlobalFunctions::openedTheme(loadedTheme) ||
		!GlobalFunctions::postOpened(loadedTheme->getOpenedPost()))
	{
		return;
	}

	std::cout << "---------" << std::endl;

	std::cout << "Comment text: ";
	char text[1024];
	std::cin.getline(text, 1024);

	Comment comment(loggedUser->getId(), text);

	loadedTheme->getOpenedPost()->addComment(comment);

	std::cout << "Comment added successfully!" << std::endl << std::endl;
}
