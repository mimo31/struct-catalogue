/**
 * main.cpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/2/16
 */
#include <cstdlib>
#include <iostream>

#include "attribute.hpp"
#include "inference-rule-manager.hpp"

namespace strcata
{

void run()
{
	const AttributeManagerPtr attr_manager = std::make_shared<AttributeManager>("../../data/defs.json");
	const InferenceRuleManagerPtr rule_manager = std::make_shared<InferenceRuleManager>(attr_manager, "../../data/rules.json");
	std::cout << rule_manager->count_classes() << std::endl;
}

}

int main()
{
	strcata::run();
	return EXIT_SUCCESS;
}