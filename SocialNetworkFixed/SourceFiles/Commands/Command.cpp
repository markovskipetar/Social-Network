#include "../../Headers/Commands/Command.h"

Command::Command()
{
	usersRepository = UsersRepository::getInstance();
	themesRepository = ThemesRepository::getInstance();
}
