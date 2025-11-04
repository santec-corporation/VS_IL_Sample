# IL Sample

Insertion Loss software developed using C#, C++, VB.NET on Visual Studio platform.

---

## List of content

### Overview of Project

This is the example software of the swept frequency test system used for IL measurement.
    
### System Requirements
| Component               | Version/Details    |
|-------------------------|--------------------|
| Development Environment | Visual Studio 2015 |
| Windows Framework       | 4.0 or later       |
| Instrument DLL          | 2.5.1              |
| STSProcess.DLL          | 2.2.2              |
| NI DLL                  | 15.5 or later      |

### Tech Stack
  + C++
  + C#
  + VB.NET

### Configuration
   - Tunable laser TSL Series (TSL-550 / TSL-710 / TSL-570 / TSL-770)
   - Power meter MPM Series (MPM-210 / MPM-210H / MPM-211 / MPM-212 / MPM-213 / MPM-215)
    
***Note: This sample software allows you to control up to two MPM main frames (MPM-210 or MPM-210H).***

### Connection setting
  ### Tunable laser (TSL)control
   - TSL-550 / TSL-710: GPIB
   - TSL-570 / TSL-770: GPIB, TCP/IP or USB
    
  ***Note: It can be changed on the source code, but the initial value is the delimiter CRLF specification.***
    
  ### Power meter (MPM) control 
   - MPM-210 / MPM-210H: GPIB or TCP/IP
    
  ### Line of reference

  Use a BNC cable to connect the following sections.  
  - TSL - _Trigger Output_  ->  MPM - _Trigger Input_
       
  - TSL - _Power Monitor_   ->  MPM - _Power Monitor_

  <img src="https://github.com/santec-corporation/VS_ILSample/assets/135589579/d8ce59c6-d88f-4a49-8ea1-5505d712eba6" alt="PCU-100 Connection 1" width="500"/>
  <br/>
  <img src="https://github.com/santec-corporation/VS_ILSample/assets/135589579/f305d7d5-cecd-4d23-809a-e233eb9fd980" alt="PCU-100 Connection 2" width="500"/>


### Operational steps

Refer to the operational manual to run the script, 
[ English Manual ](https://github.com/santec-corporation/VS_ILSample/blob/main/Santec.IL.Swept.Test.System.Manual.V1.3_EN_20231009.pdf)

---

### For more information on Swept Test System [CLICK HERE](https://inst.santec.com/products/componenttesting/sts)

---