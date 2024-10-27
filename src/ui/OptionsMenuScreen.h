#pragma once

#include "Adafruit_SPITFT.h"
#include "ui/_screen.h"
#include "ui/components/OptionsMenu.h"
#include <vector>

enum OptionsMenuOptionID {
  OPT_ADD_TO_QUEUE,
  OPT_PLAY_NEXT,
  OPT_PLAY,
  OPT_OPEN_DIR,
  OPT_REMOVE_FROM_QUEUE,
  OPT_CLEAR_QUEUE
};

enum OptionMenuType { OPTS_TYPE_FILE, OPTS_TYPE_DIR, OPTS_TYPE_QUEUE };

namespace ui {
struct MenuOption {
  String label;
  short id;
};

class OptionsMenuList : public ui::component::OptionsMenu<MenuOption> {
  String file;
  OptionMenuType type;

  void onSelectOption(MenuOption option) override;
  void onGoBack() override;
  String getOptionText(MenuOption option) override;
  String getHeaderText(MenuOption option) override;

  void onAction();

public:
  OptionsMenuList(const char *file, OptionMenuType type);

  bool isDir() const;
  bool isQueue() const;
};

class OptionsMenuScreen : public ui::Screen {
  OptionsMenuList *optionsMenu;

  long dependencies() override;
  void render() override;

public:
  OptionsMenuScreen(const char *file, OptionMenuType type);

  ControlScheme controlScheme() override;
};
} // namespace ui
