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
			{
				AugmentedAttribute attr;
				attribute_manager->get_aug_attr_by_str(prec.get<str>(), attr);
				lst.push_back(attr);
			}
		}
		else
		{
			AugmentedAttribute attr;
			attribute_manager->get_aug_attr_by_str(precs.get<str>(), attr);
			lst.push_back(attr);
		}
		AugmentedAttribute attr;
		attribute_manager->get_aug_attr_by_str(rule["cons"].get<str>(), attr);
		lst.push_back(attr.get_negation());
		rules.push_back(InferenceRule(lst));
	}
}

uint32_t InferenceRuleManager::count_classes() const
{
	return count_classes(AttributeSet(attribute_manager->get_attribute_count()));
}

void InferenceRuleManager::print_classes() const
{
	return print_classes(AttributeSet(attribute_manager->get_attribute_count()));
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

void InferenceRuleManager::print_classes(AttributeSet attrset) const
{
	attrset.infer_completely(rules);
	if (attrset.contradicted)
		return;
	AttributeSet s0, s1;
	if (!attrset.disect(s0, s1))
	{
		for (uint32_t i = 0; i < attrset.attributes.size(); i++)
		{
			const bool negated = attrset.attributes[i] == AttributeTruthValue::FALSE;
			std::cout << " " << (negated ? "!" : "") << attribute_manager->get_attr_code(i);
		}
		std::cout << std::endl;
	}
	else
	{
		print_classes(s0);
		print_classes(s1);
	}
}

AttributeSet InferenceRuleManager::infer_completely(const AttributeSet& attrset) const
{
	AttributeSet s2 = attrset;
	s2.infer_completely(rules);
	return s2;
}

}