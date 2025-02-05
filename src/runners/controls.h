#pragma once

#define PIN_CONTROL_UP 21
#define PIN_CONTROL_DOWN 27
#define PIN_CONTROL_LEFT 32
#define PIN_CONTROL_RIGHT 33
#define PIN_CONTROL_ACTION 35
#define PIN_CONTROL_VOLUME 34
#define ADC_RESOLUTION 10

namespace controls {
extern bool isLocked;

extern bool setup();
extern void loop();
} // namespace controls
