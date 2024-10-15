# Notes

## Resources
- [MAX98357A datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/MAX98357A-MAX98357B.pdf)
- [esp32 + max98357a interface](https://circuitdigest.com/fullimage?i=circuitdiagram_mic/Interface-MAX98357A-I2S-Module-with-ESP32.png)
- [MOD100717 microsd module](https://components101.com/modules/micro-sd-card-module-pinout-features-datasheet-alternatives)
---

## ESP32 notes
- pin 34, 35, 36, 39 are input only so they don't have internal pullup/down resistors

## MAX98357A digital-to-analog converter notes
For stereo, the SD (shutdown mode) pin on MAX98357A needs to be:
- greater than 1.4V for **left channel**
- between 0.77V to 1.4V for **right channel**
- (not important) less than 0.77V but >0 for `(R+L)/2` mono
- (not important) grounded for shutdown

## MOD100717 microsd card module notes
- Requires 5V on Vcc (was a bit sensitive to voltage changes)
- SPI slave with chip select pin 5

## ST7735 display notes
- 128x160 resolution
- Backlight pin connected to Vcc. Don't care about controlling it. Can use pwm if needed.
- SPI slave with chip select pin 4
- MISO not connected

