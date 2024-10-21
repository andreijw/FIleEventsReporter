# FIleEventsReporter

A simple Windows mini-filter to report and alert on all RPC file events

## Problem Statement

- Create a simple minifilter to track all the different RPC file events. Creation, deletion, update, etc. There will be a simple C++ cli console to load / unload the minifiter as well as the minifilter driver.
- The user can enter commands while the program is running. ["start", "unload"]. To load the minifilter and start reporting on event actions or to unload it and exit. Additionally, the cli can take the "exit"
command to exit the program during the execution. This will clear up any resources and exit the program gracefully. This will also unload the minifilter.

## Assumptions

## Design

## System (Versions should probably match this or be higher)

- gcc.exe (Rev3, Built by MSYS2 project) 13.2.0
- g++.exe (Rev3, Built by MSYS2 project) 13.2.0
- CMake version 3.28.3-msvc11
- Microsoft Visual Studio Professional 2022 (64-bit) - Preview Version 17.11.0 Preview 1.1
- Windows 10

## Memory Profiling

- The memory profiling for the application was done with the Dr. Memory (Windows-only tool)

## Build the FileEventsReporter

- The project is built using CMake, the CMakeLists.txt file is provided in the root directory. I was building it through VS 2022, but it can also be built manually as long as you have CMake and a C++ compiler installed.
- The project is built using the following commands:

```sh
mdkir out
cd out
cmake -DCMAKE_BUILD_TYPE=Release ..
make 
#cmake --build . --config Release
```

## Tests (Not currently implemented, TBD)

## Improvements

## Compatibility Issues

- This is a windows specific project b/c of the kernel driver

## Build the FileEventsReporterDriver

- Open the solution in VS and build it. It should generate the driver file

```sh
FileEventsReporterDriver.sys
```

### Sign the Driver

#### Create a Test Certificate

- Open a Developer Command Prompt for Visual Studio  (must be running as admin)
- Run the following command to create a test certificate:

```sh
makecert -r -pe -ss PrivateCertStore -n "CN=TestCert" TestCert.cer
certmgr.exe -add TestCert.cer -s -r localMachine trustedpublishers
certmgr.exe -add TestCert.cer -s -r localMachine root
```

#### Sign the driver

```sh
signtool sign /v /s PrivateCertStore /n "TestCert" /t http://timestamp.digicert.com /fd SHA256 .\x64\Debug\FileEventsReporterDriver\FileEventsReporterDriver.sys
```

#### Generate and Sign the catalog file

```sh
Inf2Cat /driver:"C:\Users\andre\Desktop\Progamming\FIleEventsReporter\FileEventsReporterDriver\x64\Debug\FileEventsReporterDriver" /os:10_X64
signtool sign /v /s PrivateCertStore /n "TestCert" /t http://timestamp.digicert.com /fd SHA256 C:\Users\andre\Desktop\Progamming\FIleEventsReporter\FileEventsReporterDriver\x64\Debug\FileEventsReporterDriver\fileeventsreporterdriver.cat
```

#### Manual install

```sh
pnputil /add-driver path\to\FileEventsReporterDriver.inf /install
```

#### Verify Driver Signature

```sh
signtool verify /kp path\to\FileEventsReporterDriver.sys
```
