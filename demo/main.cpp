#include <header.hpp>

using json = nlohmann::json;



int main(int argc, char* argv[]) {
  if (argc <= 1) {
    std::cout << "Invalid input. Cannot find path to JSON file" << std::endl;
    return 0;
  }
  std::string fp = (std::string)argv[1];

  std::ifstream ifs(argv[1]);
  if (!ifs) {
    throw std::runtime_error{"Can't find json file"};
  }
  json jf = json::parse(ifs);

  std::pair<std::vector<Student>,std::string> pair = parse_json(jf);
  std::vector<Student> students = pair.first;
  if (pair.second != "") {
    std::cout << "Incorrect reading json file. " << pair.second;
    return 0;
  }
  bool ok = output(students,std::cout);
  if (!ok) {
    std::cout << "Some problems with output table" << std::endl;
    return 0;
  }
  return 0;
}