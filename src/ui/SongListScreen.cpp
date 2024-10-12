#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <vector>

#include "Adafruit_SPITFT.h"
#include "runners/audio.cpp"
#include "ui/OptionsMenu.cpp"
#include "ui/_screen.cpp"

#define FONT_HEIGHT 8

namespace ui {
typedef FileInfo OptionType;

class SongOptionsMenu : public ui::OptionsMenu<OptionType> {
  void onSelectOption(OptionType option) {
    if (option.path.endsWith("/")) {
      music_loader::loadDirIntoQueue(option.path.c_str(), false);
    } else {
      music_loader::loadSongDirIntoQueue(option.path.c_str(), false);
    }
    audio::startPlaying();
  }

  String getOptionText(OptionType option) {
    return option.path + (option.isDir ? "/" : "");
  }
};

class SongListScreen : public ui::Screen {
  std::vector<OptionType> currentOptions;
  SongOptionsMenu optionsMenu;

  void renderScreen() { this->optionsMenu.render(this->drawCtx); }

  boolean shouldRender() { return this->optionsMenu.shouldRender(); }

public:
  SongListScreen(Adafruit_SPITFT &drawCtx, const char *dir)
      : ui::Screen(drawCtx) {
    this->optionsMenu.currentOptions = music_loader::listDirectory(dir);
  }

  ui::ControlScheme controlScheme() { return this->optionsMenu.controlScheme; }
};
} // namespace ui
