#pragma once
#include "Comment.h"
#include "../ResultEnums/VoteResult.h"
class Post
{
public:
	Post() = default;
	Post(const MyString& title, const MyString& content, unsigned creatorId);

	void addComment(const Comment& comment);
	Comment* findComment(int searchedId);

	const MyString& getTitle() const;
	unsigned getId() const;
	Comment* getComment(int id);

	void printPostInformation() const;
	void printDiscussion() const;

	VoteResult vote(unsigned commentId, VoteType voteType);
	Result removeComment(const User* loggedUser,int commentId);

	void removeComments();

	void write(std::ofstream& writer);

private:
	static unsigned postGlobalId;

private:
	unsigned id;
	MyString title;
	MyString content;
	unsigned creatorId;

	std::vector<Comment> comments;

	void setTitle(const MyString& title);
	void setContent(const MyString& content);
	unsigned getCommentsCount() const;

	int findCommentIndex(int searchedId);
	Result removeReply(const User* loggedUser, int replyId);
};

static bool isLowercase(char symbol);
static bool isUppercase(char symbol);
static bool isDigit(char symbol);
static bool isSymbolValid(char symbol);