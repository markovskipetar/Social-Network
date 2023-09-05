#pragma once
#include "../../Headers/Entities/Theme.h"

unsigned Theme::themeGlobalId = 0;

Theme::Theme(const MyString& title, const MyString& description, unsigned creatorId)
	:creatorId(creatorId)
{
	setTitle(title);
	setDescription(description);

	openedPostIndex = -1;

	id = themeGlobalId++;
}

void Theme::setTitle(const MyString& title)
{
	if (title.length() < 3)
	{
		throw std::invalid_argument("Title must be at least 3 symbols!");
	}

	bool hasAtLeastOneLetter = false;

	for (size_t i = 0; title[i]; i++)
	{
		if (!isLowercase(title[i]) && !isUppercase(title[i]) && !isDigit(title[i]) && !(title[i] == ' '))
		{
			throw std::invalid_argument("Title must contain only letters, digits and space!");
		}

		if ((isLowercase(title[i]) || isUppercase(title[i])) && !hasAtLeastOneLetter)
		{
			hasAtLeastOneLetter = true;
		}
	}

	if (!hasAtLeastOneLetter)
	{
		throw std::invalid_argument("Title must contain at least one letter!");
	}

	this->title = title;
}

void Theme::setDescription(const MyString& description)
{
	if (description.length() < 10)
	{
		throw std::invalid_argument("Description must be at least 10 symbols!");
	}

	this->description = description;
}

int Theme::findPostIndex(int searchedId)
{
	if (searchedId < 0)
	{
		return -1;
	}

	unsigned postsCount = posts.size();

	for (size_t index = 0; index < postsCount; index++)
	{
		if (posts[index].getId() == searchedId)
		{
			return index;
		}
	}

	return -1;
}

Post* Theme::findPostIndex(const char* postTitle)
{
	unsigned postsCount = posts.size();

	for (size_t index = 0; index < postsCount; index++)
	{
		if (!strcmp(posts[index].getTitle().c_str(), postTitle))
		{
			return &posts[index];
		}
	}

	return nullptr;
}

void Theme::addPost(const Post& post)
{
	posts.push_back(post);
}

bool Theme::openPost(int postId)
{
	int postIndex = findPostIndex(postId);

	if (postIndex >= 0)
	{
		openedPostIndex = postIndex;
		posts[postIndex].printPostInformation();

		return true;
	}

	return false;
}

const MyString& Theme::getTitle() const
{
	return title;
}

unsigned Theme::getId() const
{
	return id;
}

const Post* Theme::getOpenedPostConst() const
{
	if (openedPostIndex < 0)
	{
		return nullptr;
	}

	return &(posts[openedPostIndex]);
}

Result Theme::removePost(int postId)
{
	int postToRemoveIndex = (postId == posts[openedPostIndex].getId()) ? openedPostIndex : findPostIndex(postId);

	if (postToRemoveIndex < 0)
	{
		return Result::IdNotFound;
	}

	posts[postToRemoveIndex].removeComments();
	posts.erase(posts.begin() + postToRemoveIndex);

	if (postToRemoveIndex == openedPostIndex)
	{
		quitPost();
	}
	else if (postId < openedPostIndex)
	{
		openedPostIndex--;
	}

	return Result::Success;
}

void Theme::removePosts()
{
	for (size_t i = 0; i < posts.size(); i++)
	{
		posts[i].removeComments();
	}

	posts.clear();
}

void Theme::write(std::ofstream& writer)
{
	for (size_t i = 0; i < posts.size(); i++)
	{
		writer << "--id: " << posts[i].getId() << " " << posts[i].getTitle() << std::endl;

		posts[i].write(writer);
	}
}

Post* Theme::getOpenedPost()
{
	if (openedPostIndex < 0)
	{
		return nullptr;
	}

	return &(posts[openedPostIndex]);
}

void Theme::quitPost()
{
	openedPostIndex = -1;
}

void Theme::printPosts() const
{
	unsigned postsCount = posts.size();

	for (size_t i = 0; i < postsCount; i++)
	{
		std::cout << posts[i].getTitle() << " {id: " << posts[i].getId() << "}" << std::endl;
	}
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