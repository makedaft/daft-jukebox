#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <SPI.h>
#include <functional>
#include <vector>

#include "lib/display.h"
#include "lib/logger.h"
#include "runners/audio.h"
#include "runners/music_loader.h"
#include "runners/screen_manager.h"
#include "ui/HomeScreen.h"
#include "ui/SongListScreen.h"
#include "ui/_screen.h"
#include "ui/components/OptionsMenu.h"

#include "ui/OptionsMenuScreen.h"

namespace ui {
const std::vector<MenuOption> songOptions = {
    {.label = "Add song to queue", .id = OPT_ADD_TO_QUEUE},
    {.label = "Play next", .id = OPT_PLAY_NEXT},
    {.label = "Play", .id = OPT_PLAY},
    {.label = "Add to playlist", .id = OPT_PLAYLIST_ADD},
};

const std::vector<MenuOption> directoryOptions = {
    {.label = "Add dir to queue", .id = OPT_ADD_TO_QUEUE},
    {.label = "Open", .id = OPT_OPEN_DIR},
    {.label = "Play dir", .id = OPT_PLAY},
};

OptionsMenuList::OptionsMenuList(const char *file, bool isDir)
    : ui::component::OptionsMenu<MenuOption>(display::tft) {

  this->currentOptions = isDir ? directoryOptions : songOptions;
  this->controls.action = std::bind(&OptionsMenuList::onAction, this);

  this->isDir = isDir;
  this->file = String(file);
}

void OptionsMenuList::onGoBack() { screen_manager::goBack(); }

String OptionsMenuList::getOptionText(MenuOption option) {
  return option.label;
}
String OptionsMenuList::getHeaderText(MenuOption option) {
  return String("Options: ") + this->file;
}

void OptionsMenuList::onAction() {
  this->onSelectOption(this->getHighlightedOption());
}

void OptionsMenuList::onSelectOption(MenuOption option) {
  switch (option.id) {
  case OPT_ADD_TO_QUEUE:
    if (this->isDir)
      music_loader::loadDirIntoQueue(this->file, true);
    else
      music_loader::currentQueue.append(this->file.c_str());
    screen_manager::goBack();
    break;

  case OPT_PLAY:
    if (this->isDir)
      music_loader::loadDirIntoQueue(this->file, false);
    else
      music_loader::loadSongDirIntoQueue(this->file, false);
    audio::startPlaying();
    screen_manager::goBack();
    break;

  case OPT_PLAY_NEXT:
    if (!this->isDir) {
      logger::debug((String("Play next: ") + this->file).c_str());
      music_loader::currentQueue.insertNext(this->file.c_str());
    }
    screen_manager::goBack();
    break;

  case OPT_PLAYLIST_ADD:
    logger::debug("TODO: Add to playlist");
    screen_manager::goBack();
    break;

  case OPT_OPEN_DIR:
    if (this->isDir)
      screen_manager::openScreen(new ui::SongListScreen(this->file.c_str()));
    else
      screen_manager::goBack();
    break;

  default:
    break;
  }
}

OptionsMenuScreen::OptionsMenuScreen(const char *file, bool isDir) {
  this->optionsMenu = new OptionsMenuList(file, isDir);
}

long OptionsMenuScreen::dependencies() {
  return this->optionsMenu->dependencies();
}
void OptionsMenuScreen::render() { this->optionsMenu->render(); }

ControlScheme OptionsMenuScreen::controlScheme() {
  return this->optionsMenu->controls;
}
} // namespace ui
