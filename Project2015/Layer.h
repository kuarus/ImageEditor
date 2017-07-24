#pragma once
class Layer {
public:
	Layer( );
	virtual ~Layer( );
public:
	void draw( ) const;
	bool load( const char* filename );
private:
	int _handle;
	bool _eye;
};

