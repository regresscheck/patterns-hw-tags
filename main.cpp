#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <optional>
#include <string>

#include "input_processor.h"
#include "command_dispatcher.h"
#include "file_processor.h"

int main() {
	InputProcessor InputProcessor;
	FileProcessor fileProcessor;
	TemplateStorage templateStorage;
	UserCommandDispatcher commandDispatcher(templateStorage, fileProcessor);

	std::cout << "Usage:" << std::endl;
	std::cout << "template <template name> <template file>" << std::endl;
	std::cout << "process <file>" << std::endl;

	bool gotExitCommand = false;
	while (!commandDispatcher.shouldFinish()) {
		auto command = InputProcessor.getUserCommand();
		command->accept(commandDispatcher);
	}
}