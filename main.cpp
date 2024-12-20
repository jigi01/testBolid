#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <filesystem>
#include <fstream>
#include <cpr/cpr.h>
#include <spdlog/spdlog.h>
#include "utils.hpp"

namespace fs = std::filesystem;

std::mutex log_mutex;

void download_file(const std::string& url, const std::string& output_dir) {
    spdlog::info("Starting download: {}", url);

    auto response = cpr::Get(cpr::Url{url});
    if (response.status_code != 200) {
        spdlog::error("Failed to download {}: HTTP {}", url, response.status_code);
        return;
    }

    std::string filename;
    auto content_disposition = response.header["Content-Disposition"];
    if (!content_disposition.empty() && content_disposition.find("attachment") != std::string::npos) {
        auto filename_pos = content_disposition.find("filename=");
        if (filename_pos != std::string::npos) {
            filename_pos += 9;
            auto end_pos = content_disposition.find('"', filename_pos);
            if (end_pos != std::string::npos) {
                filename = utils::sanitize_filename(content_disposition.substr(filename_pos, end_pos - filename_pos));
            } else {
                filename = utils::sanitize_filename(content_disposition.substr(filename_pos));
            }
        }
    }

    if (filename.empty()) {
        auto pos = url.find_last_of('/');
        filename = utils::sanitize_filename(url.substr(pos + 1));
    }

    fs::path file_path = fs::path(output_dir) / filename;
    int counter = 1;
    while (fs::exists(file_path)) {
        file_path = fs::path(output_dir) / (filename + "(" + std::to_string(counter++) + ")");
    }

    std::ofstream file(file_path, std::ios::binary);
    if (file.is_open()) {
        file << response.text;
        file.close();
        spdlog::info("Completed download: {}", file_path.string());
    } else {
        spdlog::error("Failed to save file: {}", file_path.string());
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        spdlog::error("Usage: {} <url_file> <output_dir> <parallel_count>", argv[0]);
        return 1;
    }

    std::string url_file = argv[1];
    std::string output_dir = argv[2];
    int parallel_count = std::stoi(argv[3]);

    spdlog::info("Program started");
    spdlog::info("URL file: {}, Output dir: {}, Parallel count: {}", url_file, output_dir, parallel_count);

    try {
        utils::ensure_directory_exists(output_dir);

        auto urls = utils::read_urls_from_file(url_file);
        spdlog::info("Loaded {} URLs", urls.size());

        std::vector<std::thread> threads;
        for (size_t i = 0; i < urls.size(); i += parallel_count) {
            for (size_t j = i; j < i + parallel_count && j < urls.size(); ++j) {
                threads.emplace_back(download_file, urls[j], output_dir);
            }

            for (auto& t : threads) {
                if (t.joinable()) {
                    t.join();
                }
            }
            threads.clear();
        }
    } catch (const std::exception& e) {
        spdlog::error("Error: {}", e.what());
        return 1;
    }

    spdlog::info("Program finished");
    return 0;
}