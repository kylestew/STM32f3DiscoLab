# STM32f3discover Board Bring Up

    $ :openocd -f ./open-ocd-config/stlink-v2.cfg -f ./open-ocd-config/stm32f3discovery.cfg

## Working with CLion

This repo is setup to use both Make and CMake. CMake support was added for CLion, which can build and debug the labs. Most info was taken from [this repo](https://github.com/StanislavLakhtin/clion_freertos_stm32f103_template). Currently the `.gdbinit` file in the repo root needs to be copied to your home directory. This needs to be fixed, possibly by [this](https://github.com/nagelkl/clion_embedded/blob/master/setup_gdbinit.bat) workaround.


## Tasks

### Basics

- [x] Get to [miniblink](https://github.com/1Bitsy/1bitsy-examples/tree/master/examples/1bitsy/miniblink)
- [x] Push a [Button](https://github.com/1Bitsy/1bitsy-examples/tree/master/examples/1bitsy/button)
- [ ] LED Ring Driver Library (with tests)

- [ ] Debounce button press (https://www.youtube.com/watch?v=mlRM2UfrX4A&list=PL6PplMTH29SHgRPDufZhfMRoFwRAIrzOp&index=12)
- [ ] [ADC](https://github.com/libopencm3/libopencm3-examples/tree/master/examples/stm32/f3/stm32f3-discovery/adc) reading to LED


Timers?

https://github.com/libopencm3/libopencm3-examples/tree/master/examples/stm32/f3/stm32f3-discovery

### Intermediate

7 seg display
https://github.com/kylestew/BluePillTutorials/tree/master/04_7segment
Command/Response console over serials (for debugging and testing)
???

### Hard

- [ ] Write custom driver for gyroscope unit
- [ ] Write custom driver for compass unit
- [ ] Application using both above
- [ ] Enable the USB OTG port


