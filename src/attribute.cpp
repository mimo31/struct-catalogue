/**
 * attribute.cpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/2/16
 */
#include "attribute.hpp"

#include <fstream>
#include <iostream>

#include "json.hpp"

namespace strcata
{


AttributeInfo::AttributeInfo(const str& name, const str& code)
	: name(name), code(code)
{
}

AugmentedAttribute::AugmentedAttribute(const Attribute attr, const bool negated)
	: attr(attr), negated(negated)
{
}

bool AugmentedAttribute::satisfies(const AttributeTruthValue val) const
{
	return (!negated && val == AttributeTruthValue::TRUE) || (negated && val == AttributeTruthValue::FALSE);
}

AugmentedAttribute AugmentedAttribute::get_negation() const
{
	return AugmentedAttribute(attr, !negated);
}

AttributeManager::AttributeManager(const str& defs_filepath)
{
	std::ifstream ifs(defs_filepath);
	nlohmann::json js;
	ifs >> js;
	nlohmann::json ar = js["defs"];
	for (const nlohmann::json df : ar)
	{
		//std::cout << df["name"].get<str>() << " " << df["code"].get<str>() << std::endl;
		attributes.push_back(AttributeInfo(df["name"].get<str>(), df["code"].get<str>()));
	}
}

uint32_t AttributeManager::get_attribute_count() const
{
	return attributes.size();
}

bool AttributeManager::get_attr_by_code(const str& code, Attribute& attr) const
{
	for (uint32_t i = 0; i < attributes.size(); i++)
	{
		if (code == attributes[i].code)
		{
			attr = Attribute(i);
			return true;
		}
	}
	return false;
}

bool AttributeManager::get_aug_attr_by_str(const str& s, AugmentedAttribute& attr) const
{
	const bool negated = s.length() > 0 && s[0] == '!';
	const str code = negated ? s.substr(1) : s;
	Attribute at;
	if (!get_attr_by_code(code, at))
		return false;
	attr.attr = at;
	attr.negated = negated;
	return true;
}

str AttributeManager::get_attr_code(const Attribute attr) const
{
	return attributes[attr.id].code;
}

str AttributeManager::get_attr_name(const Attribute attr) const
{
	return attributes[attr.id].name;
}

Attribute::Attribute(const uint32_t id)
	: id(id)
{
}

}