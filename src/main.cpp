// #include "esp32-hal-gpio.h"
#include "AudioTools.h"
#include <Arduino.h>

#include "esp32-hal-dac.h"
#include "esp32-hal-gpio.h"
#include "example.h"

MemoryStream music(example_wav, example_wav_len);
I2SStream i2s;
VolumeStream volume(i2s);
StreamCopy copier(volume, music);

#define PIN_DAC_L_BLCK 14
#define PIN_DAC_L_LRC 15
#define PIN_DAC_L_DATA 22
#define PIN_DAC_GAIN 25
#define PIN_VOLUME_UP 21
#define PIN_VOLUME_DOWN 34
// #define PIN_DAC_L_BLCK 27
// #define PIN_DAC_L_LRC 26
// #define PIN_DAC_L_DATA 25

// Arduino Setup
void setup(void) {
  // Open Serial
  Serial.begin(BAUD_RATE);

  pinMode(PIN_VOLUME_UP, INPUT);
  pinMode(PIN_VOLUME_DOWN, INPUT);

  I2SConfig config = i2s.defaultConfig(TX_MODE);

  config.sample_rate = 44100;
  config.channels = 1;
  config.bits_per_sample = 16;

  config.pin_bck = PIN_DAC_L_BLCK;
  config.pin_ws = PIN_DAC_L_LRC;
  config.pin_data = PIN_DAC_L_DATA;

  i2s.begin(config);

  volume.begin(config);

  music.setLoop(true);
  music.begin();
}

void set_volume(float v) {
  if (v <= 1.0)
    volume.setVolume(v);

  Serial.printf("volume = %f\n", v);
}

// Arduino loop - copy sound to i2s
void loop() {
  copier.copy();

  if (digitalRead(PIN_VOLUME_UP) > 0) {
    set_volume(volume.volume() + 0.01);
  } else if (digitalRead(PIN_VOLUME_DOWN) > 0) {
    set_volume(volume.volume() - 0.01);
  }
}
