#include"stdafx.h"
#include"MainMenuState.h"


//Initializer Function
void MainMenuState::initVariables()
{

}



void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Petchlamoon-Regular.ttf"))
	{
		throw("Error to upload Fonts!!");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs;

	ifs.open("Config/mainmenustate_keybinds.ini");

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

void MainMenuState::initGui()
{
	
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//BackGround
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	
	this->backgroundTexture.loadFromFile("Resources/Images/background/background2.png");


	this->background.setTexture(&this->backgroundTexture);

	//Buttons BackGround
	this->btnBackground.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width / 5),
			static_cast<float>(vm.height)
		)
	);

	this->btnBackground.setPosition(gui::p2pX(40.5f, vm), 0.f);
	this->btnBackground.setFillColor(sf::Color(10, 10, 10, 220));

	//Buttons
	

	this->buttons["SELECT_STATE"] = new gui::Button(
		gui::p2pX(44.2f, vm), gui::p2pY(18.5f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Play Game", gui::calCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));



	this->buttons["SETTINGS_STATE"] = new gui::Button(
		gui::p2pX(44.2f, vm), gui::p2pY(27.7f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Settings", gui::calCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EDITOR_STATE"] = new gui::Button(
		gui::p2pX(44.2f, vm), gui::p2pY(37.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Editor", gui::calCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));


	this->buttons["EXIT_STATE"] = new gui::Button(
		gui::p2pX(44.2f, vm), gui::p2pY(66.6f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Quit", gui::calCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void MainMenuState::resetGui()
{

	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	this->buttons.clear();
	this->initGui();
}

MainMenuState::MainMenuState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->resetGui();

	


	

}
MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


void MainMenuState::updateInput(const float& dt)
{
	



	
}

void MainMenuState::updateButtons()
{
	// Update all the button in the state 
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}
	
	

	

	//Setting
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingState(this->stateData));
	}


	//Editor 
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}

	//Test
	if (this->buttons["SELECT_STATE"]->isPressed())
	{
		this->states->push(new SelectState(this->stateData));
	}

	//Quit this Game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);


	
	this->updateButtons();

	
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	
	target->draw(this->background);

	target->draw(this->btnBackground);
	
	this->renderButtons(*target);


	//REMOVE LATER
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x,this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}
