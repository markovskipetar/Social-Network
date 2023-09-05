#include "../../Headers/Entities/IComment.h"

unsigned IComment::globalCommentId = 0;

IComment::IComment(unsigned authorId, const MyString& text)
	: upvotes(0), downvotes(0), authorId(authorId)
{
	setText(text);

	usersRepository = UsersRepository::getInstance();

	id = globalCommentId++;
}

const MyString& IComment::getText() const
{
	return text;
}

unsigned IComment::getId() const
{
	return id;
}

void IComment::vote(VoteType voteType)
{
	switch (voteType)
	{
	case VoteType::UpVote: upvotes++; break;
	case VoteType::DownVote: downvotes++; break;
	}

	usersRepository->find(authorId)->addPoint();
}

unsigned IComment::getVoteCount(VoteType voteType) const
{
	if (voteType == VoteType::UpVote)
	{
		return upvotes;
	}

	return downvotes;
}

void IComment::removeAuthorPoints()
{
	getAuthor()->removePoints(upvotes + downvotes);
}

User* IComment::getAuthor() const
{
	return usersRepository->find(authorId);
}

const User* IComment::getAuthorConst() const
{
	return usersRepository->find(authorId);
}

void IComment::setText(const MyString& text)
{
	if (text.length() < 1)
	{
		throw std::invalid_argument("Comment length must be at least 1 symbol!");
	}

	this->text = text;
}
