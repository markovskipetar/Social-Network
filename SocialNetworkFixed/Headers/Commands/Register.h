#pragma once
#include "Command.h"
#include "../ResultEnums/RegisterResult.h"

class Register : public Command
{
public:
	Register() = default;
	virtual void execute() const override;

private:
	const User* readUser() const;
	void writeResultMessageToConsole(RegisterResult registerResult) const;

};