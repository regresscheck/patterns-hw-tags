#include "input_processor.h"
#include "template.h"

std::unique_ptr<UserCommand> InputProcessor::getUserCommand() {
	std::string command;
	if (std::cin >> command) {
		if (command == "template") {
			std::string filename, templateName;
			std::cin >> templateName >> filename;
			return std::unique_ptr<UserCommand>(new LoadTemplateCommand(filename, templateName));
		}
		else if (command == "process") {
			std::string filename;
			std::cin >> filename;
			return std::unique_ptr<UserCommand>(new ProcessFileCommand(filename));
		}
		else {
			return std::unique_ptr<UserCommand>(new UnrecognizedCommand());
		}
	}
	else {
		return std::unique_ptr<UserCommand>(new ExitCommand());
	}
}