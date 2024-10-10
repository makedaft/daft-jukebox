#pragma once
#include <Arduino.h>
#include <AudioTools.h>
#include <AudioTools/AudioCodecs/CodecMP3Helix.h>
#include <FS.h>
#include <SD.h>

#include "logger.cpp"
#include "music_loader.cpp"

#define PIN_DAC_L_BLCK 14
#define PIN_DAC_L_LRC 15
#define PIN_DAC_L_DATA 22
#define PIN_DAC_GAIN 25

namespace audio {
static I2SStream i2s;
static VolumeStream volume(i2s);
static EncodedAudioStream mp3Decoder(&volume, new MP3DecoderHelix());
static StreamCopy copier;

static I2SConfig config = i2s.defaultConfig(TX_MODE);

static bool setup(void) {
  config.pin_bck = PIN_DAC_L_BLCK;
  config.pin_ws = PIN_DAC_L_LRC;
  config.pin_data = PIN_DAC_L_DATA;

  if (!i2s.begin(config))
    return false;
  if (!volume.begin(config))
    return false;
  if (!mp3Decoder.begin())
    return false;

  return true;
}

static inline void loop() {
  if (copier.available() > 0) {
    copier.copy();
  }
}

static void playMp3(const char *filePath) {
  copier.end();
  music_loader::loadSong(filePath);

  copier.begin(mp3Decoder, music_loader::currentSong().file);
}

static float getVolume() { return volume.volume(); }

static void setVolume(float v) {
  bool done = false;
  if (v > 0 && v <= 1.0)
    done = volume.setVolume(v);

  if (done)
    logger::printf("volume = %f\n", v);
  else
    logger::printf("unable to update volume. volume = %f\n", volume.volume());
}

} // namespace audio
