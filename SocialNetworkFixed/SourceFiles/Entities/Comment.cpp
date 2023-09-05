#pragma once
#include "../../Headers/Entities/Comment.h"

Comment::Comment(unsigned authorId, const MyString& text)
	: IComment(authorId, text) {}

void Comment::addReply(const Reply& reply)
{
	replies.push_back(reply);
}

unsigned Comment::getRepliesCount() const
{
	return replies.size();
}

void Comment::printReplies() const
{
	unsigned repliesCount = replies.size();

	for (size_t i = 0; i < repliesCount; i++)
	{
		std::cout << "  |--> " << replies[i].getText() << " (" << replies[i].getVoteCount(VoteType::UpVote)
			<< " - " << replies[i].getVoteCount(VoteType::DownVote) << ") {id: " << replies[i].getId() << "}" << std::endl;
	}
}

Reply* Comment::findReply(unsigned replyId)
{
	unsigned repliesCount = replies.size();

	for (size_t i = 0; i < repliesCount; i++)
	{
		if (replies[i].getId() == replyId)
		{
			return &(replies[i]);
		}
	}

	return nullptr;
}

int Comment::findReplyIndex(unsigned replyId)
{
	unsigned repliesCount = replies.size();

	for (size_t index = 0; index < repliesCount; index++)
	{
		if (replies[index].getId() == replyId)
		{
			return index;
		}
	}

	return -1;
}

void Comment::free()
{
	removeAuthorPoints();

	unsigned repliesCount = replies.size();

	for (size_t i = 0; i < repliesCount; i++)
	{
		replies[i].free();
	}

	replies.clear();
}

Result Comment::removeReply(const User* loggedUser, int replyId)
{
	int replyIndex = findReplyIndex(replyId);

	if (replyIndex < 0)
	{
		return Result::IdNotFound;
	}

	const User* author = replies[replyIndex].getAuthorConst();

	if (author->isModerator() || author->getId() == loggedUser->getId())
	{
		replies[replyIndex].free();
		replies.erase(replies.begin() + replyIndex);
		return Result::Success;
	}

	return Result::NoPermission;
}

void Comment::write(std::ofstream& writer)
{
	for (size_t i = 0; i < replies.size(); i++)
	{
		writer << "------id: " << replies[i].getId() << " " << replies[i].getText() << std::endl;
	}
}
