#ifndef sge_level_parser_h
#define sge_level_parser_h

#include<map>
#include<string>
#include<fstream>

#include"../BackgroundElement/sge_background_element.hpp"

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

		std::vector<BackgroundElement> parse()
		{
			std::vector<BackgroundElement> elems;
			for (int y = 0; y < this->levelData.size(); y++) {
				for (int x = 0; x < this->levelData[y].size(); x++) {
					char tile = this->levelData[y][x];
					auto it = this->levelMask.find(tile);
					if (it != this->levelMask.end())
					{
						elems.emplace_back(it->second);
					}
				}
			}
			return elems;
		}
	};
}

#endif
