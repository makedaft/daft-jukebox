# Now
- [x] Song list
- [x] Home screen
- [x] Pause/Resume
- [x] Song queue screen
- [x] switch to 3.5mm jack
- [x] Stereo with 2 MAX98357A
- [x] Ability to lock controls on double press of action button
- [x] Options menus (song): Add song to queue, play next
- [x] Options menus (dir): Add dir to queue, Open dir, play dir (clear queue)
- [x] Battery + charging with overcharge/overvolt protection (+ booster?)
- [x] Options menus (queue): Play, Remove from queue, Clear queue
- [x] Volume control pot
- [x] Lock: disable screen (backlight) and pause re-drawing
- [x] Pin pio dependencies
- [x] Playlist files (.playlist -> list of absolute paths)
- [x] Home screen UI
- [x] issue: Empty queue crash
- [x] issue: Remove from queue no re-render
- [x] issue: Audio distortion when pressing button (use second core for audio processing?)
- [ ] issue: Issue with lock/double press action
- [ ] issue: Song changes from task dont reflect in main core (semaphore or move parts to main core)

# Next
- [ ] Build case
- [ ] Bluetooth for managing files
- [ ] issue: Minor noise issues (might need filter)
- [ ] issue: Invalid song crash (error handling: empty file, no file, etc)
- [ ] Battery indicator
- [ ] Save queue, current song, volume, etc to flash

# Maybe
- [ ] Use freertos and move copier to its own task
- [ ] Go into sleep mode if locked and paused?
- [ ] Show song progress bar in home screen (have to parse number of frames)
- [ ] Options menus (song): Add to playlist
- [ ] Remove from playlist
- [ ] Re-order playlist
- [ ] Exif parsing
- [ ] Support bluetooth headsets for audio?
