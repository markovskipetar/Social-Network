#pragma once
#include "Command.h"

class RemoveTheme : public Command
{
public:
	RemoveTheme() = default;
	virtual void execute() const override;

private:
	void writeResultMessageToConsole(Result removeThemeResult) const;
};
