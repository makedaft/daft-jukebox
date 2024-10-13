#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <functional>

#include "lib/logger.cpp"
#include "runners/audio.h"
#include "runners/music_loader.h"
#include "runners/screen_manager.h"
#include "ui/HomeScreen.h"
#include "ui/SongListScreen.h"
#include "ui/components/OptionsMenu.h"

#include "ui/components/SongList.h"

namespace ui {
namespace component {
typedef FileInfo OptionType;

ui::component::SongList::SongList(Adafruit_SPITFT &drawCtx)
    : ui::component::OptionsMenu<OptionType>(drawCtx) {
  this->controlScheme.action1 = std::bind(&SongList::openOptions, this);
}

void SongList::openOptions() {
  logger::msg("Opening options menu");
  // screen_manager::openScreen(new SongOptionsScreen(this->dir));
}

void SongList::onSelectOption(OptionType option) {
  if (option.isDir) {
    screen_manager::openScreen(new SongListScreen(option.path.c_str()));
  } else {
    music_loader::loadSongDirIntoQueue(option.path.c_str(), false);
    audio::startPlaying();
  }
}

void SongList::onGoBack() {
  logger::msg("go back");
  if (dir == "/") {
    screen_manager::openScreen(new HomeScreen());
  } else {
    auto parentIndex = dir.lastIndexOf('/');
    auto dirPath = dir.substring(0, parentIndex);
    dirPath = dirPath.isEmpty() ? "/" : dirPath;
    screen_manager::openScreen(new SongListScreen(dirPath.c_str()));
  }
}

String SongList::getOptionText(OptionType option) {
  return option.path + (option.isDir ? "/" : "");
}

String SongList::getHeaderText(OptionType option) { return this->dir; }
} // namespace component
} // namespace ui
