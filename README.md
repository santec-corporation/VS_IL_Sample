<p align="right"> <a href="https://www.santec.com/en/" target="_blank" rel="noreferrer"> <img src="https://www.santec.com/dcms_media/image/common_logo01.png" alt="santec" 
  width="250" height="45"/> </a> </p>
  
# VS_ILSample
Plug Loss test software developed using C#, C++, VB.net on Visual Studio platform.

## List of content

  - ### Overview of Project
    This is the example software of the swept frequency test system used for IL measurement.
    
  - ### System Requirements
    + Development environment  Visual Studio 2015
    +	Windows Framework        4.0 or later
    +	Instrument DLL           2.5.1
    +	STSProcess.DLL           2.2.2
    +	NI DLL                   15.5 or later	

- ### Tech Stack
  <p align="left"> <a href="https://isocpp.org/" target="_blank" rel="noreferrer"> <img src="https://isocpp.org/assets/images/cpp_logo.png" alt="cpp" 
  width="50" height="50"/> </a> </p> 
  <p align="left"> <a href="https://dotnet.microsoft.com/en-us/languages/csharp" target="_blank" rel="noreferrer"> <img src="https://th.bing.com/th/id/OIP.1C3f4vlPHd2AU3xuVL3OEQAAAA?w=228&h=256&rs=1&pid=ImgDetMain" alt="cs" 
  width="50" height="50"/> </a> </p> 
  <p align="left"> <a href="https://visualstudio.microsoft.com/vs/features/net-development/" target="_blank" rel="noreferrer"> <img src="https://th.bing.com/th/id/OIP.0-pGgiUq08VxtxFYUQZElgHaEb?w=400&h=239&rs=1&pid=ImgDetMain" alt="vb.net" 
  width="70" height="40"/> </a> </p> 
  <p align="left"> <a href="https://visualstudio.microsoft.com/" target="_blank" rel="noreferrer"> <img src="https://th.bing.com/th/id/OIP.I9TwwZg3mQbfGOk7sGJTiwHaHa?w=550&h=550&rs=1&pid=ImgDetMain" alt="visualstudio" 
  width="70" height="40"/> </a> </p> 

- ### Configuration
  - Tunable laser TSL Series (TSL-550/TSL-710/TSL-570/ TSL-770)
  - Power meter MPM Series (MPM-210/210H/211/212/213/215)
    
  ***Note: This sample software allows you to control up to two MPM main frames (MPM-210 or MPM-210H).***

- ### Connection setting
  - ### Tunable laser (TSL)control
    - TSL-550/710: GPIB
    - TSL-570/ TSL-770: GPIB, TCP/IP or USB
    
    ***Note: It can be changed on the source code, but the initial value is the delimiter CRLF specification.***
    
  - ### Power meter (MPM) control 
    - MPM-210/210H: GPIB or TCP/IP
    
  - ### Line of reference
    Use a BNC cable to connect the following sections.  
     - TSL-*** Trigger Output	->	MPM-*** Trigger Input
       
     - TSL-*** Power Monitor	->	MPM-*** Power Monitor

     ![Picture1](https://github.com/santec-corporation/VS_ILSample/assets/135589579/d8ce59c6-d88f-4a49-8ea1-5505d712eba6)
     ![Picture2](https://github.com/santec-corporation/VS_ILSample/assets/135589579/f305d7d5-cecd-4d23-809a-e233eb9fd980)

- ### Operational steps
  Refer to the operational manual to run the script, 
[ English Manual ](https://github.com/santec-corporation/VS_ILSample/blob/main/Santec.IL.Swept.Test.System.Manual.V1.3_EN_20231009.pdf)

## For more information on Swept Test System [CLICK HERE](https://inst.santec.com/products/componenttesting/sts)
