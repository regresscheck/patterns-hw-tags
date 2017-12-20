#pragma once

#include <string>

#include "template.h"

class FileProcessor {
public:
	void process(const std::string& filename, const TemplateStorage& templateStorage);
};