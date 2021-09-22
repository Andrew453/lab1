#include <any>

#include "../include/header.hpp"
//#include "../include/student.hpp"
using json = nlohmann::json;


std::string get_name(json* stt) {
  std::string name;
  if (stt->at("name").is_string()) {
    name = (std::string)stt->at("name");
  }

  return name;
}

std::any get_group(json* stt) {
  std::any group;
  if (stt->at("group").is_string()) {
    group = (std::string)stt->at("group");
  }

  if (stt->at("group").is_number_integer()) {
    group = (int)stt->at("group");
  }

  return group;
}


std::any get_avg (json* stt) {
  std::any avg;
  if (stt->at("avg").is_number_integer()) {
    avg = (int)stt->at("avg");
  }

  if (stt->at("avg").is_string()) {
    avg = (std::string)stt->at("avg");
  }

  if (stt->at("avg").is_number_float()) {
    avg = (float)stt->at("avg");
  }

  return avg;
}

std::any get_debt(json* stt) {
  std::any debt;
  if (stt->at("debt").is_string()) {
    debt = (std::string)stt->at("debt");
  }

  if (stt->at("debt").is_null()) {
    debt = (std::string)"null";
  }

  if (stt->at("debt").is_array()) {
    debt = (int)stt->at("debt").size();
  }

  return debt;
}


std::vector<Student> parse_json(std::string path) {
  std::ifstream ifs(path);
  if (!ifs) {
    throw std::runtime_error{"Can't find json file"};
  }
  json jf = json::parse(ifs);
  if(!jf.at("items").is_array()) {
    std::cout<< "Items is not an array!" << std::endl;
    return std::vector<Student>{};
  }
  if (jf.at("items").size() != jf.at("_meta").at("count")) {
    std::cout << "Invalid number of students. The counter doesn't match "
              << std::endl;
    return std::vector<Student>{};
  }
  std::vector<Student> students;
  for (auto& el : jf.at("items").items()) {
    json stt = el.value();
    Student student;
    // NAME-----------------------------------------
    student.name = get_name(&stt);
    if (student.name == "") {
      std::cout << "Incorrect name of Student:  " << stt.at("name") << std::endl;
      return std::vector<Student>{};
    }
    //----------------------------------------------

    // GROUP----------------------------------------
    student.group = get_group(&stt);
    if (!student.group.has_value()) {
      std::cout << "Incorrect group of Student " << stt.at("group") << std::endl;
      return std::vector<Student>{};
    }
    //    if (stt.at("group").is_number_float()) {
    //      student.group = (float)stt.at("group");
    //    }
    //----------------------------------------------

    // AVG------------------------------------------
    student.avg = get_avg(&stt);
    if (!student.avg.has_value()) {
      std::cout << "Incorrect avg of Student " << stt.at("avg") << std::endl;
      return std::vector<Student>{};
    }
    //----------------------------------------------

    // DEBT-----------------------------------------
    student.debt = get_debt(&stt);
    if (!student.debt.has_value()) {
      std::cout << "Incorrect debt of Student " << stt.at("debt") << std::endl;
      return std::vector<Student>{};
    }
    //----------------------------------------------
    //    students[counter] = student;
    //    counter++;
    students.push_back(student);
  }
  return students;
}

Lengths get_lengths(std::vector<Student> students) {
  Lengths ls{0,0,0,0};
  for (Student student1: students) {
    if ((int)student1.name.length() > ls.name) {
      ls.name = (int)student1.name.length();
    }

    if (student1.group.type() == typeid(int)) {
      std::string strgroup = std::to_string(std::any_cast<int>(student1.group));

      if ((int)strgroup.length() > ls.group) {
        ls.group = (int)strgroup.length();
      }
    } else if (student1.group.type() == typeid(std::string)) {
      //      std::cout << (int)std::any_cast<std::string>(student1.group).length() << "  " << std::any_cast<std::string>(student1.group) << std::endl;
      if ((int)std::any_cast<std::string>(student1.group).length() > ls.group) {
        ls.group = (int)std::any_cast<std::string>(student1.group).length();
      }
    } else
      return Lengths{};

    if (student1.avg.type() == typeid(int)) {
      std::string stravg = std::to_string(std::any_cast<int>(student1.avg));
      if((int)stravg.length() > ls.avg) {
        ls.avg = (int)stravg.length();
      }
    }
    else if (student1.avg.type() == typeid(std::string)) {
      if ((int)std::any_cast<std::string>(student1.avg).length() > ls.avg) {
        ls.avg = (int)std::any_cast<std::string>(student1.avg).length();
      }
    } else if (student1.avg.type() == typeid(float)) {
      std::string stravg = std::to_string(std::any_cast<float>(student1.avg));
      if ((int)stravg.length() > ls.avg) {
        ls.avg = (int)stravg.length();
      }
    } else
      return Lengths{};

    if (student1.debt.type() == typeid(std::string)) {
      if ((int)std::any_cast<std::string>(student1.debt).length() > ls.debt) {
        ls.debt = (int)std::any_cast<std::string>(student1.debt).length();
      }
    }
    else if (student1.debt.type() == typeid(int)) {
      std::string strdebt = std::to_string(std::any_cast<int>(student1.debt));
      if ((int)strdebt.length() + 6 > ls.debt) {
        ls.debt = (int)strdebt.length() + 6;
      }
    }
    else
      return Lengths{};

  }
  return  ls;
}

bool output(const std::vector<Student>& students) {
  std::string s="-";
  char dash;
  dash =s[0];
  std::string s2=" ";
  char space;
  space=s2[0];

  std::cout.fill(dash);
  std::cout.setf(std::ios::left);
  Lengths ls = get_lengths(students);
  std::cout << std::setw(ls.name + 5) << "|" << std::setw(ls.group + 7) << "|" << std::setw(ls.avg + 5) << "|" << std::setw(ls.debt + 5) << "|";
  std::cout<<"|" << std::endl;
  std::cout.fill(space);
  std::cout << std::setw(ls.name + 5) << "| name" << std::setw(ls.group + 7) << "| group" << std::setw(ls.avg + 5) << "| avg" << std::setw(ls.debt + 5) << "| debt";
  std::cout<<"|" << std::endl;
  //  std::cout << "|" << std::left << "name" <<  std::setw(ls.name + 5 -2 - 4) << "|" << std::left << "group" << std::setw(ls.group-2) << "|" << std::left << ""
  for (Student student : students) {

    std::cout.fill(dash);
    std::cout << std::setw(ls.name + 5) << "|" << std::setw(ls.group + 7) << "|" << std::setw(ls.avg + 5) << "|" << std::setw(ls.debt + 5) << "|";
    std::cout<<"|" << std::endl;
    std::cout.fill(space);
    std::string nametable = "| " + student.name;
    //    std::cout << "| ";
    std::cout << std::setw(ls.name + 5)  << nametable;

    if (student.group.type() == typeid(int)) {
      std::string grouptable = "| " + std::to_string(std::any_cast<int>(student.group));
      //      std::cout << "| ";
      std::cout << std::setw(ls.group + 7)
                <<  grouptable;
    }
    else if (student.group.type() == typeid(std::string)) {
      std::string grouptable = "| " + std::any_cast<std::string>(student.group);
      //      std::cout << "| " ;
      std::cout << std::setw(ls.group + 7)
                << grouptable;
    }else
      return false;

    if (student.avg.type() == typeid(int)) {
      std::string avgtable = "| " + std::to_string(std::any_cast<int>(student.avg));
      //      std::cout << "| ";
      std::cout << std::setw(ls.avg + 5) << avgtable;
    }else if (student.avg.type() == typeid(std::string)) {
      std::string avgtable = "| " + std::any_cast<std::string>(student.avg);
      //      std::cout << "| ";
      std::cout << std::setw(ls.avg + 5)
                << avgtable;
    }else if (student.avg.type() == typeid(float)) {
      std::string avgtable = "| " + std::to_string(std::any_cast<float>(student.avg));
      std::cout << std::setw(ls.avg + 5)
                << avgtable;
    }else
      return false;

    if (student.debt.type() == typeid(std::string)) {
      std::string debttable = "| " + std::any_cast<std::string>(student.debt);
      //      std::cout << "| ";
      std::cout << std::setw(ls.debt + 5)
                << debttable;
    }else if (student.debt.type() == typeid(int)) {
      std::string debttable = "| " + std::to_string(std::any_cast<int>(student.debt)) + " items";
      //      std::cout << "| ";
      std::cout << std::setw(ls.debt + 5)
                << debttable;
    }else
      return false;
    std::cout << "|"<< std::endl;
  }
  std::cout.fill(dash);
  std::cout << std::setw(ls.name + 5) << "|" << std::setw(ls.group + 7) << "|" << std::setw(ls.avg + 5) << "|" << std::setw(ls.debt + 5) << "|";
  std::cout<<"|" << std::endl;
  return true;
}

