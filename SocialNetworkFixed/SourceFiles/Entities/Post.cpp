#pragma once
#include "../../Headers/Entities/Post.h"
#include "../../Headers/ResultEnums/VoteResult.h"

unsigned Post::postGlobalId = 0;

Post::Post(const MyString& title, const MyString& content, unsigned creatorId)
	: creatorId(creatorId)
{
	setTitle(title);
	setContent(content);

	id = postGlobalId++;
}

const MyString& Post::getTitle() const
{
	return title;
}

unsigned Post::getId() const
{
	return id;
}

Comment* Post::getComment(int id)
{
	// invoke find + return nullptr if needed

	return &(comments[id]);
}

void Post::setTitle(const MyString& title)
{
	if (title.length() < 3)
	{
		throw std::invalid_argument("Title must be at least 3 symbols!");
	}

	this->title = title;

	//CUSTOM VALIDATION
	/*bool hasAtLeastOneLetter = false;

	for (size_t i = 0; title[i]; i++)
	{
		if (!isSymbolValid(title[i]))
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
	}*/
}

void Post::printPostInformation() const
{
	std::cout << "[Creator Id: " << creatorId << "]" << std::endl;
	std::cout << "Ttile: " << title << std::endl;
	std::cout << "Content: " << content << std::endl;
	std::cout << "Comments: " << getCommentsCount() << std::endl << std::endl;
}

void Post::printDiscussion() const
{
	std::cout << "[Post] " << title << std::endl;

	unsigned postComments = comments.size();

	for (size_t i = 0; i < postComments; i++)
	{
		std::cout << " -- " << comments[i].getText() << " (" << comments[i].getVoteCount(VoteType::UpVote)
			<< " - " << comments[i].getVoteCount(VoteType::DownVote) << ") {id: " << comments[i].getId() << "}" << std::endl;

		comments[i].printReplies();
	}

	std::cout << std::endl;
}

VoteResult Post::vote(unsigned commentId, VoteType voteType)
{
	Comment* comment = findComment(commentId);

	if (comment)
	{
		comment->vote(voteType);
		return VoteResult::Success;
	}

	unsigned commentsCount = comments.size();

	for (size_t i = 0; i < commentsCount; i++)
	{
		Reply* reply = comments[i].findReply(commentId);

		if (reply)
		{
			reply->vote(voteType);
			return VoteResult::Success;
		}
	}

	return VoteResult::IdNotFound;
}

Comment* Post::findComment(int searchedId)
{
	int commentIndex = findCommentIndex(searchedId);

	return commentIndex < 0 ? nullptr : &comments[commentIndex];
}

int Post::findCommentIndex(int searchedId)
{
	if (searchedId < 0)
	{
		return -1;
	}

	unsigned commentsCount = comments.size();

	for (size_t index = 0; index < commentsCount; index++)
	{
		if (comments[index].getId() == searchedId)
		{
			return index;
		}
	}

	return -1;
}

Result Post::removeReply(const User* loggedUser, int replyId)
{
	unsigned commentsCount = comments.size();

	for (size_t i = 0; i < commentsCount; i++)
	{
		Result result = comments[i].removeReply(loggedUser, replyId);

		if (result != Result::IdNotFound)
		{
			return result;
		}
	}

	return Result::IdNotFound;
}

Result Post::removeComment(const User* loggedUser, int commentId)
{
	int commentIndex = findCommentIndex(commentId);

	if (commentIndex >= 0)
	{
		const User* commentAuthor = comments[commentIndex].getAuthorConst();;

		if (commentAuthor->isModerator() || commentAuthor->getId() == loggedUser->getId())
		{
			comments[commentIndex].free();
			comments.erase(comments.begin() + commentIndex);

			return Result::Success;
		}

		return Result::NoPermission;
	}

	// no comment has 'commentId' id, try to remove any reply with this id
	return removeReply(loggedUser, commentId);
}

void Post::removeComments()
{
	unsigned commentsCount = comments.size();

	for (int i = commentsCount - 1; i >= 0; i--)
	{
		comments[i].free();
	}

	comments.clear();
}

void Post::write(std::ofstream& writer)
{
	for (size_t i = 0; i < comments.size(); i++)
	{
		writer << "----id: " << comments[i].getId() << " " << comments[i].getText() << std::endl;

		comments[i].write(writer);
	}
}

void Post::setContent(const MyString& content)
{
	if (content.length() < 10)
	{
		throw std::invalid_argument("Content must be at least 10 symbols!");
	}

	this->content = content;
}

unsigned Post::getCommentsCount() const
{
	unsigned commentsCount = comments.size();
	unsigned totalCount = commentsCount;

	for (size_t i = 0; i < commentsCount; i++)
	{
		totalCount += comments[i].getRepliesCount();
	}

	return totalCount;
}

void Post::addComment(const Comment& comment)
{
	comments.push_back(comment);
}

bool isSymbolValid(char symbol)
{
	return isUppercase(symbol) || isLowercase(symbol) || isDigit(symbol) ||
		symbol == ' ' || symbol == '?' || symbol == '.' || symbol == '!' || symbol == '-';
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