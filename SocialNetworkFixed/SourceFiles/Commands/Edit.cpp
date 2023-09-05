#pragma once
#include "../../Headers/Commands/Edit.h"

void Edit::execute() const
{
	User* loggedUser = usersRepository->getLoggedUser();

	if (!GlobalFunctions::userLogged(loggedUser))
	{
		return;
	}

	std::cout << "EDIT:" << std::endl;
	std::cout << "----" << std::endl;

	std::cout << "(Press ENTER for NOT editing the field)" << std::endl;

	std::cout << "New first name: ";
	char newFirstName[64];
	std::cin.getline(newFirstName, 64);

	if (newFirstName[0])
	{
		loggedUser->setFirstName(newFirstName);
	}

	std::cout << "New last name: ";
	char newLastName[64];
	std::cin.getline(newLastName, 64);

	if (newLastName[0])
	{
		loggedUser->setLastName(newLastName);
	}

	std::cout << "New password: ";
	char newPassword[64];
	std::cin.getline(newPassword, 64);

	if (newPassword[0])
	{
		loggedUser->setPassword(newPassword);
	}

	std::cout << "Account was edited!" << std::endl << std::endl;
}