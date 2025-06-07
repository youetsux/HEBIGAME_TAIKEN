#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class CsvReaderYZ {
public:
    void Load(const std::string& path);
    bool GetParamLine(const std::string& key);

    // �l�擾�i�^�ϊ��j
    std::string PopParamStr();
    int PopParamInt();
    float PopParamFloat();
    bool PopParamBool();

    // �ꊇ�擾
    std::vector<std::string> GetParamLineAsStringArray(const std::string& key) const;

private:
    std::unordered_map<std::string, std::vector<std::string>> paramMap_;
    std::vector<std::string> currentParamLine_;
    size_t paramIndex_ = 0;
};