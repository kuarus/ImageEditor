#pragma once
#include "Task.h"

class Interface : public Task {
public:
	Interface( );
	virtual ~Interface( );
public:
	void update( );
	void draw( ) const;
private:
	void drawBG( ) const;
	void drawLayerBox( ) const;
};

