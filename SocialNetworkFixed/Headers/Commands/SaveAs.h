#pragma once
#include "Command.h";

class SaveAs : public Command
{
public:
	SaveAs() = default;
	virtual void execute() const override;
};