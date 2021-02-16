/**
 * attribute.hpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/2/16
 */

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

class AttributeManager
{
	std::vector<AttributeInfo> attributes;

public:
	AttributeManager(const str& defs_filepath);
	uint32_t get_attribute_count() const;

	bool get_attr_by_code(Attribute& attr) const;
	str get_attr_code(const Attribute attr) const;
	str get_attr_name(const Attribute attr) const;
};
typedef std::shared_ptr<AttributeManager> AttributeManagerPtr;

//AttributeManagerPtr attribute_manager;

class Attribute
{
public:
	uint32_t id;
};

}