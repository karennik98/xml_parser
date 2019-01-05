#ifndef READ_XML_H
#define READ_XML_H

#include <string>
#include <fstream>
#include "Tag.h"

class Read : public Tag
{
public:
	Read();
	Read(const std::string&);
	void EraseWhiteSpace(std::string&);
	bool Open(const std::string&);
	bool Parse();

	std::string takeTagName(std::string& str);
	std::string takeTagAttrName(std::string& str);
	std::string takeTagAttrValue(std::string& str);
	std::string takeTagValue(std::string& str);
	//std::shared_ptr<Tag> find(std::shared_ptr<Tag>);

	//Geters
	std::string getTagValue(std::string name);

	void getAllTags();
private:
	std::ifstream m_stream;
};


#endif