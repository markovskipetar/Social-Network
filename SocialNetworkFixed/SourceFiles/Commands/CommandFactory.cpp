#pragma once
#include "../../Headers/Commands/CommandFactory.h"

CommandFactory* CommandFactory::instance = nullptr;

CommandFactory* CommandFactory::getInstance()
{
	if (!instance)
	{
		instance = new CommandFactory();
	}

	return instance;
}

void CommandFactory::freeInstance()
{
	delete instance;
}

Command* CommandFactory::readCommand(const char* commandText) const
{
	if (!strcmp(commandText, "signup"))
	{
		return new Register();
	}
	else if (!strcmp(commandText, "login"))
	{
		return new Login();
	}
	else if (!strcmp(commandText, "edit"))
	{
		return new Edit();
	}
	else if (!strcmp(commandText, "edit id"))
	{
		return new EditId();
	}
	else if (!strcmp(commandText, "create"))
	{
		return new Create();
	}
	else if (!strcmp(commandText, "logout"))
	{
		return new Logout();
	}
	else if (!strcmp(commandText, "search"))
	{
		return new Search();
	}
	else if (!strcmp(commandText, "open"))
	{
		return new Open();
	}
	else if (!strcmp(commandText, "list"))
	{
		return new List();
	}
	else if (!strcmp(commandText, "post"))
	{
		return new PostCommand();
	}
	else if (!strcmp(commandText, "post_open"))
	{
		return new PostOpen();
	}
	else if (!strcmp(commandText, "post_quit"))
	{
		return new PostQuit();
	}
	else if (!strcmp(commandText, "add_comment"))
	{
		return new AddComment();
	}
	else if (!strcmp(commandText, "discussion"))
	{
		return new PrintDiscussion();
	}
	else if (!strcmp(commandText, "reply"))
	{
		return new MakeReply();
	}
	else if (!strcmp(commandText, "vote"))
	{
		return new Vote();
	}
	else if (!strcmp(commandText, "remove_comment"))
	{
		return new RemoveComment();
	}
	else if (!strcmp(commandText, "remove_post"))
	{
		return new RemovePost();
	}
	else if (!strcmp(commandText, "remove_theme"))
	{
		return new RemoveTheme();
	}
	else if (!strcmp(commandText, "save as"))
	{
		return new SaveAs();
	}
	else
	{
		return nullptr;
	}
}
