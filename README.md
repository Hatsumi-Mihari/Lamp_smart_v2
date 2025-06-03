# _ESP32-WiFi-IoT-Led-controller_

This project is a controller for LED strips type WS2812Bб with WiFi control via web interface, and can be run on ESP32 microcontrollers, which are equipped with SPIRAM, (ESP32, ESP32-S2, ESP32-S3, ESP32-C3), in the future it may be better optimized for these three (ESP32, ESP32-S3, ESP32-C3) platforms since the project is optimized for ESP32-S2. The project is currently in pre-beta, and at the moment, basic rendering functions and animation queues are implemented.

The project does not use external libraries except those in the ESP-IDF development environment.
# _Demo picture from IDE_
<img width="1007" alt="Снимок экрана 2025-06-04 в 00 25 06" src="https://github.com/user-attachments/assets/939ab1cc-dd63-42f5-82ce-2045ee6276b7" />
# _Project file structure_

```
main/
┣ Render_Engine/
┃ ┣ GFX_core/
┃ ┃ ┣ GFX_animation_core/
┃ ┃ ┃ ┣ GFX_effects/
┃ ┃ ┃ ┃ ┣ rainbow_fill.c
┃ ┃ ┃ ┃ ┗ rainbow_fill.h
┃ ┃ ┃ ┣ GFX_maneger_animation.c
┃ ┃ ┃ ┗ GFX_maneger_animation.h
┃ ┃ ┣ GFX_Utils.c
┃ ┃ ┗ GFX_Utils.h
┃ ┣ RE_DEBUG/
┃ ┃ ┣ RE_DEBUG.c
┃ ┃ ┣ RE_DEBUG.h
┃ ┃ ┗ RE_Time_Layer_proto.h
┃ ┣ lib/
┃ ┃ ┣ STL_Lib/
┃ ┃ ┃ ┣ List.c
┃ ┃ ┃ ┗ List.h
┃ ┃ ┣ Color_Spaces.c
┃ ┃ ┣ Color_Spaces.h
┃ ┃ ┣ HSL_color.c
┃ ┃ ┣ HSL_color.h
┃ ┃ ┗ RGB_prototype.h
┃ ┣ Render_State.c
┃ ┣ Render_State.h
┃ ┣ Render_init.c
┃ ┗ Render_init.h
┣ main/
┃ ┣ Devices_store.c
┃ ┣ Devices_store.h
┃ ┣ LED_RTM.c
┃ ┗ LED_RTM.h
┣ CMakeList                  This is the file you are currently reading
```

