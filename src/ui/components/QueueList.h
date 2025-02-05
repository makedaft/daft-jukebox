#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>

#include "runners/music_loader.h"
#include "ui/components/OptionsMenu.h"

namespace ui {
namespace component {
struct QueueItem {
  String path;
};

typedef FileInfo OptionType;

class QueueList : public ui::component::OptionsMenu<OptionType> {
public:
  Adafruit_SPITFT *drawCtx;

  QueueList(Adafruit_SPITFT &drawCtx);

  void openOptions();
  void onSelectOption(OptionType option) override;
  void onGoBack() override;
  String getOptionText(OptionType option) override;
  String getHeaderText(OptionType option) override;
  uint16_t getOptionColor(OptionType option, bool highlighted) override;
  long dependencies() override;
};
} // namespace component
} // namespace ui
