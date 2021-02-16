/**
 * attribute-set.hpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/2/16
 */
#ifndef ATTRIBUTE_SET_HPP
#define ATTRIBUTE_SET_HPP

#include "attribute.hpp"
#include "inference-rule.hpp"

namespace strcata
{

class AttributeSet
{
	uint32_t attr_count;

public:
	std::vector<AttributeTruthValue> attributes;
	bool contradicted = false;

	AttributeSet() = default;
	AttributeSet(const uint32_t attr_count);
	AttributeSet(const uint32_t attr_count, const AugmentedAttributeList& set_attributes);

	void infer_completely(const InferenceRuleList& rules);
	bool disect(AttributeSet& s0, AttributeSet& s1);
};

};

#endif // ATTRIBUTE_SET_HPP