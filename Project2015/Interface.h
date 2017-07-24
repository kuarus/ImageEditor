#pragma once
class Interface {
public:
	Interface( );
	virtual ~Interface( );
public:
	void update( );
	void draw( ) const;
private:
	void drawBG( ) const;
	void drawLayerBox( ) const;
private:
	int _handle;
};

