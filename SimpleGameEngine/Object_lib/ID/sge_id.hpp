#ifndef sge_id_h
#define sge_id_h

namespace SGE {
    
	/**
     * \brief 
     */
    class ID{
		long id;
	protected:
	    /**
		 * \brief 
		 */
		ID(const ID&) = default;
	    /**
		 * \brief 
		 * \return 
		 */
		ID& operator=(const ID&) = default;
	    /**
	     * \brief 
	     * \param _id 
	     */
	    ID(const long _id);

	public:
	    /**
	     * \brief 
	     * \return 
	     */
	    long getID() const;

	    /**
	     * \brief 
	     * \param _id 
	     * \return 
	     */
	    bool operator<(const ID& _id) const;

	    /**
	     * \brief 
	     * \param _id 
	     * \return 
	     */
	    bool operator==(const ID& _id) const;
    };
    
}

#endif /* sge_id_h */
