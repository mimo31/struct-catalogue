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

enum AttributeTruthValue
{
	TRUE, FALSE, UNKNOWN
};

struct AugmentedAttribute
{
	Attribute attr;
	bool negated;

	AugmentedAttribute(const Attribute attr, const bool negated);
	bool satisfies(const AttributeTruthValue val) const;
	AugmentedAttribute get_negation() const;
};
typedef std::vector<AugmentedAttribute> AugmentedAttributeList;

class InferenceRule
{
public:
	AugmentedAttributeList and_of_attributes;
	InferenceRule(const AugmentedAttributeList& and_of_attributes);
};
typedef std::vector<InferenceRule> InferenceRuleList;

}

#endif // INFERENCE_RULE_HPP