
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
const char* enemyNickName = "Some guy";

float playerAnger;

Manager manager;

auto& wall(manager.addEntity());
auto& trafficLight = manager.addEntity<TrafficLightEntity>(5);
auto& house(manager.addEntity());

auto& player = manager.addEntity<CharacterEntity>("assets/cars/player_car.png", 74, 600, true);
auto& enemy = manager.addEntity<CharacterEntity>("assets/cars/enemy_car.png", 200, 64, false);
auto& enemy1 = manager.addEntity<CharacterEntity>("assets/cars/enemy_car.png", 260, 64, false);
auto& enemy2 = manager.addEntity<CharacterEntity>("assets/cars/enemy_car.png", 320, 64, false);
auto& enemy3= manager.addEntity<CharacterEntity>("assets/cars/enemy_car.png", 380, 64, false);
auto& enemy4 = manager.addEntity<CharacterEntity>("assets/cars/enemy_car.png", 440, 64, false);


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

	enemyPatience = enemy.getComponent<TraitComponent>().getTrait("Anger");


	trafficLight.getComponent<ColliderComponent>().scaleColliderUniform(10);
	trafficLight.getComponent<ColliderComponent>().debugCollider(true);

	player.getComponent<ColliderComponent>().debugCollider(true);

	enemy.getComponent<TraitComponent>().serializeToJSON(enemy.getComponent<TraitComponent>().traitData);
    enemy.getComponent<TraitComponent>().saveData("assets/traits/traitsData.json");
    enemy.getComponent<TraitComponent>().loadData("assets/traits/traitsData.json");
	enemy.getComponent<TraitComponent>().deserializeFromJSON(enemy.getComponent<TraitComponent>().loadedData);

	house.addComponent<TransformComponent>(300, 200, 100, 100, 2);
	house.addComponent<SpriteComponent>("assets/environment/house.png");
	house.addComponent<TextBoxComponent>(imguiContext);

	enemyPatience = enemy.getComponent<TraitComponent>().getTrait("Anger");

	playerAnger = player.getComponent<TraitComponent>().getTrait("Anger");

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

	playerAnger = player.getComponent<TraitComponent>().getTrait("Anger");

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider, trafficLight.getComponent<ColliderComponent>().collider))
	{
		if (trafficLight.getTrafficColor() == 1)
		{
			if (!gotAngry)
			{
				enemy.getComponent<TraitComponent>().modifyTrait("Patience", -5.0f);
				enemyPatience = enemy.getComponent<TraitComponent>().getTrait("Patience");
				std::cout << "Enemy patience: " << enemyPatience << std::endl;
				gotAngry = true;
			}
		}
	}
	if (gotAngry)
		std::cout << "Hey fuck you guy!" << std::endl;

	if (trafficLight.getComponent<TimerComponent>().timerDone)
	{
		player.saveEntityState("assets/entityData/entitySaveFile.json");
		trafficLight.switchToNextColor();
		enemy.getComponent<TraitComponent>().modifyTrait("Patience", -5.0f);
		enemy.getComponent<TraitComponent>().serializeToJSON(enemy.getComponent<TraitComponent>().traitData);
	}

	if (playerAnger < 50)
	{
		enemyNickName = "Fucking asshole";
	}
	else
	{
		enemyNickName = "Some Guy";
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

	ImGui::SetNextWindowPos(ImVec2(enemy.getComponent<TransformComponent>().position.x, enemy.getComponent<TransformComponent>().position.y + 35), ImGuiCond_Always);

	// ImGui content
	ImGui::Begin(enemyNickName, nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing); // Window title

	// Add ImGui content here
	ImGui::Text(enemy.getComponent<TraitComponent>().characterQuirks.quirks["Treacherous"].c_str());

	ImGui::End();

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1, 0, 0, 1));


	ImGui::SetNextWindowPos(ImVec2(player.getComponent<TransformComponent>().position.x, player.getComponent<TransformComponent>().position.y + 35), ImGuiCond_Always);

	ImGui::Begin("Player");
	ImGui::Text("I'm the player");
	ImGui::SliderFloat("Anger", &playerAnger, 0.0f, 100.0f);
	ImGui::End();
	player.getComponent<TraitComponent>().setTrait("Anger", playerAnger);
	player.saveEntityState("assets/entityData/playerSaveFile.json");

	
	ImGui::PopStyleColor(1);

	// Render ImGui content for TextBoxComponent



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

