#pragma once
#include <memory>
#include <vector>

class Layer;

class Work {
public:
	Work( );
	virtual ~Work( );
public:
	bool load( const char* filename );
	bool save( const char* filename ) const;
	void draw( ) const;
private:
	int _active_layer;
	std::vector< std::shared_ptr< Layer > > _layer;
};

