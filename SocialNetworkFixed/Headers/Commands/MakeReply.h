#pragma once
#include "Command.h"

class MakeReply : public Command
{
public:
	MakeReply() = default;
	virtual void execute() const override;

private:
	void replyToComment(Comment* comment, unsigned authorId) const;
	void writeResultMessageToConsole(Result replyResult) const;
};

