#pragma once
#include "../EntityComponentSystem.h"
#include "Components.h"
#include "imgui_internal.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

class TextBoxComponent : public Component
{
private:
	ImGuiContext* imguiContext;

public:

	TextBoxComponent() = default;

	TextBoxComponent(ImGuiContext* imguiContext) : imguiContext(imguiContext) {}

	void draw(float interpolation) override
	{

		ImGui::SetNextWindowPos(ImVec2(entity->getComponent<TransformComponent>().position.x, entity->getComponent<TransformComponent>().position.y + 35), ImGuiCond_Always);

		// ImGui content
		ImGui::Begin("Some hole"); // Window title

		// Add ImGui content here
		ImGui::Text("I'm a house!");

		ImGui::End();
	}
};