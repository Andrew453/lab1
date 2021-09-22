#include <header.hpp>

using json = nlohmann::json;



int main(int argc, char* argv[]) {
  if (argc <= 1) {
    std::cout << "Invalid input. Cannot find path to JSON file" << std::endl;
    return 0;
  }
  std::string fp = (std::string)argv[1];
  std::vector<Student> students = parse_json(fp);
  if (students.empty()) {
    std::cout << "Incorrect reading json file. There are in file problems with "
                 "types of fields";
    return 0;
  }
  bool ok = output(students);
  if (!ok) {
    std::cout << "Some problems with output table" << std::endl;
    return 0;
  }
  //  bool ok = output(students);
  return 0;
}