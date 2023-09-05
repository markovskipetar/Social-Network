#pragma once
#include "Command.h"

class Search : public Command
{
private:
	void printMatches(const char* pattern, const std::vector<Theme>& themes) const;
	bool isMatch(const MyString& title, const char* pattern) const;

public:
	Search() = default;
	virtual void execute() const override;
};

