#pragma once
#include "../../Headers/Commands/PostCommand.h"

void PostCommand::execute() const
{
	const User* loggedUser = usersRepository->getLoggedUserConst();
	Theme* openedTheme = themesRepository->getOpenedTheme();

	if (!GlobalFunctions::userLogged(loggedUser) ||
		!GlobalFunctions::openedTheme(openedTheme))
	{
		return;
	}

	const Post* post = readPost(loggedUser->getId(), openedTheme);

	PostResult postResult = PostResult::PostExists;

	if (post)
	{
		openedTheme->addPost(*post);
		postResult = PostResult::Success;

		delete post;
	}

	writeResultMessageToConsole(postResult, openedTheme->getTitle());
}

const Post* PostCommand::readPost(unsigned creatorId, Theme* openedTheme) const
{
	std::cout << "---------" << std::endl;

	std::cout << "Title: ";
	char title[64];
	std::cin.getline(title, 64);

	if (openedTheme->findPostIndex(title)) // post with same title exists
	{
		return nullptr;
	}

	std::cout << "Content: ";
	char content[256];
	std::cin.getline(content, 256);

	return new Post(title, content, creatorId);
}

void PostCommand::writeResultMessageToConsole(PostResult postResult, const MyString& themeTitle) const
{
	if (postResult == PostResult::Success)
	{
		std::cout << "Post added successfully to \"" << themeTitle << "\"!" << std::endl << std::endl;
		return;
	}

	std::cout << "Post with the same title already exists!" << std::endl << std::endl;
}
