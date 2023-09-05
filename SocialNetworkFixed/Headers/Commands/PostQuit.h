#pragma once
#include "Command.h"

class PostQuit : public Command
{
public:
	PostQuit() = default;
	virtual void execute() const override;
};
