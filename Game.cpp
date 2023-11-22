
#include "Game.h"

#include "entities/CharacterEntity.h"
#include "components/ColliderComponent.h"
#include "Map.h"
#include "components/Components.h"
#include "Collision.h"
#include "components/TimerComponent.h"
#include "entities/TrafficLightEntity.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;

SDL_Event Game::event;

float enemyPatience;
bool gotAngry = false;

const char* doucheNickName = "Some guy";
std::string doucheText;

const char* oldLadyNickName = "A sweet old lady";
std::string oldLadyText;


TraitComponent playerInfo;

float playerAnger;
float playerPatience;
float playerIntelligence;
float playerStrength;
float playerPerception;

Manager manager;

auto& trafficLight = manager.addEntity<TrafficLightEntity>(5);
auto& house(manager.addEntity());

auto& player = manager.addEntity<CharacterEntity>("assets/cars/player_car.png", 74, 600, 90, true);
auto& douche = manager.addEntity<CharacterEntity>("assets/cars/blue_car.png", 200, 64, 0, false);
auto& oldLady = manager.addEntity<CharacterEntity>("assets/cars/enemy_car.png", 710, 300, -90, false);

Game::Game() : window(nullptr)
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flag = 0;
	if(fullscreen)
	{
		flag = SDL_WINDOW_FULLSCREEN;
	}

	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);

		if(window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if(renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created!" << std::endl;
		}

		isRunning = true;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	imguiContext = ImGui::GetCurrentContext();
	ImGuiIO &io = ImGui::GetIO();
	io.Fonts->AddFontDefault();
	io.Fonts->Build();
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);

	map = new Map();

	manager.init();

	douche.getComponent<ControllerComponent>().setSpeed(1);
	oldLady.getComponent<ControllerComponent>().setSpeed(0.3f);

	doucheText = douche.getComponent<TraitComponent>().getQuirk("Normal");
	oldLadyText = oldLady.getComponent<TraitComponent>().getQuirk("Senile");


	trafficLight.getComponent<ColliderComponent>().scaleColliderUniform(10);
	trafficLight.getComponent<ColliderComponent>().debugCollider(true);

	player.getComponent<ColliderComponent>().debugCollider(true);

	house.addComponent<TransformComponent>(300, 200, 100, 100, 2);
	house.addComponent<SpriteComponent>("assets/environment/house.png");
	house.addComponent<TextBoxComponent>();

	//Set player Stats
	playerInfo = player.getComponent<TraitComponent>();
	playerAnger = playerInfo.getStats("Anger");
	playerPatience = playerInfo.getStats("Patience");
	playerIntelligence = playerInfo.getStats("Intelligence");
	playerStrength = playerInfo.getStats("Strength");
	playerPerception = playerInfo.getStats("Perception");

	player.loadEntityState("assets/entityData/entitySaveFile.json");
}


void Game::handleEvents()
{

	SDL_PollEvent(&event);

	ImGui_ImplSDL2_ProcessEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}

}


void Game::update(float deltaTime)
{
	manager.refresh();
	manager.update();

	

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider, trafficLight.getComponent<ColliderComponent>().collider))
	{
		if (trafficLight.getTrafficColor() == 1)
		{
			if (!gotAngry)
			{
				douche.getComponent<TraitComponent>().modifyTrait("Patience", -5.0f);
				enemyPatience = douche.getComponent<TraitComponent>().getStats("Patience");
				std::cout << "Enemy patience: " << enemyPatience << std::endl;
				gotAngry = true;
			}
		}
	}

	if (trafficLight.getComponent<TimerComponent>().timerDone)
	{
		player.saveEntityState("assets/entityData/entitySaveFile.json");
		trafficLight.switchToNextColor();
		douche.getComponent<TraitComponent>().modifyTrait("Patience", -5.0f);
		douche.getComponent<TraitComponent>().serializeToJSON(douche.getComponent<TraitComponent>().traitData);
	}

	

	if (playerAnger > 50)
	{
		doucheNickName = "Fucking asshole";
		doucheText = "A particularly vile piece of human excrement";
	}
	else
	{
		doucheNickName = "Some Guy";
		doucheText = "I'll suffer his existence";
	}

	if (playerPerception > 80)
	{
		oldLadyNickName = "Bag o' bones";
		oldLadyText = "Wait a minute... That bitch is senile";

		if (playerPerception > 90)
		{
			oldLadyNickName = "1000 year old psychopath";
			oldLadyText = "Oh, she's not senile. She just " + oldLady.getComponent<TraitComponent>().getQuirk("Psychopath");
		}
	}

	else
	{
		oldLadyNickName = "A sweet old lady";
		oldLadyText = "What a dearie";
	}
}


void Game::render(float interpolation)
{
	if (renderer == nullptr)
	{
			return;
	}

	ImGui::SetCurrentContext(imguiContext);
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	//Douchebag Information Window
	ImGui::SetNextWindowPos(ImVec2(douche.getComponent<TransformComponent>().position.x, douche.getComponent<TransformComponent>().position.y + 35), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(200, 100));
	ImGui::Begin(doucheNickName, nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing); // Window title
	ImGui::TextWrapped(doucheText.c_str());
	ImGui::End();

	//Old lady Information Window
	ImGui::SetNextWindowPos(ImVec2(oldLady.getComponent<TransformComponent>().position.x -140, oldLady.getComponent<TransformComponent>().position.y + 35), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(200, 100));
	ImGui::Begin(oldLadyNickName, nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing); // Window title
	ImGui::TextWrapped(oldLadyText.c_str());
	ImGui::End();

	//Player Information window
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1, 0, 0, 1));
	ImGui::SetNextWindowPos(ImVec2(player.getComponent<TransformComponent>().position.x, player.getComponent<TransformComponent>().position.y + 35), ImGuiCond_Always);

	ImGui::Begin("Player");
	ImGui::Text("I'm the player");
	ImGui::SliderFloat("Anger", &playerAnger, 0.0f, 100.0f);
	ImGui::SliderFloat("Patience", &playerPatience, 0.0f, 100.0f);
	ImGui::SliderFloat("Intelligence", &playerIntelligence, 0.0f, 100.0f);
	ImGui::SliderFloat("Strength", &playerStrength, 0.0f, 100.0f);
	ImGui::SliderFloat("Perception", &playerPerception, 0.0f, 100.0f);
	ImGui::End();

	//Set Player Traits
	player.getComponent<TraitComponent>().setTrait("Anger", playerAnger);
	player.getComponent<TraitComponent>().setTrait("Patience", playerPatience);
	player.getComponent<TraitComponent>().setTrait("Intelligence", playerIntelligence);
	player.getComponent<TraitComponent>().setTrait("Strength", playerStrength);
	player.getComponent<TraitComponent>().setTrait("Perception", playerPerception);
	player.saveEntityState("assets/entityData/playerSaveFile.json");

	
	ImGui::PopStyleColor(1);


	SDL_RenderClear(renderer);
	map->DrawMap();
	manager.draw(interpolation);
	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

