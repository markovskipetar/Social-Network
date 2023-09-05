#pragma once
#include "../Entities/User.h"
#include "../ResultEnums/LoginResult.h"

class UsersRepository
{
public:
	static UsersRepository* getInstance();
	static void freeInstance();

public:
	void addUser(const User& user);
	User* find(int userId);
	int find(const char* username) const;
	const User* getLoggedUserConst() const;
	User* getLoggedUser();
	LoginResult logUser(const char* username, const char* password);
	void logOutUser();

private:
	static UsersRepository* instance;

	std::vector<User> users;
	int loggedUserIndex;

private:
	UsersRepository();
};

