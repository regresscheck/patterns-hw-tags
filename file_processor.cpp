#include "file_processor.h"

void FileProcessor::process(const std::string& filename, const TemplateStorage& templateStorage) {
	std::ifstream inputFile(filename);
	std::string text((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

	const auto match = templateStorage.getMatchedTemplate(text);
	if (match) {
		std::cout << "Matched pattern: " << match.value() << std::endl;
	}
	else {
		std::cout << "No match" << std::endl;
	}
}