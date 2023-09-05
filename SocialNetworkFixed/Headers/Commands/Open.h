#pragma once
#include "Command.h"
#include <iostream>
#include <string>

class Open : public Command
{
public:
	Open() = default;
	virtual void execute() const override;

private:
	void writeResultMessageToConsole(OpenResult openResult) const;
};

