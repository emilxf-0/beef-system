#pragma once
#include "EntityComponentSystem.h"
#include <string>
#include <fstream>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "data/HandleData.h"

using json = nlohmann::json;

class TraitComponent :
    public Component
{
struct CharacterStats
{
	std::unordered_map<std::string, float> stats;

	CharacterStats()
	{
		stats["Anger"] = 10.0f;
		stats["Patience"] = 90.0f;
		stats["Vocabulary"] = 50.0f;
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

struct CharacterTraits
{
	std::unordered_map<std::string, std::string> traits;

	CharacterTraits() = default;
};


public:
	HandleData importer;
	CharacterStats characterStats;
	CharacterTraits characterTraits;
	CharacterQuirks characterQuirks;

	json traitData;
	json loadedData;

	void serializeToJSON(json& data) const
	{
		data["Anger"] = getStats("Anger");
	}

	void deserializeFromJSON(const json& data)
	{
		characterStats.stats["Anger"] = data["Anger"];
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



	float getStats(const std::string& traitName) const
	{
		auto stat = characterStats.stats.find(traitName);
		if (stat != characterStats.stats.end())
		{
			return stat->second;
		}

		return 50.0f;
	}

	std::string getTrait(const std::string& traitName) const
	{
		auto trait = characterTraits.traits.find(traitName);
		if (trait != characterTraits.traits.end())
		{
			return trait->second;
		}

		return "Sort of blank and dead inside";
	}

	std::string getQuirk(const std::string& traitName) const
	{
		auto quirk = characterQuirks.quirks.find(traitName);
		if (quirk != characterQuirks.quirks.end())
		{
			return quirk->second;
		}

		return "Just a regular citizen";
	}

	void setTrait(const std::string& traitName, float value)
	{
		characterStats.stats[traitName] = value;
	}

	void modifyTrait(const std::string& traitName, float value)
	{
		auto trait = characterStats.stats.find(traitName);
		if (trait != characterStats.stats.end())
		{
			characterStats.stats[traitName] += value;
		}
	}

	void init() override
	{
		loadStats("assets/stats/stats.csv");
		loadTraits("assets/traits/traits.csv");
		loadQuirks("assets/quirks/quirks.csv");
	}

	void loadStats(const std::string& path)
	{
		importer.importFloatData(characterStats.stats, path);
	}

	void loadTraits(const std::string& path)
	{
		importer.importStringData(characterTraits.traits, path);
	}

	void loadQuirks(const std::string& path)
	{
		importer.importStringData(characterQuirks.quirks, path);
	}

};
