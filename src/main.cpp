// #include "esp32-hal-gpio.h"
#include <Arduino.h>
#include <AudioTools.h>
#include <AudioTools/AudioCodecs/CodecMP3Helix.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <esp32-hal-dac.h>
#include <esp32-hal-gpio.h>

// #include "example.h"

// MemoryStream music(example_wav, example_wav_len);
I2SStream i2s;
VolumeStream volume(i2s);
EncodedAudioStream decoder(&volume, new MP3DecoderHelix());
StreamCopy copier;
File audioFile;

#define PIN_DAC_L_BLCK 14
#define PIN_DAC_L_LRC 15
#define PIN_DAC_L_DATA 22
#define PIN_DAC_GAIN 25
#define PIN_VOLUME_UP 21
#define PIN_VOLUME_DOWN 34

void setup(void) {
  Serial.begin(BAUD_RATE);
  pinMode(PIN_VOLUME_UP, INPUT);
  pinMode(PIN_VOLUME_DOWN, INPUT);

  if (!SD.begin(5)) {
    Serial.println("SD Card Mount Failed");
    return;
  }
  Serial.println("SD Card mounted");
  audioFile = SD.open("/day-goes-on.mp3", FILE_READ);

  I2SConfig config = i2s.defaultConfig(TX_MODE);

  config.pin_bck = PIN_DAC_L_BLCK;
  config.pin_ws = PIN_DAC_L_LRC;
  config.pin_data = PIN_DAC_L_DATA;

  i2s.begin(config);
  volume.begin(config);

  decoder.begin();

  copier.begin(decoder, audioFile);
}

void set_volume(float v) {
  bool done = false;
  if (v <= 1.0)
    done = volume.setVolume(v);

  if (done)
    Serial.printf("volume = %f\n", v);
  else
    Serial.printf("unable to update volume. volume = %f\n", volume.volume());
}

void loop() {
  copier.copy();

  if (digitalRead(PIN_VOLUME_UP) > 0) {
    set_volume(volume.volume() + 0.01);
  } else if (digitalRead(PIN_VOLUME_DOWN) > 0) {
    set_volume(volume.volume() - 0.01);
  }
}
