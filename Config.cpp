#include "Config.h"
#include <iostream>
#include <fstream>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

Config* Config::instance = nullptr;

Config::Config() {
    projectRoot = findProjectRoot();
    if (projectRoot.empty()) {
        // По умолчанию - текущая директория
        projectRoot = ".";
    }
    std::cout << "Project root set to: " << projectRoot << std::endl;
}

Config& Config::getInstance() {
    if (instance == nullptr) {
        instance = new Config();
    }
    return *instance;
}

std::string Config::findProjectRoot() {
    // Попробуем найти папку с картинками
    std::vector<std::string> possiblePaths = {
        ".",
        "..",
        "../..",
        "../../..",
        "Graphproject",
        "../Graphproject",
        "../../Graphproject"
    };
    
    for (const auto& path : possiblePaths) {
        std::string testPath = path + "/Pictures/Земля.png";
        std::ifstream file(testPath);
        if (file.good()) {
            file.close();
            return std::filesystem::absolute(path).string();
        }
    }
    
    return "";  // Не нашли
}

void Config::setProjectRoot(const std::string& root) {
    projectRoot = root;
    if (!projectRoot.empty() && projectRoot.back() != '/' && projectRoot.back() != '\\') {
        projectRoot += "/";
    }
}

std::string Config::getPicturePath(const std::string& filename) {
    return projectRoot + "/Pictures/" + filename;
}

std::string Config::getMusicPath(const std::string& filename) {
    return projectRoot + "/Music/" + filename;
}

std::string Config::getAbsolutePath(const std::string& relativePath) {
    return projectRoot + "/" + relativePath;
}

bool Config::fileExists(const std::string& path) {
    std::ifstream file(path);
    return file.good();
}