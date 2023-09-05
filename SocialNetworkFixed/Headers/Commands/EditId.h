#pragma once
#include "Command.h"

class EditId : public Command
{
public:
	EditId() = default;
	virtual void execute() const override;
};

