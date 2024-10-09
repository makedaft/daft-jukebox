#pragma once
#include <Arduino.h>
#include <AudioTools.h>
#include <AudioTools/AudioCodecs/CodecMP3Helix.h>
#include <FS.h>
#include <SD.h>
#include <optional>

#include "log.cpp"

#define PIN_DAC_L_BLCK 14
#define PIN_DAC_L_LRC 15
#define PIN_DAC_L_DATA 22
#define PIN_DAC_GAIN 25

#define PIN_SD_CHIP_SELECT 5

namespace audio {
static I2SStream i2s;
static VolumeStream volume(i2s);
static EncodedAudioStream mp3Decoder(&volume, new MP3DecoderHelix());
static StreamCopy copier;

struct Song {
  bool isAvailable;
  String filePath;
  File file;
};

static Song currentSong = {.isAvailable = false};

static I2SConfig config = i2s.defaultConfig(TX_MODE);

static bool setup(void) {
  if (!SD.begin(PIN_SD_CHIP_SELECT)) {
    logger::error("SD Card Mount Failed");
    return false;
  }

  config.pin_bck = PIN_DAC_L_BLCK;
  config.pin_ws = PIN_DAC_L_LRC;
  config.pin_data = PIN_DAC_L_DATA;

  i2s.begin(config);
  volume.begin(config);
  mp3Decoder.begin();

  return true;
}

static inline void loop() {
  if (copier.available() > 0) {
    copier.copy();
  }
}

static void loadSongFile(const char *filePath) {
  if (currentSong.isAvailable) {
    currentSong.isAvailable = false;
    currentSong.file.close();
  }

  File file = SD.open(filePath, FILE_READ, false);
  currentSong.file = file;
  currentSong.filePath = filePath;
  currentSong.isAvailable = true;
}

static void playMp3(const char *filePath) {
  copier.end();
  loadSongFile(filePath);

  copier.begin(mp3Decoder, currentSong.file);
}

static float getVolume() { return volume.volume(); }

static void setVolume(float v) {
  bool done = false;
  if (v <= 1.0)
    done = volume.setVolume(v);

  if (done)
    logger::printf("volume = %f\n", v);
  else
    logger::printf("unable to update volume. volume = %f\n", volume.volume());
}

} // namespace audio
