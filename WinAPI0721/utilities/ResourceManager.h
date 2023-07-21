#pragma once
class ResourceManger : public singletonBase<ResourceManger>
{
public:
	friend class singletonBase<ResourceManger>;

	HBRUSH& GetBrush(string brushName);
	void AddBrush(string key, COLORREF color);


private:

	ResourceManger();
	~ResourceManger();

	void InitBrush();

private:
	unordered_map<string, HBRUSH> brushMap;


};