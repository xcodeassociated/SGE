#ifndef SGE_WORLDSTEP
#define SGE_WORLDSTEP

#include "../../../Box2D/Dynamics/b2World.h"
#include "../../sge_logic.hpp"

namespace SGE
{
	class WorldStep : public Logic
	{
		b2World* world;
		int vel = 8;
		int pos = 3;
	public:
		explicit WorldStep(b2World*) noexcept;
		WorldStep(b2World*,int,int) noexcept;
		void performLogic() override;
		int getVelocityIterations() const;
		int getPositionIterations() const;
		void setVelocityIterations(int);
		void setPositionIterations(int);
	};
}

#endif
