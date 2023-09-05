#include "../../Headers/Commands/RemovePost.h"
#include <string>

void RemovePost::execute() const
{
	const User* loggedUser = usersRepository->getLoggedUserConst();
	Theme* openedTheme = themesRepository->getOpenedTheme();

	if (!GlobalFunctions::userLogged(loggedUser) ||
		!GlobalFunctions::openedTheme(openedTheme))
	{
		return;
	}

	Result removePostResult = Result::IdNotFound;

	if (!loggedUser->isModerator())
	{
		removePostResult = Result::NoPermission;
		writeResultMessageToConsole(removePostResult);

		return;
	}

	std::cout << "---------" << std::endl;

	std::cout << "Post Id: ";
	char idText[16];
	std::cin.getline(idText, 16);

	int postId = GlobalFunctions::ParseId(idText);

	if (postId >= 0)
	{
		removePostResult = openedTheme->removePost(postId);
	}

	writeResultMessageToConsole(removePostResult);
}

void RemovePost::writeResultMessageToConsole(Result removePostResult) const
{
	const char* resultMessage = "";

	switch (removePostResult)
	{
	case Result::Success: resultMessage = "Post was removed!";
		break;
	case Result::IdNotFound:resultMessage = "Post with such id does not exist in the current theme!";
		break;
	case Result::NoPermission:resultMessage = "You don not have permission to remove the post!";
		break;
	}

	std::cout << resultMessage << std::endl << std::endl;
}
