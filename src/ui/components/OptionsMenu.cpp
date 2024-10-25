#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <functional>

#include "lib/display.h"
#include "lib/logger.h"
#include "lib/utils.h"
#include "runners/music_loader.h"
#include "ui/OptionsMenuScreen.h"
#include "ui/_screen.h"
#include "ui/components/OptionsMenu.h"

namespace ui {
namespace component {
// Explicit template instantiation
template class OptionsMenu<FileInfo>;
template class OptionsMenu<ui::MenuOption>;

template <typename OptionType>
OptionsMenu<OptionType>::OptionsMenu(Adafruit_SPITFT &drawCtx) {
  this->drawCtx = &drawCtx;
  this->controls.up = std::bind(&OptionsMenu::highlightPrevious, this);
  this->controls.down = std::bind(&OptionsMenu::highlightNext, this);
  this->controls.left = std::bind(&OptionsMenu::goBack, this);
  this->controls.right = std::bind(&OptionsMenu::selectHighlightedOption, this);
}

template <typename OptionType> long OptionsMenu<OptionType>::dependencies() {
  auto header = String();
  if (!this->currentOptions.empty())
    header = this->getHeaderText(this->getHighlightedOption());
  return utils::stringHash(header.c_str()) * 100 + this->highlightedIndex;
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
  this->drawCtx->setTextColor(0x2947);
  this->drawCtx->setCursor(6, FONT_HEIGHT + 6);
  logger::printf("::: %d/%d\n", size, selectedIndex);
  if (!options.empty())
    this->drawCtx->print(this->getHeaderText(options[selectedIndex]));
  this->drawCtx->drawFastHLine(0, y - 1, w, 0xb596);

  this->drawCtx->setTextSize(1);
  this->drawCtx->setTextWrap(false);

  if (options.empty()) {
    this->drawCtx->setCursor(6, 2 * FONT_HEIGHT + 12);
    this->drawCtx->print("Empty");
    return;
  }

  for (int i = selectedIndex - 2; i < selectedIndex + 6; i++) {
    int index = i < 0 ? size + i : i % size;
    auto option = options[index];
    auto highlighted = selectedIndex == i;

    this->drawCtx->fillRect(0, y, w, y + option_height,
                            highlighted ? 0xFFFF : 0x0000);
    this->drawCtx->setTextColor(this->getOptionColor(option, highlighted));

    this->drawCtx->setCursor(padx, y + (option_height + FONT_HEIGHT) / 2);
    this->drawCtx->print(this->getOptionText(option));

    if (index == 0) {
      this->drawCtx->drawFastHLine(0, y, w, 0x2947);
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
void OptionsMenu<OptionType>::setHighlightedIndex(unsigned int index) {
  this->highlightedIndex = index;
}

template <typename OptionType>
OptionType OptionsMenu<OptionType>::getHighlightedOption() {
  auto opts = this->currentOptions;
  return opts[this->highlightedIndex];
}
template <typename OptionType>
uint16_t OptionsMenu<OptionType>::getOptionColor(OptionType option,
                                                 bool highlighted) {
  return highlighted ? 0x0000 : 0xFFFF;
}

} // namespace component
} // namespace ui
