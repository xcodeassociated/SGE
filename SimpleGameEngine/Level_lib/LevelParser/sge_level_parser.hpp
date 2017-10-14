#ifndef sge_level_parser_h
#define sge_level_parser_h

#include <vector>
#include<map>
#include<string>
#include<fstream>
#include<cctype>

#include "sge_level.hpp"
//#include "../Object/Shape/sge_shape.hpp"
//#include "../ObjectManager/sge_object_manager.hpp"

namespace SGE {
	class LevelParser {
		//const char* path;
        std::map<char, std::string> levelMask;
		std::vector<std::string> levelData;
        
	public:
		LevelParser(const char* path, const std::map<char, std::string>& mask) : levelMask(mask)
		{
			std::ifstream lvl; 
			lvl.open(path);
			if (lvl.fail())
			{
				throw std::runtime_error("Failed to open level data");
			}
			std::string temp;
			std::getline(lvl,temp);

			while (lvl >> temp) {
				this->levelData.push_back(temp);
			}
		}

/*		Level parse()
		{
			Level lev(this->levelData[0].size(), this->levelData.size());
			for (int y = 0; y < this->levelData.size(); y++) {
				for (int x = 0; x < this->levelData[y].size(); x++) {
					char tile = this->levelData[y][x];
					auto it = this->levelMask.find(tile);
					if (it != this->levelMask.end())
					{
						lev.getBackground().emplace_back(it->second);
					}
				}
			}
			return lev;
		}
*/
		Level parse()
		{
			Rectangle* tile = reinterpret_cast<Rectangle*>(getBaseTileShape());
			const float width = tile->getWidth();
			const float height = tile->getHeight();
			Level lev(this->levelData[0].size(), this->levelData.size());
			for (int y = 0; y < this->levelData.size(); y++) {
				for (int x = 0; x < this->levelData[y].size(); x++) {
					char tile = this->levelData[y][x];
					auto it = this->levelMask.find(tile);
					if (it != this->levelMask.end())
					{
                        if(std::isupper(tile)) lev.getWorld().emplace_back(x*width,y*height,it->second);
                        else lev.getBackground().emplace_back(x*width,y*height,it->second);
					}
				}
			}
			return lev;
		}
	};
}

#endif
