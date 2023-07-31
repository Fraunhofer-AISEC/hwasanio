# HWASanIO: Detecting C/C++ Intra-object Overflows with Memory Shading.
This project is not maintained. It has been published as part of the following SOAP '23 conference paper:

> Konrad Hohentanner, Florian Kasten, and Lukas Auer. 2023. 
> HWASanIO: Detecting C/C++ Intra-object Overflows with Memory Shading." 
> Proceedings of the 12th ACM SIGPLAN International Workshop on the State Of the Art in Program Analysis.
> https://dl.acm.org/doi/abs/10.1145/3589250.3596139


Note that these repositories present a **prototype** implementation and are **not** to be used in production.

## Introduction
This archive contains the necessary patches and scripts to setup and build the
HWASanIO LLVM project. Because of its dependency on the ARM Top-Byte Ignore feature, it **only supports ARMv8**. The build results in a Clang compiler that is able to build
HWASanIO-instrumented programs from C/C++ source code.

## Setup Source Code
To setup the project, run:

    $ ./setup.sh

Note that cmake and a working clang compiler is required for the build.
This script will:

  * Clone the LLVM 14 repository with the added HWASanIO Sources
  * Build the LLVM repository to generate the clang compiler with HWASanIO enabled

Afterwards, the HWASanIO code can be found in the following subdirectories:

  * `llvm/lib/Transforms/Instrumentation/HWAddressSanitizer.cpp` - Contains the modified HWAddressSanitizer Pass to instrument
    C/C++ source code with intra-object detection
  * `compiler-rt/hwasan` - Contains the source code of the
    modified HWAddresSanitizer compiler-rt library

## ARMv8 Linux: Run Example
After setting up the LLVM repository with the added HWASanIO changes, the following command will run an example showing the bug detection of HWASanIO:

    $ ./example.sh