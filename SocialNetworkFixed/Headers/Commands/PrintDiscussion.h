#pragma once
#include "Command.h"

class PrintDiscussion : public Command
{
public:
	PrintDiscussion() = default;
	virtual void execute() const override;
};