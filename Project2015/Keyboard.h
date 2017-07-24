#pragma once
#include "Task.h"
class Keyboard : public Task {
public:
	static std::shared_ptr< Keyboard > getTask( );
public:
	Keyboard();
	virtual ~Keyboard();
public:
	void update( );
	bool isPushKey( int key ) const;
	bool isHoldKey( int key ) const;
private:
	char _key[ 256 ];
};

