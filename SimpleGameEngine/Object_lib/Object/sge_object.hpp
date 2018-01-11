#ifndef sge_object_h
#define sge_object_h

#include <glm/vec2.hpp>
#include <GL/glew.h>
#include "sge_shape.hpp"
#include "sge_shapeless.hpp"
#include "sge_logic_priority.hpp"

namespace SGE
{
	class Object;
        
	/**
     * \brief 
     * \todo Shouldn't this be a separate file?
     */
    struct GLTexture
	{
        GLuint id;
        unsigned int width;
        unsigned int height;
    };

    
	/**
	 * \brief 
	 */
	class Object
	{
    private:
        
	protected:
		/**
		 * \brief 
		 */
		float X = 0.f;
		/**
		 * \brief 
		 */
		float Y = 0.f;
		/**
		 * \brief 
		 */
		bool drawable = false;
		/**
		 * \brief 
		 */
		Shape* shape = getShapeless();
		/**
		 * \brief 
		 */
		LogicPriority lock = LogicPriority::None;

	public:
		bool hasTexture = false;

		/**
		 * \brief 
		 */
		Object() = default;
		/**
		 * \brief 
		 * \param x 
		 * \param y 
		 */
		Object(float x, float y);
		/**
		 * \brief 
		 * \param x 
		 * \param y 
		 * \param shape 
		 */
		Object(float x, float y, Shape* shape);
		/**
		 * \brief 
		 * \param x 
		 * \param y 
		 * \param draw 
		 */
		Object(float x, float y, bool draw);
		/**
		 * \brief 
		 * \param x 
		 * \param y 
		 * \param draw 
		 * \param shape 
		 */
		Object(float x, float y, bool draw, Shape* shape);
		/**
		 * \brief 
		 */
		virtual ~Object() = 0;

		/**
         * \brief 
         */
        GLTexture texture = {0,0,0};
		/**
         * \brief 
         */
        const char* path = nullptr;

		/**
		 * \brief 
		 * \return 
		 */
		virtual float getX() const noexcept;

		/**
		 * \brief 
		 * \return 
		 */
		virtual float getY() const noexcept;

		/**
		 * \brief 
		 * \param e 
		 */
		virtual void setDrawable(bool e) noexcept;

		/**
		 * \brief 
		 * \return 
		 */
		virtual bool getDrawable() const noexcept;

		/**
		 * \brief 
		 * \param x 
		 * \param y 
		 */
		virtual void setPosition(float x, float y);

		/**
		 * \brief 
		 * \return 
		 */
		virtual glm::vec2 getPosition() const noexcept;

		/**
		 * \brief 
		 * \return 
		 */
		virtual Shape* getShape() noexcept;

		/**
		 * \brief 
		 * \return 
		 * \todo Rework Lock system
		 */
		virtual LogicPriority getLock() const noexcept;

		/**
		 * \brief 
		 * \param lock 
		 */
		virtual void setLock(const LogicPriority& lock) noexcept;
    };
	
	/**
	 * \brief 
	 * \todo Shouldn't this be a separate file?
	 */
	class VoidObject : public Object
	{
	public:
		/**
		 * \brief 
		 */
		VoidObject();
	};

}

#endif /* sge_object_h */
