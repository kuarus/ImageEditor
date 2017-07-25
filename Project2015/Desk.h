#pragma once
#include "Task.h"
#include <vector>
#include "define.h"

class Layer;

class Desk : public Task {
public:
	static std::shared_ptr< Desk > getTask( );
public:
	Desk( );
	virtual ~Desk( );
public:
	void update( );
	bool create( );
	bool load( std::string filename );
	bool save( std::string filename, EXTENSION extension ) const;
	void draw( ) const;
	int getLayerSize( ) const;
	std::shared_ptr< Layer > getLayer( int idx ) const;
private:
	int _active_layer;
	int _trans_handle;
	int _handle;
	int _zoom;//í èÌ:100
	std::vector< std::shared_ptr< Layer > > _layer;
};

