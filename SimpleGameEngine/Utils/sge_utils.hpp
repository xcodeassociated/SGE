#ifndef sge_path_h
#define sge_path_h

#include <string>
#include <glm/vec2.hpp>

namespace SGE
{
	/**
	 * \brief 
	 * \return 
	 */
	const std::string& getPath();

	/**
	 * \brief 
	 * \param _screenCoords 
	 * \param coords 
	 * \param scale 
	 * \return 
	 */
	glm::vec2 screenToWorld(glm::vec2 screen, glm::vec2 _screenCoords, glm::vec2 coords, double scale);
}

#endif /* sge_path_h */
