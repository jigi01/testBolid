#include <gtest/gtest.h>
#include "../include/utils.hpp"
#include <filesystem>
#include <fstream>

TEST(UtilsTest, SanitizeFilename) {
    EXPECT_EQ(utils::sanitize_filename("valid_name.txt"), "valid_name.txt");
    EXPECT_EQ(utils::sanitize_filename("invalid/name.txt"), "invalid_name.txt");
    EXPECT_EQ(utils::sanitize_filename("inva*lid?.txt"), "inva_lid_.txt");
    EXPECT_EQ(utils::sanitize_filename("sp ace.txt"), "sp_ace.txt");
}

TEST(UtilsTest, ReadUrlsFromFile) {
    auto current_path = std::filesystem::current_path();
    std::cout << "Current working directory: " << current_path << std::endl;

    std::string test_file = (current_path / "test_urls.txt").string();
    std::ofstream file(test_file);
    ASSERT_TRUE(file.is_open()) << "Failed to create test file at " << test_file;
    file << "https://bolid.ru/favicon.ico\nhttps://bolid.ru/bld/images/logo.png\n";
    file.close();

    auto urls = utils::read_urls_from_file(test_file);
    EXPECT_EQ(urls.size(), 2);
    EXPECT_EQ(urls[0], "https://bolid.ru/favicon.ico");
    EXPECT_EQ(urls[1], "https://bolid.ru/bld/images/logo.png");

    std::filesystem::remove(test_file);
}

TEST(UtilsTest, EnsureDirectoryExists) {
    std::string test_dir = "test_dir";
    utils::ensure_directory_exists(test_dir);
    EXPECT_TRUE(std::filesystem::exists(test_dir));
    EXPECT_TRUE(std::filesystem::is_directory(test_dir));

    std::filesystem::remove_all(test_dir);
}
