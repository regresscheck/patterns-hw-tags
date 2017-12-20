#pragma once

#include <string>

class AbstractCommandDispatcher;

class UserCommand {
public:
	virtual void accept(AbstractCommandDispatcher& dispatcher) = 0;
	virtual ~UserCommand() = default;
};

class LoadTemplateCommand;
class ProcessFileCommand;
class ExitCommand;
class UnrecognizedCommand;

class AbstractCommandDispatcher {
public:
	virtual void dispatch(LoadTemplateCommand& command) = 0;
	virtual void dispatch(ProcessFileCommand& command) = 0;
	virtual void dispatch(ExitCommand& command) = 0;
	virtual void dispatch(UnrecognizedCommand& command) = 0;
};

class LoadTemplateCommand : public UserCommand {
private:
	std::string filename;
	std::string templateName;
public:
	LoadTemplateCommand(const std::string& filename, const std::string& templateName)
		: filename(filename)
		, templateName(templateName) {}

	std::string getFilename() {
		return filename;
	}

	std::string getTemplateName() {
		return templateName;
	}

	void accept(AbstractCommandDispatcher& dispatcher) override {
		dispatcher.dispatch(*this);
	}
};

class ProcessFileCommand : public UserCommand {
private:
	std::string filename;
public:
	ProcessFileCommand(std::string filename)
		: filename(filename) {}

	std::string getFilename() {
		return filename;
	}

	void accept(AbstractCommandDispatcher &dispatcher) override {
		dispatcher.dispatch(*this);
	}
};

class ExitCommand : public UserCommand {
public:
	void accept(AbstractCommandDispatcher &dispatcher) override {
		dispatcher.dispatch(*this);
	}
};

class UnrecognizedCommand : public UserCommand {
public:
	void accept(AbstractCommandDispatcher &dispatcher) override {
		dispatcher.dispatch(*this);
	}
};