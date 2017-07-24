#pragma once
#include <memory>
#include <vector>

class Work;

class Desk {
public:
	Desk( );
	virtual ~Desk( );
public:
	bool load( const char* filename );
	bool save( const char* filename ) const;
private:
	int _active_work;
	std::vector< std::shared_ptr< Work > > _work;
};

