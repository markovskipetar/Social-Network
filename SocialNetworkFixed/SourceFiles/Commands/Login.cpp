#pragma once
#include "../../Headers/Commands/Login.h"

void Login::execute() const
{
	if (usersRepository->getLoggedUserConst())
	{
		std::cout << "User is already logged!" << std::endl << std::endl;
		return;
	}

	std::cout << "---------" << std::endl;

	std::cout << "Username: ";
	char username[64];
	std::cin.getline(username, 64);

	std::cout << "Password: ";
	char password[64];
	std::cin.getline(password, 64);

	LoginResult loginResult = usersRepository->logUser(username, password);

	writeResultMessageToConsole(loginResult);
}

void Login::writeResultMessageToConsole(LoginResult loginResult) const
{
	const char* resultMessage = "";

	switch (loginResult)
	{
	case LoginResult::Success: resultMessage = "User logged successfully!"; break;
	case LoginResult::WrongPassword: resultMessage = "Wrong password!"; break;
	case LoginResult::UsernameNotFound: resultMessage = "Username does not exist!"; break;
	}

	std::cout << resultMessage << std::endl << std::endl;
}