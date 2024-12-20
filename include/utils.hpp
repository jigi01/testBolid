#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <regex>
#include <stdexcept>

namespace utils {

inline void ensure_directory_exists(const std::string& path) {
    namespace fs = std::filesystem;
    if (!fs::exists(path)) {
        if (!fs::create_directories(path)) {
            throw std::runtime_error("Failed to create directory: " + path);
        }
    }
}

inline std::string sanitize_filename(const std::string& filename) {
    std::string sanitized = filename;
    std::replace(sanitized.begin(), sanitized.end(), ' ', '_');
    for (char& c : sanitized) {
        if (c == '/' || c == '\\' || c == '*' || c == '?' || c == ':' || c == '"' || c == '<' || c == '>' || c == '|') {
            c = '_';
        }
    }
    return sanitized;
}

inline std::vector<std::string> read_urls_from_file(const std::string& file_path) {
    std::ifstream infile(file_path);
    if (!infile.is_open()) {
        throw std::runtime_error("Failed to open file: " + file_path);
    }

    std::vector<std::string> urls;
    std::string line;
    while (std::getline(infile, line)) {
        if (!line.empty()) {
            urls.push_back(line);
        }
    }
    infile.close();
    return urls;
}

} 

#endif 
