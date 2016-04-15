#ifndef sge_path_h
#define sge_path_h

#include "../include/sge_include.hpp"

namespace SGE {
	const std::string& getPath() {
		static std::string base_path = []()->std::string{
			char* path = SDL_GetBasePath();
			std::string ret;
			if(path)
			{
				ret = std::string(path);
				SDL_free(path);
			}
			else
			{
				ret = std::string("./");
			}
			return ret;
		}();
		return base_path;
	}

}

#endif /* sge_path_h */
