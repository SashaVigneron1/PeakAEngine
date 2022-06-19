#pragma once
#include <Document.h>


class JsonParser final
{
public:
	JsonParser(const std::string& filePath);
	~JsonParser();

	JsonParser(const JsonParser& other) = delete;
	JsonParser(JsonParser&& other) noexcept = delete;
	JsonParser& operator=(const JsonParser& other) = delete;
	JsonParser& operator=(JsonParser&& other) noexcept = delete;

	rapidjson::Document* GetDocument() const { return m_pDocument; }

private:
	void LoadDocument();

	std::string m_FilePath;
	rapidjson::Document* m_pDocument;
};

