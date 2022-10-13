#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#define __cpp_lib_format
#include <format>
#include <cctype>
#include <execution>

class Database {
public:
    Database(std::string path) {
        _path = path;
        std::ifstream db(_path);
        if (db.is_open()) {
            std::string line;
            while (getline(db, line)) {
                std::string delim = "\t";
                int split = line.find('\t');
                std::string key = line.substr(0, split);
                std::string value = line.substr(split + 1, line.size());
                _map[key] = value;
            }
            return;
        }
    }
    void Insert(std::string key, std::string value) {
        _map[key] = value;
        std::transform(key.begin(), key.end(),key.begin(), ::toupper);
        _map[key] = value;
    }

    std::string Get(std::string key) {
        return _map[key];
    }

    void Save() {
        std::string contents = "";
        for (auto entry : _map) {
            contents += std::format("{}\t{}\n", entry.first, entry.second);
        }

        std::ofstream db(_path);
        if (db.is_open()) {
            db.write(contents.c_str(), contents.size());
        }
    }

    ~Database() = default;
private:
    std::string _path;
    std::unordered_map<std::string, std::string> _map;
};

int main(int argc,char** argv ) {

    Database database("sample_cpp.db");
    if (argc < 3) throw std::runtime_error("No arguments passed to program.");
    std::string arg = argv[1];
    if (arg == "set") {
        std::string key = argv[2];
        std::string value = argv[3];

        std::cout << std::format("Added new entry: The key is '{}' and the value is '{}'", key, value) << '\n';
        database.Insert(key, value);
        database.Save();
    } else if (arg == "get") {
        std::string key = argv[2];
        std::string value = database.Get(key);
        std::cout << std::format("The value of '{}' is '{}'", key, value) << '\n';
    }

    return 0;
}
