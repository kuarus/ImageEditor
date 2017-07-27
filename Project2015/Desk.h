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
	struct ColorData {
		int r;
		int g;
		int b;
		int a;
		ColorData( ) {
			r = 0;
			g = 0;
			b = 0;
			a = 0;
		}
	};
private:
	void updateViewPos( );
	void updateZoom( );
	void updateTool( );
	void convertScreenPosToLayerPos( int& x, int& y ) const;
	void paint( ) const;
	void select( );
	void erase( );
	void drawSelect( ) const;
	void fill( );
	void fillAlgorithm( const int& x, const int& y, const int& width, const int& height, const int& pr, const int& pg, const int& pb, const int& br, const int& bg, const int& bb ) const;
	void fillAlgorithm0( const int& x, const int& y, const int& width, const int& height, const int& pr, const int& pg, const int& pb, const int& br, const int& bg, const int& bb ) const;
	void fillAlgorithm1( const int& x, const int& y, const int& width, const int& height, const int& pr, const int& pg, const int& pb, const int& br, const int& bg, const int& bb ) const;
	void fillAlgorithm2( const int& x, const int& y, const int& width, const int& height, const int& pr, const int& pg, const int& pb, const int& br, const int& bg, const int& bb ) const;
	void fillAlgorithm3( const int& x, const int& y, const int& width, const int& height, const int& pr, const int& pg, const int& pb, const int& br, const int& bg, const int& bb ) const;
	bool isAllowedFill( const int& x, const int& y, const int& width, const int& height, const int& pr, const int& pg, const int& pb, const int& br, const int& bg, const int& bb ) const;
private:
	//選択範囲
	int _select_start_x;
	int _select_start_y;
	int _select_end_x;
	int _select_end_y;
	//描画ハンドル
	int _trans_handle;
	int _handle;
	int _si_handle;
	//表示設定
	int _view_x;
	int _view_y;
	int _zoom;//通常:100
	//描画設定
	int _alpha;
	unsigned int _color;
	int _allow_value;
	int _active_layer;
	std::vector< std::shared_ptr< Layer > > _layer;
	TOOL _tool;
};

