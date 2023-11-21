#include "HandleData.h"

#include <iomanip>


void HandleData::importStringData(std::unordered_map<std::string, std::string> &data, const std::string& path)
{
	std::ifstream inputFile(path);

	if (inputFile.is_open())
	{
		std::string line;
		std::getline(inputFile, line);

		while (std::getline(inputFile, line))
		{
			std::string key;
			std::string value;

			//read CSV format
			size_t commaPos = line.find(',');
			if (commaPos < line.length()) {
				key = line.substr(0, commaPos);
				value = line.substr(commaPos + 1);

				data[key] = value;
			}

		}

		inputFile.close();
	}

	else
	{
		std::cerr << "Failed to open file" << std::endl;
	}
}

void HandleData::importFloatData(std::unordered_map<std::string, float> &data, const std::string& path)
{
	std::ifstream inputFile(path);

	if (inputFile.is_open())
	{
		std::string line;
		std::getline(inputFile, line);

		while (std::getline(inputFile, line))
		{
			std::string key;
			float value;

			//read CSV format
			size_t commaPos = line.find(',');
			if (commaPos != std::string::npos) {
				key = line.substr(0, commaPos);
				value = std::stof(line.substr(commaPos + 1));

				data[key] = value;
			}

		}

		inputFile.close();
	}

	else
	{
		std::cerr << "Failed to open file" << std::endl;
	}
}

void HandleData::saveData(const std::string &data, const json& jsonData)
{
	std::ofstream outputFile(data);
	outputFile << std::setw(4) << jsonData;
	outputFile.close();
}

void HandleData::loadData(const std::string& data, json& jsonData)
{
	std::ifstream inputFile(data);
	inputFile >> jsonData;
	inputFile.close();
}
