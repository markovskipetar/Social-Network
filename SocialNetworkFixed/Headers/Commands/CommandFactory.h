#pragma once
#include "Command.h"
#include "Register.h"
#include "Login.h"
#include "Create.h"
#include "Logout.h"
#include "Search.h"
#include "Open.h"
#include "List.h"
#include "PostCommand.h"
#include "PostOpen.h"
#include "PostQuit.h"
#include "AddComment.h"
#include "PrintDiscussion.h"
#include "MakeReply.h"
#include "Vote.h"
#include "RemoveComment.h"
#include "RemovePost.h"
#include "RemoveTheme.h"
#include "Edit.h"
#include "SaveAs.h"
#include "EditId.h"
#include <string>

class CommandFactory
{
public:
	static CommandFactory* getInstance();
	static void freeInstance();

	Command* readCommand(const char* commandText) const;

private:
	static CommandFactory* instance;

private:
	CommandFactory() = default;
};

