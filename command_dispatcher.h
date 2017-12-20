#pragma once

#include "command.h"
#include "template.h"
#include "file_processor.h"

class UserCommandDispatcher : public AbstractCommandDispatcher {
private:
	bool gotExit;
	TemplateStorage& templateStorage;
	FileProcessor& fileProcessor;
public:
	UserCommandDispatcher(TemplateStorage& templateStorage, FileProcessor& fileProcessor)
		: gotExit(false)
		, templateStorage(templateStorage)
		, fileProcessor(fileProcessor) {}

	bool shouldFinish() const {
		return gotExit;
	}

	void dispatch(LoadTemplateCommand& command) override {
		Template newTemplate = Template::fromFile(command.getTemplateName(), command.getFilename());
		templateStorage.addTemplate(newTemplate);
		std::cout << "Loaded" << std::endl;
	}

	void dispatch(ProcessFileCommand& command) override {
		fileProcessor.process(command.getFilename(), templateStorage);
	}

	void dispatch(ExitCommand& command) override {
		gotExit = true;
	}

	void dispatch(UnrecognizedCommand& command) override {
		std::cout << "Unrecognized command" << std::endl;
	}
};