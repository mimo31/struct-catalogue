/**
 * inference-rule-manager.hpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/2/16
 */
#ifndef INFERENCE_RULE_MANAGER_HPP
#define INFERENCE_RULE_MANAGER_HPP

#include "attribute-set.hpp"
#include "inference-rule.hpp"

namespace strcata
{

class InferenceRuleManager
{
private:
	AttributeManagerPtr attribute_manager;
	InferenceRuleList rules;

public:
	InferenceRuleManager(const AttributeManagerPtr attribute_manager, const str& rules_filepath);

	uint32_t count_classes() const;
	void print_classes() const;
	uint32_t count_classes(AttributeSet attrset) const;
	void print_classes(AttributeSet attrset) const;
	AttributeSet infer_completely(const AttributeSet& attrset, const bool print_steps) const;
};
typedef std::shared_ptr<InferenceRuleManager> InferenceRuleManagerPtr;

}

#endif // INFERENCE_RULE_MANAGER_HPP