#pragma once
#include "../Repositories/UsersRepository.h"
#include "../Repositories/ThemesRepository.h"
#include "../../Headers/Global/GlobalFunctions.h"
#include "../ResultEnums/Result.h"

class Command
{
public:
	Command();
	virtual void execute() const = 0;
	virtual ~Command() = default;

protected:
	UsersRepository* usersRepository;
	ThemesRepository* themesRepository;
};

