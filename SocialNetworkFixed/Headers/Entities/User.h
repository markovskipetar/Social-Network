#pragma once
#include "MyString.h"
#include <vector>

class User
{
private:
	static unsigned globalUserId;

private:
	MyString username;
	MyString password;
	MyString firstName;
	MyString lastName;
	unsigned id;

	bool hasModeratorAccss;
	unsigned points;

	std::vector<int> votedCommentsIds;

	void setUsername(const MyString& username);

public:
	User();
	User(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName);

	const MyString& getUsername() const;
	unsigned getId() const;
	bool isModerator() const;

	void setPassword(const MyString& password);
	void setFirstName(const MyString& firstName);
	void setLastName(const MyString& lastName);
	void setModeratorAccess(const User* user, bool giveModeratorAcces);

	bool matchPassword(const MyString& passwordToMatch) const;

	bool hasVoted(unsigned commentId) const;
	void addVotedCommentId(unsigned commentId);

	void addPoint();
	void removePoints(unsigned points);

	void printPoints() const;
};

static void validateName(const MyString& name);
static bool isLowercase(char symbol);
static bool isUppercase(char symbol);
static bool isDigit(char symbol);
static bool isDotOrDashOrUnderscore(char symbol);

