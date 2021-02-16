/**
 * inference-rule.cpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/2/16
 */
#include "inference-rule.hpp"

namespace strcata
{

AugmentedAttribute::AugmentedAttribute(const Attribute attr, const bool negated)
	: attr(attr), negated(negated)
{
}

bool AugmentedAttribute::satisfies(const AttributeTruthValue val) const
{
	return (!negated && val == AttributeTruthValue::TRUE) || (negated && val == AttributeTruthValue::FALSE);
}

InferenceRule::InferenceRule(const AugmentedAttributeList& andOfAttributes)
	: and_of_attributes(and_of_attributes)
{
}

}