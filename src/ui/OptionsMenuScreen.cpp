#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <SPI.h>
#include <functional>
#include <vector>

#include "esp32-hal.h"
#include "lib/display.h"
#include "lib/logger.h"
#include "runners/audio.h"
#include "runners/music_loader.h"
#include "runners/screen_manager.h"
#include "ui/SongListScreen.h"
#include "ui/_screen.h"
#include "ui/components/OptionsMenu.h"

#include "ui/OptionsMenuScreen.h"

namespace ui {
const std::vector<MenuOption> songOptions = {
    {.label = "Add to queue", .id = OPT_ADD_TO_QUEUE},
    {.label = "Play next", .id = OPT_PLAY_NEXT},
    {.label = "Remove from queue", .id = OPT_REMOVE_FROM_QUEUE},
    {.label = "Play", .id = OPT_PLAY},
};

const std::vector<MenuOption> directoryOptions = {
    {.label = "Add dir to queue", .id = OPT_ADD_TO_QUEUE},
    {.label = "Open", .id = OPT_OPEN_DIR},
    {.label = "Play dir", .id = OPT_PLAY},
};

const std::vector<MenuOption> queueOptions = {
    {.label = "Play", .id = OPT_PLAY},
    {.label = "Remove from queue", .id = OPT_REMOVE_FROM_QUEUE},
    {.label = "Clear queue", .id = OPT_CLEAR_QUEUE},
};

// :::::::::::::: OptionsMenuList ::::::::::::::
OptionsMenuList::OptionsMenuList(const char *file, OptionMenuType type)
    : ui::component::OptionsMenu<MenuOption>(display::tft) {
  this->currentOptions = type == OPTS_TYPE_DIR     ? directoryOptions
                         : type == OPTS_TYPE_QUEUE ? queueOptions
                                                   : songOptions;
  this->controls.action = std::bind(&OptionsMenuList::onAction, this);
  this->file = String(file);
}

bool OptionsMenuList::isDir() const { return this->type == OPTS_TYPE_DIR; }
bool OptionsMenuList::isQueue() const { return this->type == OPTS_TYPE_QUEUE; }

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
    if (this->isDir())
      music_loader::loadDirIntoQueue(this->file, true);
    else
      music_loader::addSongToEndOfQueue(this->file);
    screen_manager::goBack();
    break;

  case OPT_PLAY:
    if (this->isDir())
      music_loader::loadDirIntoQueue(this->file, false);
    if (this->isQueue())
      music_loader::currentQueue.setCurrentAs(this->file.c_str());
    else
      music_loader::loadSongDirIntoQueue(this->file, false);
    audio::startPlaying();
    screen_manager::goBack();
    break;

  case OPT_PLAY_NEXT:
    if (!this->isDir()) {
      logger::debug((String("Play next: ") + this->file).c_str());
      music_loader::addSongToNextInQueue(this->file.c_str());
    }
    screen_manager::goBack();
    break;

  case OPT_OPEN_DIR:
    if (this->isDir())
      screen_manager::openScreen(new ui::SongListScreen(this->file.c_str()));
    else
      screen_manager::goBack();
    break;

  case OPT_REMOVE_FROM_QUEUE:
    music_loader::removeFromQueue(this->file);
    if (music_loader::currentSong().path == this->file) {
      audio::startPlaying();
    }
    screen_manager::goBack();
    break;

  case OPT_CLEAR_QUEUE:
    music_loader::clearQueue();
    audio::pause();
    screen_manager::goBack();
    break;

  default:
    break;
  }
}

// :::::::::::::: OptionsMenuScreen ::::::::::::::
OptionsMenuScreen::OptionsMenuScreen(const char *file, OptionMenuType type) {
  this->optionsMenu = new OptionsMenuList(file, type);
}

long OptionsMenuScreen::dependencies() {
  return this->optionsMenu->dependencies();
}
void OptionsMenuScreen::render() { this->optionsMenu->render(); }

ControlScheme OptionsMenuScreen::controlScheme() {
  return this->optionsMenu->controls;
}
} // namespace ui
