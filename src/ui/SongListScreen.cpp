#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <vector>

#include "Adafruit_SPITFT.h"
#include "lib/display.cpp"
#include "runners/audio.cpp"
#include "runners/screen_manager.cpp"
#include "ui/OptionsMenu.cpp"
#include "ui/_screen.cpp"

#define FONT_HEIGHT 8

namespace ui {
typedef FileInfo OptionType;

static void onSelectOption(OptionType option);
static void onGoBack(String dir);

class SongOptionsMenu : public ui::OptionsMenu<OptionType> {
public:
  String dir;

  SongOptionsMenu(Adafruit_SPITFT &drawCtx)
      : ui::OptionsMenu<OptionType>(drawCtx) {}
  void onSelectOption(OptionType option) { ui::onSelectOption(option); }
  void onGoBack() { ui::onGoBack(this->dir); }
  String getOptionText(OptionType option) {
    return option.path + (option.isDir ? "/" : "");
  }
};

class SongListScreen : public ui::Screen {
  std::vector<OptionType> currentOptions;
  SongOptionsMenu *optionsMenu = new SongOptionsMenu(display::tft);

  void renderScreen() { this->optionsMenu->render(); }
  bool shouldRender() { return this->optionsMenu->shouldRender(); }

public:
  SongListScreen(const char *dir) {
    this->optionsMenu->currentOptions = music_loader::listDirectory(dir);
    this->optionsMenu->dir = dir;
  }

  ui::ControlScheme controlScheme() { return this->optionsMenu->controlScheme; }
};

static void onSelectOption(OptionType option) {
  if (option.isDir) {
    screen_manager::openScreen(new SongListScreen(option.path.c_str()));
  } else {
    music_loader::loadSongDirIntoQueue(option.path.c_str(), false);
    audio::startPlaying();
  }
}

static void onGoBack(String dir) {
  auto parentIndex = dir.lastIndexOf('/');
  auto dirPath = dir.substring(0, parentIndex);
  dirPath = dirPath.isEmpty() ? "/" : dirPath;
  screen_manager::openScreen(new SongListScreen(dirPath.c_str()));
}
} // namespace ui
