#ifndef TAG_H
#define TAG_H

#include <string>
#include <vector>
#include <memory>

class BaseExeption
{

};
class SyntaxError : public BaseExeption
{

};
class RangError : public BaseExeption
{

};
class WrongTagName : public BaseExeption
{

};
class EmptyValue : public BaseExeption
{

};

class Tag
{
public:
	using tagVecElement = std::vector<std::shared_ptr<Tag>>;

	Tag();
	Tag(const Tag&);

	void setTagName(const std::string name);
	void setTagValue(const std::string value);
	void setTagChild(const Tag child);
	void setTagParent(const std::shared_ptr<Tag> parent);
	void setTagAttributName(const std::string name);
	void setTagAttributValue(const std::string value);
	void setTagAttrCount(const int count);
	void setTagHasPair(const bool flag);
	void setTagAttr(std::string name, std::string value);

	std::string          getTagName()const;
	std::string          getTagValue()const;
	std::shared_ptr<Tag> getTagParent()const;
	int                  getTagAttrCount()const;
	bool                 getTagHasPair()const;
	int                  getTagCount();
	std::shared_ptr<Tag> getPenultimateTag();
	std::shared_ptr<Tag> getLastTag();

	//Operator overloading
	inline bool operator == (const Tag&)const;/////ok
	inline bool operator != (const Tag&)const;/////ok

	//Helper functions
	/*std::vector<std::shared_ptr<Tag>>::iterator*/ auto findTag(std::shared_ptr<Tag> tag);

	std::string duumySearch(Tag tag);

	void show();

	class Attribut
	{
	public:
		Attribut(std::string name, std::string value);
		Attribut();
		void setAttrName(const std::string name);
		void setAttrValue(const std::string value);
	private:
		std::string m_attrName;
		std::string m_attrValue;
	};
public:
	std::vector<Attribut>               m_vecAttr;
	std::vector<std::shared_ptr<Tag>>   m_vecChildren;
	std::shared_ptr<Tag>                m_tagParent;
	std::string                         m_tagName;
	std::string                         m_tagValue;
	int                                 m_tagAttrCount;
	int                                 m_tagCount;
	bool                                m_hasPair;
};

#endif
