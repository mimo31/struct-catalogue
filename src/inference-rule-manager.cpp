/**
 * inference-rule-manager.cpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/2/16
 */
#include "inference-rule-manager.hpp"

namespace strcata
{

uint32_t InferenceRuleManager::count_classes() const
{
	return count_classes(AttributeSet(attribute_manager->get_attribute_count()));
}

uint32_t InferenceRuleManager::count_classes(AttributeSet attrset) const
{
	attrset.infer_completely(rules);
	if (attrset.contradicted)
		return 0;
	AttributeSet s0, s1;
	if (!attrset.disect(s0, s1))
		return 1;
	return count_classes(s0) + count_classes(s1);
}
AttributeSet InferenceRuleManager::infer_completely(const AttributeSet& attrset) const
{
	AttributeSet s2 = attrset;
	s2.infer_completely(rules);
	return s2;
}

}