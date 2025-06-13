#include <filesystem>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

/**
 * @brief 更新数据
 * @param srcFolder 新周期
 * @param dstFolder 旧周期
 * @return 更新文件数量
 */
inline int moveFiles (const fs::path &srcFolder, const fs::path &dstFolder) {
    int copiedCount = 0;
    if (!fs::exists(dstFolder)) {
        fs::create_directories(dstFolder);
    }
    for (const auto &entry : fs::directory_iterator(srcFolder)) {
        if (entry.is_regular_file()) {
            const auto &srcFile = entry.path();
            auto dstFile = dstFolder / srcFile.filename();
            bool needCopy = true;
            if (fs::exists(dstFile)) {
                std::ifstream f1(srcFile, std::ios::binary);
                std::ifstream f2(dstFile, std::ios::binary);
                if (f1.is_open() && f2.is_open()) {
                    std::string line;
                    for (int i = 0; i < 3; ++i) {
                        std::getline(f1, line);
                        std::getline(f2, line);
                    }
                    if (std::equal(
                        std::istreambuf_iterator<char>(f1), std::istreambuf_iterator<char>(),
                        std::istreambuf_iterator<char>(f2), std::istreambuf_iterator<char>())) {
                        needCopy = false;
                    }
                }
            }
            if (needCopy) {
                try {
                    if (fs::exists(dstFile)) {
                        fs::remove(dstFile);
                    }
                    fs::copy_file(srcFile, dstFile);
                    ++copiedCount;
                }
                catch (const fs::filesystem_error &e) {
                    std::cerr << entry.path().string();
                    continue;
                }
            }
        }
    }
    return copiedCount;
}

int main () {
    fs::path srcFolder = R"(.)";
    fs::path dstFolder = R"(.)";
    int count = moveFiles(srcFolder, dstFolder);
    std::cout << "update: " << count << std::endl;
}
