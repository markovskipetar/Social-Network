#pragma once
#include "../../Headers/Commands/Register.h"

void Register::execute() const
{
	if (usersRepository->getLoggedUserConst())
	{
		std::cout << "User is logged. Log out to register new user!" << std::endl << std::endl;
		return;
	}

	const User* user = readUser();
	RegisterResult registerResult = RegisterResult::UsernameExists;

	if (user)
	{
		usersRepository->addUser(*user);
		registerResult = RegisterResult::Success;

		delete user;
	}

	writeResultMessageToConsole(registerResult);
}

const User* Register::readUser() const
{
	std::cout << "---------" << std::endl;

	std::cout << "Username: ";
	char username[64];
	std::cin.getline(username, 64);

	if (usersRepository->find(username) >= 0)
	{
		// check if username exists, otherwise new user with 
		// exisintg username will be created with with valid id

		return nullptr;
	}

	std::cout << "Password: ";
	char password[64];
	std::cin.getline(password, 64);

	std::cout << "First name: ";
	char firstName[64];
	std::cin.getline(firstName, 64);

	std::cout << "Last name: ";
	char lastName[64];
	std::cin.getline(lastName, 64);

	return new User(username, password, firstName, lastName);
}

void Register::writeResultMessageToConsole(RegisterResult registerResult) const
{
	const char* resultMessage = "";

	switch (registerResult)
	{
	case RegisterResult::Success: resultMessage = "User registered successfully!";
		break;
	case RegisterResult::UsernameExists: resultMessage = "Username already exsits!";
		break;
	}

	std::cout << resultMessage << std::endl << std::endl;
}
