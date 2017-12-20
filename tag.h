#pragma once

#include <string>

class Tag {
protected:
	std::string value;
public:
	Tag(const std::string& value)
		: value(value) {}
	
	virtual ~Tag() = default;

	std::string getValue() const {
		return value;
	}

	virtual bool isPaired() const {
		return false;
	}

	virtual bool pairedWith(const Tag& tag) const {
		return false;
	}

	virtual bool isOpening() const {
		return false;
	}

	virtual bool matches(const std::string& text, size_t position) const {
		if (text.size() - position < value.size()) {
			return false;
		}
		return text.substr(position, value.size()) == value;
	}
};

class OpeningTag : public Tag {
protected:
	size_t id;
public:
	OpeningTag(size_t id, const std::string& value)
		: Tag(value)
		, id(id) {}	

	virtual ~OpeningTag() = default;

	bool isPaired() const override {
		return true;
	}

	bool pairedWith(const Tag& tag) const override;

	size_t getId() const {
		return id;
	}

	virtual bool isOpening() const override {
		return true;
	}
};

class ClosingTag : public OpeningTag {
public:
	ClosingTag(size_t id, const std::string& value)
		: OpeningTag(id, value) {}
	bool pairedWith(const Tag& tag) const override;

	bool isOpening() const override {
		return false;
	}

};