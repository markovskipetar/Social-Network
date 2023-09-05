#pragma once
#include "../../Headers/Entities/User.h"

unsigned User::globalUserId = 0;

User::User() : hasModeratorAccss(false) {};

User::User(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName)
	: hasModeratorAccss(false), points(0)
{
	setUsername(username);
	setPassword(password);
	setFirstName(firstName);
	setLastName(lastName);

	id = globalUserId++;
}

// validation needed!
void User::setUsername(const MyString& username)
{
	if (username.length() < 3)
	{
		throw std::invalid_argument("Username must be at least 3 symbols!");
	}

	bool hasAtLeastOneLowercas = false;

	for (size_t i = 0; username[i]; i++)
	{
		if (!isLowercase(username[i]) && !isDigit(username[i]) && !isDotOrDashOrUnderscore(username[i]))
		{
			throw std::invalid_argument("Username must contain only lowercase letters, digits, dot, dash and underscore!");
		}

		if (isLowercase(username[i]) && !hasAtLeastOneLowercas)
		{
			hasAtLeastOneLowercas = true;
		}
	}

	if (!hasAtLeastOneLowercas)
	{
		throw std::invalid_argument("Username must contain at least one lowercase letter!");
	}

	this->username = username;
}

void User::setPassword(const MyString& password)
{
	if (password.length() < 4)
	{
		throw std::invalid_argument("Password must be at least 4 symbols!");
	}

	this->password = password;
}

void User::setFirstName(const MyString& firstName)
{
	validateName(firstName);

	this->firstName = firstName;
}
void  User::setLastName(const MyString& lastName)
{
	validateName(lastName);

	this->lastName = lastName;
}

void validateName(const MyString& name)
{
	if (name.length() < 2)
	{
		throw std::invalid_argument("First/Last name must be at least 2 symbols!");
	}

	for (size_t i = 0; name[i]; i++)
	{
		if (!isLowercase(name[i]) && !isUppercase(name[i]))
		{
			throw std::invalid_argument("Username must contain only letters!");
		}
	}
}

const MyString& User::getUsername() const
{
	return username;
}

unsigned User::getId() const
{
	return id;
}

bool User::isModerator() const
{
	return hasModeratorAccss || !id;
}

void User::setModeratorAccess(const User* user, bool accessValue)
{
	if (user->isModerator())
	{
		hasModeratorAccss = accessValue;
	}
	else
	{
		throw std::invalid_argument("Prohibited access!");
	}
}

bool User::matchPassword(const MyString& passwordToMatch) const
{
	return !strcmp(password.c_str(), passwordToMatch.c_str());
}

bool User::hasVoted(unsigned commentId) const
{
	unsigned votedCommentsIdsCount = votedCommentsIds.size();

	for (size_t i = 0; i < votedCommentsIdsCount; i++)
	{
		if (votedCommentsIds[i] == commentId)
		{
			return true;
		}
	}

	return false;
}

void User::addVotedCommentId(unsigned commentId)
{
	votedCommentsIds.push_back(commentId);
}

void User::addPoint()
{
	points++;
}

void User::removePoints(unsigned points)
{
	this->points -= points;
}

void User::printPoints() const
{
	std::cout << points << std::endl;
}

bool isUppercase(char symbol)
{
	return 'A' <= symbol && symbol <= 'Z';
}

bool isLowercase(char symbol)
{
	return 'a' <= symbol && symbol <= 'z';
}

bool isDigit(char symbol)
{
	return '0' <= symbol && symbol <= '9';
}

bool isDotOrDashOrUnderscore(char symbol)
{
	return symbol == '.' || symbol == '-' || symbol == '_';
}