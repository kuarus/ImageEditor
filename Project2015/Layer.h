#pragma once
class Layer {
public:
	Layer( );
	virtual ~Layer( );
public:
	bool load( const char* filename );
private:
	int _handle;
};

