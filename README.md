# x64BareBones

64-bit operative system with multitasking capabilities built on top of [x64BareBones](https://bitbucket.org/RowDaBoat/x64barebones/wiki/Home).

# Building

1. To be able to build this project, the following tools are needed:

    `build-essential` package, which includes [GCC](https://gcc.gnu.org/) and [Make](https://www.gnu.org/software/make/manual/make.html). 
    ```
    sudo apt-get install build-essential
    ```

    [NASM](https://www.nasm.us/) for compiling assembly code.
    ```
    sudo apt-get install nasm
    ``` 

    [QEMU](https://www.qemu.org/) for running the OS image. It also offers a comfortable way to do system-wide debugging. 
    ```
    sudo apt-get install qemu
    ``` 

2. Build the Toolchain
    and Kernerl From the project root directory, run:
    ```
    ./build.sh
    ```
    
# Booting   
To boot the OS, type the following command inside project root directory:
   ```
   ./run.sh
   ```