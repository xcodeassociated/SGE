#ifndef sge_level_parser_h
#define sge_level_parser_h

#include<map>
#include<string>
#include<fstream>

#include "../Object/BackgroundElement/sge_background_element.hpp"
#include "../Level/sge_level.hpp"

namespace SGE {
	class LevelParser {
		const char* path;
		std::map<char, std::string> levelMask;
		std::vector<std::string> levelData;
	public:
		LevelParser(const char* path, const std::map<char, std::string>& mask) : path(path), levelMask(mask)
		{
			std::ifstream lvl; 
			lvl.open(this->path);
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
			Level lev(this->levelData[0].size(), this->levelData.size());
			for (int y = 0; y < this->levelData.size(); y++) {
				for (int x = 0; x < this->levelData[y].size(); x++) {
					char tile = this->levelData[y][x];
					auto it = this->levelMask.find(tile);
					if (it != this->levelMask.end())
					{
						lev.getBackground().emplace_back(x,y,it->second);
					}
				}
			}
			return lev;
		}
	};
}

#endif
