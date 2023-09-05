#pragma once
#include "Command.h"

class RemovePost : public Command
{
public:
	RemovePost() = default;
	virtual void execute() const override;

private:
	void writeResultMessageToConsole(Result removePostResult) const;
};
