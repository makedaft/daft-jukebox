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
- [ ] Playlist files (.playlist -> list of absolute paths)
- [ ] Options menus (song): Add to playlist

# Issues
- [x] Empty queue crash
- [x] Remove from queue no re-render
- [ ] Issue with lock/double press action
- [ ] Invalid song crash (error handling: empty file, no file, etc)
- [ ] Audio distortion when pressing button
- [ ] Minor noise issues (might need filter)

# Next
- [ ] Remove from playlist
- [ ] Re-order playlist?
- [ ] Bluetooth for managing files
- [ ] Battery percentage

# Maybe
- [ ] Show song progress bar in home screen (have to parse number of frames)
- [ ] Exif parsing
- [ ] Go into sleep mode if locked and not playing music
- [ ] Use freertos and move copier to its own task
- [ ] Save last queue, volume, etc to flash
- [ ] Bluetooth for sending audio
