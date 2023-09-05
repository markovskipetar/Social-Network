#include "../../Headers/Repositories/ThemesRepository.h"

ThemesRepository::ThemesRepository() : loadedThemeIndex(-1) {}

ThemesRepository* ThemesRepository::instance = nullptr;

ThemesRepository* ThemesRepository::getInstance()
{
	if (!instance)
	{
		instance = new ThemesRepository();
	}

	return instance;
}

void ThemesRepository::freeInstance()
{
	delete instance;
	instance = nullptr;
}

Theme* ThemesRepository::find(int themeId)
{
	int themeIndex = findThemeIndex(themeId);

	return themeIndex < 0 ? nullptr : &themes[themeIndex];
}

Theme* ThemesRepository::find(const char* title)
{
	unsigned themesCount = themes.size();

	for (size_t i = 0; i < themesCount; i++)
	{
		if (!strcmp(themes[i].getTitle().c_str(), title))
		{
			return &themes[i];
		}
	}

	return nullptr;
}

int ThemesRepository::findThemeIndex(int themeId)
{
	unsigned themesCount = themes.size();

	for (size_t index = 0; index < themesCount; index++)
	{
		if (themes[index].getId() == themeId)
		{
			return index;
		}
	}

	return -1;
}

const Theme* ThemesRepository::getOpenedThemeConst() const
{
	return loadedThemeIndex < 0 ? nullptr : &themes[loadedThemeIndex];
}

Theme* ThemesRepository::getOpenedTheme()
{
	return loadedThemeIndex < 0 ? nullptr : &themes[loadedThemeIndex];
}

void ThemesRepository::addTheme(const Theme& theme)
{
	themes.push_back(theme);
}

OpenResult ThemesRepository::openTheme(int themeId)
{
	unsigned themesCount = themes.size();

	for (size_t index = 0; index < themesCount; index++)
	{
		if (themes[index].getId() == themeId)
		{
			loadedThemeIndex = index;
			return OpenResult::Success;
		}
	}

	return OpenResult::IdNotFound;
}

OpenResult ThemesRepository::openTheme(const char* title)
{
	unsigned themesCount = themes.size();

	for (size_t index = 0; index < themesCount; index++)
	{
		if (!strcmp(themes[index].getTitle().c_str(), title))
		{
			loadedThemeIndex = index;
			return OpenResult::Success;
		}
	}

	return OpenResult::TitleNotFound;

}

Result ThemesRepository::removeTheme(int themeId)
{
	int themeToRemoveIndex = (themeId == themes[loadedThemeIndex].getId()) ? loadedThemeIndex : findThemeIndex(themeId);

	if (themeToRemoveIndex < 0)
	{
		return Result::IdNotFound;
	}

	themes[themeToRemoveIndex].removePosts();
	themes.erase(themes.begin() + themeToRemoveIndex);

	if (themeToRemoveIndex == loadedThemeIndex)
	{
		loadedThemeIndex = -1;
	}
	else if (themeToRemoveIndex < loadedThemeIndex)
	{
		loadedThemeIndex--;
	}

	return Result::Success;
}

void ThemesRepository::quitTheme()
{
	themes[loadedThemeIndex].quitPost();

	loadedThemeIndex = -1;
}

const std::vector<Theme> ThemesRepository::getThemes() const
{
	return themes;
}
