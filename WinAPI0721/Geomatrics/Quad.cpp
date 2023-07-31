#include "stdafx.h"
#include "Quad.h"

Quad::Quad()
{

	rect.left = rect.top = 0;
	rect.right = rect.bottom = 100;
}

Quad::Quad(long left, long top, long right, long bottom)
{

	rect.left = left;
	rect.right = right;
	rect.top = top;
	rect.bottom = bottom;
}

Quad::~Quad()
{
}

void Quad::Update()
{
	Move();
}

void Quad::Render()
{
	FillRect(memDC, &rect, ResourceManger::Get()->GetBrush("Green"));
}

void Quad::Move()
{
	auto key = keyboard::Get();
	if (keyboard::Get()->Press('W'))
	{
		rect.bottom -= 10;
		rect.top -= 10;
	}
	else if (key->Press('S'))
	{
		rect.bottom += 10;
		rect.top += 10;
	}

	if (key->Press('A'))
	{
		rect.left -= 10;
		rect.right -= 10;
	}

	else if (key->Press('D'))
	{
		rect.left += 10;
		rect.right += 10;
	}


}
