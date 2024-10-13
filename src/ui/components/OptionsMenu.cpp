#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <functional>

#include "lib/display.h"
#include "lib/logger.cpp"
#include "runners/music_loader.h"
#include "ui/_screen.h"
#include "ui/components/OptionsMenu.h"

namespace ui {
namespace component {
// Explicit template instantiation
template class OptionsMenu<FileInfo>;

template <typename OptionType>
OptionsMenu<OptionType>::OptionsMenu(Adafruit_SPITFT &drawCtx) {
  this->drawCtx = &drawCtx;
  this->controlScheme.up = std::bind(&OptionsMenu::highlightPrevious, this);
  this->controlScheme.down = std::bind(&OptionsMenu::highlightNext, this);
  this->controlScheme.left = std::bind(&OptionsMenu::goBack, this);
  this->controlScheme.right =
      std::bind(&OptionsMenu::selectHighlightedOption, this);
}

template <typename OptionType> long OptionsMenu<OptionType>::dependencies() {
  auto header = this->getHeaderText(this->getHighlightedOption());
  return STRING_HASH(header.c_str()) * 100 + this->highlightedIndex;
}

template <typename OptionType> void OptionsMenu<OptionType>::render() {
  int padx = 6;
  int option_height = 20;

  int selectedIndex = this->highlightedIndex;
  auto options = this->currentOptions;
  auto size = options.size();
  unsigned int y = 20;

  uint16_t w = this->drawCtx->width();

  // Header
  this->drawCtx->setTextColor(0x5aeb);
  this->drawCtx->setCursor(6, FONT_HEIGHT + 6);
  this->drawCtx->print(this->getHeaderText(options[selectedIndex]));
  this->drawCtx->drawFastHLine(0, y - 1, w, 0xb596);

  this->drawCtx->setTextSize(1);
  this->drawCtx->setTextWrap(false);

  for (int i = selectedIndex - 2; i < selectedIndex + 6; i++) {
    int index = i < 0 ? size + i : i % size;
    auto option = options[index];
    auto highlighted = selectedIndex == i;

    this->drawCtx->fillRect(0, y, w, y + option_height,
                            highlighted ? 0xFFFF : 0x0000);
    this->drawCtx->setTextColor(highlighted ? 0x0000 : 0xFFFF);

    this->drawCtx->setCursor(padx, y + (option_height + FONT_HEIGHT) / 2);
    this->drawCtx->print(this->getOptionText(option));

    if (index == 0) {
      this->drawCtx->drawFastHLine(0, y, w, 0x5aeb);
    }

    y += option_height;
  }
}

template <typename OptionType>
void OptionsMenu<OptionType>::selectHighlightedOption() {
  this->onSelectOption(this->getHighlightedOption());
}

template <typename OptionType> void OptionsMenu<OptionType>::goBack() {
  this->onGoBack();
}

template <typename OptionType> void OptionsMenu<OptionType>::highlightNext() {
  this->highlightedIndex =
      (this->highlightedIndex + 1) % this->currentOptions.size();
}

template <typename OptionType>
void OptionsMenu<OptionType>::highlightPrevious() {
  this->highlightedIndex = this->highlightedIndex == 0
                               ? this->currentOptions.size() - 1
                               : this->highlightedIndex - 1;
}

template <typename OptionType>
unsigned int OptionsMenu<OptionType>::getHighlightedIndex() {
  return this->highlightedIndex;
}

template <typename OptionType>
OptionType OptionsMenu<OptionType>::getHighlightedOption() {
  auto opts = this->currentOptions;
  return opts[this->highlightedIndex];
}
} // namespace component
} // namespace ui
