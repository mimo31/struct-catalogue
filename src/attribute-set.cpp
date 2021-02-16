/**
 * attribute-set.cpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/2/16
 */
#include "attribute-set.hpp"

namespace strcata
{

AttributeSet::AttributeSet(const uint32_t attr_count)
	: attr_count(attr_count), attributes(std::vector<AttributeTruthValue>(attr_count))
{
	fill(attributes.begin(), attributes.end(), AttributeTruthValue::UNKNOWN);
}

AttributeSet::AttributeSet(const uint32_t attr_count, const AugmentedAttributeList& set_attributes)
	: AttributeSet(attr_count)
{
	for (const AugmentedAttribute aug_attr : set_attributes)
		attributes[aug_attr.attr.id] = aug_attr.negated ? AttributeTruthValue::FALSE : AttributeTruthValue::TRUE;
}

void AttributeSet::infer_completely(const InferenceRuleList& rules)
{
	bool changed;
	do
	{
		changed = false;
		for (const InferenceRule rule : rules)
		{
			for (uint32_t i = 0; i < rule.and_of_attributes.size(); i++)
			{
				bool fail = false;
				for (uint32_t j = 0; j < rule.and_of_attributes.size(); j++)
				{
					if (i != j)
					{
						const AugmentedAttribute attr = rule.and_of_attributes[j];
						if (!attr.satisfies(attributes[attr.attr.id]))
						{
							fail = true;
							continue;
						}
					}
				}
				if (!fail)
				{
					const AugmentedAttribute attr = rule.and_of_attributes[i];
					if (attr.satisfies(attributes[attr.attr.id]))
					{
						contradicted = true;
						return;
					}
					else if (attributes[attr.attr.id] == AttributeTruthValue::UNKNOWN)
					{
						attributes[attr.attr.id] = attr.negated ? AttributeTruthValue::TRUE : AttributeTruthValue::FALSE;
						changed = true;
					}
				}
			}	
		}
	} while (changed);
}

bool AttributeSet::disect(AttributeSet& s0, AttributeSet& s1)
{
	uint32_t unknind = 0;
	while (unknind < attr_count && attributes[unknind] != AttributeTruthValue::UNKNOWN)
		unknind++;
	if (unknind == attr_count)
		return false;
	s0 = *this;
	s0.attributes[unknind] = AttributeTruthValue::TRUE;
	s1 = *this;
	s1.attributes[unknind] = AttributeTruthValue::FALSE;
	return true;
}

}