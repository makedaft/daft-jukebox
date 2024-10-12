#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <functional>
#include <vector>

#include "lib/logger.cpp"
#include "ui/_screen.cpp"

#define FONT_HEIGHT 8
namespace ui {
template <typename OptionType> class OptionsMenu {
  Adafruit_SPITFT *drawCtx;

public:
  unsigned int highlightedIndex = 0;
  unsigned int prevHighlightedIndex = 1;
  std::vector<OptionType> currentOptions;
  ControlScheme controlScheme;

  virtual void onSelectOption(OptionType option) = 0;
  virtual void onGoBack() = 0;
  virtual String getOptionText(OptionType option) = 0;

  OptionsMenu(Adafruit_SPITFT &drawCtx) {
    this->drawCtx = &drawCtx;
    this->controlScheme.up = std::bind(&OptionsMenu::highlightPrevious, this);
    this->controlScheme.down = std::bind(&OptionsMenu::highlightNext, this);
    this->controlScheme.left = std::bind(&OptionsMenu::goBack, this);
    this->controlScheme.right =
        std::bind(&OptionsMenu::selectHighlightedOption, this);
  }

  bool shouldRender() {
    return this->highlightedIndex != this->prevHighlightedIndex;
  }

  void render() {
    this->prevHighlightedIndex = this->highlightedIndex;

    int padx = 6;
    int option_height = 20;

    int selectedIndex = this->highlightedIndex;
    auto options = this->currentOptions;
    auto size = options.size();
    unsigned int y = 30;

    this->drawCtx->setTextSize(1);
    this->drawCtx->setTextWrap(false);
    for (int i = selectedIndex - 2; i < selectedIndex + 3; i++) {
      int index = i < 0 ? size + i : i % size;
      auto option = options[index];
      auto highlighted = selectedIndex == i;

      this->drawCtx->fillRect(0, y, this->drawCtx->width(), y + option_height,
                              highlighted ? 0xFFFF : 0x0000);
      this->drawCtx->setTextColor(highlighted ? 0x0000 : 0xFFFF);

      this->drawCtx->setCursor(padx, y + (option_height + FONT_HEIGHT) / 2);
      this->drawCtx->print(this->getOptionText(option));
      y += option_height;
    }
  }

  void selectHighlightedOption() {
    this->onSelectOption(this->getHighlightedOption());
  }

  void goBack() { this->onGoBack(); }

  void highlightNext() {
    this->highlightedIndex =
        (this->highlightedIndex + 1) % this->currentOptions.size();
  }

  void highlightPrevious() {
    this->highlightedIndex = this->highlightedIndex == 0
                                 ? this->currentOptions.size() - 1
                                 : this->highlightedIndex - 1;
  }

  unsigned int getHighlightedIndex() { return this->highlightedIndex; }

  OptionType getHighlightedOption() {
    auto opts = this->currentOptions;
    return opts[this->highlightedIndex];
  }
};
} // namespace ui
