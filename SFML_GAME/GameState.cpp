#include"stdafx.h"
#include"GameState.h"
#include "Bullet.h"




//Initializer functions

void GameState::initDefferedRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(
		0,
		0,
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height));
}

void GameState::initbackground()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//BackGround
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)));

	this->backgroundTexture.loadFromFile("Resources/Images/background/forest1.png");


	this->background.setTexture(&this->backgroundTexture);
}

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<int>(this->stateData->gfxSettings->resolution.width),
			static_cast<int>(this->stateData->gfxSettings->resolution.height)

		)
	);

	this->view.setCenter(
		sf::Vector2f(
			static_cast<int>(this->stateData->gfxSettings->resolution.width) / 2.f,
			static_cast<int>(this->stateData->gfxSettings->resolution.height) / 2.f

		)
	);
}


void GameState::initKeybinds()
{
	std::ifstream ifs;

	ifs.open("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{

		std::string key = "";
		std::string key2 = "";


		while (ifs >> key >> key2)
		{

			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Petchlamoon-Regular.ttf"))
	{
		throw("Error to upload Fonts!!");
	}
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprite/Player/wizard3.png"))
	{
		throw("Error Game State could not load player idle textures");
	}

	if (this->textures["PINK_FAIRY"].loadFromFile("Resources/Images/Sprite/Enemy/pink_fairy.png"))
	{
		std::cout << "NOT ERROR FOR LOAT PINK FAIRY" << "\n";
	}
	
		
	
}

void GameState::initPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calCharSize(vm), "Quit");
}

void GameState::initShader()
{
	this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag");
}

void GameState::initPlayers()
{
	this->player = new Player(550, 2600, this->textures["PLAYER_SHEET"]);
	//this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

void GameState::initPlayerGui()
{
	this->playerGui = new PlayerGui(this->player, this->stateData->gfxSettings->resolution);
}

void GameState::initTileMap(std::string Map_name)
{

	this->tileMap = new TileMap(Map_name);

}

//Contructor / Destructors
GameState::GameState(StateData* state_data, int stage_number)
	:State(state_data)
{
	this->down_timer = 0;
	this->initDefferedRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();

	this->initPlayers();
	this->initPlayerGui();
	if (stage_number == 1)
	{
		this->initTileMap("text.slmp");
	}
	else if (stage_number == 2)
	{
		this->initTileMap("text2.slmp");
	}
	else if (stage_number == 3)
	{
		this->initTileMap("Map_1.slmp");
	}

	this->activeEnemies.push_back(new Enemy(550, 2800, this->textures["PINK_FAIRY"]));
	this->activeEnemies.push_back(new Enemy(650, 2900, this->textures["PINK_FAIRY"]));
	this->activeEnemies.push_back(new Enemy(750, 3000, this->textures["PINK_FAIRY"]));
	this->activeEnemies.push_back(new Enemy(850, 3100, this->textures["PINK_FAIRY"]));
	this->activeEnemies.push_back(new Enemy(950, 3200, this->textures["PINK_FAIRY"]));

}
GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->playerGui;
	delete this->tileMap;

	
	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}

}


//Functions
void GameState::updateView(const float& dt)
{
	this->view.setCenter(
		std::floor(this->player->getPosition().x),
		std::floor(this->player->getPosition().y)
	);

	if (this->view.getSize().x >= this->view.getSize().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
		{
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeF().x)
		{
			this->view.setCenter(this->tileMap->getMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}
	if (this->view.getSize().y >= this->view.getSize().y)
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
		{
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		}
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeF().x)
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeF().x - this->view.getSize().y / 2.f);
		}
	}
	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{

	//Update player Input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	{
		direction = -1.f;
		this->player->move(-1.f, 0.f, dt);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	{
		direction = 1.f;
		this->player->move(1.f, 0.f, dt);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))) && this->player->get_can_jump())
	{
		this->player->jump(this->player->get_jump_height());
		this->player->set_can_jump(false);


		this->player->set_gravity(0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && bullet_timer >= 50.f)
	{

		//std::cout << "SHOOT" << "\n";
		this->bullets.push_back(new Bullet(this->player->getPosition().x + 100.f, this->player->getPosition().y, direction));

		bullet_timer = 0.f;
	}



}

void GameState::updatePlayerGui(const float& dt)
{
	this->playerGui->update(dt);
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateTileMap(const float& dt)
{
	
	this->tileMap->update(this->player, dt);

	for (auto* i : this->activeEnemies)
	{
		this->tileMap->update(i, dt);
	}
	
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) // unpaused update
	{

		this->updateView(dt);

		this->updatePlayerInput(dt);

		this->updateTileMap(dt);




		this->player->get_jump_height();

		this->player->set_gravity(10.f);



		bullet_timer++;


		for (int i = 0;i < bullets.size();i++)
		{
			this->bullets[i]->update();
		}

		this->player->update(dt);

		this->playerGui->update(dt);

		for (auto* i : this->activeEnemies)
		{
			i->update(dt);
		}


	}
	else // Puased update
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;



	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
	this->tileMap->render(
		this->renderTexture,
		this->viewGridPosition

	);

	


	this->player->render(this->renderTexture);

	for (auto* i : this->activeEnemies)
	{
		i->render(this->renderTexture);
	}
	

	for (int i = 0;i < bullets.size();i++)
	{
		std::cout << "RENDER " << i << "\n";
		this->bullets[i]->render(this->renderTexture);
	}

	

	this->tileMap->renderDefferred(this->renderTexture);

	

	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGui->render(this->renderTexture);

	

	//Render GUI
	if (this->paused) // Puase maenu render
	{
		//this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	//Final Render


	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);

}