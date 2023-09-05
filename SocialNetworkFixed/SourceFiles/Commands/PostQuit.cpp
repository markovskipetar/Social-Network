#include "../../Headers/Commands/PostQuit.h"

void PostQuit::execute() const
{
	Theme* openedTheme = themesRepository->getOpenedTheme();

	if (!GlobalFunctions::userLogged(usersRepository->getLoggedUserConst()) ||
		!GlobalFunctions::openedTheme(openedTheme) ||
		!GlobalFunctions::postOpened(openedTheme->getOpenedPostConst()))
	{
		return;
	}

	openedTheme->quitPost();

	std::cout << "Post quietted!" << std::endl << std::endl;
}
