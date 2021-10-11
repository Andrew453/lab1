// Copyright 2020 Andrew Prokushev <senior.prockuschev2017@yandex.ru>

#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#endif  // INCLUDE_STUDENT_HPP_


#include <string>
#include "header.hpp"

struct Student : public std::_Resetiosflags {
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};

struct Lengths {
  int name;   // Максимальная длина слова в name
  int group;  //
  int avg;    //
  int debt;   //
};
