#pragma once

#include "Adafruit_SPITFT.h"
#include "ui/_screen.h"
#include "ui/components/OptionsMenu.h"
#include <vector>

enum OptionsMenuOptionID {
  OPT_ADD_TO_QUEUE,
  OPT_PLAY_NEXT,
  OPT_PLAYLIST_ADD,
  OPT_PLAY,
  OPT_OPEN_DIR
};

namespace ui {
struct MenuOption {
  String label;
  short id;
};

class OptionsMenuList : public ui::component::OptionsMenu<MenuOption> {
  String file;
  bool isDir;

  void onSelectOption(MenuOption option) override;
  void onGoBack() override;
  String getOptionText(MenuOption option) override;
  String getHeaderText(MenuOption option) override;

  void onAction();

public:
  OptionsMenuList(const char *file, bool isDir);
};

class OptionsMenuScreen : public ui::Screen {
  OptionsMenuList *optionsMenu;

  long dependencies() override;
  void render() override;

public:
  OptionsMenuScreen(const char *file, bool isDir);

  ControlScheme controlScheme() override;
};
} // namespace ui
