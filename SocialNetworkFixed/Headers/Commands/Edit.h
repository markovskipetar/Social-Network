#pragma once
#include "Command.h"

class Edit : public Command
{
public:
	Edit() = default;
	virtual void execute() const override;
};

