#ifndef sge_reactive_h
#define sge_reactive_h

#include "sge_object.hpp"
#include "Box2D/Dynamics/b2Body.h"
#include <Box2D/Dynamics/b2Fixture.h>

namespace SGE
{
	/**
     * \brief 
     */
    class Reactive : public Object
    {
    protected:
		b2Body* body = nullptr;
    public:
        using Object::Object;
		Reactive(b2Body* body);
		Reactive(float x, float y, b2Body* body);
		Reactive(float x, float y, bool draw, b2Body* body);

	    void setBody(b2Body* b2Body);

	    b2Body* getBody();

		const b2Body* getBody() const;

	    virtual glm::vec2 getPosition() const noexcept override;

	    virtual void setPosition(float x, float y) override;

	    virtual float getX() const noexcept override;

	    virtual float getY() const noexcept override;

	    b2Fixture* addFixture(const b2FixtureDef& fixtureDef);

	    /**
	     * \brief Adds fixture using given shape with 0 density.
	     * \param shape 
	     */
	    b2Fixture* addFixture(const b2Shape& shape);
    };
    
}

#endif /* sge_reactive_h */
