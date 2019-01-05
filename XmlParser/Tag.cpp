#include "pch.h"
#include "Tag.h"
#include <iostream>
#include <algorithm>
/////////////Attribut class/////////////
void Tag::Attribut::setAttrName(const std::string name)
{
	m_attrName = name;
}
void Tag::Attribut::setAttrValue(const std::string value)
{
	m_attrValue = value;
}
Tag::Attribut::Attribut()
{
	setAttrName("");
	setAttrValue("");
}
Tag::Attribut::Attribut(std::string name, std::string value)
{
	setAttrName(name);
	setAttrValue(value);
}
/////////////Attribut class/////////////

/////////////Tag class////////////
Tag::Tag()
{
	setTagName("");
	setTagValue("");
	setTagParent(nullptr);
	setTagAttrCount(0);
	m_hasPair = false;
	m_tagCount = 1;
}
Tag::Tag(const Tag& copy)
{
	setTagName(copy.getTagName());
	setTagValue(copy.getTagValue());
	setTagParent(copy.getTagParent());
	setTagAttrCount(copy.getTagAttrCount());
	this->m_vecAttr = copy.m_vecAttr;
	this->m_vecChildren = copy.m_vecChildren;
	this->m_hasPair = copy.m_hasPair;
	this->m_tagCount = copy.m_tagCount;
}
void Tag::setTagAttrCount(const int count)
{
	if (count < 0)
		throw RangError();
	m_tagAttrCount = count;
}
void Tag::setTagName(const std::string name)
{
	m_tagName = name;
}
void Tag::setTagValue(const std::string value)
{
	m_tagValue = value;
}
void Tag::setTagHasPair(const bool flag)
{
	m_hasPair = flag;
}
std::string Tag::getTagName()const
{
	return m_tagName;
}
std::string Tag::getTagValue()const
{
	return m_tagValue;
}
bool Tag::getTagHasPair()const
{
	return m_hasPair;
}
std::shared_ptr<Tag> Tag::getTagParent()const
{
	return m_tagParent;
}
int Tag::getTagAttrCount()const
{
	return m_tagAttrCount;
}
void Tag::setTagChild(const Tag child)
{
	m_tagCount++;
	m_vecChildren.push_back(std::make_shared<Tag>(Tag(child)));
}
void Tag::setTagParent(std::shared_ptr<Tag> parent)
{
	m_tagParent = parent;
}
void Tag::setTagAttributName(const std::string name)
{
	Attribut dummy;
	dummy.setAttrName(name);
	m_vecAttr.push_back(dummy);
}
void Tag::setTagAttributValue(const std::string value)
{
	m_vecAttr[m_tagAttrCount].setAttrValue(value);
}
void Tag::setTagAttr(std::string name, std::string value)
{
	Attribut tmp(name, value);
	m_vecAttr.push_back(tmp);
}
int Tag::getTagCount()
{
	return m_tagCount;
}
std::shared_ptr<Tag> Tag::getPenultimateTag()
{
	if(m_vecChildren.size() == 1)
		return m_vecChildren[m_vecChildren.size() - 1];
	else 
		return m_vecChildren[m_vecChildren.size() - 2];
}
std::shared_ptr<Tag> Tag::getLastTag()
{
	return m_vecChildren[m_vecChildren.size() - 1];
}

//Operator overloading
inline bool Tag::operator == (const Tag& tag)const
{
	return (this->m_tagName == tag.m_tagName);
}
inline bool Tag::operator != (const Tag& tag)const
{
	return !(this->operator==(tag));
}

//Helper functions
///*std::vector<std::shared_ptr<Tag>>::iterator*/auto Tag::findTag(std::shared_ptr<Tag> tag)
//{
//	return std::find(m_vecChildren.begin(), m_vecChildren.end(), tag);
//}

std::string Tag::duumySearch(Tag tag)
{
	for (int i = 0; i < m_vecChildren.size(); i++)
	{
		if (m_vecChildren[i]->getTagName() == tag.getTagName())
		{
			if (m_vecChildren[i]->getTagValue() != "")
			{
				return m_vecChildren[i]->getTagValue();
			}
			else
			{
				throw EmptyValue();
			}
		}
	}
	throw WrongTagName();
}

/////////////Tag class////////////


void Tag::show()
{
	for (int i = 0; i < m_vecChildren.size(); i++)
	{
		std::cout << m_vecChildren[i]->getTagName() << '\t' << m_vecChildren[i]->getTagValue() << std::endl;
	}
}
