#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <functional>

#include "lib/logger.h"
#include "runners/audio.h"
#include "runners/music_loader.h"
#include "runners/screen_manager.h"
#include "ui/HomeScreen.h"
#include "ui/OptionsMenuScreen.h"
#include "ui/SongListScreen.h"
#include "ui/components/OptionsMenu.h"

#include "ui/components/SongList.h"

namespace ui {
namespace component {
ui::component::SongList::SongList(Adafruit_SPITFT &drawCtx)
    : ui::component::OptionsMenu<OptionType>(drawCtx) {
  this->controls.action = std::bind(&SongList::openOptions, this);
}

void SongList::openOptions() {
  auto option = this->getHighlightedOption();
  auto path = option.path.c_str();
  logger::printf("Opening options menu for %s\n", path);
  screen_manager::openScreen(new OptionsMenuScreen(
      path, option.isDir ? OPTS_TYPE_DIR : OPTS_TYPE_FILE));
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
  logger::debug("go back");
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
  auto filename = new String(option.path);
  filename->replace(this->dir, "");
  filename->replace("/", "");
  return (option.isDir ? ">  " : "") + *filename;
}

uint16_t SongList::getOptionColor(OptionType option, bool highlighted) {
  if (option.isDir) {
    return 0x49d4;
  }

  return highlighted ? 0x0000 : 0xFFFF;
}

String SongList::getHeaderText(OptionType option) { return this->dir; }
} // namespace component
} // namespace ui
