#include "../../Headers/Commands/Quit.h"

void Quit::execute() const
{
	if (!GlobalFunctions::userLogged(usersRepository->getLoggedUserConst()) ||
		!GlobalFunctions::openedTheme(themesRepository->getOpenedThemeConst()))
	{
		return;
	}

	themesRepository->quitTheme();
}
