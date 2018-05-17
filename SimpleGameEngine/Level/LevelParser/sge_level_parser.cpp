#include "sge_level_parser.hpp"
#include "../../Object/Shape/sge_shape_rectangle.hpp"
#include <fstream>
#include <cctype>

SGE::LevelParser::LevelParser(const char* path, const std::map<char, std::string>& mask): levelMask(mask)
{
	std::ifstream lvl;
	lvl.open(path);
	if (lvl.fail())
	{
		throw std::runtime_error("Failed to open level data");
	}
	std::string temp;
	std::getline(lvl, temp);

	while (lvl >> temp)
	{
		this->levelData.push_back(temp);
	}
}

SGE::Level SGE::LevelParser::parse()
{
	Rectangle* tile = reinterpret_cast<Rectangle*>(getBaseTileShape());
	const float width = tile->getWidth();
	const float height = tile->getHeight();
	Level lev(this->levelData[0].size(), this->levelData.size());
	for (int y = 0; y < this->levelData.size(); y++)
	{
		for (int x = 0; x < this->levelData[y].size(); x++)
		{
			char tile = this->levelData[y][x];
			auto it = this->levelMask.find(tile);
			if (it != this->levelMask.end())
			{
				if (std::isupper(tile))
                    lev.getWorld().emplace_back(x * width, y * height, it->second);
				else
                    lev.getBackground().emplace_back(x * width, y * height, it->second);
			}
		}
	}
	return lev;
}
