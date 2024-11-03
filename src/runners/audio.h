#pragma once

#define PIN_DAC_L_BLCK 14
#define PIN_DAC_L_LRC 15
#define PIN_DAC_L_DATA 22

namespace audio {
extern bool setup(void);
extern void loop();
extern void loopTask();

extern void playMp3(const char *filePath);
extern void startPlaying();
extern void pauseToggle();
extern bool isPaused();
extern void pause();

extern float getVolume();
extern void setVolume(float v);
} // namespace audio
