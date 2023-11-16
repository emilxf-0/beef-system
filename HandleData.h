#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


class HandleData
{
public:
	HandleData() = default;

	void importFloatData(std::unordered_map<std::string, float> &data, const std::string& path);
	void importStringData(std::unordered_map<std::string, std::string> &data, const std::string& path);
	void saveData(const std::string& data, const json& jsonData);
	void loadData(const std::string& data, json& jsonData);

};
