# VS_ILSample
VS platform using C#, C++, VB.net development of plug loss test software

## 1. Overview of Project
This is the example software of the swept frequency test system used for IL measurement
  + Development environment  Visual Studio 2015
  +	Windows Framework        4.0 or later
  +	Instrument DLL           2.5.1
  +	STSProcess.DLL           2.2.2
  +	NI DLL                   15.5 or later

## 2. Configuration
1.	Tunable laser TSL Series (TSL-550/TSL-710/TSL-570/ TSL-770)
2.	Power meter MPM Series (MPM-210/210H/211/212/213/215)
This sample software allows you to control up to two MPM main frames (MPM-210 or MPM-210H).

## 3. Connection setting
### Tunable laser (TSL)control
  - TSL-550/710: GPIB
  - TSL-570/ TSL-770: GPIB, TCP/IP or USB
    
    Note: It can be changed on the source code, but the initial value is the delimiter CRLF specification.
### Power meter (MPM) control
  - MPM-210/210H: GPIB or TCP/IP
    
 Line of reference
   Use a BNC cable to connect the following sections.
  
  - TSL-*** Trigger Output	->	MPM-*** Trigger Input;
  - TSL-*** Power Monitor	->	MPM-*** Power Monitor;

  ![Picture1](https://github.com/santec-corporation/VS_ILSample/assets/135589579/d8ce59c6-d88f-4a49-8ea1-5505d712eba6)
  ![Picture2](https://github.com/santec-corporation/VS_ILSample/assets/135589579/f305d7d5-cecd-4d23-809a-e233eb9fd980)

## 4. Operational steps

Refer to the Manual [HERE](https://github.com/santec-corporation/VS_ILSample/files/12852241/Santec.IL.Swept.Test.System.Manual.V1.3_EN_20231009.pdf)

