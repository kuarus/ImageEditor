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
	enum TOOL {
		TOOL_SELECT,
		TOOL_MOVE,
		TOOL_FILL,
		TOOL_PAINT,
		MAX_TOOL,
	};
private:
	void convertScreenPosToLayerPos( int& x, int& y ) const;
	void zoom( );
	void paint( ) const;
	void select( );
	void erase( );
	void drawSelect( ) const;
	void fill( );
	void fillAlgorithm( int x, int y, unsigned int base_color, int allow_value, int width, int height ) const;
private:
	int _select_start_x;
	int _select_start_y;
	int _select_end_x;
	int _select_end_y;
	TOOL _tool;
	int _active_layer;
	int _trans_handle;
	int _handle;
	int _si_handle;
	unsigned int _color;
	int _allow_value;
	int _alpha;
	int _zoom;//í èÌ:100
	std::vector< std::shared_ptr< Layer > > _layer;
};

