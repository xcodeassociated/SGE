#ifndef sge_object_h
#define sge_object_h

#include <glm/vec2.hpp>
#include "sge_id.hpp"
#include "sge_shape.hpp"

namespace SGE {
	class ObjectManager;
	class Object;
        
    struct GLTexture {
        GLuint id;
        unsigned int width;
        unsigned int height;
    };
    
	enum class LogicPriority
	{
		Highest = 0,
		High,
		Mid,
		Low,
		None
	};

	class ObjectID : public ID {
		friend class ObjectManager;
		Object* obj = nullptr;
		ObjectID(const long id, Object* o) : ID(id), obj(o) {}
	public:
        ObjectID() : ID(0) {}
		ObjectID(Object* o) : ID(-1L), obj(o) {}
		Object* getObject() const
		{
			return this->obj;
		}
		Object* operator->() const
		{
			return this->obj;
		}

        ObjectID(const ObjectID&) = default;
        ObjectID& operator=(const ObjectID&) = default;
	};

    
	class Object
	{
    private:
        
	protected:
		float X = 0.f;
		float Y = 0.f;
		bool drawable = false;
		Shape* shape = getShapeless();
		LogicPriority lock = LogicPriority::None;

	public:
		Object() = default;
		Object(float x, float y) : X(x), Y(y){}
        Object(float x, float y, Shape* shape): X(x), Y(y), shape(shape){}
		Object(float x, float y, bool draw) : X(x), Y(y), drawable(draw){}
		Object(float x, float y, bool draw, Shape* shape) : X(x), Y(y), drawable(draw), shape(shape){}
		virtual ~Object() = 0;
		using ID = ObjectID;
        
        GLTexture texture = {0,0,0};
        const char* path = nullptr;
        
        virtual float& getX() noexcept final
        {
            return this->X;
        }
        
        virtual float& getY() noexcept final
        {
            return this->Y;
        }
        
        virtual void setDrawable(bool e) noexcept final{
            this->drawable = e;
        }
        
        virtual bool getDrawable(void) const noexcept final {
            return this->drawable;
        }
        
        virtual void setPosition(float x, float y){
            this->X=x;
            this->Y=y;
        }
        
		virtual glm::vec2 getPosition() const noexcept
		{
			return glm::vec2(this->X, this->Y);
		}

        virtual Shape* getShape(void) noexcept final {
            return this->shape;
        }

		virtual LogicPriority getLock(void) const noexcept final
		{
			return lock;
		}

		virtual void setLock(const LogicPriority lock) noexcept final
		{
			this->lock = lock;
		}
    };

	inline Object::~Object()
	{
		if(this->shape->isDisposable()) delete this->shape;
	}
	
	class VoidObject : public Object {
	public:
		VoidObject() :Object() {};
	};

	class ObjectBind {
		ObjectID* _begin = nullptr;
		ObjectID* _end = nullptr;
	public:
		ObjectBind(const std::initializer_list<ObjectID>& object) {
			this->_begin = new ObjectID[object.size()];
			int i = 0;
			for (ObjectID o : object) {
				*(this->_begin + i) = o;
				i++;
			}
			this->_end = (this->_begin + object.size());
		}
		ObjectBind(ObjectID object) : ObjectBind({ object }) {
			;;
		}
		ObjectBind() = default;
		~ObjectBind() {
			if (this->_begin != nullptr)
				delete[] this->_begin;
		}
		ObjectBind(const ObjectBind& b){
			this->_begin = new ObjectID[b.size()];
			int i = 0;
			for (ObjectID o : b) {
				*(this->_begin + i) = o;
				i++;
			}
			this->_end = (this->_begin + i);
		}
		ObjectBind(ObjectBind&& b) : _begin(b._begin), _end(b._end){
			b._begin = nullptr;
			b._end = nullptr;
		}

		ObjectBind& operator=(const ObjectBind& b) {
			if (this != &b) {
				this->_begin = new ObjectID[b.size()];
				int i = 0;
				for (ObjectID o : b) {
					*(this->_begin + i) = o;
					i++;
				}
				this->_end = (this->_begin + i);
			}
			return *this;
		}

		ObjectBind& operator=(ObjectBind&& b) {
			if (this != &b) {
				this->_begin = b._begin;
				this->_end = b._end;
				b._begin = nullptr;
				b._end = nullptr;
			}
			return *this;
		}

		ObjectID& operator[](std::size_t i) { return *(this->_begin + i); }
		const ObjectID& operator[](std::size_t i) const { return *(this->_begin + i); }
		ObjectID* begin() { return this->_begin; }
		ObjectID* end() { return this->_end; }
		ObjectID* begin() const { return this->_begin; }
		ObjectID* end() const { return this->_end; }
		std::size_t size() const { return this->_end - this->_begin; }
	};
}

#endif /* sge_object_h */
