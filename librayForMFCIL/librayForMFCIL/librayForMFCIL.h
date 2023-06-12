// librayForMFCIL.h


#pragma once
#include <stdlib.h>
#include "string.h"
#include "stdio.h"
#include <fstream> //定义读写已命名文件的类型
#include <iostream>
#include <msclr\marshal_cppstd.h>
#include <string>
#include <vector>
using std::vector;
using std::string;

using namespace System;
using namespace Santec;
using namespace cli;
using namespace Santec::Communication;
using namespace Santec::STSProcess;
using namespace System::Diagnostics;
using namespace System::Runtime::InteropServices;

namespace librayForMFCIL {

	public ref class Class1
	{
	public:

		cli::array<String^>^ SPU_Resource;                                  //SPU(DAQ) resource
		cli::array<String^>^ USB_Resource;                                  //USB resource

		String^ TSL_Communicater;                                           // TSL communication method
		String^ MPM_Communicater;                                           // MPM communication method
		String^ PCU_Communicater;                                           // PCU commnuication method

		String^ TSL_Address;                                                // TSL Address  (GPIB/IP address/USB resource number)
		int TSL_Portnumber;                                                 // TSL LAN port number

		int MPM_Count;                                                      // MPM number of control count
		cli::array<String^>^ MPM_Address;                                   // MPM Address(GPIB/IP address/USB resource number)
		cli::array<int>^ MPM_Portnumber;                                    // MPM LAN Port number
		

		String^ PCU_Address;                                                // PCU Address(GPIB/IP address/USB resource number)
		int PCU_Portnumber;                                                 // PCU LAN Port number

		String^ SPU_DeviveID;                                               // SPU(DAQ) Device ID 
		bool PCU_useing_internal_DAQ;                                       // SPU(DAQ) use inside PCU or not  T:in PCU F: other

		static Class1^ get_instance()
		{
			if (cls1 == nullptr)
			{
				cls1 = gcnew Class1;
			}
			return cls1;
		}

		CommunicationMethod tsl_communcation_method;                       // communication method for TSL
		CommunicationMethod mpm_communcation_method;                       // communication method for MPM    
		CommunicationMethod pcu_communcation_method;                       // communication methode for PCU

		double start_wave;             // Startwavelength(nm)
		double stop_wave;              // Stopwavelength(nm)
		double step_wave;              // wavelenthg step(nm)

		TSL ^tsl;                                                           // TSL Control Class
		cli::array <MPM^> ^mpms = gcnew cli::array <MPM^>(5);               // MPM Control Class
		SPU ^spu;                                                           // SPU Control Class
		PCU ^pcu;                                                           // PCU Control Class
		ILSTS ^cal_sts;                                                     // STS Calucrate Class   PDLSTS Class -> Sub class of ILSTS   
		cli::array<STSDataStruct> ^Data_struct;        // STS data Struct for Measure
		cli::array<STSDataStruct> ^Refdata_struct; // STS data Struct for Reference
		cli::array<STSDataStructForMerge> ^Mergedata_struct;               // Data struct for merge  
		cli::array<STSMonitorStruct> ^Meas_monitor_struct;                    // Measurement monitor data struct
		cli::array<STSDataStruct> ^Ref_monitordata_struct;                      // Reference monitor data struct

		cli::array<int> ^Meas_rang;              // Measurement Range 
		bool Flag_213;                                                      // Exist 213 flag      T: Exist F: nothing
		bool Flag_215;                                                      // Exist 215 flag      T: Exist F: nothing 
		cli::array<int> ^rangeList = gcnew cli::array<int>(5);              // Range List
		cli::array<int> ^channelList = gcnew cli::array<int>(100);          // Channel List
		int rangeCnt;
		int channelCnt;
		int mpmCnt;
		STSMonitorStruct Ref_monitor_struct;
		String^ filepath;
	private:
		static Class1 ^cls1;
	};
}
