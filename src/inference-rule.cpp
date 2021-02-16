/**
 * inference-rule.cpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/2/16
 */
#include "inference-rule.hpp"

namespace strcata
{

InferenceRule::InferenceRule(const AugmentedAttributeList& and_of_attributes)
	: and_of_attributes(and_of_attributes)
{
}

}