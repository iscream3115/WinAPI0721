#pragma once


class Quad
{
public:
	Quad();
	Quad(long left, long top, long right, long bottom);
	virtual ~Quad();

	void Update();
	void Render();

	void Move();

private:

protected:
	RECT rect;

};
