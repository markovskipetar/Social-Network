#pragma once
#include "Command.h"

class List : public Command
{
public:
	List() = default;
	virtual void execute() const override;
};

