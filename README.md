# Actually important stuff
### A. Enable float scanning and processing:
1. Add to `CMakeLists.txt`:
- `set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -u _printf_float")`

- `set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -u _scanf_float")`
2. Increase the min stack and heap size in the project manager
3. If using FreeRTOS, **CHANGE THE TASK STACK SIZE**
4. Add a stack overflow check `CHECK_FOR_STACK_OVERFLOW` in FreeRTOS config parameters in CubeMX

### B. View serial I/O on your computer:
1. Setup USB CDC by following [**this article**](https://www.bennettnotes.com/notes/stm32-blackpill-with-stmcubeide-usb-serial/) 
2. Connect the board's USB port to your computer
3. You can view serial output using `PuTTY` on Windows, `screen` on Mac, `minicom` on Linux, or using the Arduino IDE Serial Monitor. I personally like the Arduino IDE because you can monitor serial output as soon as the program starts


## Problems that took me way too long to solve, or isn't mentioned in common guides:
- **Wiring up the STM32 to the STLink:** [**this article**](https://waterpigs.co.uk/articles/black-blue-pill-stm32-st-link-connection/) helps a lot, for some reason it was quite difficult to find this - a lot of people were using the cheap STLink clone that looks like a USB.
- **Compiling using VSCode**: [**this article**](https://devblogs.microsoft.com/cppblog/importing-st-projects-into-visual-studio-code/), make sure that `STM32CubeIDE` is installed
- **Program doesn't run after pressing Launch in Run and Debug**: Press the continue button (first button on the debug bar). In general it's a really good idea to learn how to use the VSCode debugger.
- **Update STLink firmware using `STM32CubeProgrammer`**. I don't think the firmware updater is maintained anymore (you can only use it on Win10 and below)
- **vcpkg Errors**: It doesn't cause any compilation problems and I've spent way too long trying to solve it, so now the red vcpkg label just sits on the bottom of my VSCode indefinitely. YMMV, I don't think this occurs to everyone.