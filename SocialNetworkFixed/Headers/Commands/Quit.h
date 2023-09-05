#pragma once
#include "Command.h"

class Quit : public Command
{
public:
	Quit() = default;
	virtual void execute() const override;
};

