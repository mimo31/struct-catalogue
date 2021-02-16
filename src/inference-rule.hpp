/**
 * inference-rule.hpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/2/16
 */
#ifndef INFERENCE_RULE_HPP
#define INFERENCE_RULE_HPP

#include <vector>

#include "attribute.hpp"

namespace strcata
{

class InferenceRule
{
public:
	AugmentedAttributeList and_of_attributes;
	InferenceRule(const AugmentedAttributeList& and_of_attributes);
};
typedef std::vector<InferenceRule> InferenceRuleList;

}

#endif // INFERENCE_RULE_HPP