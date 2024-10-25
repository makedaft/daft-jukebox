#include <Arduino.h>
#include <AudioTools.h>
#include <AudioTools/AudioCodecs/CodecMP3Helix.h>
// #include <AudioTools/Concurrency/All.h>
#include <FS.h>
#include <SD.h>

#include "lib/logger.h"
#include "runners/music_loader.h"

#include "audio.h"

namespace audio {
namespace {
static I2SStream i2s;
static VolumeStream volume(i2s);
static LogarithmicVolumeControl logVolumeControl(0.1);
static MP3DecoderHelix decoder;
static EncodedAudioStream mp3AudioStream(&volume, &decoder);
static StreamCopy copier;
// static Task task("copierTask", 10000, 1, 0);

I2SConfig config = i2s.defaultConfig(TX_MODE);
} // namespace

bool setup(void) {
  config.pin_bck = PIN_DAC_L_BLCK;
  config.pin_ws = PIN_DAC_L_LRC;
  config.pin_data = PIN_DAC_L_DATA;

  if (!i2s.begin(config))
    return false;
  if (!volume.begin(config))
    return false;
  if (!mp3AudioStream.begin())
    return false;

  volume.setVolume(0.7);
  volume.setVolumeControl(logVolumeControl);

  return true;
}

void loop() {
  if (isPaused())
    return;
  if (music_loader::currentQueue.empty())
    return;

  if (copier.available() > 0) {
    copier.copy();
  } else {
    logger::debug("end of song");
    music_loader::nextSong();
    startPlaying();
  }
}

void playSongFile(const char *filePath) {
  logger::printf("Playing %s\n", filePath);

  copier.end();
  music_loader::loadSong(filePath);

  copier.begin(mp3AudioStream, music_loader::currentSong().file);
  copier.setActive(true);
}

void startPlaying() {
  audio::playSongFile(music_loader::getSongPath().c_str());
}

void pauseToggle() {
  logger::debug(copier.isActive() ? "Pausing" : "Resuming");
  copier.setActive(!copier.isActive());
}

bool isPaused() { return !copier.isActive(); }
void pause() { copier.setActive(false); }

float getVolume() { return volume.volume(); }

void setVolume(float v) {
  v = constrain(v, 0.1, 1.);

  if (!volume.setVolume(v)) {
    logger::printf(
        "Error: unable to update volume to %f. Current volume = %f\n", v,
        volume.volume());
  }
}

} // namespace audio
