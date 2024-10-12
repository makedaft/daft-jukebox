#pragma once
#include <Arduino.h>
#include <AudioTools.h>
#include <AudioTools/AudioCodecs/CodecMP3Helix.h>
#include <FS.h>
#include <SD.h>

#include "lib/logger.cpp"
#include "runners/music_loader.cpp"

#define PIN_DAC_L_BLCK 14
#define PIN_DAC_L_LRC 15
#define PIN_DAC_L_DATA 22
#define PIN_DAC_GAIN 25

namespace audio {
namespace {
static I2SStream i2s;
static VolumeStream volume(i2s);
static EncodedAudioStream mp3AudioStream(&volume, new MP3DecoderHelix());
static StreamCopy copier;

static I2SConfig config = i2s.defaultConfig(TX_MODE);
} // namespace

static bool setup(void) {
  config.pin_bck = PIN_DAC_L_BLCK;
  config.pin_ws = PIN_DAC_L_LRC;
  config.pin_data = PIN_DAC_L_DATA;

  if (!i2s.begin(config))
    return false;
  if (!volume.begin(config))
    return false;
  if (!mp3AudioStream.begin())
    return false;

  volume.setVolume(1.0);

  return true;
}

static void playMp3(const char *filePath) {
  logger::printf("Playing %s\n", filePath);

  copier.end();
  music_loader::loadSong(filePath);

  copier.begin(mp3AudioStream, music_loader::currentSong().file);
}

static void startPlaying() {
  audio::playMp3(music_loader::getSongPath().c_str());
  delay(200); // TODO: Maybe?
}

static inline void loop() {
  if (copier.isActive()) {
    if (copier.available() > 0) {
      copier.copy();
    } else {
      logger::debug("end of song");
      music_loader::nextSong();
      startPlaying();
    }
  }
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
