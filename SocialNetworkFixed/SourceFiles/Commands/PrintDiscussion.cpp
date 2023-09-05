#include "../../Headers/Commands/PrintDiscussion.h"

void PrintDiscussion::execute() const
{
	const User* loggedUser = usersRepository->getLoggedUserConst();
	const Theme* openedTheme = themesRepository->getOpenedThemeConst();

	if (!GlobalFunctions::userLogged(loggedUser) ||
		!GlobalFunctions::openedTheme(openedTheme) ||
		!GlobalFunctions::postOpened(openedTheme->getOpenedPostConst()))
	{
		return;
	}

	std::cout << "---------" << std::endl;

	openedTheme->getOpenedPostConst()->printDiscussion();
	loggedUser->printPoints();
}
