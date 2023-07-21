#include "stdafx.h"
#include "ResourceManager.h"

HBRUSH& ResourceManger::GetBrush(string brushName)
{
	if (brushMap.find(brushName) != brushMap.end())
		return brushMap.find(brushName)->second;

	return GetBrush("White");
}

void ResourceManger::AddBrush(string key, COLORREF color)
{
	HBRUSH brush;
	brush = (HBRUSH)CreateSolidBrush(color);
	brushMap.insert(make_pair(key, brush));

}

ResourceManger::ResourceManger()
{
	InitBrush();

}

ResourceManger::~ResourceManger()
{

	//배열처럼 있는 브러쉬를 하나하나씩 빼서 지워준다.
	for (pair<string, HBRUSH> b : brushMap) DeleteObject(b.second);

}

void ResourceManger::InitBrush()
{
	AddBrush("Red", RGB(255, 0, 0));
	AddBrush("Green", RGB(0, 255, 0));
	AddBrush("Blue", RGB(0, 0, 255));
	AddBrush("White", RGB(255, 255, 255));
	AddBrush("Black", RGB(0, 0, 0));

}
