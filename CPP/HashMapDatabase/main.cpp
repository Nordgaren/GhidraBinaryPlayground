#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

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
                std::string value = line.substr(split, line.size());
                _map.emplace(key, value);
            }
            return;
        }
    }
    void Insert(std::string key, std::string value) {
        _map.emplace(key, value);
    }

    std::string Get(std::string key) {
        return _map[key];
    }

    void Save(){

    }

    ~Database() = default;
private:
    std::string _path;
    std::unordered_map<std::string, std::string> _map;
};

int main() {
    Database database("sample_cpp.db");
    return 0;
}
