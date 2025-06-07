#include "NCsvReader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>

void CsvReaderYZ::Load(const std::string& path) {
    std::filesystem::path p = std::filesystem::current_path();
    std::ifstream file("Assets\\" + path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open CSV file: " + path);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        std::getline(iss, key, ',');

        std::vector<std::string> values;
        std::string token;
        while (std::getline(iss, token, ',')) {
            values.push_back(token);
        }

        paramMap_[key] = std::move(values);
    }
}

bool CsvReaderYZ::GetParamLine(const std::string& key) {
    auto it = paramMap_.find(key);
    if (it != paramMap_.end()) {
        currentParamLine_ = it->second;
        paramIndex_ = 0;
        return true;
    }
    return false;
}

std::string CsvReaderYZ::PopParamStr() {
    if (paramIndex_ >= currentParamLine_.size()) {
        throw std::out_of_range("CsvReader::PopParamStr: No more parameters to pop");
    }
    return currentParamLine_[paramIndex_++];
}

int CsvReaderYZ::PopParamInt() {
    return std::stoi(PopParamStr());
}

float CsvReaderYZ::PopParamFloat() {
    return std::stof(PopParamStr());
}

bool CsvReaderYZ::PopParamBool() {
    std::string val = PopParamStr();
    return (val == "1" || val == "true" || val == "TRUE");
}

std::vector<std::string> CsvReaderYZ::GetParamLineAsStringArray(const std::string& key) const {
    auto it = paramMap_.find(key);
    if (it != paramMap_.end()) {
        return it->second;
    }
    return {};
}