/**
 * attribute.hpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/2/16
 */
#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace strcata
{

typedef std::string str;

struct AttributeInfo
{
	str name;
	str code;

	AttributeInfo(const str& name, const str& code);
};

class Attribute
{
public:
	uint32_t id;

	Attribute() = default;
	Attribute(const uint32_t id);
};

enum AttributeTruthValue
{
	TRUE, FALSE, UNKNOWN
};

struct AugmentedAttribute
{
	Attribute attr;
	bool negated;

	AugmentedAttribute() = default;
	AugmentedAttribute(const Attribute attr, const bool negated);
	bool satisfies(const AttributeTruthValue val) const;
	AugmentedAttribute get_negation() const;
};
typedef std::vector<AugmentedAttribute> AugmentedAttributeList;

class AttributeManager
{
	std::vector<AttributeInfo> attributes;

public:
	AttributeManager(const str& defs_filepath);
	uint32_t get_attribute_count() const;

	bool get_attr_by_code(const str& code, Attribute& attr) const;
	bool get_aug_attr_by_str(const str& s, AugmentedAttribute& attr) const;
	str get_attr_code(const Attribute attr) const;
	str get_attr_name(const Attribute attr) const;
};
typedef std::shared_ptr<AttributeManager> AttributeManagerPtr;

//AttributeManagerPtr attribute_manager;
}

#endif // ATTRIBUTE_HPP