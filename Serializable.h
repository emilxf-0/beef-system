#pragma once

class Serializable
{
public:
	virtual void serializeToJSON(json& data) = 0;
	virtual void deserializeFromJSON(json& data) = 0;
	virtual ~Serializable() = default;
};
