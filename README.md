# Producer Consumer Problem
an example of Producer and Consumer problem

## Project Structure
**Producer-Comsumer-Problem**
*README.md*
*buffer.h/buffer.c* - define/implement buffer structure/functions and signals
*procsyn.c* - main fuction of the project && producer/consumer implementation
*makefile* - help make this project(only support gcc && make)

## Make & run
### *1.* Linux
Make sure you've installed gcc and make first:
`sudo apt update && sudo apt install gcc make -y`
Then you can make this project by makefile:
`make` 
also, you can run this command:
`gcc -c procsyn.c buffer.c -o procsyn`
Finally, you can use the *procsyn* command according to the following usage:
`[usage:] /FileDir/procsyn <sleep time> <producer nums> <consumer nums>`
### *2.* Windows
If you have minGW toolchain, you can make this project by makefile as well.In the MinGW toolchain environment, run the following command:
`make`
As the same, You can run the following command as an alternative if you cannot use make:
`gcc -c procsyn.c buffer.c -o procsyn`
If you have MSVC toolchain, you can make this project in MSVC environment like this:
`cl /EHsc /c procsyn.c buffer.c | link procsyn.obj buffer.obj /OUT:procsyn.exe`
Finally, you can use the *procsyn* command according to the following usage:
`[usage:] ./FileDir/procsyn <sleep time> <producer nums> <consumer nums>`

## NOTES
***1.*This project is an example that addresses the producer-consumer problem, implemented based on the requirements specified on pages 236-241 of *Operating System Concepts, Tenth Edition*.**
***2.*Due to the author's limited level, some parts of the code may have defects in terms of efficiency and security, and is provided solely as an example for reference.**