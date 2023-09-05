#pragma once
#include "../../Headers/Commands/Logout.h"

void Logout::execute() const
{
	if (GlobalFunctions::userLogged(usersRepository->getLoggedUserConst()))
	{
		usersRepository->logOutUser();

		std::cout << "User logged out!" << std::endl << std::endl;
	}
}