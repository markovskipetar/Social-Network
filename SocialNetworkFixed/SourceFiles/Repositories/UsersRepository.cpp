#include "../../Headers/Repositories/UsersRepository.h"

UsersRepository::UsersRepository() : loggedUserIndex(-1) {}

UsersRepository* UsersRepository::instance = nullptr;

UsersRepository* UsersRepository::getInstance()
{
	if (!instance)
	{
		instance = new UsersRepository();
	}

	return instance;
}

void UsersRepository::freeInstance()
{
	delete instance;
	instance = nullptr;
}

void UsersRepository::addUser(const User& user)
{
	users.push_back(user);
}

User* UsersRepository::find(int userId)
{
	if (userId < 0)
	{
		return nullptr;
	}

	unsigned usersCount = users.size();

	for (size_t i = 0; i < usersCount; i++)
	{
		if (users[i].getId() == userId)
		{
			return &users[i];
		}
	}

	return nullptr;
}

const User* UsersRepository::getLoggedUserConst() const
{
	return loggedUserIndex < 0 ? nullptr : &users[loggedUserIndex];
}

User* UsersRepository::getLoggedUser()
{
	return loggedUserIndex < 0 ? nullptr : &users[loggedUserIndex];
}

LoginResult UsersRepository::logUser(const char* username, const char* password)
{
	int userIndex = find(username);

	if (userIndex < 0)
	{
		return LoginResult::UsernameNotFound;
	}

	if (users[userIndex].matchPassword(password))
	{
		loggedUserIndex = userIndex;
		return LoginResult::Success;
	}

	return LoginResult::WrongPassword;
}

int UsersRepository::find(const char* username) const
{
	unsigned usersCount = users.size();

	for (size_t index = 0; index < usersCount; index++)
	{
		if (!strcmp(users[index].getUsername().c_str(), username))
		{
			return index;
		}
	}

	return -1;
}

void UsersRepository::logOutUser() 
{
	loggedUserIndex = -1;
}