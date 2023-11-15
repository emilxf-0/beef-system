#pragma once
#include "EntityComponentSystem.h"
#include <string>
#include <fstream>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "ImportData.h"

using json = nlohmann::json;

class TraitComponent :
    public Component
{
struct CharacterTraits
{
	std::unordered_map<std::string, float> traits;

	CharacterTraits()
	{
		traits["Anger"] = 10.0f;
		traits["Patience"] = 90.0f;
		traits["Vocabulary"] = 50.0f;
	}

};

struct CharacterQuirks
{
	std::unordered_map<std::string, std::string> quirks;

	CharacterQuirks()
	{
		quirks["Treacherous"] = "Notoriously two-faced and will betray anyone";
	}

};


public:
	ImportData importer;
	CharacterTraits characterTraits;
	CharacterQuirks characterQuirks;
	json traitData;
	json loadedData;

	void serializeToJSON(json& data) const
	{
		data["Anger"] = getTrait("Anger");
	}

	void deserializeFromJSON(const json& data)
	{
		characterTraits.traits["Anger"] = data["Anger"];
	}

	void saveData(const std::string& data)
	{
		std::ofstream outputFile(data);
		outputFile << std::setw(4) << traitData;
		outputFile.close();
	}

	void loadData(const std::string& data)
	{
		std::ifstream inputFile(data);
		inputFile >> loadedData;
		inputFile.close();
		
	}

	TraitComponent() = default;


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
		importer.importFloatData(characterTraits.traits, "assets/traits/traits.csv");
		importer.importStringData()
		//importTraitsCSV("assets/traits/traits.csv");
	}

};
