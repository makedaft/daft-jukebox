#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <functional>
#include <string>

#include "WString.h"
#include "lib/logger.h"
#include "lib/utils.h"
#include "runners/audio.h"
#include "runners/music_loader.h"
#include "runners/screen_manager.h"
#include "ui/HomeScreen.h"
#include "ui/SongListScreen.h"
#include "ui/components/OptionsMenu.h"

#include "ui/components/QueueList.h"

namespace ui {
namespace component {
ui::component::QueueList::QueueList(Adafruit_SPITFT &drawCtx)
    : ui::component::OptionsMenu<OptionType>(drawCtx) {
  this->controlScheme.action1 = std::bind(&QueueList::openOptions, this);
}

long QueueList::dependencies() {
  return ui::component::OptionsMenu<OptionType>::dependencies() +
         utils::stringHash(music_loader::currentQueue.current().c_str());
}

void QueueList::openOptions() { logger::debug("TODO: Opening options menu"); }

void QueueList::onSelectOption(OptionType option) {
  music_loader::currentQueue.setCurrentAs(option.path.c_str());
  audio::startPlaying();
}

void QueueList::onGoBack() {
  logger::debug("go back");
  screen_manager::openScreen(new HomeScreen());
}

String QueueList::getOptionText(OptionType option) {
  auto songPath = new String(option.path);
  auto lastSlashI = songPath->lastIndexOf('/');
  auto dirPath = songPath->substring(0, lastSlashI) + "/";
  auto songName = songPath->substring(lastSlashI + 1);
  songName.replace(".mp3", "");

  String prefix =
      option.path == music_loader::currentQueue.current() ? "* " : "";
  return prefix + songName + " (" + dirPath + ")";
}

uint16_t QueueList::getOptionColor(OptionType option, bool highlighted) {
  if (option.path == music_loader::currentQueue.current())
    return 0x2947;

  return highlighted ? 0x0000 : 0xFFFF;
}

String QueueList::getHeaderText(OptionType option) {
  auto head =
      "Song queue (" + std::to_string(this->currentOptions.size()) + ")";

  return String(head.c_str());
}

} // namespace component
} // namespace ui
