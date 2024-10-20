#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <cstdint>

#include "lib/Renderable.h"
#include "ui/_screen.h"

namespace ui {
namespace component {
template <typename OptionType> class OptionsMenu : Renderable {
  Adafruit_SPITFT *drawCtx;

public:
  unsigned int highlightedIndex = 0;
  std::vector<OptionType> currentOptions;
  ControlScheme controls;

  virtual void onSelectOption(OptionType option) = 0;
  virtual void onGoBack() = 0;
  virtual String getOptionText(OptionType option) = 0;
  virtual String getHeaderText(OptionType option) = 0;
  virtual uint16_t getOptionColor(OptionType option, bool isHighlighted);

  OptionsMenu(Adafruit_SPITFT &drawCtx);

  virtual long dependencies() override;
  void render() override;
  void selectHighlightedOption();
  void goBack();
  void highlightNext();
  void highlightPrevious();
  unsigned int getHighlightedIndex();
  OptionType getHighlightedOption();
};
} // namespace component
} // namespace ui
