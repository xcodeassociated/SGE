#ifndef SGE_LEVEL_HPP
#define SGE_LEVEL_HPP

#include <vector>
#include "../Object/BackgroundElement/sge_background_element.hpp"
#include "../Object/WorldElement/sge_world_element.hpp"

namespace SGE
{
	/**
	 * \brief Tile-based Level class
	 */
	class Level
	{
	private:
		/**
		 * \brief Number of tiles on Y axis
		 */
		size_t height = 0;
		/**
		 * \brief Number of tiles on X axis
		 */
		size_t width = 0;
		/**
		 * \brief Vector of background elements (Drawable, non-interactive)
		 */
		std::vector<BackgroundElement> background;
		/**
         * \brief Vector of world elements (Drawable, interactive)
         */
        std::vector<WorldElement> world;
	public:
		/**
		 * \brief Default level constructor
		 */
		Level() = default;
		/**
		 * \brief Constructs level of given size
		 * \param x Number of tiles on X axis
		 * \param y Number of tiles on Y axis
		 */
		Level(size_t x, size_t y);
		/**
		 * \brief Default move constructor
		 */
		Level(Level&&) = default;
		/**
		 * \brief Default move operator
		 * \return 
		 */
		Level& operator=(Level&&) = default;

		/**
		 * \brief Returns height of the level
		 * \return Number of tiles on Y axis
		 */
		const size_t& getHeight() const;

		/**
		 * \brief Returns width of the level
		 * \return Number of tiles on X axis
		 */
		const size_t& getWidth() const;

		/**
		 * \brief Returns reference to Background objects vector
		 * \return Vector of background elements
		 */
		std::vector<BackgroundElement>& getBackground();

		/**
		 * \brief Returns reference to World objects vector
		 * \return Vector of world elements
		 */
		std::vector<WorldElement>& getWorld();

		void clear();
	};
}

#endif // !SGE_LEVEL_HPP
