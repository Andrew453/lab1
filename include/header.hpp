// Copyright 2020 Andrew Prokushev <senior.prockuschev2017@yandex.ru>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <stdint.h>

#include <any>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>

#include <utility>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "student.hpp"

#define STUDENT_PAIR std::vector<Student>, std::string

using json = nlohmann::json;

std::string get_name(json* stt);

std::any get_group(json* stt);

std::any get_avg(json* stt);

std::any get_debt(json* stt);

std::pair<STUDENT_PAIR> parse_json(const json & jf);

Lengths get_lengths(std::vector<Student> students);

bool output(const std::vector<Student>& students, std::ostream& os);

#endif  // INCLUDE_HEADER_HPP_
