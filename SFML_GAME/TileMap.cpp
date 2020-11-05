#include"stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height,std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;
	this->textureFile = texture_file;

		this->map.resize(this->maxSize.x , std::vector< std::vector<Tile*> >());
		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				this->map[x].resize(this->maxSize.y, std::vector<Tile*>());
				for (size_t z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers,NULL);
				}
			}
		}

		if (!this->tileSheet.loadFromFile(texture_file))
			std::cout << "ERROR::TILEMAP:FAIL TO LOAD TEXTURESHEET :: FILENAME" << texture_file <<  "\n";
}

TileMap::~TileMap()
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
			}
		}
	}
}

//Accessors

const sf::Texture* TileMap::getTileSheet() const
{

	return &this->tileSheet;
}

//Functions

void TileMap::addTile(const unsigned  x, const  unsigned y ,const unsigned z,const sf::IntRect& texture_rect)
{

	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == NULL) 
		{
			/*OK TO add TILE*/
			this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF,this->tileSheet,texture_rect);
			std::cout << "DEBUG for create Tile!! \n";
		}
		
	}
}

void TileMap::removeTile(const unsigned  x, const  unsigned y, const unsigned z)
{

	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != NULL)
		{
			/*OK TO remove TILE*/
			delete this->map[x][y][z] ;
			this->map[x][y][z] = NULL;
			std::cout << "DEBUG for remove Tile!!  \n";
		}

	}
	

}

void TileMap::saveToFile(const std::string file_name)
{
	/*Save the entire tile map to a text-file 
	Format:
	Basic :
	Size x y
	gridSize
	layers
	texture file

	All tiles:
	gridPos  x y , Texture rect x y , collision ,type
	*/

	std::ofstream out_file;

	out_file.open(file_name);
	
	if (out_file.is_open())
	{
		out_file << this->maxSize.x << " " << this->maxSize.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";

		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{
					if(this->map[x][y][z])
					out_file <<  this->map[x][y][z] -> getAsString() << " "; // MAKE SURE THIS LAST SPACE IS NOT SAVED!!
				}
			}
		}
			
	}
	else
	{
		std::cout << "ERROR:: RILE MAP COUL DNOT T OSAVE FILE " << file_name << "\n";
	}

	out_file.close();


}

void TileMap::loadRoFile(const std::string file_name)
{

}
void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto *z : y)
			{
				if(z != NULL)
				z->render(target);
			}
		}
	}
}


