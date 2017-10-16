#ifndef sge_id_h
#define sge_id_h

namespace SGE {
    
    class ID{
		long id;
	protected:
		ID(const ID&) = default;
		ID& operator=(const ID&) = default;
	    ID(const long _id);

	public:
	    long getID() const;

	    bool operator<(const ID& _id) const;

	    bool operator==(const ID& _id) const;
    };
    
}

#endif /* sge_id_h */
