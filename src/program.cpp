/**
 * program.cpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/2/16
 */
#include "program.hpp"

#include <iostream>

#include "attribute-set.hpp"

namespace strcata
{

void Program::print_attribute_set(const AttributeSet& attrset, const bool include_unknowns) const
{
	std::cout << "TRUE:";
	for (uint32_t i = 0; i < attrset.attributes.size(); i++)
	{
		if (attrset.attributes[i] == AttributeTruthValue::TRUE)
		{
			std::cout << " " << attr_manager->get_attr_code(Attribute(i));
		}
	}
	std::cout << std::endl;
	std::cout << "FALSE:";
	for (uint32_t i = 0; i < attrset.attributes.size(); i++)
	{
		if (attrset.attributes[i] == AttributeTruthValue::FALSE)
		{
			std::cout << " " << attr_manager->get_attr_code(Attribute(i));
		}
	}
	std::cout << std::endl;
	if (include_unknowns)
	{
		std::cout << "UNKNOWN:";
		for (uint32_t i = 0; i < attrset.attributes.size(); i++)
		{
			if (attrset.attributes[i] == AttributeTruthValue::UNKNOWN)
			{
				std::cout << " " << attr_manager->get_attr_code(Attribute(i));
			}
		}
		std::cout << std::endl;
	}
}

void Program::run()
{
	attr_manager = std::make_shared<AttributeManager>("../../data/defs.json");
	rule_manager = std::make_shared<InferenceRuleManager>(attr_manager, "../../data/rules.json");
	n = attr_manager->get_attribute_count();

	AugmentedAttribute aug_attr;
	attr_manager->get_aug_attr_by_str("!nzr", aug_attr);
	AttributeSet attrset(n, AugmentedAttributeList{ aug_attr });
	std::cout << "initial" << std::endl;
	print_attribute_set(attrset, false);
	std::cout << std::endl;

	const AttributeSet inferred = rule_manager->infer_completely(attrset);
	std::cout << "inferred" << std::endl;
	print_attribute_set(inferred, true);
	std::cout << std::endl;
	
	std::cout << rule_manager->count_classes() << std::endl;
}

}