#pragma once
#include "Command.h"
#include <string>

class PostOpen : public Command
{
public:
	PostOpen() = default;
	virtual void execute() const override;
};
