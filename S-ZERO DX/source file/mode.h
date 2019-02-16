#ifndef _MODE_H_
#define _MODE_H_
#include "main.h"
#include <d3d9.h>
#include <d3dx9.h> 

class CMode
{
private:
	//static CMode *m_Mode[3];

public:
	/*CMode();
	virtual ~CMode();*/
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

};
#endif 
