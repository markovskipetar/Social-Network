#pragma once
#include "Post.h"

class Theme
{
private:
	static unsigned themeGlobalId;

public:
	Theme() = default;
	Theme(const MyString& title, const MyString& description, unsigned creatorId);

public:
	void addPost(const Post& post);
	int findPostIndex(int searchedId);
	Post* findPostIndex(const char* postTitle);

	bool openPost(int id);
	void quitPost();

	unsigned getId() const;
	const MyString& getTitle() const;
	const Post* getOpenedPostConst() const;
	Post* getOpenedPost();

	void printPosts() const;

	Result removePost(int postId);
	void removePosts();

	void write(std::ofstream& writer);

private:
	unsigned id;
	MyString title;
	MyString description;
	unsigned creatorId;

	std::vector<Post> posts;
	int openedPostIndex;

private:
	void setTitle(const MyString& title);
	void setDescription(const MyString& title);
};

static bool isLowercase(char symbol);
static bool isUppercase(char symbol);
static bool isDigit(char symbol);
