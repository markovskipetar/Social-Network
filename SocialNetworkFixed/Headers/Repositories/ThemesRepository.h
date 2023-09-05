#pragma once
#include <vector>
#include "../Entities/Theme.h"
#include "../ResultEnums/OpenResult.h"

class ThemesRepository
{
public:
	static ThemesRepository* getInstance();
	static void freeInstance();

public:
	Theme* find(int themeId);
	Theme* find(const char* title);
	int findThemeIndex(int themeId);
	const Theme* getOpenedThemeConst() const;
	Theme* getOpenedTheme();
	void addTheme(const Theme& theme);
	OpenResult openTheme(int themeId);
	OpenResult openTheme(const char* title);
	Result removeTheme(int themeId);
	void quitTheme();
	const std::vector<Theme> getThemes() const;

private:
	static ThemesRepository* instance;

	std::vector<Theme> themes;
	int loadedThemeIndex;

private:
	ThemesRepository();
};

