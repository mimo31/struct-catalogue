/**
 * inference-rule-manager.hpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/2/16
 */
#include "attribute-set.hpp"
#include "inference-rule.hpp"

namespace strcata
{

class InferenceRuleManager
{
	AttributeManagerPtr attribute_manager;
	InferenceRuleList rules;

	InferenceRuleManager(const AttributeManagerPtr attribute_manager, const str& rules_filepath);

	uint32_t count_classes() const;
	uint32_t count_classes(AttributeSet attrset) const;
	AttributeSet infer_completely(const AttributeSet& attrset) const;
};
typedef std::shared_ptr<InferenceRuleManager> InferenceRuleManagerPtr;

}