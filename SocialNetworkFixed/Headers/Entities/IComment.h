#pragma once
#include "../Repositories/UsersRepository.h"

enum class VoteType
{
	UpVote,
	DownVote
};

class IComment
{
private:
	static unsigned globalCommentId;

public:
	IComment() = default;
	IComment(unsigned authorId, const MyString& text);

	const MyString& getText() const;
	unsigned getId() const;

	void vote(VoteType voteType);
	unsigned getVoteCount(VoteType voteType) const;

	const User* getAuthorConst() const;

protected:
	void removeAuthorPoints();
	User* getAuthor() const;

private:
	unsigned id;

	unsigned authorId;
	MyString text;

	unsigned upvotes;
	unsigned downvotes;

	UsersRepository* usersRepository;

private:
	void setText(const MyString& text);
};

