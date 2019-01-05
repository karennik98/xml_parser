#include "pch.h"
#include "ReadXml.h"
#include "Tag.h"
#include <iostream>
#include <string>
#include <fstream>
#include <memory>

Read::Read()
{
}
Read::Read(const std::string& file)
{
	Open(file);
}
int getIndent(std::string& str)
{
	int indent = 0;
	int i = 0;
	while (str[i] == ' ' || str[i] == '\t')
	{
		if (str[0] == '\t')
			indent += 4;
		else
			indent++;
		i++;
	}
	return indent;
}
bool Read::Open(const std::string& file)
{
	m_stream.open(file);
	return m_stream.is_open();
}
void Read::EraseWhiteSpace(std::string& str)
{
	while (str[0] == ' ' || str[0] == '\t' )
		str.erase(0, 1);
}
std::string Read::takeTagAttrName(std::string& str)
{
	EraseWhiteSpace(str);
	int i = 0;
	std::string attrName;
	if (!str.empty())
	{
		while (str[i] != '=' && str[i] != ' ')
		{
			attrName += str[i++];
		}
	}
	else throw SyntaxError();
	str.erase(str.begin(), str.begin() + (attrName.size()));
	return attrName;
}
std::string Read::takeTagAttrValue(std::string& str)
{
	EraseWhiteSpace(str);
	int i = 1;
	std::string value;
	if (!str.empty() && str[0] == '=')
	{
		while (str[i] != '>' && str[i] != ' ')
		{
			value += str[i++];
		}
	}
	else throw SyntaxError();
	/*if(str[i] == '>')
		str.erase(str.begin() , str.begin() + (value.size() + 2));
						else */
	str.erase(str.begin(), str.begin() + (value.size() + 1));
	return value;
}
std::string Read::takeTagName(std::string& str)
{
	std::string name;
	int i = 0;
	if (str[i] == '<')
	{
		i++;
		while (str[i] != ' ' && str[i] != '>')
		{
			name += str[i++];
		}
	}
	else throw SyntaxError(); //???? maybe line it is the value???
	str.erase(str.begin(), str.begin() + (name.size() + 1));
	//EraseWhiteSpace(str); maybe wrong case
	return name;
}
std::string Read::takeTagValue(std::string& str)
{
	std::string value;
	int i = 1;
	if (!str.empty())
	{
		while (str[i] != '<' && str[i])
		{
			value += str[i++];
		}
	}
	str.erase(str.begin(), str.begin() + value.size() + 1);
	EraseWhiteSpace(str);
	return value;
}
bool Read::Parse()
{
	int i = 0;
	int prevIndent = 0;
	while (!m_stream.eof())
	{
		Tag tempTag;
		std::string tmpStr;
		std::getline(m_stream, tmpStr);
		int indent = getIndent(tmpStr);
		if (indent == 0 && prevIndent == 0)
		{
			tempTag.setTagParent(nullptr);/// see late
			if (tmpStr[0] == '<')
			{
				tempTag.setTagName(takeTagName(tmpStr));
				if (tmpStr[0] == '>' && tmpStr.size() == 1)
				{
					setTagChild(tempTag);
					prevIndent = indent;
					continue;
				}
				else if (tmpStr[0] == ' ')
				{
					int count = 0;
					while (tmpStr[0] != '>')
					{
						count++;
						tempTag.setTagAttrCount(count);
						std::string tmpAttrName = takeTagAttrName(tmpStr);
						std::string tmpAttrValue = takeTagAttrValue(tmpStr);
						tempTag.setTagAttr(tmpAttrName, tmpAttrValue);
					}
					if (tmpStr[0] == '>' && tmpStr.size() > 2)
					{
						tempTag.setTagValue(takeTagValue(tmpStr));
					}
					if (tmpStr[0] == '<' && tmpStr[1] == '/')
					{
						tempTag.setTagHasPair(true);
						tmpStr.clear();
					}
				}
			}
			prevIndent = indent;
			setTagChild(tempTag);
		}
		else if(indent > prevIndent)
		{
			EraseWhiteSpace(tmpStr);
			if (tmpStr[0] == '<')
			{
				if (indent > prevIndent)
					tempTag.setTagParent(getLastTag());
					//tempTag.setTagParent(getPenultimateTag());
				else
					tempTag.setTagParent(getLastTag()->getTagParent());
				tempTag.setTagName(takeTagName(tmpStr));
				if (tmpStr[0] == '>' && tmpStr.size() == 1)
				{
					setTagChild(tempTag);
					prevIndent = indent;
					continue;
				}
				else if (tmpStr[0] == ' ')
				{
					int count = 0;
					while (tmpStr[0] != '>')
					{
						count++;
						tempTag.setTagAttrCount(count);
						std::string tmpAttrName = takeTagAttrName(tmpStr);
						std::string tmpAttrValue = takeTagAttrValue(tmpStr);
						tempTag.setTagAttr(tmpAttrName, tmpAttrValue);
					}
					if (tmpStr[0] == '>' && tmpStr.size() > 2)
					{
						tempTag.setTagValue(takeTagValue(tmpStr));
					}
					if (tmpStr[0] == '<' && tmpStr[1] == '/')
					{
						tempTag.setTagHasPair(true);
						tmpStr.clear();
					}
				}
			}
			else
			{
				tempTag.getPenultimateTag()->setTagValue(takeTagValue(tmpStr));
			}
			setTagChild(tempTag);
			prevIndent = indent;
		}
		else if (indent == prevIndent)
		{
			EraseWhiteSpace(tmpStr);
			if (tmpStr[0] == '<')
			{
				if (tmpStr[1] == '/')
					continue;
				if (indent > prevIndent)
					tempTag.setTagParent(getLastTag());
				//tempTag.setTagParent(getPenultimateTag());
				else
					tempTag.setTagParent(getLastTag()->getTagParent());
				tempTag.setTagName(takeTagName(tmpStr));
				if (tmpStr[0] == '>' && tmpStr.size() == 1)
				{
					setTagChild(tempTag);
					prevIndent = indent;
					continue;
				}
				else if (tmpStr[0] == ' ')
				{
					int count = 0;
					while (tmpStr[0] != '>')
					{
						count++;
						tempTag.setTagAttrCount(count);
						std::string tmpAttrName = takeTagAttrName(tmpStr);
						std::string tmpAttrValue = takeTagAttrValue(tmpStr);
						tempTag.setTagAttr(tmpAttrName, tmpAttrValue);
					}
					if (tmpStr[0] == '>' && tmpStr.size() > 2)
					{
						tempTag.setTagValue(takeTagValue(tmpStr));
					}
					if (tmpStr[0] == '<' && tmpStr[1] == '/')
					{
						tempTag.setTagHasPair(true);
						tmpStr.clear();
					}
				}
			}
			else
			{
				tempTag.getPenultimateTag()->setTagValue(takeTagValue(tmpStr));
			}
			setTagChild(tempTag);
			prevIndent = indent;
		}
		else if (indent < prevIndent)
		{
			EraseWhiteSpace(tmpStr);
			if (tmpStr[0] == '<' && tmpStr[1] == '/')
			{
				prevIndent = indent;
				continue; //TODO: in this case we need use setTagHasPair();
			}
		}
	}
	return true;
}

//////////////////Geters/////////////////
std::string Read::getTagValue(std::string name)
{
	Tag tmp;
	tmp.setTagName(name);
	return duumySearch(tmp);
}

void Read::getAllTags()
{
	show();
}
