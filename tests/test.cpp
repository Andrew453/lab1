// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include "header.hpp"

TEST(Printing, tableTest) {
  std::stringstream ss;
  std::vector<Student> students;
  Student stdt;
  stdt.name ="TestStudent1";
  stdt.group = (int)11;
  stdt.debt = (int)2;
  stdt.avg = (float)3.12;
  students.push_back(stdt);
  stdt.name ="TestStudent2";
  stdt.group = (std::string)"12";
  stdt.debt = (std::string)"C++";
  stdt.avg = (int)5;
  students.push_back(stdt);
  bool ok = output(students,ss);
//  bool ok = output(students,std::cout);
  if (!ok) {
    std::cout << "Some problems with output table" << std::endl;
//    return 0;
  }
  ASSERT_EQ("|----------------|--------|------------|-----------|\n"
      "| name           | group  | avg        | debt      |\n"
      "|----------------|--------|------------|-----------|\n"
      "| TestStudent1   | 11     | 3.120000   | 2 items   |\n"
      "|----------------|--------|------------|-----------|\n"
      "| TestStudent2   | 12     | 5          | C++       |\n"
      "|----------------|--------|------------|-----------|\n",ss.str());
//  EXPECT_TRUE(true);
}


TEST(Printing, oneStudent) {
  std::stringstream ss;
  std::vector<Student> students;
  Student stdt;
  stdt.name ="AloneStudent";
  stdt.group = (int)0;
  stdt.debt = (int)4;
  stdt.avg = (int)5;
  students.push_back(stdt);
  bool ok = output(students,ss);
  //  bool ok = output(students,std::cout);
  if (!ok) {
    std::cout << "Some problems with output table" << std::endl;
    //    return 0;
  }
  ASSERT_EQ("|----------------|-------|-----|-----------|\n"
      "| name           | group | avg | debt      |\n"
      "|----------------|-------|-----|-----------|\n"
      "| AloneStudent   | 0     | 5   | 4 items   |\n"
      "|----------------|-------|-----|-----------|\n",ss.str());
  //  EXPECT_TRUE(true);
}


TEST(Errorhandling, Meta) {
  std::stringstream ss;
  std::pair<std::vector<Student>,std::string> pair = parse_json("../metaTest.json");
  std::vector<Student> students = pair.first;
  if (pair.second != "") {
    ss << "Incorrect reading json file." << pair.second;
  } else {
    output(students, ss);
  }
  ASSERT_EQ("Incorrect reading json file.Invalid number of students. The counter doesn't match",ss.str());
  //  EXPECT_TRUE(true);
}


TEST(Errorhandling, NameNotString) {
  std::stringstream ss;
  std::pair<std::vector<Student>,std::string> pair = parse_json("../nameTest.json");
  std::vector<Student> students = pair.first;
  if (pair.second != "") {
    ss << "Incorrect reading json file." << pair.second;
  } else {
    output(students, ss);
  }
  ASSERT_EQ("Incorrect reading json file.Incorrect name of Student:  1",ss.str());
  //  EXPECT_TRUE(true);
}

TEST(Errorhandling, DebtProccessing) {
  std::stringstream ss;
  std::pair<std::vector<Student>,std::string> pair = parse_json("../jsons/debtTest.json");
  std::vector<Student> students = pair.first;
  if (pair.second != "") {
    ss << "Incorrect reading json file. " << pair.second;
  } else {
    output(students, ss);
  }
  ASSERT_EQ("Incorrect reading json file. Incorrect debt of Student: 4",ss.str());
  //  EXPECT_TRUE(true);
}

TEST(Errorhandling, AvgProccessing) {
  std::stringstream ss;
  std::pair<std::vector<Student>,std::string> pair = parse_json("../avgTest.json");
  std::vector<Student> students = pair.first;
  if (pair.second != "") {
    ss << "Incorrect reading json file. " << pair.second;
  } else {
    output(students, ss);
  }
  ASSERT_EQ("Incorrect reading json file. Incorrect avg of Student [\"dsasd\",\"dsasads\"]",ss.str());
  //  EXPECT_TRUE(true);
}

TEST(Errorhandling, ItemsProccessing) {
  std::stringstream ss;
  std::pair<std::vector<Student>,std::string> pair = parse_json("../itemsTest.json");
  std::vector<Student> students = pair.first;
  if (pair.second != "") {
    ss << "Incorrect reading json file. " << pair.second;
  } else {
    output(students, ss);
  }
  ASSERT_EQ("Incorrect reading json file. Items is not an array!",ss.str());
  //  EXPECT_TRUE(true);
}

TEST(Errorhandling, GroupProccessing) {
  std::stringstream ss;
  std::pair<std::vector<Student>,std::string> pair = parse_json("../groupTest.json");
  std::vector<Student> students = pair.first;
  if (pair.second != "") {
    ss << "Incorrect reading json file. " << pair.second;
  } else {
    output(students, ss);
  }
  ASSERT_EQ("Incorrect reading json file. Incorrect group of Student [\"fdsfdsfssadas\"]",ss.str());
  //  EXPECT_TRUE(true);
}








