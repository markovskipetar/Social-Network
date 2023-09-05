#pragma once
#include "Command.h"
#include "../ResultEnums/PostResult.h"

class PostCommand : public Command
{
public:
	PostCommand() = default;
	virtual void execute() const override;

private:
	const Post* readPost(unsigned creatorId, Theme* openedTheme) const;
	void writeResultMessageToConsole(PostResult postResult, const MyString& themeTitle) const;
};

