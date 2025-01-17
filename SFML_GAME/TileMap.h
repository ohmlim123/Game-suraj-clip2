#ifndef TILEMAP_H
#define TILEMAP_H


#include"Tile.h"
#include"Entity.h"
#include"MovementComponent.h"



class Tile;
class Entity;

class TileMap
{
private:
	void clear();


	float gridSizeF;
	int gridSizeI;
	sf::Vector2i maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	sf::Clock Hp_timer;
	int layers;
	std::vector< std::vector< std::vector< std::vector<Tile*> > > > map;
	std::stack <Tile*> defferedRenderStack;
	std::string textureFile;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;


	//

	//Culling

	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;


public:
	TileMap(float gridSize, int width, int height,std::string texture_file);
	TileMap(const std::string file_name);
	virtual ~TileMap();

	//Accessor]
	const bool TileEmpty(const int x, const int y, const int z) const ;
	const sf::Texture* getTileSheet() const;
	const int getLayerSize(const int x, const int y, const int z) const;
	const sf::Vector2i& getMaxSizeGrid() const;
	const sf::Vector2f& getMaxSizeF() const;


	//Functions

	void addTile(const int  x, const int y, const int z, const sf::IntRect& texture_rect,const bool& collision, const short& type);
	void removeTile(const int  x, const  int y, const int z);

	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void update(Entity* entity, const float& dt);

	//Type of Tile
	void update_normal_tile(const float& dt, Entity* entity, sf::FloatRect playerBounds, sf::FloatRect wallBounds);
	void update_attack_tile(const float& dt, Entity* entity, sf::FloatRect playerBounds, sf::FloatRect wallBounds);
	void update_healing_tile(const float& dt, Entity* entity, sf::FloatRect playerBounds, sf::FloatRect wallBounds);
	void update_jump_high_tile(const float& dt, Entity* entity, sf::FloatRect playerBounds, sf::FloatRect wallBounds);
	void update_jump_low_tile(const float& dt, Entity* entity, sf::FloatRect playerBounds, sf::FloatRect wallBounds);
	void update_speed_down_tile(const float& dt, Entity* entity, sf::FloatRect playerBounds, sf::FloatRect wallBounds);
	void update_speed_up_tile(const float& dt, Entity* entity, sf::FloatRect playerBounds, sf::FloatRect wallBounds);
	void update_jump_very_high_tile(const float& dt, Entity* entity, sf::FloatRect playerBounds, sf::FloatRect wallBounds);

	
	void render(sf::RenderTarget& target,const sf::Vector2i& gridPosition);
	void renderDefferred(sf::RenderTarget& target );
	

	
};
#endif

