#pragma once

#include <memory>
#include <iostream>

#include "command.h"

class InputProcessor {
public:
	std::unique_ptr<UserCommand> getUserCommand();
};