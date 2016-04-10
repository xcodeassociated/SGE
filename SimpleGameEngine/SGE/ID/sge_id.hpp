#ifndef sge_id_h
#define sge_id_h

namespace SGE {
    
    class ID{
		long id;

	protected:
		long getID() const {
			return id;
		}

	public:
		ID(const long _id) : id(_id) {}
		bool operator<(const ID& _id) const {
			return id < _id.id;
		}

		bool operator==(const ID& _id) const
		{
			return this->id == _id.id;
		}
    };
    
}

#endif /* sge_id_h */