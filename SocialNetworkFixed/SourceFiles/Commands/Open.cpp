#pragma once
#include "../../Headers/Commands/Open.h"
#include "../../Headers/ResultEnums/OpenResult.h"

void Open::execute() const
{
	if (!GlobalFunctions::userLogged(usersRepository->getLoggedUserConst()))
	{
		return;
	}

	std::cout << "---------" << std::endl;

	std::cout << "Title or id: ";
	char loadType[64];
	std::cin.getline(loadType, 64);

	int themeId = GlobalFunctions::ParseId(loadType);

	OpenResult openResult;

	if (themeId >= 0)
	{
		openResult = themesRepository->openTheme(themeId);
	}
	else
	{
		openResult = themesRepository->openTheme(loadType);
	}

	writeResultMessageToConsole(openResult);
}

void Open::writeResultMessageToConsole(OpenResult openResult) const
{
	const char* resultMessage = " ";

	switch (openResult)
	{
	case OpenResult::Success: std::cout << "Welcome to \"" << themesRepository->getOpenedThemeConst()->getTitle() << "\"" << std::endl << std::endl;
		return;
	case OpenResult::IdNotFound: resultMessage = "Theme with such id does not exist!"; 
		break;
	case OpenResult::TitleNotFound: "Theme with such title does not exist!"; 
		break;
	}

	std::cout << resultMessage << std::endl << std::endl;
}
