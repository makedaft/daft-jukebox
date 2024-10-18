#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>

#include "runners/music_loader.h"
#include "ui/components/OptionsMenu.h"

namespace ui {
namespace component {
typedef FileInfo OptionType;

class SongList : public ui::component::OptionsMenu<OptionType> {
public:
  Adafruit_SPITFT *drawCtx;
  String dir;

  SongList(Adafruit_SPITFT &drawCtx);

  void openOptions();
  void onSelectOption(OptionType option) override;
  void onGoBack() override;
  String getOptionText(OptionType option) override;
  String getHeaderText(OptionType option) override;
  uint16_t getOptionColor(OptionType option, bool highlighted) override;
};
} // namespace component
} // namespace ui
