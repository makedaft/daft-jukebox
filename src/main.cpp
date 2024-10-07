#include <Arduino.h>

#include "example.h"

#include "AudioTools.h"

// SineWaveGenerator<int16_t> sineWave(32000);
// GeneratedSoundStream<int16_t> music(sineWave);

MemoryStream music(mail_wav, mail_wav_len);
I2SStream i2s;                 // Output to I2S
StreamCopy copier(i2s, music); // copies sound into i2s

// Arduino Setup
void setup(void) {
  // Open Serial
  Serial.begin(BAUD_RATE);

  // start i2s
  Serial.println("starting I2S...");
  I2SConfig config = i2s.defaultConfig(TX_MODE);

  config.sample_rate = 44100;
  config.channels = 1;
  config.bits_per_sample = 16;

  config.pin_bck = 27;
  config.pin_ws = 26;
  config.pin_data = 25;

  i2s.begin(config);
  music.setLoop(true);
  music.begin();
}

// Arduino loop - copy sound to i2s
void loop() { copier.copy(); }
