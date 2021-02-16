/**
 * attribute-set.hpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/2/16
 */
#include "attribute.hpp"
#include "inference-rule.hpp"

namespace strcata
{

class AttributeSet
{
	uint32_t attr_count;
	std::vector<AttributeTruthValue> attributes;

public:
	bool contradicted;

	AttributeSet() = default;
	AttributeSet(const uint32_t attr_count);

	void infer_completely(const InferenceRuleList& rules);
	bool disect(AttributeSet& s0, AttributeSet& s1);
};

};