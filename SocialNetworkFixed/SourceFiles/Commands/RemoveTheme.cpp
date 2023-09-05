#include "../../Headers/Commands/RemoveTheme.h"

#include <string>

void RemoveTheme::execute() const
{
	const User* loggedUser = usersRepository->getLoggedUserConst();

	if (!GlobalFunctions::userLogged(loggedUser))
	{
		return;
	}

	Result removeThemeResult = Result::IdNotFound;

	if (!loggedUser->isModerator())
	{
		removeThemeResult = Result::NoPermission;
		writeResultMessageToConsole(removeThemeResult);

		return;
	}

	std::cout << "---------" << std::endl;

	std::cout << "Theme Id: ";
	char idText[16];
	std::cin.getline(idText, 16);

	int themeId = GlobalFunctions::ParseId(idText);

	if (themeId >= 0)
	{
		int themeIndex = themesRepository->findThemeIndex(themeId);

		if (themeIndex >= 0)
		{
			removeThemeResult = themesRepository->removeTheme(themeId);
		}
	}

	writeResultMessageToConsole(removeThemeResult);
}

void RemoveTheme::writeResultMessageToConsole(Result removeThemeResult) const
{
	const char* resultMessage = "";

	switch (removeThemeResult)
	{
	case Result::Success: resultMessage = "Theme was removed!";
		break;
	case Result::IdNotFound:resultMessage = "Theme with such id does not exist!";
		break;
	case Result::NoPermission:resultMessage = "You do not have permission to remove themes!";
		break;
	}

	std::cout << resultMessage << std::endl << std::endl;
}