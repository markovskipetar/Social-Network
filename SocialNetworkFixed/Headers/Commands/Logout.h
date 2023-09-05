#pragma once
#include "Command.h"

class Logout : public Command
{
public:
	Logout() = default;
	virtual void execute() const override;
};

