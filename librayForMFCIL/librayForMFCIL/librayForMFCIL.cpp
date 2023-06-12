// ������ DLL �ļ���

#include "stdafx.h"
#include "librayForMFCIL.h"
#include<tchar.h>

void Show_Inst_Error(int errordata)
{
	// ------------------------------------
	// Show error code
	// ------------------------------------
	cli::array<String^>^ errorstring = Enum::GetNames(ExceptionCode::typeid);
	cli::array<int>^ errorvale = static_cast<cli::array<int>^>(Enum::GetValues(ExceptionCode::typeid));
	int loop1;
	for (loop1 = 0; loop1 <= errorvale->Length - 1; loop1++)
	{
		if (errorvale[loop1] == errordata)
		{
			MessageBox(GetForegroundWindow(), (LPCTSTR)(void*)Marshal::StringToHGlobalAnsi(errorstring[loop1]), _T("prompt message"), MB_OK);
			break;
		}
	}
}

void Show_STS_Error(int errordata)
{
	// ------------------------------------
	// Show error code for STS
	// ------------------------------------
	cli::array<String^>^ errorstring = Enum::GetNames(ErrorCode::typeid);
	cli::array<int>^ errorvale = static_cast<cli::array<int>^>(Enum::GetValues(ErrorCode::typeid));
	int loop1;
	for (loop1 = 0; loop1 <= errorvale->Length - 1; loop1++)
	{
		if (errorvale[loop1] == errordata)
		{
			MessageBox(GetForegroundWindow(), (LPCTSTR)(void*)Marshal::StringToHGlobalAnsi(errorstring[loop1]), _T("prompt message"), MB_OK);
			break;
		}
	}
}

extern "C" __declspec(dllexport) char* getDAQList()
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	if (obj->spu == nullptr)
	{
		obj->spu = gcnew SPU();
	}
	cli::array<String^> ^spudev;
	int errorcode = obj->spu->Get_Device_ID(spudev);
	String^ returnStr = "";
	if (errorcode == 0) {
		for (int i = 0; i < spudev->Length; i++)
		{
			if (i != 0)
				returnStr = returnStr + "," + spudev->GetValue(i);
			else
				returnStr = returnStr + spudev->GetValue(i);
		}
	}

	char* reval = (char*)(void*)Marshal::StringToHGlobalAnsi(returnStr);
	return reval;
}

extern "C" __declspec(dllexport) char* getUSBList()
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	cli::array<String^> ^usb_resource;
	usb_resource = Santec::Communication::MainCommunication::Get_USB_Resouce();

	String^ returnStr = "";
	for (int i = 0; i < usb_resource->Length; i++) {

		if (i != 0)
			returnStr = returnStr + "," + usb_resource->GetValue(i);
		else
			returnStr = returnStr + usb_resource->GetValue(i);
	}

	char* reval = (char*)(void*)Marshal::StringToHGlobalAnsi(returnStr);
	return reval;
}

extern "C" __declspec(dllexport) int setTSLConnection(char* ip, int port)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();

	if (obj->tsl == nullptr) {
		obj->tsl = gcnew TSL();
	}

	obj->tsl_communcation_method = CommunicationMethod::TCPIP;
	obj->tsl->Terminator = CommunicationTerminator::Cr;
	obj->tsl->IPAddress = gcnew String(ip);
	obj->tsl->Port = port;

	int errorcode = obj->tsl->Connect(obj->tsl_communcation_method);
	//char* d = (char*)(void*)Marshal::StringToHGlobalAnsi(obj->tsl->Information->ProductName);
	//obj->tsl->DisConnect();

	return errorcode;
}

extern "C" __declspec(dllexport) int setTSLGPIBConnection(int addr)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();

	if (obj->tsl == nullptr) {
		obj->tsl = gcnew TSL();
	}

	obj->tsl_communcation_method = CommunicationMethod::GPIB;
	obj->tsl->Terminator = CommunicationTerminator::CrLf;
	obj->tsl->GPIBAddress = addr;
	obj->tsl->GPIBBoard = 0;
	obj->tsl->GPIBConnectType = GPIBConnectType::NI4882;

	int errorcode = obj->tsl->Connect(obj->tsl_communcation_method);
	//char* d = (char*)(void*)Marshal::StringToHGlobalAnsi(obj->tsl->Information->ProductName);
	//obj->tsl->DisConnect();

	return errorcode;
}

extern "C" __declspec(dllexport) int setTSLUSBConnection(int addr)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();

	if (obj->tsl == nullptr) {
		obj->tsl = gcnew TSL();
	}

	obj->tsl_communcation_method = CommunicationMethod::USB;
	obj->tsl->DeviceID = addr;
	obj->tsl->Terminator = CommunicationTerminator::Cr;

	int errorcode = obj->tsl->Connect(obj->tsl_communcation_method);
	//char* d = (char*)(void*)Marshal::StringToHGlobalAnsi(obj->tsl->Information->ProductName);
	//obj->tsl->DisConnect();

	return errorcode;
}

extern "C" __declspec(dllexport) int setMPMConnection(char* ip, int port, int index)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();

	MPM ^mpm = gcnew MPM();
	mpm->IPAddress = gcnew String(ip);
	mpm->Port = port;
	obj->mpm_communcation_method = CommunicationMethod::TCPIP;
	mpm->TimeOut = 11000;
	int errorcode = mpm->Connect(CommunicationMethod::TCPIP);


	obj->mpms->SetValue(mpm, index - 1);
	obj->mpmCnt = index;
	char* d = (char*)(void*)Marshal::StringToHGlobalAnsi(mpm->Information->ProductName);
	//mpm->DisConnect();
	return  errorcode;
}

extern "C" __declspec(dllexport) int setMPMGPIBConnection(int addr, int index)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();

	MPM ^mpm = gcnew MPM();
	mpm->GPIBAddress = addr;

	obj->mpm_communcation_method = CommunicationMethod::GPIB;
	mpm->TimeOut = 11000;
	int errorcode = mpm->Connect(obj->mpm_communcation_method);


	obj->mpms->SetValue(mpm, index - 1);
	obj->mpmCnt = index;
	char* d = (char*)(void*)Marshal::StringToHGlobalAnsi(mpm->Information->ProductName);
	//mpm->DisConnect();
	return  errorcode;
}

extern "C" __declspec(dllexport) char* connectMPM(int index)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();

	MPM ^mpm = (MPM ^)obj->mpms->GetValue(index - 1);

	int errorcode = mpm->Connect(CommunicationMethod::TCPIP);

	char* d = (char*)(void*)Marshal::StringToHGlobalAnsi(mpm->Information->ProductName);
	mpm->DisConnect();
	return  d;
}

extern "C" __declspec(dllexport) int setDAQConnection(char* daqStr)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	if (obj->spu == nullptr) {
		obj->spu = gcnew SPU();
	}

	obj->spu->DeviceName = gcnew String(daqStr);
	String^ ans;
	int errorcode = obj->spu->Connect(ans);

	return errorcode;
}

extern "C" __declspec(dllexport) int Check_Module_Information()
{

	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	// ------------------------------------------------------------
	// check Module information inside system
	// ------------------------------------------------------------
	int loop1;
	int loop2;
	int counter_215 = 0;                           // 215 counter 

	// MPM device loop
	for (loop1 = 0; loop1 < obj->mpmCnt; loop1++)
	{
		MPM ^mpm = (MPM ^)obj->mpms->GetValue(loop1);
		// Slot loop
		for (loop2 = 0; loop2 <= 4; loop2++)
		{
			// Enable Slot
			if (mpm->Information->ModuleEnable[loop2])
			{

				// Check MPM-215 insert
				if (mpm->Information->ModuleType[loop2] == "MPM-215")
				{
					obj->Flag_215 = true;
					counter_215 = counter_215 + 1;
				}

				// Check MPM-213 insert
				if (mpm->Information->ModuleType[loop2] == "MPM-213")
					obj->Flag_213 = true;
			}
		}
	}


	// Check MPM-215 count & Module total count
	// STS system can't use 215 together other module.
	int enable_module_count = 0;                      // enable module count

	for (int loop1 = 0; loop1 < obj->mpmCnt; loop1++) {
		MPM ^mpm = (MPM ^)obj->mpms->GetValue(loop1);
		enable_module_count = mpm->Information->NumberofModule + enable_module_count;// total module count
	}

	if (obj->Flag_215 == true)
	{
		if (enable_module_count != counter_215)
			return -1;
		return 1;
	}
	return 0;
}

extern "C" __declspec(dllexport) char* Add_TSL_Sweep_Speed()
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	// ---------------------------------------------------------
	// Add in selectable sweep speed to speed combbox
	// this function can use only TSL-570
	// ----------------------------------------------------------
	int inst_error;                       // instullment error
	array<double> ^sweep_table;           // table


	// Get Sweep speed tabele
	// Except for TSL-570 "Device Error" occurre when call this function.
	inst_error = obj->tsl->Get_Sweep_Speed_table(sweep_table);

	if (inst_error != 0 && inst_error != Convert::ToInt32(ExceptionCode::DeviceError))
		//return inst_error;
		return "error";


	// -----Add in combbox when TSL-570
	int loop1;

	String ^reval = "";
	if (inst_error != Convert::ToInt32(ExceptionCode::DeviceError))
	{
		for (loop1 = 0; loop1 < sweep_table->Length; loop1++) {
			char buffer[10];
			sprintf_s(buffer, "%.1f", (double)sweep_table->GetValue(loop1));
			String ^s = gcnew String(buffer);
			if (loop1 != 0)
				reval = reval + "," + s;
			else
				reval = reval + s;

		}
	}

	//char* reVal = "1.0,2.0,5.0,10.0,20.0,50.0,100.0,200.0";

	char* creval = (char*)(void*)Marshal::StringToHGlobalAnsi(reval);

	return creval;
}

void Prepare_dataST_Each()
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	// -----------------------------------------------
	// Prepar STS data struct
	// -----------------------------------------------
	int rangecout;                        // number of range
	int chcount;                          // number of ch 
	int loop1;                            // loop count1
	int loop2;                            // loop count2
	int loop3 = 0;
	String^ text_st = "";            // text String 
	array<String^> ^split_st;              // split string array

										   // List clear 
	obj->Meas_rang = gcnew cli::array<int>(obj->rangeCnt);                                // Measurement Range
	obj->Data_struct = gcnew cli::array<STSDataStruct>(obj->channelCnt * obj->rangeCnt);  // DataSturct of STS
	obj->Refdata_struct = gcnew cli::array<STSDataStruct>(obj->channelCnt);               // Reference data struct
	obj->Meas_monitor_struct = gcnew cli::array<STSMonitorStruct>(obj->channelCnt * obj->rangeCnt);            // Measurement monitor data struct 
	obj->Mergedata_struct = gcnew cli::array<STSDataStructForMerge>(obj->channelCnt); // DataStruct of Merge 
	obj->Ref_monitordata_struct = gcnew cli::array<STSDataStruct>(obj->channelCnt); // DataStruct of Merge 

	rangecout = obj->rangeCnt;
	chcount = obj->channelCnt;

	if (obj->Flag_215 == true)
		//If mom215 range must be set 1
		obj->Meas_rang->SetValue(1, 0);
	else
	{
		if (rangecout == 0 || chcount == 0)
		{
			//MessageBox.Show("Please check measurement parameters.", "", MessageBoxButtons.OK);
			return;
		}
		// hold range data 
		for (loop1 = 0; loop1 < obj->rangeCnt; loop1++)
		{
			//if (this.chklst_range.GetItemChecked(loop1) == true)
			obj->Meas_rang->SetValue((int)obj->rangeList->GetValue(loop1), loop1);
		}
	}
	int device_number;
	int slot_number;
	int ch_number;
	int sweep_count;                          // Sweep count 

	STSDataStruct *set_struct = new STSDataStruct();
	STSDataStructForMerge *set_struct_merge = new STSDataStructForMerge();

	// --for measurement MPM data
	for (loop2 = 0; loop2 <= obj->rangeCnt - 1; loop2++)
	{
		for (loop1 = 0; loop1 <= obj->channelCnt - 1; loop1++)
		{
			int channelInfo = (int)obj->channelList->GetValue(loop1);

			// ch parameter
			device_number = channelInfo / 100;
			slot_number = channelInfo % 100 / 10;
			ch_number = channelInfo % 100 % 10;

			// for data
			set_struct->MPMNumber = device_number;
			set_struct->SlotNumber = slot_number;
			set_struct->ChannelNumber = ch_number;
			set_struct->RangeNumber = (int)obj->Meas_rang->GetValue(loop2);
			set_struct->SweepCount = loop2 + 1;
			set_struct->SOP = 0;
			obj->Data_struct->SetValue(*set_struct, loop3);
			loop3++;
		}
	}
	loop3 = 0;
	// ---for merasurement Monitor data
	// monitor data need each sweep times data
	STSMonitorStruct *set_monitor_struct = new STSMonitorStruct();              // set struct for monitor
	STSDataStruct *set_ref_monitor_struct = new STSDataStruct();

	for (loop2 = 0; loop2 <= obj->rangeCnt - 1; loop2++)
	{
		for (loop1 = 0; loop1 <= obj->channelCnt - 1; loop1++)
		{
			int channelInfo = (int)obj->channelList->GetValue(loop1);

			// ch parameter
			device_number = channelInfo / 100;

			set_monitor_struct->MPMNumber = device_number;
			set_monitor_struct->SOP = 0;
			set_monitor_struct->SweepCount = loop2 + 1;

			obj->Meas_monitor_struct->SetValue(*set_monitor_struct, loop3);
			loop3++;
			if (obj->Meas_monitor_struct->Length == loop2 + 1)
				break;
		}
	}
	// ---for　reference MPM data & merge data
	// reference data need only 1 range data
	for (loop1 = 0; loop1 <= obj->channelCnt - 1; loop1++)
	{
		int channelInfo = (int)obj->channelList->GetValue(loop1);

		// ch parameter
		device_number = channelInfo / 100;
		slot_number = channelInfo % 100 / 10;
		ch_number = channelInfo % 100 % 10;

		// for reference data
		set_struct->MPMNumber = device_number;
		set_struct->SlotNumber = slot_number;
		set_struct->ChannelNumber = ch_number;
		set_struct->RangeNumber = 1;
		set_struct->SweepCount = 1;
		set_struct->SOP = 0;

		obj->Refdata_struct->SetValue(*set_struct, loop1);

		// for reference monitor data
		set_ref_monitor_struct->MPMNumber = device_number;
		set_ref_monitor_struct->SlotNumber = slot_number;
		set_ref_monitor_struct->ChannelNumber = ch_number;
		set_ref_monitor_struct->RangeNumber = 1;
		set_ref_monitor_struct->SOP = 0;
		set_ref_monitor_struct->SweepCount = 1;
		obj->Ref_monitordata_struct->SetValue(*set_ref_monitor_struct, loop1);

		// for mege
		set_struct_merge->MPMNumber = device_number;
		set_struct_merge->SlotNumber = slot_number;
		set_struct_merge->ChannelNumber = ch_number;
		set_struct_merge->SOP = 0;
		obj->Mergedata_struct->SetValue(*set_struct_merge, loop1);
	}
}

void Prepare_dataST()
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	// -----------------------------------------------
	// Prepar STS data struct
	// -----------------------------------------------
	int rangecout;                        // number of range
	int chcount;                          // number of ch 
	int loop1;                            // loop count1
	int loop2;                            // loop count2
	int loop3 = 0;
	String^ text_st = "";            // text String 
	array<String^> ^split_st;              // split string array

	// List clear 
	obj->Meas_rang = gcnew cli::array<int>(obj->rangeCnt);                                // Measurement Range
	obj->Data_struct = gcnew cli::array<STSDataStruct>(obj->channelCnt * obj->rangeCnt);  // DataSturct of STS
	obj->Refdata_struct = gcnew cli::array<STSDataStruct>(obj->channelCnt);               // Reference data struct
	obj->Meas_monitor_struct = gcnew cli::array<STSMonitorStruct>(obj->channelCnt * obj->rangeCnt);            // Measurement monitor data struct 
	obj->Mergedata_struct = gcnew cli::array<STSDataStructForMerge>(obj->channelCnt); // DataStruct of Merge 
	obj->Ref_monitordata_struct = gcnew cli::array<STSDataStruct>(1); // DataStruct of Merge 

	rangecout = obj->rangeCnt;
	chcount = obj->channelCnt;

	if (obj->Flag_215 == true)
		//If mom215 range must be set 1
		obj->Meas_rang->SetValue(1, 0);
	else
	{
		if (rangecout == 0 || chcount == 0)
		{
			//MessageBox.Show("Please check measurement parameters.", "", MessageBoxButtons.OK);
			return;
		}
		// hold range data 
		for (loop1 = 0; loop1 < obj->rangeCnt; loop1++)
		{
			//if (this.chklst_range.GetItemChecked(loop1) == true)
			obj->Meas_rang->SetValue((int)obj->rangeList->GetValue(loop1), loop1);
		}
	}
	int device_number;
	int slot_number;
	int ch_number;
	int sweep_count;                          // Sweep count 

	STSDataStruct *set_struct = new STSDataStruct();
	STSDataStructForMerge *set_struct_merge = new STSDataStructForMerge();

	// --for measurement MPM data
	for (loop2 = 0; loop2 <= obj->rangeCnt - 1; loop2++)
	{
		for (loop1 = 0; loop1 <= obj->channelCnt - 1; loop1++)
		{
			int channelInfo = (int)obj->channelList->GetValue(loop1);

			// ch parameter
			device_number = channelInfo / 100;
			slot_number = channelInfo % 100 / 10;
			ch_number = channelInfo % 100 % 10;

			// for data
			set_struct->MPMNumber = device_number;
			set_struct->SlotNumber = slot_number;
			set_struct->ChannelNumber = ch_number;
			set_struct->RangeNumber = (int)obj->Meas_rang->GetValue(loop2);
			set_struct->SweepCount = loop2 + 1;
			set_struct->SOP = 0;
			obj->Data_struct->SetValue(*set_struct, loop3);
			loop3++;
		}
	}
	loop3 = 0;
	// ---for merasurement Monitor data
	// monitor data need each sweep times data
	STSMonitorStruct *set_monitor_struct = new STSMonitorStruct();              // set struct for monitor
	for (loop2 = 0; loop2 <= obj->rangeCnt - 1; loop2++)
	{
		for (loop1 = 0; loop1 <= obj->channelCnt - 1; loop1++)
		{
			int channelInfo = (int)obj->channelList->GetValue(loop1);

			// ch parameter
			device_number = channelInfo / 100;

			set_monitor_struct->MPMNumber = device_number;
			set_monitor_struct->SOP = 0;
			set_monitor_struct->SweepCount = loop2 + 1;

			obj->Meas_monitor_struct->SetValue(*set_monitor_struct, loop3);
			loop3++;
			if (obj->Meas_monitor_struct->Length == loop2 + 1)
				break;
		}
	}
	// ---for　reference MPM data & merge data
	// reference data need only 1 range data
	for (loop1 = 0; loop1 <= obj->channelCnt - 1; loop1++)
	{
		int channelInfo = (int)obj->channelList->GetValue(loop1);

		// ch parameter
		device_number = channelInfo / 100;
		slot_number = channelInfo % 100 / 10;
		ch_number = channelInfo % 100 % 10;

		// for reference data
		set_struct->MPMNumber = device_number;
		set_struct->SlotNumber = slot_number;
		set_struct->ChannelNumber = ch_number;
		set_struct->RangeNumber = 1;
		set_struct->SweepCount = 1;
		set_struct->SOP = 0;

		obj->Refdata_struct->SetValue(*set_struct, loop1);

		// for mege
		set_struct_merge->MPMNumber = device_number;
		set_struct_merge->SlotNumber = slot_number;
		set_struct_merge->ChannelNumber = ch_number;
		set_struct_merge->SOP = 0;
		obj->Mergedata_struct->SetValue(*set_struct_merge, loop1);
	}


	// ----for referece Monitor data 
	STSDataStruct *set_ref_monitor_struct = new STSDataStruct();
	for (loop1 = 0; loop1 <= obj->channelCnt - 1; loop1++)
	{
		int channelInfo = (int)obj->channelList->GetValue(loop1);

		// ch parameter
		device_number = channelInfo / 100;
		slot_number = channelInfo % 100 / 10;
		ch_number = channelInfo % 100 % 10;

		// for reference monitor data
		set_ref_monitor_struct->MPMNumber = device_number;
		set_ref_monitor_struct->SlotNumber = slot_number;
		set_ref_monitor_struct->ChannelNumber = ch_number;
		set_ref_monitor_struct->RangeNumber = 1;
		set_ref_monitor_struct->SOP = 0;
		set_ref_monitor_struct->SweepCount = 1;
		obj->Ref_monitordata_struct->SetValue(*set_ref_monitor_struct, loop1);
		break;
	}

}

extern "C" __declspec(dllexport) void setSweepCondition(double startWL, double stopWL, double step, double pSpeed, double power, bool chkeach_ch)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	if (obj->cal_sts == nullptr) {
		obj->cal_sts = gcnew ILSTS();
	}
	// -------------------------------------------------------------------------
	// Set Parameter
	// --------------------------------------------------------------------------
	double startwave;             // Startwavelength(nm)
	double stopwave;              // Stopwavelength(nm)
	double set_pow;               // Power(dBm)
	double wavestep;              // wavelenthg step(nm)
	double speed;                 // Sweep Speed (nm/sec)
	int inst_error;           // instullment error


	startwave = startWL;
	stopwave = stopWL;
	wavestep = step;
	speed = pSpeed;
	set_pow = power;

	obj->start_wave = startWL;
	obj->stop_wave = stopWL;
	obj->step_wave = step;

	// ------------TSL Setting--------------------------------------------------- 
	// set Power
	inst_error = obj->tsl->Set_APC_Power_dBm(set_pow);
	if (inst_error != 0)
	{
		Show_Inst_Error(inst_error);
		return;
	}

	// busy check
	inst_error = obj->tsl->TSL_Busy_Check(3000);
	if (inst_error != 0)
	{
		Show_Inst_Error(inst_error);
		return;
	}

	double tsl_acctualstep;          // TSL output trigger step(nm)

	// set Sweep parameter
	inst_error = obj->tsl->Set_Sweep_Parameter_for_STS(startwave, stopwave, speed, wavestep, tsl_acctualstep);
	if (inst_error != 0)
	{
		Show_Inst_Error(inst_error);
		return;
	}

	// wavelength -> start wavelength
	inst_error = obj->tsl->Set_Wavelength(startwave);
	if (inst_error != 0)
	{
		Show_Inst_Error(inst_error);
		return;
	}

	// busy check
	inst_error = obj->tsl->TSL_Busy_Check(3000);
	if (inst_error != 0)
	{
		Show_Inst_Error(inst_error);
		return;
	}


	// ----------MPM setting ---------------------------------------------------;
	for (int loop1 = 0; loop1 < obj->mpmCnt; loop1++)
	{
		MPM^ mpm = (MPM^)obj->mpms->GetValue(loop1);
		// Sweep parameter setting 
		inst_error = mpm->Set_Logging_Paremeter_for_STS(startwave, stopwave, wavestep, speed, MPM::Measurement_Mode::Freerun);
		if (inst_error != 0)
		{
			Show_Inst_Error(inst_error);
			return;
		}
	}

	// ---------SPU setting------------------------------------------------------ 
	double averaging_time;

	MPM^ mpm = (MPM^)obj->mpms->GetValue(0);
	inst_error = mpm->Get_Averaging_Time(averaging_time);

	if (inst_error != 0)
	{
		Show_Inst_Error(inst_error);
		return;
	}

	// parameter setting 
	inst_error = obj->spu->Set_Sampling_Parameter(startwave, stopwave, speed, tsl_acctualstep);

	if (inst_error != 0)
	{
		Show_Inst_Error(inst_error);
		return;
	}

	// mpm averageing time-> spu
	obj->spu->AveragingTime = averaging_time;


	// -------------set STS Process parameter-----------------------------------

	int sts_error;            // sts process class error

	// data Clear 
	sts_error = obj->cal_sts->Clear_Measdata();

	if (sts_error != 0)
	{
		Show_STS_Error(sts_error);
		return;
	}

	sts_error = obj->cal_sts->Clear_Refdata();

	if (sts_error != 0)
	{
		Show_STS_Error(sts_error);
		return;
	}

	// Setting for STS rescaling mode
	sts_error = obj->cal_sts->Set_Rescaling_Setting(RescalingMode::Freerun_SPU, averaging_time, true);

	if (sts_error != 0)
	{
		Show_STS_Error(sts_error);
		return;
	}

	// Make acctual wavelength step table
	sts_error = obj->cal_sts->Make_Sweep_Wavelength_Table(startwave, stopwave, tsl_acctualstep);

	if (sts_error != 0)
	{
		Show_STS_Error(sts_error);
		return;
	}

	// Make rescaling wavelength step table
	sts_error = obj->cal_sts->Make_Target_Wavelength_Table(startwave, stopwave, wavestep);

	if (sts_error != 0)
	{
		Show_STS_Error(sts_error);
		return;
	}


	// ----prepare data struct & hold instrument condition
	// ----prepare data struct & hold instrument condition
	if (chkeach_ch == true)
	{
		Prepare_dataST_Each();
	}
	else
	{
		Prepare_dataST();
	}
	MessageBox(GetForegroundWindow(), _T("Completed."), _T("prompt message"), MB_OK);
}


extern "C" __declspec(dllexport) void setRange(int range, int index)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	obj->rangeList->SetValue(range, index - 1);
	obj->rangeCnt = index;

}
extern "C" __declspec(dllexport) bool GetFlag_213()
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	return obj->Flag_213;
}

extern "C" __declspec(dllexport) bool GetFlag_215()
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	return obj->Flag_215;
}

extern "C" __declspec(dllexport) char* GetModuleEnable(int index)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	MPM ^mpm = (MPM ^)obj->mpms->GetValue(index);
	String^ ca;
	for (int i = 0; i < mpm->Information->ModuleEnable->Length; i++)
	{
		ca = ca + mpm->Information->ModuleEnable[i].ToString() + ",";
	}
	return (char*)(void*)Marshal::StringToHGlobalAnsi(ca);
}

extern "C" __declspec(dllexport) char* GetModuleType(int index, int channel)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	MPM ^mpm = (MPM ^)obj->mpms->GetValue(index);

	return (char*)(void*)Marshal::StringToHGlobalAnsi(mpm->Information->ModuleType[channel]);
}

extern "C" __declspec(dllexport) void setChannel(int channel, int index)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	obj->channelList->SetValue(channel, index - 1);
	obj->channelCnt = index;
}

int Sweep_Process()
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	// ------------------------------------------------------------
	// Sweep Process
	// ------------------------------------------------------------
	int inst_error;               // Instullment error
	int loop1;                    // loop count 


	// MPM sampling start 
	for (loop1 = 0; loop1 < obj->mpmCnt; loop1++)
	{
		MPM ^mpm = (MPM ^)obj->mpms->GetValue(loop1);
		inst_error = mpm->Logging_Start();
		if (inst_error != 0)
			return inst_error;
	}

	// TSL waiting for start status 
	inst_error = obj->tsl->Waiting_For_Sweep_Status(2000, TSL::Sweep_Status::WaitingforTrigger);

	// ---error handling -> MPM Logging Stop
	if (inst_error != 0)
	{
		for (loop1 = 0; loop1 < obj->mpmCnt; loop1++) {
			MPM ^mpm = (MPM ^)obj->mpms->GetValue(loop1);

			mpm->Logging_Stop();
		}
		return inst_error;
	}

	// SPU sampling start
	inst_error = obj->spu->Sampling_Start(false);
	if (inst_error != 0)
		return inst_error;

	// TSL issue software trigger
	inst_error = obj->tsl->Set_Software_Trigger();

	// ---error handling -> MPM Logging Stop
	if (inst_error != 0)
	{
		for (loop1 = 0; loop1 < obj->mpmCnt; loop1++) {
			MPM ^mpm = (MPM ^)obj->mpms->GetValue(loop1);
			mpm->Logging_Stop();
		}
		return inst_error;
	}

	// SPU waiting for sampling 
	inst_error = obj->spu->Waiting_for_sampling();

	// ---error handling -> MPM Logging Stop
	if (inst_error != 0)
	{
		for (loop1 = 0; loop1 < obj->mpmCnt; loop1++) {
			MPM ^mpm = (MPM ^)obj->mpms->GetValue(loop1);
			mpm->Logging_Stop();
		}
		return inst_error;
	}

	int mpm_stauts = 0;                   // mpm logging status 0:douring measurement 1:Compleated -1:Stopped
	int mpm_count = 0;                    // mpm number of logging completed point  
	Stopwatch ^st = gcnew Stopwatch();    // stopwatch           
	bool mpm_completed_falg = true;       // mpm logging completed flag  F:not completed T:completed    
	bool isSweeping = true;
	// MPM waiting for sampling 
	st->Start();                          // stopwathc start 
	do
	{
		for (loop1 = 0; loop1 < obj->mpmCnt; loop1++)
		{
			MPM ^mpm = (MPM ^)obj->mpms->GetValue(loop1);
			inst_error = mpm->Get_Logging_Status(mpm_stauts, mpm_count);
			if (inst_error != 0)
				return inst_error;
			if (mpm_stauts == 1)
			{
				isSweeping = false;
				break;
			}
			if (st->ElapsedMilliseconds >= 5000)
			{
				//Logging time out(time out = 2sec after from SPU sampling  completed.)
				mpm_completed_falg = false;
				isSweeping = false;
				break;
			}
		}
	} while (isSweeping);

	st->Stop();

	// MPM sampling stop
	for (loop1 = 0; loop1 < obj->mpmCnt; loop1++)
	{
		MPM ^mpm = (MPM ^)obj->mpms->GetValue(loop1);
		inst_error = mpm->Logging_Stop();
		if (inst_error != 0)
			return inst_error;
	}


	// TSL Waiting for standby
	inst_error = obj->tsl->Waiting_For_Sweep_Status(5000, TSL::Sweep_Status::Standby);

	if (inst_error != 0)
		return inst_error;

	if (mpm_completed_falg == false)
		// mpm logging timeout occurred.
		return -9999;

	return 0;
}


int Get_reference_samplingdata(bool inst_flag)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	// ---------------------------------------------------------------
	// Get logging reference data & add in 
	// ---------------------------------------------------------------
	int inst_error;                        // Instullment error
	cli::array<float> ^logg_data;         // MPM Logging data
	int cal_error;                         // process error
	MPM ^mpm;

	// ----Load　Reference MPM data & add in data for STS Process Class for each channel
	for (int i = 0; i < obj->Refdata_struct->Length; i++)
	{
		STSDataStruct item = (STSDataStruct)obj->Refdata_struct->GetValue(i);

		// Read corresponded MPM data

		mpm = (MPM ^)obj->mpms->GetValue(item.MPMNumber - 1);
		inst_error = mpm->Get_Each_Channel_Logdata(item.SlotNumber, item.ChannelNumber, logg_data);


		if (inst_error != 0)
		{
			inst_flag = true;
			return inst_error;
		}

		// Add in to MPM reference data to STS Process Class
		cal_error = obj->cal_sts->Add_Ref_MPMData_CH(logg_data, item);

		if (cal_error != 0)
		{
			inst_flag = false;
			return cal_error;
		}
	}

	// ------Load Monitor data & add in data for STS Proccsess class with "STS Data Struct"
	cli::array<float> ^triggerdata;     // tigger data 
	cli::array<float> ^monitordata;     // monitor data

	inst_error = obj->spu->Get_Sampling_Rawdata(triggerdata, monitordata);

	if (inst_error != 0)
	{
		inst_flag = true;
		return inst_error;
	}

	if (triggerdata == nullptr || monitordata == nullptr)
	{
		inst_flag = true;
		return inst_error;
	}

	for each(STSDataStruct monitor_item in obj->Ref_monitordata_struct)
	{
		cal_error = obj->cal_sts->Add_Ref_MonitorData(triggerdata, monitordata, monitor_item);

		if (cal_error != 0)
		{
			inst_flag = false;
			return cal_error;
		}
	}

	return 0;
}

int Get_Each_channel_reference_samplingdata(bool inst_flag, int currentMPMNumber, int currentSlotNumber, int currentChannelNumber, int currentSweepCount)
{
	// ---------------------------------------------------------------
	// Get logging reference data & add in 
	// ---------------------------------------------------------------
	int inst_error;                        // Instullment error
	cli::array<float> ^ logg_data = nullptr;              // mpm Logging data
	int cal_error;                         // process error
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	MPM ^mpm;

	// ----Load　Reference MPM data & add in data for STS Process Class for each channel
	for each(STSDataStruct item in obj->Refdata_struct)
	{
		if ((item.MPMNumber != currentMPMNumber | item.SlotNumber != currentSlotNumber | item.ChannelNumber != currentChannelNumber))
			continue;

		// Read corresponded MPM data
		mpm = (MPM ^)obj->mpms->GetValue(item.MPMNumber - 1);
		inst_error = mpm->Get_Each_Channel_Logdata(item.SlotNumber, item.ChannelNumber, logg_data);

		if (inst_error != 0)
		{
			inst_flag = true;
			return inst_error;
		}

		// Add in to MPM reference data to STS Process Class
		cal_error = obj->cal_sts->Add_Ref_MPMData_CH(logg_data, item);

		if (cal_error != 0)
		{
			inst_flag = false;
			return cal_error;
		}
	}

	// ------Load Monitor data & add in data for STS Proccsess class with "STS Data Struct"
	cli::array<float> ^ triggerdata = nullptr;     // tigger data 
	cli::array<float> ^ monitordata = nullptr;     // monitor data

	inst_error = obj->spu->Get_Sampling_Rawdata(triggerdata, monitordata);

	if (inst_error != 0)
	{
		inst_flag = true;
		return inst_error;
	}

	for each(STSDataStruct monitor_item in obj->Ref_monitordata_struct)
	{
		cal_error = obj->cal_sts->Add_Ref_MonitorData(triggerdata, monitordata, monitor_item);
		if (cal_error != 0)
		{
			inst_flag = false;
			return cal_error;
		}
	}

	return 0;
}

extern "C" __declspec(dllexport) void reference(bool chkeach_ch)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();

	// ------------------------------------------------------------------------------
	// Get Reference
	// ------------------------------------------------------------------------------
	int inst_error;                       // Instullment error
	int loop1;

	// ----- MPM setting for selected 1st range
	for (loop1 = 0; loop1 < obj->mpmCnt; loop1++)
	{
		MPM ^mpm = (MPM ^)obj->mpms->GetValue(loop1);
		// set Range for MPM
		if (obj->Flag_215) {
			inst_error = mpm->Set_Range(1);
			inst_error = mpm->Set_READ_Range_Mode(MPM::READ_Range_Mode::Auto);

		}
		else {
			inst_error = mpm->Set_READ_Range_Mode(MPM::READ_Range_Mode::Manual);
			inst_error = mpm->Set_Range((int)obj->Meas_rang->GetValue(0));
		}

		if ((inst_error != 0))
		{
			Show_Inst_Error(inst_error);
			return;
		}
	}
	// ----Move to start wavelength with Sweep Start method.
	inst_error = obj->tsl->Sweep_Start();
	if (inst_error != 0)
		Show_Inst_Error(inst_error);

	if (chkeach_ch)
	{
		// Reference measurement one channel at a time
		for each(STSDataStruct item in obj->Refdata_struct)
		{
			char* str = (char*)(void*)Marshal::StringToHGlobalAnsi("Connect fiber to MPM" + item.MPMNumber + "_Slot" + item.SlotNumber + "_Ch" + item.ChannelNumber + ".");
			MessageBox(GetForegroundWindow(), str, _T("prompt message"), MB_OK);

			// -----Sweep 
			inst_error = Sweep_Process();
			if (inst_error == -9999)
			{
				// MPM logging timeout occurred.
				MessageBox(GetForegroundWindow(), _T("MPM Trigger receive error! Please check trigger cable connection."), _T("prompt message"), MB_OK);
				return;
			}
			if (inst_error != 0)
			{
				Show_Inst_Error(inst_error);
				return;
			}

			// ---Move to start wavelength with Sweep Start method for next sweep.
			inst_error = obj->tsl->Sweep_Start();
			if (inst_error != 0)
				Show_Inst_Error(inst_error);

			// ---get logging data & add in STSProcess class
			bool inst_flag = new bool();

			inst_error = Get_Each_channel_reference_samplingdata(inst_flag, item.MPMNumber, item.SlotNumber, item.ChannelNumber, item.SweepCount);

			if (inst_error != 0)
			{
				if (inst_flag == true)
					Show_Inst_Error(inst_error);             // Instullment error
				else
					Show_STS_Error(inst_error);// Processing error
				return;
			}

			// ------Reference data rescaling 
			int process_error;
			process_error = obj->cal_sts->Cal_RefData_Rescaling();

			if (process_error != 0)
			{
				Show_STS_Error(process_error);
				return;
			}
		}
	}
	else
	{

		// -----Sweep 
		inst_error = Sweep_Process();
		if (inst_error == -9999)
		{
			// MPM logging timeout occurred.
			MessageBox(GetForegroundWindow(), _T("MPM Trigger receive error! Please check trigger cable connection."), _T("prompt message"), MB_OK);
			return;
		}
		if (inst_error != 0)
		{
			Show_Inst_Error(inst_error);
			return;
		}

		// ---Move to start wavelength with Sweep Start method for next sweep.
		inst_error = obj->tsl->Sweep_Start();
		if (inst_error != 0)
			Show_Inst_Error(inst_error);

		// ---get logging data & add in STSProcess class
		bool inst_flag;

		inst_error = Get_reference_samplingdata(inst_flag);

		if (inst_error != 0)
		{
			if (inst_flag == true)
				Show_Inst_Error(inst_error);             // Instullment error
			else
				Show_STS_Error(inst_error);// Processing error
			return;
		}

		// ------Reference data rescaling 
		int process_error;
		process_error = obj->cal_sts->Cal_RefData_Rescaling();

		if (process_error != 0)
		{
			Show_STS_Error(process_error);
			return;
		}
	}
	// TSL Sweep Stop
	inst_error = obj->tsl->Sweep_Stop();
	if (inst_error != 0)
	{
		Show_Inst_Error(inst_error);
		return;
	}

	MessageBox(GetForegroundWindow(), _T("Completed."), _T("prompt message"), MB_OK);

}

int Get_measurement_samplingdata(int sweepcount, bool inst_flag)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	// ---------------------------------------------------------------
	// Get logging measurement data & add in 
	// ---------------------------------------------------------------
	int inst_error;                        // Instullment error
	cli::array<float> ^logg_data;         // MPM Logging data
	int cal_error;                        // process error


	// -- Load MPM Logging data & Add in STS Process class with measurment sts data struct 
	//foreach(STSDataStruct item in Data_struct)
	for (int i = 0; i < obj->Data_struct->Length; i++)
	{
		STSDataStruct item = (STSDataStruct)obj->Data_struct->GetValue(i);
		if (item.SweepCount != sweepcount)
			continue;

		// Read corresponded MPM data
		//inst_error = Get_MPM_Loggdata(item.MPMNumber, item.SlotNumber, item.ChannelNumber);
		MPM ^mpm = (MPM ^)obj->mpms->GetValue(item.MPMNumber - 1);
		inst_error = mpm->Get_Each_Channel_Logdata(item.SlotNumber, item.ChannelNumber, logg_data);

		if (inst_error != 0)
		{
			inst_flag = true;
			return inst_error;
		}

		// Add in to MPM reference data to STS Process Class
		cal_error = obj->cal_sts->Add_Meas_MPMData_CH(logg_data, item);
		if (cal_error != 0)
		{
			inst_flag = false;
			return cal_error;
		}
	}

	// --Lado SPU monitor data & Add in STS Process class with measurement monitor data struct
	cli::array<float> ^triggerdata;
	cli::array<float> ^monitordata;

	inst_error = obj->spu->Get_Sampling_Rawdata(triggerdata, monitordata);

	if (inst_error != 0)
	{
		inst_flag = true;
		return inst_error;
	}

	// Search item from measurement monitor data structure according to sweep count.
	for each(STSMonitorStruct item in obj->Meas_monitor_struct)
	{
		if (item.SweepCount == sweepcount)
		{
			cal_error = obj->cal_sts->Add_Meas_MonitorData(triggerdata, monitordata, item);

			if (cal_error != 0)
			{
				inst_flag = false;
				return cal_error;
			}
			break;
		}
	}
	return 0;
}

int Save_Measurement_data()
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	// -------------------------------------------------------
	// Save Measurement data
	// -------------------------------------------------------
	cli::array<double> ^wavelength_table;            // Rescaled wavelength table  
	cli::array<cli::array<float>^> ^lstILdata;      // IL data list 
	int process_error;                               // process class error  
	int loop1;                                       // loop count
	cli::array<float> ^ildata;                      // il data arrray

	// Get Rescaled wavelength tabel 
	process_error = obj->cal_sts->Get_Target_Wavelength_Table(wavelength_table);

	// Get IL data 
	if (obj->Flag_215 == true)
	{
		lstILdata = gcnew cli::array<cli::array<float>^>(obj->Data_struct->Length);
		for (int i = 0; i < obj->Data_struct->Length; i++)
		{
			ildata = gcnew cli::array<float>(1);
			STSDataStruct items = (STSDataStruct)obj->Data_struct->GetValue(i);
			process_error = obj->cal_sts->Get_IL_Data(ildata, items);
			if (process_error != 0)
				return process_error;

			lstILdata->SetValue(ildata, i);
		}
	}
	else
	{
		lstILdata = gcnew cli::array<cli::array<float>^>(obj->Mergedata_struct->Length);
		for (int i = 0; i < obj->Mergedata_struct->Length; i++)
		{
			ildata = gcnew cli::array<float>(1);
			STSDataStructForMerge items = (STSDataStructForMerge)obj->Mergedata_struct->GetValue(i);
			process_error = obj->cal_sts->Get_IL_Merge_Data(ildata, items);
			if (process_error != 0)
				return process_error;

			lstILdata->SetValue(ildata, i);
		}
	}

	// -----Data Save 
	std::string path = msclr::interop::marshal_as<std::string>(obj->filepath->ToString());
	if (path != "") {
		String^ write_string = "";
		std::ofstream file(path);
		if (file)
		{
			String^  hedder = "";
			hedder = "Wavelength(nm)";
			for each(STSDataStruct item in obj->Data_struct)
			{
				if (item.SweepCount != 1)
				{
					continue;
				}
				hedder = hedder + ",MPM" + item.MPMNumber.ToString() + "Slot" + item.SlotNumber.ToString() + "Ch" + item.ChannelNumber.ToString();
			}
			//write hedder
			char strContent[10000];
			sprintf(strContent, "%s", hedder); //%.6lf\n  d=lf

			file << strContent << "\n";

			for (int loop1 = 0; loop1 < wavelength_table->Length; loop1++)
			{
				char wlBuffer[150];
				sprintf_s(wlBuffer, "%.7f", (double)wavelength_table->GetValue(loop1));
				String ^wlStr = gcnew String(wlBuffer);
				write_string = wlStr;

				for (int loop2 = 0; loop2 < lstILdata->Length; loop2++) {

					char buffer[150];
					sprintf_s(buffer, "%.7f", (float)((cli::array<float>^)lstILdata->GetValue(loop2))->GetValue(loop1));
					String ^s = gcnew String(buffer);
					write_string = write_string + "," + s;

				}

				//char* cContent = (char*)(void*)Marshal::StringToHGlobalAnsi(write_string);
				char strContent[10000];
				sprintf(strContent, "%s", write_string); //%.6lf\n  d=lf
				file << strContent << "\n";
			}
		}
		file.close();
	}

	return 0;
}


extern "C" __declspec(dllexport) void Measure()
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	// -------------------------------------------------------------------------
	// Mesurement Process
	// -------------------------------------------------------------------------
	int loop1;                        // loop Count 1
	int loop2;                        // Loop count 2
	int inst_error;                   // instllment error   
	bool inst_flag = new bool();                    // instrment error flag

	// -------Measurement-----------------------------------------------

	// Move to start wavelength  with Sweep Start method.
	inst_error = obj->tsl->Sweep_Start();
	if (inst_error != 0)
	{
		Show_Inst_Error(inst_error);
		return;
	}

	// --------Rang Loop
	for (loop1 = 0; loop1 < obj->rangeCnt; loop1++)
	{

		// MPM range Setting 
		for (loop2 = 0; loop2 < obj->mpmCnt; loop2++)
		{
			MPM ^mpm = (MPM^)obj->mpms->GetValue(loop2);
			if (obj->Flag_215) {
				inst_error = mpm->Set_Range(1);
				//inst_error = mpm->Set_READ_Range_Mode(MPM::READ_Range_Mode::Auto);

			}
			else {
				inst_error = mpm->Set_READ_Range_Mode(MPM::READ_Range_Mode::Manual);
				inst_error = mpm->Set_Range((int)obj->Meas_rang->GetValue(loop1));
			}


			if (inst_error != 0)
			{
				Show_Inst_Error(inst_error);
				return;
			}
		}
		Sleep(2);
		// Sweep process
		inst_error = Sweep_Process();
		if (inst_error != 0)
		{
			Show_Inst_Error(inst_error);
			return;
		}

		// Move to start wavelength  with Sweep Start method for next sweep.
		inst_error = obj->tsl->Sweep_Start();
		if (inst_error != 0)
		{
			Show_Inst_Error(inst_error);
			return;
		}

		// get loggging data & Add in STS Process class
		inst_error = Get_measurement_samplingdata(loop1 + 1, inst_flag);

		if (inst_error != 0)
		{
			if (inst_flag == true)
				Show_Inst_Error(inst_error);
			else
				Show_STS_Error(inst_error);
			return;
		}
	}

	// ----------STS Process-------------------------------------------------

	int process_error;                    // STS　Process error

	// Rescaling
	process_error = obj->cal_sts->Cal_MeasData_Rescaling();

	if (process_error != 0)
	{
		Show_STS_Error(process_error);
		return;
	}

	// merge or IL calculate
	Module_Type merge_type;

	if (obj->Flag_215 == false)
	{
		if (obj->Flag_213 == true)
			merge_type = Module_Type::MPM_213;
		else
			merge_type = Module_Type::MPM_211;

		// Process ranges merge
		process_error = obj->cal_sts->Cal_IL_Merge(merge_type);
	}
	else
		// just IL process
		process_error = obj->cal_sts->Cal_IL();
	// data save
	process_error = Save_Measurement_data();
	if (process_error != 0)
		Show_STS_Error(process_error);

	inst_error = obj->tsl->Sweep_Stop();
	if (inst_error != 0)
	{
		Show_Inst_Error(inst_error);
		return;
	}
	MessageBox(GetForegroundWindow(), _T("Completed."), _T("prompt message"), MB_OK);

}

extern "C" __declspec(dllexport) void setFileName(char* fileName)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();

	obj->filepath = gcnew String(fileName);

}

extern "C" __declspec(dllexport) void saveRawdata(char* path)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();

	// -------------------------------------------------------------------------
	// Save mesurement raw data
	// -------------------------------------------------------------------------
	int loop1;                                        // loop1
	int loop2;                                        // loop2
	int loop3;                                        // loop3
	cli::array<double> ^wavelength_table;                  // Wavelength table
	cli::array<float> ^monitordata;
	cli::array<float> ^powerdata;
	int errorcode;                                    // Errorcode
	cli::array<cli::array<float>^> ^lstpower = gcnew cli::array<cli::array<float>^>(obj->channelCnt);

	// -- Get Wavelength table
	errorcode = obj->cal_sts->Get_Target_Wavelength_Table(wavelength_table);

	if (errorcode != 0)
	{
		Show_STS_Error(errorcode);
		return;
	}


	String^ fpath;              // File　path
	//System.IO.StreamWriter writer;            // Writer 
	String^ write_string;
	String^ hedder;


	for (loop1 = 0; loop1 < obj->rangeCnt; loop1++)
	{
		loop3 = 0;
		// get raw data same range data
		for (int i = 0; i < obj->Data_struct->Length; i++)
		{
			STSDataStruct item = (STSDataStruct)obj->Data_struct->GetValue(i);
			if (item.RangeNumber != (int)obj->Meas_rang->GetValue(loop1))
				continue;

			powerdata = gcnew cli::array<float>(1);
			errorcode = obj->cal_sts->Get_Meas_Power_Rawdata(item, powerdata);

			if (errorcode != 0)
			{
				Show_STS_Error(errorcode);
				return;
			}

			lstpower->SetValue(powerdata, loop3);
			loop3++;
		}
		//----get raw monitor data same range
		for each(STSMonitorStruct monitoritem in obj->Meas_monitor_struct)
		{
			if (monitoritem.SweepCount == loop1 + 1)
				errorcode = obj->cal_sts->Get_Meas_Monitor_Rawdata(monitoritem, monitordata);
			else
				continue;

		}
		std::string rawDataPath = msclr::interop::marshal_as<std::string>(gcnew String(path));
		// --File save at same range data 
		switch (loop1)
		{
		case 0:
		{
			rawDataPath = rawDataPath.insert(rawDataPath.length() - 4, "_1nd Range");
			break;
		}

		case 1:
		{
			rawDataPath = rawDataPath.insert(rawDataPath.length() - 4, "_2nd Range");
			break;
		}
		case 2:
		{
			rawDataPath = rawDataPath.insert(rawDataPath.length() - 4, "_3nd Range");
			break;
		}
		case 3:
		{
			rawDataPath = rawDataPath.insert(rawDataPath.length() - 4, "_4nd Range");
			break;
		}
		case 4:
		{
			rawDataPath = rawDataPath.insert(rawDataPath.length() - 4, "_5nd Range");
			break;
		}
		}

		std::ofstream file(rawDataPath);
		if (file)
		{
			hedder = "wavelength";

			//foreach(STSDataStruct item in onj->Data_struct)
			for (int i = 0; i < obj->Data_struct->Length; i++)
			{
				STSDataStruct item = (STSDataStruct)obj->Data_struct->GetValue(i);
				if (item.RangeNumber != (int)obj->Meas_rang->GetValue(loop1))
					continue;

				char buffer1[100];
				sprintf_s(buffer1, "%d", (int)item.MPMNumber);
				String ^s1 = gcnew String(buffer1);

				char buffer2[100];
				sprintf_s(buffer2, "%d", (int)item.SlotNumber);
				String ^s2 = gcnew String(buffer2);

				char buffer3[100];
				sprintf_s(buffer3, "%d", (int)item.ChannelNumber);
				String ^s3 = gcnew String(buffer3);

				hedder = hedder + "," + "MPM" + s1 + "Slot" + s2 + "Ch" + s3;
			}

			hedder = hedder + "," + "Monitordata";

			char* cHeader = (char*)(void*)Marshal::StringToHGlobalAnsi(hedder);

			char strHeader[2000];
			sprintf(strHeader, "%s", cHeader); //%.6lf\n  d=lf
			file << strHeader << "\n";


			for (loop2 = 0; loop2 < wavelength_table->Length; loop2++)
			{
				char buffer[150];
				sprintf_s(buffer, "%.7f", (double)wavelength_table->GetValue(loop2));
				String ^s = gcnew String(buffer);
				write_string = s;

				for (loop3 = 0; loop3 < lstpower->Length; loop3++) {

					char buffer1[2000];
					sprintf_s(buffer1, "%.7f", (float)((cli::array<float>^)lstpower->GetValue(loop3))->GetValue(loop2));
					String ^s1 = gcnew String(buffer1);

					write_string = write_string + "," + s1;
				}

				char buffer2[2000];
				sprintf_s(buffer2, "%.7f", (float)monitordata->GetValue(loop2));
				String ^s2 = gcnew String(buffer2);
				write_string = write_string + "," + s2;

				char* cContent = (char*)(void*)Marshal::StringToHGlobalAnsi(write_string);
				char strContent[30000];
				sprintf(strContent, "%s", write_string); //%.6lf\n  d=lf
				file << strContent << "\n";
			}

		}
		file.close();
	}
	MessageBox(GetForegroundWindow(), _T("Completed."), _T("prompt message"), MB_OK);
}

extern "C" __declspec(dllexport) void saveReference(char* path, bool chkeach_ch)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	// ---------------------------------------------------------------------------
	// Save reference Raw data
	// --------------------------------------------------------------------------- 
	int process_error;                                    // process class error
	cli::array<double> ^wavetable;                            // wavelength table
	cli::array<float> ^monitordata;                          // monitordata rescaled 

	cli::array<cli::array<float>^> ^lstpowdata = gcnew cli::array<cli::array<float>^>(obj->channelCnt);     // Power data list 
	cli::array<cli::array<float>^> ^lstmonitordata = gcnew cli::array<cli::array<float>^>(obj->Ref_monitordata_struct->Length);     // monitor data list 


	// ----Get reference Raw data (after the rescaling)

	for (int i = 0; i < obj->Refdata_struct->Length; i++)
	{
		STSDataStruct item = (STSDataStruct)obj->Refdata_struct[i];

		cli::array<float> ^powdata;                              // powerdata  rescaled    

		// monitor data is 1 data for each sweep. It can be overwrite.
		process_error = obj->cal_sts->Get_Ref_Power_Rawdata(item, powdata);
		if (process_error != 0)
		{
			Show_STS_Error(process_error);
			return;
		}

		lstpowdata[i] = powdata;
	}
	// Get reference Raw monitor data
	STSDataStruct ^get_struct = gcnew STSDataStruct();                 // struct of get
	STSDataStruct ^befor_struct = gcnew STSDataStruct();           // befor struct
	int loop;
	for each(STSDataStruct item in obj->Ref_monitordata_struct)
	{
		if (chkeach_ch)
		{
			// Reference measurement one channel at a time
			if ((item.MPMNumber == befor_struct->MPMNumber) & (item.SlotNumber == befor_struct->SlotNumber) & (item.ChannelNumber == befor_struct->ChannelNumber))
				continue;
		}
		monitordata = gcnew cli::array<float>(1);

		process_error = obj->cal_sts->Get_Ref_Monitor_Rawdata(item, monitordata);

		if (process_error != 0)
		{
			Show_STS_Error(process_error);
			return;
		}

		get_struct->MPMNumber = item.MPMNumber;
		get_struct->SlotNumber = item.SlotNumber;
		get_struct->ChannelNumber = item.ChannelNumber;
		// get_struct.SOP = item.SOP

		lstmonitordata[loop] = monitordata;
		befor_struct = get_struct;
		loop++;
	}


	// Get Target wavelengt table
	process_error = obj->cal_sts->Get_Target_Wavelength_Table(wavetable);

	if (process_error != 0)
	{
		Show_STS_Error(process_error);
		return;
	}

	String^ write_string;
	String^ hedder;
	int loop1 = 0;
	int loop2 = 0;

	std::string rawDataPath = msclr::interop::marshal_as<std::string>(gcnew String(path));
	std::ofstream file(rawDataPath);
	if (file)
	{
		hedder = "Wavelength(nm)";

		//foreach(STSDataStruct item in onj->Data_struct)
		for (int i = 0; i < obj->Data_struct->Length; i++)
		{
			STSDataStruct item = (STSDataStruct)obj->Data_struct[i];
			if (item.SweepCount != 1)
				continue;

			char buffer1[100];
			sprintf_s(buffer1, "%d", (int)item.MPMNumber);
			String ^s1 = gcnew String(buffer1);

			char buffer2[100];
			sprintf_s(buffer2, "%d", (int)item.SlotNumber);
			String ^s2 = gcnew String(buffer2);

			char buffer3[100];
			sprintf_s(buffer3, "%d", (int)item.ChannelNumber);
			String ^s3 = gcnew String(buffer3);

			hedder = hedder + "," + "MPM" + s1 + "Slot" + s2 + "Ch" + s3;
		}

		if (chkeach_ch == true)
		{
			//Reference measurement one channel at a time
			for each(STSDataStruct item in obj->Refdata_struct)
			{
				if (item.SOP != loop1)
					continue;
				hedder = hedder + ",monitordata_MPM" + item.MPMNumber.ToString() + "Slot" + item.SlotNumber.ToString() + "Ch" + item.ChannelNumber.ToString();
			}
		}
		else
		{
			hedder = hedder + ",monitordata";
		}

		char* cHeader = (char*)(void*)Marshal::StringToHGlobalAnsi(hedder);

		char strHeader[2000];
		sprintf(strHeader, "%s", cHeader); //%.6lf\n  d=lf
		file << strHeader << "\n";
		int loop3;// loop count 3

		for (loop1 = 0; loop1 < wavetable->Length; loop1++)
		{
			char buffer[150];
			sprintf_s(buffer, "%.7f", (double)wavetable[loop1]);
			String ^s = gcnew String(buffer);
			write_string = s;

			for (loop2 = 0; loop2 < lstpowdata->Length; loop2++) {

				char buffer1[2000];
				sprintf_s(buffer1, "%.7f", (float)((cli::array<float>^)lstpowdata[loop2])->GetValue(loop1));
				String ^s1 = gcnew String(buffer1);

				write_string = write_string + "," + s1;
			}
			// monitordata
			for (loop3 = 0; loop3 < lstmonitordata->Length; loop3++)
			{
				char buffer2[2000];
				sprintf_s(buffer2, "%.7f", (float)((cli::array<float>^)lstmonitordata[loop3])->GetValue(loop1));
				String ^s2 = gcnew String(buffer2);
				write_string = write_string + "," + s2;
			}

			char* cContent = (char*)(void*)Marshal::StringToHGlobalAnsi(write_string);
			char strContent[30000];
			sprintf(strContent, "%s", write_string); //%.6lf\n  d=lf
			file << strContent << "\n";
		}

	}
	file.close();
	MessageBox(GetForegroundWindow(), _T("Completed."), _T("prompt message"), MB_OK);
}

extern "C" __declspec(dllexport) void loadReference(char* path, bool chkeach_ch)
{
	librayForMFCIL::Class1 ^obj = librayForMFCIL::Class1::get_instance();
	// -----------------------------------------------------------------------------
	// Reference Data Read
	// This function must use after "SET" 
	// -----------------------------------------------------------------------------
	String ^fpath = String::Empty;

	// ----Reference file　Read 
	String ^read_st = String::Empty;                        // Read String 
	cli::array<String^> ^split_st;                             // split strin array

	// hedder Read 
	std::string refDataPath = msclr::interop::marshal_as<std::string>(gcnew String(path));

	//vector<string> svec;
	int count = 0;

	std::ifstream ifs;
	ifs.open(refDataPath);
	vector<string> svec;
	string add_str = "";
	while (ifs)
	{
		getline(ifs, add_str);
		if (add_str.compare("") != 0)
			svec.push_back(add_str);
	}
	ifs.close();

	read_st = msclr::interop::marshal_as<String^>(svec[0]);
	read_st = read_st->Trim();
	split_st = read_st->Split(',');

	// Check data cout 
	int ch_count;                // file data ch count 
	int loop1;                                            // Loop count1
	String ^chk_str = String::Empty;                        // check string
	int mpm_number;                             // MPM number
	int slot_number;                                      // Slot number
	int ch_number;                                        // ch number 
														  //Check data cout 
	if (chkeach_ch == true)
	{
		//Reference measurement one channel at a time
		ch_count = (split_st->Length - 1) / 2;
	}
	else
	{
		ch_count = split_st->Length - 2;
	}

	if (ch_count != obj->channelCnt)
	{
		MessageBox(GetForegroundWindow(), _T("Reference data mismatch.Please selecet right data."), _T("prompt message"), MB_OK);
		return;
	}

	// ----Check parameter & make reference data struct 
						   // Data struct for reference
	cli::array<STSDataStruct> ^lst_refdata_struct = gcnew cli::array<STSDataStruct>(ch_count);        // Data struct for reference List    
	bool match_flag = false;                                                   // match flag


	for (loop1 = 1; loop1 <= ch_count; loop1++)
	{
		// MPM device number 
		chk_str = split_st[loop1]->Substring(3, 1);
		mpm_number = System::Convert::ToInt32(chk_str);

		// MPM Slot number 
		chk_str = split_st[loop1]->Substring(8, 1);
		slot_number = System::Convert::ToInt32(chk_str);

		// MPM Ch number 
		chk_str = split_st[loop1]->Substring(11, 1);
		ch_number = System::Convert::ToInt32(chk_str);


		// Check exsist data in data struct 
		//foreach(STSDataStruct item in Data_struct)
		for each(STSDataStruct item in obj->Data_struct)
		{
			if (item.MPMNumber == mpm_number & item.SlotNumber == slot_number & item.ChannelNumber == ch_number)
			{
				match_flag = true;
				break;
			}
		}

		if (match_flag == false)
		{
			MessageBox(GetForegroundWindow(), _T("Reference data mismatch.Please selecet right data."), _T("prompt message"), MB_OK);
			return;
		}

		STSDataStruct refdata_strunct;
		// Add reference data struct 
		refdata_strunct.MPMNumber = mpm_number;
		refdata_strunct.SlotNumber = slot_number;
		refdata_strunct.ChannelNumber = ch_number;
		refdata_strunct.RangeNumber = 1;
		refdata_strunct.SweepCount = 1;

		lst_refdata_struct[loop1 - 1] = refdata_strunct;
	}

	// ----Read Reference data
	cli::array<cli::array<float>^> ^power;                          // Power data list 
	int counter = 0;                         // Counter
	double wavelength;                // Read Wavelength 
	bool finish = true;
	if (chkeach_ch)
	{
		// Reference measurement one channel at a time
		cli::array<cli::array<float>^> ^monitor = gcnew cli::array<cli::array<float>^>(ch_count);
		power = gcnew cli::array<cli::array<float>^>(ch_count);

		for (loop1 = 0; loop1 <= ch_count - 1; loop1++)
		{
			power[loop1] = gcnew cli::array<float>(svec.size() - 1);

			monitor[loop1] = gcnew cli::array<float>(svec.size() - 1);
		}
		for (int i = 1; i < svec.size(); i++)
		{
			read_st = msclr::interop::marshal_as<String^>(svec[i]);
			if (read_st->Equals(""))
				break;
			read_st = read_st->Trim();
			split_st = read_st->Split(',');

			// Check Start Wavelength 
			if (counter == 0)
			{
				if (System::Convert::ToDouble(split_st[0]) != obj->start_wave)
				{
					MessageBox(GetForegroundWindow(), _T("Reference data mismatch.Please selecet right data."), _T("prompt message"), MB_OK);
					return;
				}
			}

			// hold wavelength data
			wavelength = System::Convert::ToDouble(split_st[0]);
			for (loop1 = 0; loop1 <= ch_count - 1; loop1++)
			{
				power[loop1]->SetValue(System::Convert::ToSingle(split_st[loop1 + 1]), i - 1);
				monitor[loop1]->SetValue(System::Convert::ToSingle(split_st[ch_count + loop1 + 1]), i - 1);
			}
			counter = counter + 1;
		}

		// Check Stop wavelength 
		if (wavelength != obj->stop_wave)
		{
			MessageBox(GetForegroundWindow(), _T("Reference data mismatch.Please selecet right data."), _T("prompt message"), MB_OK);
			return;
		}

		// check number of point 

		int datapoint;                            // number of data point 

		datapoint = (int)(Math::Abs(obj->stop_wave - obj->start_wave) / obj->step_wave) + 1;

		if (datapoint != monitor[0]->Length)
		{
			MessageBox(GetForegroundWindow(), _T("Reference data mismatch.Please selecet right data."), _T("prompt message"), MB_OK);
			return;
		}
		// -------Add in  data to STS Process class
		int errorcode;                            // Errorcode
		counter = 0;

		for each(auto item in lst_refdata_struct)
		{
			// Add in reference data of rescaled.
			errorcode = obj->cal_sts->Add_Ref_Rawdata(power[counter], monitor[counter], item);

			if (errorcode != 0)
			{
				Show_Inst_Error(errorcode);

				return;
			}
			counter = counter + 1;
		}
	}
	else
	{
		// -------Read Reference data

		cli::array<float> ^monitor = gcnew cli::array<float>(svec.size() - 1);     // Monitordata

		power = gcnew cli::array<cli::array<float>^>(ch_count);

		for (loop1 = 0; loop1 <= ch_count - 1; loop1++)
			power[loop1] = gcnew cli::array<float>(monitor->Length);


		for (int i = 1; i < svec.size(); i++)
		{
			read_st = msclr::interop::marshal_as<String^>(svec[i]);
			if (read_st->Equals(""))
				break;
			read_st = read_st->Trim();
			split_st = read_st->Split(',');

			// Check Start Wavelength 
			if (counter == 0)
			{
				if (System::Convert::ToDouble(split_st[0]) != obj->start_wave)
				{
					MessageBox(GetForegroundWindow(), _T("Reference data mismatch.Please selecet right data."), _T("prompt message"), MB_OK);
					return;
				}
			}

			// hold wavelength data
			wavelength = System::Convert::ToDouble(split_st[0]);
			for (loop1 = 0; loop1 <= ch_count - 1; loop1++)
				power[loop1]->SetValue(System::Convert::ToSingle(split_st[loop1 + 1]), i - 1);
			monitor->SetValue(System::Convert::ToSingle(split_st[ch_count + 1]), i - 1);
			counter = counter + 1;
		}

		// Check Stop wavelength 
		if (wavelength != obj->stop_wave)
		{
			MessageBox(GetForegroundWindow(), _T("Reference data mismatch.Please selecet right data."), _T("prompt message"), MB_OK);
			return;
		}

		// check number of point 

		int datapoint;                            // number of data point 

		datapoint = (int)(Math::Abs(obj->stop_wave - obj->start_wave) / obj->step_wave) + 1;

		if (datapoint != monitor->Length)
		{
			MessageBox(GetForegroundWindow(), _T("Reference data mismatch.Please selecet right data."), _T("prompt message"), MB_OK);
			return;
		}

		// ----Add in  data to STS Process class
		int errorcode;                            // Errorcode
		counter = 0;

		for each(auto item in lst_refdata_struct)
		{
			// Add in reference data of rescaled.
			errorcode = obj->cal_sts->Add_Ref_Rawdata(power[counter], monitor, item);

			if (errorcode != 0)
			{
				Show_Inst_Error(errorcode);
				return;
			}
			counter = counter + 1;
		}
	}
	MessageBox(GetForegroundWindow(), _T("Completed."), _T("prompt message"), MB_OK);
}


