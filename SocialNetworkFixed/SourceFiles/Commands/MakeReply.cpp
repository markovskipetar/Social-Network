#pragma once
#include "../../Headers/Commands/MakeReply.h"

void MakeReply::execute() const
{
	const User* loggedUser = usersRepository->getLoggedUserConst();
	Theme* openedTheme = themesRepository->getOpenedTheme();

	if (!GlobalFunctions::userLogged(loggedUser) ||
		!GlobalFunctions::openedTheme(openedTheme) ||
		!GlobalFunctions::postOpened(openedTheme->getOpenedPostConst()))
	{
		return;
	}

	std::cout << "---------" << std::endl;

	std::cout << "Comment Id: ";
	char idText[16];
	std::cin.getline(idText, 16);

	int commentId = GlobalFunctions::ParseId(idText);

	Result replyResult = Result::IdNotFound;

	if (commentId >= 0)
	{
		Comment* comment = openedTheme->getOpenedPost()->findComment(commentId);

		if (comment)
		{
			replyToComment(comment, loggedUser->getId());
			replyResult = Result::Success;
		}
	}

	writeResultMessageToConsole(replyResult);
}

void MakeReply::replyToComment(Comment* comment, unsigned authorId) const
{
	std::cout << "Reply text: ";
	char text[1024];
	std::cin.getline(text, 1024);

	Reply replay(authorId, text);

	comment->addReply(replay);
}

void MakeReply::writeResultMessageToConsole(Result replyResult) const
{
	const char* replyResultText = "";
	switch (replyResult)
	{
	case Result::Success: replyResultText = "Reply was added successfully!";
		break;
	case Result::IdNotFound: replyResultText = "Comment with such id does not exist!";
		break;
	}

	std::cout << replyResultText << std::endl << std::endl;
}
