#pragma once
#include <string>

class Layer {
public:
	Layer( );
	virtual ~Layer( );
public:
	void draw( ) const;
	bool load( std::string filename );
	void create( int width, int height );
	int getHandle( ) const;
	std::string getName( ) const;
	void fill( int x, int y, unsigned int base_color, unsigned int paint_color, int allow_value );
	int getColor( int x, int y ) const;
private:
	int _handle;
	bool _eye;
	std::string _name;
};

