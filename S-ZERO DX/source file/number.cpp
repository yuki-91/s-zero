//-----------------------------------//
//--ƒiƒ“ƒo[•`‰æˆ—----[number.cpp]-//
//-----------------------------------//
//------Author:Â‹{ —C‹G-------------//
//-----------------------------------//
#include"Polygon.h"
#include"number.h"


void CNumber::DrawNumber(int n,float x,float y)
{

	if( n < 0 || n > 9 ) return;

	CPolygon::PolygonDraw2(0,D3DCOLOR_RGBA(255,255,255,255),x,y ,60.0f,162.0f,430,100,43.4 * n,60 * 0,43.5,NUMBER_HEIGHT);
}