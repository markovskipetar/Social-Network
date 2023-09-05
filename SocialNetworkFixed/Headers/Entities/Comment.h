#pragma once
#include "Reply.h"

#include "IComment.h"
#include "../ResultEnums/Result.h"

#include <fstream>
#include <vector>

class Comment : public IComment
{
public:
	Comment() = default;
	Comment(unsigned authorId, const MyString& text);

	void addReply(const Reply& reply);
	unsigned getRepliesCount() const;

	void printReplies() const;
	Reply* findReply(unsigned replyId);
	int findReplyIndex(unsigned replyId);

	void free();
	Result removeReply(const User* loggedUser, int replyId);

	void write(std::ofstream& writer);

private:
	std::vector<Reply> replies;
};

