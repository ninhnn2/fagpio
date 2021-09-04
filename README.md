# GPIO library for Licheepi Nano

## 1. Current support
- Control gpio output pin (E0 to E7)

## 2. How to use

### create libfagpio
- git clone https://github.com/ninhnn2/licheepi_nano_gpio.git

- cd licheepi_nano_gpio/

- make -j8

### copy library to blink example
- cp libfagpio.so examples/blink/

### compile blink exmaple
- make -j8

## 3. Run app on target

### Copy library and blink app to target (LicheePi Nano board) and run blink app

- LD_LIBRARY_PATH=./path/library/lib ./blink



