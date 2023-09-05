#pragma once
#include "../../Headers/Commands/RemoveComment.h"

#include <string>

void RemoveComment::execute() const
{
	const User* loggedUser = usersRepository->getLoggedUserConst();
	Theme* openedTheme = themesRepository->getOpenedTheme();

	if (!GlobalFunctions::userLogged(loggedUser) ||
		!GlobalFunctions::openedTheme(openedTheme) ||
		!GlobalFunctions::postOpened(openedTheme->getOpenedPostConst()))
	{
		return;
	}

	std::cout << "---------" << std::endl;

	std::cout << "Comment Id: ";
	char idText[16];
	std::cin.getline(idText, 16);

	int commentId = GlobalFunctions::ParseId(idText);

	Result removeCommentResult = Result::IdNotFound;

	if (commentId >= 0)
	{
		removeCommentResult = openedTheme->getOpenedPost()->removeComment(loggedUser, commentId);
	}

	writeResultMessageToConsole(removeCommentResult);
}

void RemoveComment::writeResultMessageToConsole(Result removeCommentResult) const
{
	const char* resultMessage = "";

	switch (removeCommentResult)
	{
	case Result::Success: resultMessage = "Comment was removed!";
		break;
	case Result::IdNotFound:resultMessage = "Comment with such id does not exist in the current post!";
		break;
	case Result::NoPermission:resultMessage = "You don not have permission to remove the comment!";
		break;
	}

	std::cout << resultMessage << std::endl << std::endl;
}
