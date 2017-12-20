#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <optional>
#include <fstream>
#include <sstream>
#include <memory>

#include "tag.h"

class Template {
private:
	std::string name;
	// lazy way
	std::vector<std::shared_ptr<Tag>> tags;
	size_t totalPairs;
public:
	Template(const std::string& name)
		: name(name)
		, totalPairs(0) {}

	std::string getName() const {
		return name;
	}

	void addSingleTag(const std::string& tag) {
		tags.push_back(std::make_shared<Tag>(tag));
	}

	void addPairedTag(const std::string& openingTag, const std::string& closingTag) {
		tags.push_back(std::make_shared<OpeningTag>(totalPairs, openingTag));
		tags.push_back(std::make_shared<ClosingTag>(totalPairs, closingTag));
		++totalPairs;
	}

	bool matches(const std::string& text) const;

	static Template fromFile(const std::string& name, const std::string& filename);
};

class TemplateStorage {
private:
	std::vector<Template> templates;
public:
	void addTemplate(const Template& newTemplate) {
		templates.push_back(newTemplate);
	}

	std::optional<std::string> getMatchedTemplate(std::string text) const;
};