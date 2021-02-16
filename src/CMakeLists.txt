cmake_minimum_required(VERSION 3.16)

project(struct-catalogue)

add_executable(${PROJECT_NAME}
	attribute.cpp
	attribute-set.cpp
	inference-rule.cpp
	inference-rule-manager.cpp
	main.cpp
	program.cpp
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
