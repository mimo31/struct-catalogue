/**
 * program.hpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/2/16
 */
#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "attribute.hpp"
#include "inference-rule-manager.hpp"

namespace strcata
{

class Program
{
	AttributeManagerPtr attr_manager;
	InferenceRuleManagerPtr rule_manager;

	uint32_t n;

	void print_attribute_set(const AttributeSet& attrset, const bool include_unknowns) const;

public:
	void run();
};

}

#endif // PROGRAM_HPP