#pragma once
#include "Command.h"

class Vote : public Command
{
public:
	Vote() = default;
	virtual void execute() const override;

private:
	bool validateVoteType(const char* voteType) const;
	void writeResultMessageToConsole(VoteResult voteResult) const;
};
