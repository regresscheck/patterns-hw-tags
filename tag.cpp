#include "tag.h"

bool OpeningTag::pairedWith(const Tag& tag) const {
	if (!tag.isPaired()) {
		return false;
	}

	const ClosingTag* closingTag = dynamic_cast<const ClosingTag*>(&tag);
	if (closingTag == nullptr) {
		return false;
	}

	return closingTag->getId() == id;
}

bool ClosingTag::pairedWith(const Tag& tag) const {
	if (!tag.isPaired()) {
		return false;
	}

	const OpeningTag* openingTag = dynamic_cast<const OpeningTag*>(&tag);
	if (openingTag == nullptr) {
		return false;
	}

	return openingTag->getId() == id;
}