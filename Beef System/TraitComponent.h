#pragma once
#include "EntityComponentSystem.h"
#include <string>
#include <fstream>
#include <unordered_map>

class TraitComponent :
    public Component
{
struct CharacterTraits
{
	std::unordered_map<std::string, float> traits;

	CharacterTraits()
	{
		traits["Patience"] = 100.0f;
		traits["Vocabulary"] = 50.0f;
	}
};


public:

	CharacterTraits characterTraits;

	float getTrait(const std::string& traitName) const
	{
		auto trait = characterTraits.traits.find(traitName);
		if (trait != characterTraits.traits.end())
		{
			return trait->second;
		}

		return 0.0f;
	}

	void setTrait(const std::string& traitName, float value)
	{
		characterTraits.traits[traitName] = value;
	}

	void modifyTrait(const std::string& traitName, float value)
	{
		auto trait = characterTraits.traits.find(traitName);
		if (trait != characterTraits.traits.end())
		{
			characterTraits.traits[traitName] += value;
		}
	}


	void init() override
	{
		readFile("assets/traits/traits.csv");
	}

	void readFile(const char* path)
	{
		std::ifstream inputFile(path);

		if (inputFile.is_open())
		{
			std::string line;
			std::getline(inputFile, line);

			while (std::getline(inputFile, line))
			{
				std::string traitName;
				float value;

				//read CSV format
				size_t commaPos = line.find(',');
				if (commaPos != std::string::npos) {
					traitName = line.substr(0, commaPos);
					value = std::stof(line.substr(commaPos + 1));

					characterTraits.traits[traitName] = value;
				}

			}

			inputFile.close();
		}

		else
		{
			std::cerr << "Failed to open file" << std::endl;
		}
	}

};



