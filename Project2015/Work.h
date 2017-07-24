#pragma once
#include <memory>
#include <vector>

class Layer;

class Work {
public:
	Work( );
	virtual ~Work( );
public:
	void update( );
	bool create( );
	bool load( std::string filename );
	bool save( std::string filename ) const;
	void draw( ) const;
private:
	int _active_layer;
	int _handle;
	double _zoom;
	std::vector< std::shared_ptr< Layer > > _layer;
};

