#pragma once
#include "EntityComponentSystem.h"
#include <string>
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

};

