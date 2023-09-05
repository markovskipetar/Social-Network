#pragma once
#include "../Headers/Engine.h"

void Engine::Run()
{
	CommandFactory* commandFactory = CommandFactory::getInstance();

	while (true)
	{
		char commandText[32];
		std::cin.getline(commandText, 32);

		if (!strcmp(commandText, "exit"))
		{
			break;
		}

		Command* command = commandFactory->readCommand(commandText);

		if (command)
		{
			command->execute();
			continue;
		}

		std::cout << "---------" << std::endl;
		std::cout << "Invalid command!" << std::endl << std::endl;
	}

	CommandFactory::freeInstance();
}