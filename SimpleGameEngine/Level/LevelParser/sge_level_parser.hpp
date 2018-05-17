#ifndef sge_level_parser_h
#define sge_level_parser_h

#include <vector>
#include <map>

#include "../sge_level.hpp"

namespace SGE
{
	class LevelParser
	{
		/**
         * \brief Maps tile codes to texture filepath
         * \todo Check for level Y Inversion.
         */
        std::map<char, std::string> levelMask;
		/**
		 * \brief 
		 */
		std::vector<std::string> levelData;
        
	public:
		/**
		 * \brief Construct LevelParser by reading levelData from file at path
		 * \param path path to file hodling level layout
		 * \param mask Map of textures
		 */
		LevelParser(const char* path, const std::map<char, std::string>& mask);

		/**
		 * \brief Parses level data creating either world or background tiles with base size and appriopriate texture
		 * \return Parsed Level
		 */
		Level parse();
	};
}

#endif
