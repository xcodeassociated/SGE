#ifndef sge_object_h
#define sge_object_h

#include <glm/vec2.hpp>
#include <GL/glew.h>
#include "Shape/sge_shape.hpp"
#include "Shape/sge_shapeless.hpp"
#include "sge_logic_priority.hpp"
#include "Box2D/Common/b2Math.h"

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
	protected:
		b2Vec2 position = b2Vec2_zero;
		float orientation = 0.f;
		/**
		 * \brief 
		 */
		Shape* shape = getShapeless();
		/**
		 * \brief 
		 */
		LogicPriority lock = LogicPriority::None;
		/**
		* \brief
		*/
		bool drawable = false;
		bool visible = false;
		bool textured = false;
		GLTexture texture = {0,0,0};
	public:
		GLTexture getTexture() const;
		void setTexture(GLTexture texture);
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
		explicit Object(b2Vec2 position);
		/**
		 * \brief 
		 * \param x 
		 * \param y 
		 * \param shape 
		 */
		Object(float x, float y, Shape* shape);
		Object(b2Vec2 position, Shape* shape);
		/**
		 * \brief 
		 * \param x 
		 * \param y 
		 * \param draw 
		 */
		Object(float x, float y, bool draw);
		Object(b2Vec2 position, bool draw);
		/**
		 * \brief 
		 * \param x 
		 * \param y 
		 * \param draw 
		 * \param shape 
		 */
		Object(float x, float y, bool draw, Shape* shape);
		Object(b2Vec2 position, bool draw, Shape* shape);
		/**
		 * \brief 
		 */
		virtual ~Object() = 0;

		/**
		 * \brief 
		 * \return 
		 */
		virtual float getXGLM() const noexcept;
		virtual float getX() const noexcept;

		/**
		 * \brief 
		 * \return 
		 */
		virtual float getYGLM() const noexcept;
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
		
		virtual void setVisible(bool e) noexcept;

		/**
		* \brief
		* \return
		*/
		virtual bool getVisible() const noexcept;

		/**
		 * \brief 
		 * \param x 
		 * \param y 
		 */
		virtual void setPositionGLM(float x, float y);
		virtual void setPositionGLM(glm::vec2 vec);
		virtual void setPosition(b2Vec2 vec);

		/**
		 * \brief 
		 * \return 
		 */
		virtual glm::vec2 getPositionGLM() const noexcept;
		virtual b2Vec2 getPosition() const noexcept;

		float getOrientation() const;
		void setOrientation(float orientation);
		/**
		 * \brief 
		 * \return 
		 */
		virtual Shape* getShape() noexcept;

		/**
		* \brief
		* \return
		*/
		virtual void setShape(Shape* newShape) noexcept;

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

		void setTextured(bool b);

		bool isTextured() const;
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
