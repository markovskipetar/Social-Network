#pragma once
#include "Command.h"

class AddComment : public Command
{
public:
	AddComment() = default;
	virtual void execute() const override;
};
