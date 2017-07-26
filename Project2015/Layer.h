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
private:
	int _handle;
	bool _eye;
	std::string _name;
};

