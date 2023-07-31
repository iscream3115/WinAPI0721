#include "stdafx.h"
#include "Program.h"

#include "Geomatrics/Quad.h"

Program::Program()
{
	ResourceManger::Create();
	quad = new Quad();
}

Program::~Program()
{
	SAFE_DELETE(quad);
}

void Program::Update()
{
	quad->Update();

}

void Program::Render()
{
	quad->Render();

}
