#include "template.h"

// optimization friendly function
bool Template::matches(const std::string& text) const {
	std::stack<const Tag*> tagStack;
	for (size_t i = 0; i < text.size(); ++i) {
		bool hasTag = false;

		for (const auto& tag : tags) {
			if (tag->matches(text, i)) {
				if (tag->isPaired() && !tag->isOpening() && tagStack.top()->pairedWith(*tag)) {
					tagStack.pop();
					hasTag = true;
					break;
				}
				else if (tag->isPaired() && tag->isOpening()) {
					tagStack.push(tag.get());
					hasTag = true;
					break;
				}
				else if (!tag->isPaired()) {
					hasTag = true;
					break;
				}
			}
		}

		if (text[i] == '<' && !hasTag) {
			// wow, unknown tag
			return false;
		}
	}
	return tagStack.size() == 0;
}

std::optional<std::string> TemplateStorage::getMatchedTemplate(std::string text) const {
	for (size_t i = 0; i < templates.size(); ++i) {
		const auto& t = templates[i];
		if (t.matches(text)) {
			return t.getName();
		}
	}
	return {};
}

Template Template::fromFile(const std::string& name, const std::string& filename) {
	Template newTemplate(name);
	std::ifstream inputFile(filename);

	std::string line;
	while (std::getline(inputFile, line)) {
		std::stringstream iss(line);

		std::string firstTag, secondTag;
		iss >> firstTag;

		if (iss >> secondTag) {
			newTemplate.addPairedTag(firstTag, secondTag);
		}
		else {
			newTemplate.addSingleTag(firstTag);
		}
	}

	return newTemplate;
}