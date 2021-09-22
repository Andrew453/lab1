// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_


#include <iostream>
#include <stdint.h>
#include <filesystem>
#include <exception>
#include <fstream>
#include <any>
// #include <boost/program_options.hpp>
#include <nlohmann/json.hpp>
#include "student.hpp"


using json = nlohmann::json;

std::string get_name(json* stt);
std::any get_group(json* stt);
std::any get_avg (json* stt);
std::any get_debt(json* stt);
std::vector<Student> parse_json(std::string path);
Lengths get_lengths(std::vector<Student> students);
bool output(const std::vector<Student>& students);

#endif // INCLUDE_HEADER_HPP_
