/**
 * inference-rule-manager.cpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/2/16
 */
#include "inference-rule-manager.hpp"

#include <fstream>
#include <iostream>

#include "json.hpp"

namespace strcata
{

AugmentedAttribute InferenceRuleManager::str_to_aug_attr(const str& s)
{
	const bool negated = s.length() > 0 && s[0] == '!';
	const str code = negated ? s.substr(1) : s;
	Attribute attr;
	attribute_manager->get_attr_by_code(code, attr);
	return AugmentedAttribute(attr, negated);
}

InferenceRuleManager::InferenceRuleManager(const AttributeManagerPtr attribute_manager, const str& rules_filepath)
	: attribute_manager(attribute_manager)
{
	std::ifstream ifs(rules_filepath);
	nlohmann::json js;
	ifs >> js;
	nlohmann::json ar = js["rules"];
	for (const nlohmann::json rule : ar)
	{
		//std::cout << df["name"].get<str>() << " " << df["code"].get<str>() << std::endl;
		AugmentedAttributeList lst;
		nlohmann::json precs = rule["prec"];
		if (precs.is_array())
		{
			for (const nlohmann::json prec : precs)
				lst.push_back(str_to_aug_attr(prec.get<str>()));
		}
		else
		{
			lst.push_back(str_to_aug_attr(precs.get<str>()));
		}
		lst.push_back(str_to_aug_attr(rule["cons"].get<str>()).get_negation());
		rules.push_back(InferenceRule(lst));
	}
}

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
	const uint32_t cou0 = count_classes(s0), cou1 = count_classes(s1);
	return cou0 + cou1;
}
AttributeSet InferenceRuleManager::infer_completely(const AttributeSet& attrset) const
{
	AttributeSet s2 = attrset;
	s2.infer_completely(rules);
	return s2;
}

}