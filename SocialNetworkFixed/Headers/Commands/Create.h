#pragma once
#include "Command.h";

class Create : public Command
{
public:
	Create() = default;
	virtual void execute() const override;

private:
	const Theme* readTheme(unsigned creatorId) const;
};