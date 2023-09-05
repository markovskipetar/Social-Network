#pragma once
#include "Command.h"

class RemoveComment : public Command
{
public:
	RemoveComment() = default;
	virtual void execute() const override;

private:
	void writeResultMessageToConsole(Result removeCommentResult) const;
};
