#pragma once
#include "../../Headers/Commands/EditId.h"

void EditId::execute() const
{
	const User* loggedUser = usersRepository->getLoggedUserConst();

	if (!GlobalFunctions::userLogged(loggedUser))
	{
		return;
	}

	if (!loggedUser->isModerator())
	{
		std::cout << "You dont have permission to edit other users!" << std::endl << std::endl;
		return;
	}

	std::cout << "-------" << std::endl;
	std::cout << "Id to edit: ";

	char idText[16];
	std::cin.getline(idText, 16);

	int userToEditId = GlobalFunctions::ParseId(idText);

	User* userToEdit = usersRepository->find(userToEditId);

	if (!userToEdit)
	{
		std::cout << "No user with such id exists!" << std::endl << std::endl;
		return;
	}

	std::cout << "(Press ENTER for NOT editing the field)" << std::endl;

	std::cout << "New first name: ";
	char newFirstName[64];
	std::cin.getline(newFirstName, 64);

	if (newFirstName[0])
	{
		userToEdit->setFirstName(newFirstName);
	}

	std::cout << "New last name: ";
	char newLastName[64];
	std::cin.getline(newLastName, 64);

	if (newLastName[0])
	{
		userToEdit->setLastName(newLastName);
	}

	std::cout << "New password: ";
	char newPassword[64];
	std::cin.getline(newPassword, 64);

	if (newPassword[0])
	{
		userToEdit->setPassword(newPassword);
	}

	std::cout << "Moderator access. Give-True/Take-False ";
	bool accessValue;
	std::cin >> std::boolalpha >> accessValue;
	std::cin.ignore();

	userToEdit->setModeratorAccess(loggedUser, accessValue);

	std::cout << "User with id: " << userToEdit->getId() << " was edited!" << std::endl << std::endl;
}