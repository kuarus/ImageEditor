#pragma once
#include <memory>
#include <vector>

class Work;

class Desk {
public:
	Desk( );
	virtual ~Desk( );
public:
	void draw( ) const;
	bool load( std::string filename );
	bool save( std::string filename ) const;
private:
	int _active_work;
	std::vector< std::shared_ptr< Work > > _work;
};

