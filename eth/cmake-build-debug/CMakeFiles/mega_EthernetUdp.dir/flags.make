# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.12

# compile CXX with C:/Program Files (x86)/Arduino/hardware/tools/avr/bin/avr-g++.exe
CXX_FLAGS = -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD    -DF_CPU=16000000L -DARDUINO=10805 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR -mmcu=atmega2560 -I"C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino" -I"C:/Program Files (x86)/Arduino/libraries" -I"C:/Program Files (x86)/Arduino/hardware/arduino/avr/variants/mega" -I"C:/Program Files (x86)/Arduino/hardware/arduino/avr/libraries/SPI" -I"C:/Program Files (x86)/Arduino/hardware/arduino/avr/libraries/SPI/src" -I"C:/Program Files (x86)/Arduino/hardware/arduino/avr/libraries/SPI/utility" -I"C:/Program Files (x86)/Arduino/libraries/Ethernet/src/socket" -I"C:/Program Files (x86)/Arduino/libraries/Ethernet/src/socket/src" -I"C:/Program Files (x86)/Arduino/libraries/Ethernet/src/socket/utility" -I"C:/Program Files (x86)/Arduino/libraries/Ethernet/src/EthernetServer" -I"C:/Program Files (x86)/Arduino/libraries/Ethernet/src/EthernetServer/src" -I"C:/Program Files (x86)/Arduino/libraries/Ethernet/src/EthernetServer/utility" -I"C:/Program Files (x86)/Arduino/libraries/Ethernet/src/EthernetClient" -I"C:/Program Files (x86)/Arduino/libraries/Ethernet/src/EthernetClient/src" -I"C:/Program Files (x86)/Arduino/libraries/Ethernet/src/EthernetClient/utility" -I"C:/Program Files (x86)/Arduino/libraries/Ethernet/src/Dns" -I"C:/Program Files (x86)/Arduino/libraries/Ethernet/src/Dns/src" -I"C:/Program Files (x86)/Arduino/libraries/Ethernet/src/Dns/utility" -I"C:/Program Files (x86)/Arduino/libraries/Ethernet/src/EthernetUdp" -I"C:/Program Files (x86)/Arduino/libraries/Ethernet/src/EthernetUdp/src" -I"C:/Program Files (x86)/Arduino/libraries/Ethernet/src/EthernetUdp/utility"  -I"D:/locker1540-arduino/eth" -I"C:/Program Files (x86)/Arduino/libraries/Ethernet" -I"C:/Program Files (x86)/Arduino/libraries/Ethernet/src" -I"C:/Program Files (x86)/Arduino/libraries/DFPlayer_Mini_Mp3" -I"C:/Program Files (x86)/Arduino/libraries/DFPlayer_Mini_Mp3/src" -I"C:/Program Files (x86)/Arduino/libraries/QueueList" -I"C:/Program Files (x86)/Arduino/libraries/QueueList/src" -I"C:/Program Files (x86)/Arduino/hardware/arduino/avr/libraries/SPI" -I"C:/Program Files (x86)/Arduino/hardware/arduino/avr/libraries/SPI/src" -I"C:/Program Files (x86)/Arduino/libraries/SD" -I"C:/Program Files (x86)/Arduino/libraries/SD/src"

CXX_DEFINES = 

CXX_INCLUDES = -IC:\PROGRA~2\Arduino\LIBRAR~1\Ethernet -IC:\PROGRA~2\Arduino\LIBRAR~1\Ethernet\src -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\utility" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\w5100" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\w5100\src" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\w5100\utility" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\Dhcp" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\Dhcp\src" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\Dhcp\utility" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\util" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\util\src" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\util\utility" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetUdp" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetUdp\src" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetUdp\utility" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\Dns" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\Dns\src" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\Dns\utility" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetClient" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetClient\src" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetClient\utility" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetServer" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetServer\src" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetServer\utility" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\socket" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\socket\src" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\src\socket\utility" -IC:\PROGRA~2\Arduino\hardware\arduino\avr\LIBRAR~1\SPI -IC:\PROGRA~2\Arduino\hardware\arduino\avr\LIBRAR~1\SPI\src -I"C:\Program Files (x86)\Arduino\hardware\arduino\avr\libraries\SPI\utility" -IC:\PROGRA~2\Arduino\LIBRAR~1\DFPLAY~2 -I"C:\Program Files (x86)\Arduino\libraries\DFPlayer_Mini_Mp3\src" -I"C:\Program Files (x86)\Arduino\libraries\DFPlayer_Mini_Mp3\utility" -IC:\PROGRA~2\Arduino\hardware\arduino\avr\LIBRAR~1\SOFTWA~1 -IC:\PROGRA~2\Arduino\hardware\arduino\avr\LIBRAR~1\SOFTWA~1\src -I"C:\Program Files (x86)\Arduino\hardware\arduino\avr\libraries\SoftwareSerial\utility" -IC:\PROGRA~2\Arduino\LIBRAR~1\QUEUEL~1 -I"C:\Program Files (x86)\Arduino\libraries\QueueList\src" -I"C:\Program Files (x86)\Arduino\libraries\QueueList\utility" -IC:\PROGRA~2\Arduino\LIBRAR~1\SD -IC:\PROGRA~2\Arduino\LIBRAR~1\SD\src -I"C:\Program Files (x86)\Arduino\libraries\SD\utility" -I"C:\Program Files (x86)\Arduino\libraries\SD\src\SdFat" -I"C:\Program Files (x86)\Arduino\libraries\SD\src\SdFat\src" -I"C:\Program Files (x86)\Arduino\libraries\SD\src\SdFat\utility" -I"C:\Program Files (x86)\Arduino\libraries\SD\src\SdFatUtil" -I"C:\Program Files (x86)\Arduino\libraries\SD\src\SdFatUtil\src" -I"C:\Program Files (x86)\Arduino\libraries\SD\src\SdFatUtil\utility" 

