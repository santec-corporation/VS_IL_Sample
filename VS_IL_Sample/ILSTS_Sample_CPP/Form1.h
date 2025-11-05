#pragma once
#include "Instrument_Setting.h"
namespace ILSTS_Sample_CPP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Santec;
	using namespace STSProcess;
	/// <summary>
	/// Form1 摘要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//
		}
		TSL tsl;                                              // TSL control class
		cli::array<MPM^>^ mpm = gcnew cli::array<MPM^>(2);                                                // MPM control class
		SPU spu;                                              // SPU control class
		ILSTS Cal_STS;                                        // STS calucrate class
		System::Collections::Generic::List<STSDataStruct> Data_struct;                   // STS data Struct 
		System::Collections::Generic::List<STSDataStruct> Refdata_struct;                // Reference data Struct
		System::Collections::Generic::List<STSMonitorStruct> Meas_monitor_struct;           // Measurement monitor data struct
		System::Collections::Generic::List<STSDataStruct> Ref_monitordata_struct;                         // Reference monitor data struct
		System::Collections::Generic::List<STSDataStructForMerge> Mergedata_struct;      // Data struct for merge  
		System::Collections::Generic::List<int> Meas_rang;                           // Measurement Range 
		bool Flag_213;                                         // Exist 213 flag      T: Exist F: nothing
		bool Flag_215;                                         // Exist 215 flag      T: Exist F: nothing
	    internal: System::Windows::Forms::CheckBox^  chkeach_ch;
	public:
		cli::array<int> ^ MPM_Portnumber = gcnew cli::array<int>(2);             // MPM LAN port number

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	internal: System::Windows::Forms::Button^  btnsaveRawdata;
	protected:
	internal: System::Windows::Forms::Button^  Button1;
	internal: System::Windows::Forms::TextBox^  txtstopwave;
	internal: System::Windows::Forms::Button^  btnsaveref_rawdata;
	internal: System::Windows::Forms::Button^  btnmeas;
	internal: System::Windows::Forms::Button^  btnget_reference;
	internal: System::Windows::Forms::Button^  btnset;
	internal: System::Windows::Forms::Label^  Label2;
	internal: System::Windows::Forms::Label^  Label1;
	internal: System::Windows::Forms::TextBox^  txtpower;
	internal: System::Windows::Forms::ComboBox^  cmbspeed;
	internal: System::Windows::Forms::TextBox^  txtstepwave;
	internal: System::Windows::Forms::GroupBox^  GroupBox2;
	internal: System::Windows::Forms::Label^  Label7;
	internal: System::Windows::Forms::Label^  Label6;
	internal: System::Windows::Forms::CheckedListBox^  chklst_range;
	internal: System::Windows::Forms::CheckedListBox^  chklst_ch;
	internal: System::Windows::Forms::Label^  Label3;
	internal: System::Windows::Forms::GroupBox^  GroupBox1;
	internal: System::Windows::Forms::Label^  Label5;
	internal: System::Windows::Forms::Label^  Label4;
	internal: System::Windows::Forms::TextBox^  txtstartwave;
	internal: System::Windows::Forms::SaveFileDialog^  SaveFileDialog1;
	internal: System::Windows::Forms::OpenFileDialog^  OpenFileDialog1;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->btnsaveRawdata = (gcnew System::Windows::Forms::Button());
			this->Button1 = (gcnew System::Windows::Forms::Button());
			this->txtstopwave = (gcnew System::Windows::Forms::TextBox());
			this->btnsaveref_rawdata = (gcnew System::Windows::Forms::Button());
			this->btnmeas = (gcnew System::Windows::Forms::Button());
			this->btnget_reference = (gcnew System::Windows::Forms::Button());
			this->btnset = (gcnew System::Windows::Forms::Button());
			this->Label2 = (gcnew System::Windows::Forms::Label());
			this->Label1 = (gcnew System::Windows::Forms::Label());
			this->txtpower = (gcnew System::Windows::Forms::TextBox());
			this->cmbspeed = (gcnew System::Windows::Forms::ComboBox());
			this->txtstepwave = (gcnew System::Windows::Forms::TextBox());
			this->GroupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->Label7 = (gcnew System::Windows::Forms::Label());
			this->Label6 = (gcnew System::Windows::Forms::Label());
			this->chklst_range = (gcnew System::Windows::Forms::CheckedListBox());
			this->chklst_ch = (gcnew System::Windows::Forms::CheckedListBox());
			this->Label3 = (gcnew System::Windows::Forms::Label());
			this->GroupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->Label5 = (gcnew System::Windows::Forms::Label());
			this->Label4 = (gcnew System::Windows::Forms::Label());
			this->txtstartwave = (gcnew System::Windows::Forms::TextBox());
			this->SaveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->OpenFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->chkeach_ch = (gcnew System::Windows::Forms::CheckBox());
			this->GroupBox2->SuspendLayout();
			this->GroupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnsaveRawdata
			// 
			this->btnsaveRawdata->Location = System::Drawing::Point(188, 276);
			this->btnsaveRawdata->Name = L"btnsaveRawdata";
			this->btnsaveRawdata->Size = System::Drawing::Size(132, 35);
			this->btnsaveRawdata->TabIndex = 22;
			this->btnsaveRawdata->Text = L"Save Rawdata";
			this->btnsaveRawdata->UseVisualStyleBackColor = true;
			this->btnsaveRawdata->Click += gcnew System::EventHandler(this, &Form1::btnsaveRawdata_Click);
			// 
			// Button1
			// 
			this->Button1->Location = System::Drawing::Point(384, 276);
			this->Button1->Name = L"Button1";
			this->Button1->Size = System::Drawing::Size(132, 35);
			this->Button1->TabIndex = 23;
			this->Button1->Text = L"Read Reference Data";
			this->Button1->UseVisualStyleBackColor = true;
			this->Button1->Click += gcnew System::EventHandler(this, &Form1::Button1_Click);
			// 
			// txtstopwave
			// 
			this->txtstopwave->Location = System::Drawing::Point(178, 54);
			this->txtstopwave->Name = L"txtstopwave";
			this->txtstopwave->Size = System::Drawing::Size(117, 20);
			this->txtstopwave->TabIndex = 1;
			this->txtstopwave->Text = L"1600";
			// 
			// btnsaveref_rawdata
			// 
			this->btnsaveref_rawdata->Location = System::Drawing::Point(37, 276);
			this->btnsaveref_rawdata->Name = L"btnsaveref_rawdata";
			this->btnsaveref_rawdata->Size = System::Drawing::Size(132, 35);
			this->btnsaveref_rawdata->TabIndex = 21;
			this->btnsaveref_rawdata->Text = L"Save Reference Rawdata";
			this->btnsaveref_rawdata->UseVisualStyleBackColor = true;
			this->btnsaveref_rawdata->Click += gcnew System::EventHandler(this, &Form1::btnsaveref_rawdata_Click);
			// 
			// btnmeas
			// 
			this->btnmeas->Location = System::Drawing::Point(609, 165);
			this->btnmeas->Name = L"btnmeas";
			this->btnmeas->Size = System::Drawing::Size(106, 35);
			this->btnmeas->TabIndex = 20;
			this->btnmeas->Text = L"Measurement";
			this->btnmeas->UseVisualStyleBackColor = true;
			this->btnmeas->Click += gcnew System::EventHandler(this, &Form1::btnmeas_Click);
			// 
			// btnget_reference
			// 
			this->btnget_reference->Location = System::Drawing::Point(485, 165);
			this->btnget_reference->Name = L"btnget_reference";
			this->btnget_reference->Size = System::Drawing::Size(102, 35);
			this->btnget_reference->TabIndex = 19;
			this->btnget_reference->Text = L"Reference";
			this->btnget_reference->UseVisualStyleBackColor = true;
			this->btnget_reference->Click += gcnew System::EventHandler(this, &Form1::btnget_reference_Click);
			// 
			// btnset
			// 
			this->btnset->Location = System::Drawing::Point(384, 165);
			this->btnset->Name = L"btnset";
			this->btnset->Size = System::Drawing::Size(83, 35);
			this->btnset->TabIndex = 18;
			this->btnset->Text = L"SET";
			this->btnset->UseVisualStyleBackColor = true;
			this->btnset->Click += gcnew System::EventHandler(this, &Form1::btnset_Click);
			// 
			// Label2
			// 
			this->Label2->AutoSize = true;
			this->Label2->Location = System::Drawing::Point(176, 38);
			this->Label2->Name = L"Label2";
			this->Label2->Size = System::Drawing::Size(107, 13);
			this->Label2->TabIndex = 6;
			this->Label2->Text = L"StopWavelength(nm)";
			// 
			// Label1
			// 
			this->Label1->AutoSize = true;
			this->Label1->Location = System::Drawing::Point(25, 37);
			this->Label1->Name = L"Label1";
			this->Label1->Size = System::Drawing::Size(107, 13);
			this->Label1->TabIndex = 5;
			this->Label1->Text = L"StartWavelength(nm)";
			// 
			// txtpower
			// 
			this->txtpower->Location = System::Drawing::Point(562, 53);
			this->txtpower->Name = L"txtpower";
			this->txtpower->Size = System::Drawing::Size(117, 20);
			this->txtpower->TabIndex = 4;
			this->txtpower->Text = L"0";
			// 
			// cmbspeed
			// 
			this->cmbspeed->FormattingEnabled = true;
			this->cmbspeed->Location = System::Drawing::Point(437, 53);
			this->cmbspeed->Name = L"cmbspeed";
			this->cmbspeed->Size = System::Drawing::Size(102, 21);
			this->cmbspeed->TabIndex = 3;
			// 
			// txtstepwave
			// 
			this->txtstepwave->Location = System::Drawing::Point(314, 54);
			this->txtstepwave->Name = L"txtstepwave";
			this->txtstepwave->Size = System::Drawing::Size(100, 20);
			this->txtstepwave->TabIndex = 2;
			this->txtstepwave->Text = L"0.01";
			// 
			// GroupBox2
			// 
			this->GroupBox2->Controls->Add(this->Label7);
			this->GroupBox2->Controls->Add(this->Label6);
			this->GroupBox2->Controls->Add(this->chklst_range);
			this->GroupBox2->Controls->Add(this->chklst_ch);
			this->GroupBox2->Location = System::Drawing::Point(25, 155);
			this->GroupBox2->Name = L"GroupBox2";
			this->GroupBox2->Size = System::Drawing::Size(332, 89);
			this->GroupBox2->TabIndex = 17;
			this->GroupBox2->TabStop = false;
			this->GroupBox2->Text = L"Measurement ch And Range";
			// 
			// Label7
			// 
			this->Label7->AutoSize = true;
			this->Label7->Location = System::Drawing::Point(176, 21);
			this->Label7->Name = L"Label7";
			this->Label7->Size = System::Drawing::Size(106, 13);
			this->Label7->TabIndex = 3;
			this->Label7->Text = L"Measurement Range";
			// 
			// Label6
			// 
			this->Label6->AutoSize = true;
			this->Label6->Location = System::Drawing::Point(10, 21);
			this->Label6->Name = L"Label6";
			this->Label6->Size = System::Drawing::Size(86, 13);
			this->Label6->TabIndex = 2;
			this->Label6->Text = L"Measurement ch";
			// 
			// chklst_range
			// 
			this->chklst_range->FormattingEnabled = true;
			this->chklst_range->Location = System::Drawing::Point(177, 37);
			this->chklst_range->Name = L"chklst_range";
			this->chklst_range->Size = System::Drawing::Size(118, 34);
			this->chklst_range->TabIndex = 1;
			// 
			// chklst_ch
			// 
			this->chklst_ch->FormattingEnabled = true;
			this->chklst_ch->Location = System::Drawing::Point(12, 37);
			this->chklst_ch->Name = L"chklst_ch";
			this->chklst_ch->Size = System::Drawing::Size(135, 34);
			this->chklst_ch->TabIndex = 0;
			// 
			// Label3
			// 
			this->Label3->AutoSize = true;
			this->Label3->Location = System::Drawing::Point(312, 38);
			this->Label3->Name = L"Label3";
			this->Label3->Size = System::Drawing::Size(107, 13);
			this->Label3->TabIndex = 7;
			this->Label3->Text = L"WavelengthStep(nm)";
			// 
			// GroupBox1
			// 
			this->GroupBox1->Controls->Add(this->Label5);
			this->GroupBox1->Controls->Add(this->Label4);
			this->GroupBox1->Controls->Add(this->Label3);
			this->GroupBox1->Controls->Add(this->Label2);
			this->GroupBox1->Controls->Add(this->Label1);
			this->GroupBox1->Controls->Add(this->txtpower);
			this->GroupBox1->Controls->Add(this->cmbspeed);
			this->GroupBox1->Controls->Add(this->txtstepwave);
			this->GroupBox1->Controls->Add(this->txtstopwave);
			this->GroupBox1->Controls->Add(this->txtstartwave);
			this->GroupBox1->Location = System::Drawing::Point(25, 37);
			this->GroupBox1->Name = L"GroupBox1";
			this->GroupBox1->Size = System::Drawing::Size(709, 101);
			this->GroupBox1->TabIndex = 16;
			this->GroupBox1->TabStop = false;
			this->GroupBox1->Text = L"Sweep Setting";
			// 
			// Label5
			// 
			this->Label5->AutoSize = true;
			this->Label5->Location = System::Drawing::Point(560, 37);
			this->Label5->Name = L"Label5";
			this->Label5->Size = System::Drawing::Size(87, 13);
			this->Label5->TabIndex = 9;
			this->Label5->Text = L"TSL Power(dBm)";
			// 
			// Label4
			// 
			this->Label4->AutoSize = true;
			this->Label4->Location = System::Drawing::Point(435, 37);
			this->Label4->Name = L"Label4";
			this->Label4->Size = System::Drawing::Size(113, 13);
			this->Label4->TabIndex = 8;
			this->Label4->Text = L"SweepSpeed(nm/sec)";
			// 
			// txtstartwave
			// 
			this->txtstartwave->Location = System::Drawing::Point(27, 54);
			this->txtstartwave->Name = L"txtstartwave";
			this->txtstartwave->Size = System::Drawing::Size(117, 20);
			this->txtstartwave->TabIndex = 0;
			this->txtstartwave->Text = L"1500";
			// 
			// OpenFileDialog1
			// 
			this->OpenFileDialog1->FileName = L"OpenFileDialog1";
			// 
			// chkeach_ch
			// 
			this->chkeach_ch->AutoSize = true;
			this->chkeach_ch->Location = System::Drawing::Point(384, 206);
			this->chkeach_ch->Name = L"chkeach_ch";
			this->chkeach_ch->Size = System::Drawing::Size(145, 17);
			this->chkeach_ch->TabIndex = 24;
			this->chkeach_ch->Text = L"each channel individually";
			this->chkeach_ch->UseVisualStyleBackColor = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(758, 348);
			this->Controls->Add(this->chkeach_ch);
			this->Controls->Add(this->btnsaveRawdata);
			this->Controls->Add(this->Button1);
			this->Controls->Add(this->btnsaveref_rawdata);
			this->Controls->Add(this->btnmeas);
			this->Controls->Add(this->btnget_reference);
			this->Controls->Add(this->btnset);
			this->Controls->Add(this->GroupBox2);
			this->Controls->Add(this->GroupBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Form1";
			this->Text = L"STS IL sample software";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->GroupBox2->ResumeLayout(false);
			this->GroupBox2->PerformLayout();
			this->GroupBox1->ResumeLayout(false);
			this->GroupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnset_Click(System::Object^  sender, System::EventArgs^  e) {
		// -------------------------------------------------------------------------
		// Set Parameter
		// --------------------------------------------------------------------------
		double startwave;             // Startwavelength(nm)
		double stopwave;              // Stopwavelength(nm)
		double set_pow;               // Power(dBm)
		double wavestep;              // wavelenthg step(nm)
		double speed;                 // Sweep Speed (nm/sec)
		int inst_error;           // instullment error


		startwave = double::Parse(txtstartwave->Text);
		stopwave = double::Parse(txtstopwave->Text);
		wavestep = double::Parse(txtstepwave->Text);
		speed = double::Parse(cmbspeed->Text);
		set_pow = double::Parse(txtpower->Text);

		// ------------TSL Setting--------------------------------------------------- 
		// set Power
		inst_error = tsl.Set_APC_Power_dBm(set_pow);
		if (inst_error != 0)
		{
			Show_Inst_Error(inst_error);
			return;
		}

		// busy check
		inst_error = tsl.TSL_Busy_Check(3000);
		if (inst_error != 0)
		{
			Show_Inst_Error(inst_error);
			return;
		}

		double tsl_acctualstep;          // TSL output trigger step(nm)

										 // set Sweep parameter
		inst_error = tsl.Set_Sweep_Parameter_for_STS(startwave, stopwave, speed, wavestep, tsl_acctualstep);
		if (inst_error != 0)
		{
			Show_Inst_Error(inst_error);
			return;
		}

		// wavelength -> start wavelength
		inst_error = tsl.Set_Wavelength(startwave);
		if (inst_error != 0)
		{
			Show_Inst_Error(inst_error);
			return;
		}

		// busy check
		inst_error = tsl.TSL_Busy_Check(3000);
		if (inst_error != 0)
		{
			Show_Inst_Error(inst_error);
			return;
		}


		// ----------MPM setting ---------------------------------------------------
		int loop1;

		for (loop1 = 0; loop1 <= mpm->GetUpperBound(0); loop1++)
		{
			// Sweep parameter setting 
			inst_error = mpm[loop1]->Set_Logging_Paremeter_for_STS(startwave, stopwave, wavestep, speed, Santec::MPM::Measurement_Mode::Freerun);
			if (inst_error != 0)
			{
				Show_Inst_Error(inst_error);
				return;
			}
			inst_error = mpm[loop1]->Set_Wavelength((startwave + stopwave) / 2);
			if (inst_error != 0)
			{
				Show_Inst_Error(inst_error);
				return;
			}
		}

		// ---------SPU setting------------------------------------------------------ 
		double averaging_time;

		inst_error = mpm[0]->Get_Averaging_Time(averaging_time);

		if (inst_error != 0)
		{
			Show_Inst_Error(inst_error);
			return;
		}

		// parameter setting 
		inst_error = spu.Set_Sampling_Parameter(startwave, stopwave, speed, tsl_acctualstep);

		if (inst_error != 0)
		{
			Show_Inst_Error(inst_error);
			return;
		}

		// mpm averageing time-> spu
		spu.AveragingTime = averaging_time;


		// -------------set STS Process parameter-----------------------------------

		int sts_error;            // sts process class error

								  // data Clear 
		sts_error = Cal_STS.Clear_Measdata();

		if (sts_error != 0)
		{
			Show_STS_Error(sts_error);
			return;
		}

		sts_error = Cal_STS.Clear_Refdata();

		if (sts_error != 0)
		{
			Show_STS_Error(sts_error);
			return;
		}

		// Setting for STS rescaling mode
		sts_error = Cal_STS.Set_Rescaling_Setting(RescalingMode::Freerun_SPU, averaging_time, true);

		if (sts_error != 0)
		{
			Show_STS_Error(sts_error);
			return;
		}

		// Make acctual wavelength step table
		sts_error = Cal_STS.Make_Sweep_Wavelength_Table(startwave, stopwave, tsl_acctualstep);

		if (sts_error != 0)
		{
			Show_STS_Error(sts_error);
			return;
		}

		// Make rescaling wavelength step table
		sts_error = Cal_STS.Make_Target_Wavelength_Table(startwave, stopwave, wavestep);

		if (sts_error != 0)
		{
			Show_STS_Error(sts_error);
			return;
		}

		// ----prepare data struct & hold instrument condition
		if (chkeach_ch->Checked == true)
		{
			Prepare_dataST_Each();
		}
		else
		{
			Prepare_dataST();
		}
		MessageBox::Show("Completed.", "", MessageBoxButtons::OK);

	}

	private: void Show_Inst_Error(int errordata)
	{
		// ------------------------------------
		// Show error code
		// 显示错误编号
		// ------------------------------------

		cli::array<String^>^ errorstring = Enum::GetNames(ExceptionCode::typeid);
		cli::array<int>^ errorvale = static_cast<cli::array<int>^>(Enum::GetValues(ExceptionCode::typeid));
		int loop1;
		for (loop1 = 0; loop1 <= errorvale->Length - 1; loop1++)
		{
			if (errorvale[loop1] == errordata)
			{
				MessageBox::Show(errorstring[loop1]);
				break;
			}
		}
	}

	private:void Show_STS_Error(int errordata)
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
				MessageBox::Show(errorstring[loop1]);
				break;
			}
		}
	}

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		// -------------------------------------------------------------------------
		// Form Load    (MainForm)
		// -------------------------------------------------------------------------
		cli::array<String^> ^spudev;                        // spu device name
		int errorcode;                                // errorcode 
		cli::array<String^> ^usb_resource;                  // usb communication resource

															// ----Check Connction of spu deviece
		errorcode = spu.Get_Device_ID(spudev);

		if (errorcode != 0)
		{
			Show_Inst_Error(errorcode);
			System::Environment::Exit(0);
		}


		// ----Check usb resource
		usb_resource = Santec::Communication::MainCommunication::Get_USB_Resouce();


		// ------show Setting Form
		Instrument_Setting^ set_form = gcnew Instrument_Setting();

		set_form->Owner = this;
		set_form->SPU_Resource = spudev;
		set_form->USB_Resource = usb_resource;
		set_form->ShowDialog();

		// ---Apply to communication parametere from Instrument setting form
		Santec::Communication::CommunicationMethod tsl_communcation_method;
		Santec::Communication::CommunicationMethod mpm_communcation_method;

		// ----tsl　Communication method
		if (set_form->TSL_Communicater == "GPIB")
		{
			tsl_communcation_method = Santec::Communication::CommunicationMethod::GPIB;
			tsl.Terminator = CommunicationTerminator::CrLf;
			tsl.GPIBAddress = int::Parse(set_form->TSL_Address);
			tsl.GPIBBoard = 0;
			tsl.GPIBConnectType = Santec::Communication::GPIBConnectType::NI4882;
		}
		else if (set_form->TSL_Communicater == "LAN")
		{
			tsl_communcation_method = Santec::Communication::CommunicationMethod::TCPIP;
			tsl.Terminator = CommunicationTerminator::Cr;
			tsl.IPAddress = set_form->TSL_Address;
			tsl.Port = set_form->TSL_Portnumber;
		}
		else
		{
			// USB 
			tsl_communcation_method = Santec::Communication::CommunicationMethod::USB;
			tsl.DeviceID = System::Convert::ToUInt32(set_form->TSL_Address);
			tsl.Terminator = CommunicationTerminator::Cr;
		}

		// ---mpm Communicatipon method
		int loop1;
		int mpmcount;                     // mpm count

		if (set_form->MPM_Communicater == "GPIB")
			mpm_communcation_method = Santec::Communication::CommunicationMethod::GPIB;
		else
			mpm_communcation_method = Santec::Communication::CommunicationMethod::TCPIP;

		mpmcount = set_form->MPM_Count;

		mpm = gcnew cli::array<MPM^>(mpmcount);

		for (loop1 = 0; loop1 <= mpmcount - 1; loop1++)
		{
			mpm[loop1] = gcnew MPM();

			if (set_form->MPM_Communicater == "GPIB")
				mpm[loop1]->GPIBAddress = int::Parse(set_form->MPM_Address[loop1]);
			else
			{
				mpm[loop1]->IPAddress = set_form->MPM_Address[loop1];
				mpm[loop1]->Port = set_form->MPM_Portnumber[loop1];
			}

			// -------------------------------------------------------------------------
			// mpm muximum logging data read time is 11s
			// communication time out must to set > mpm logging data read time.
			// --------------------------------------------------------------------------
			mpm[loop1]->TimeOut = 11000;
		}

		// ----spu Communcation Setting 
		spu.DeviceName = set_form->SPU_DeviveID;

		// -----------Connect------------------------------------------------- 
		// tsl
		errorcode = tsl.Connect(tsl_communcation_method);

		if (errorcode != 0)
		{
			MessageBox::Show("tsl can't connect.Please check connection.", "", MessageBoxButtons::OK);
			System::Environment::Exit(0);
		}

		// mpm
		for (loop1 = 0; loop1 <= mpm->GetUpperBound(0); loop1++)
		{
			errorcode = mpm[loop1]->Connect(mpm_communcation_method);

			if (errorcode != 0)
			{
				MessageBox::Show("mpm can't connect.Please check connection.", "", MessageBoxButtons::OK);
				System::Environment::Exit(0);
			}

		}

		// spu(DAQ)
		String ^ans = String::Empty;
		errorcode = spu.Connect(ans);

		if (errorcode != 0)
		{
			MessageBox::Show("spu Can't connect. Please check connection.", "", MessageBoxButtons::OK);

			System::Environment::Exit(0);
		}


		// ------------Check mpm Module information
		errorcode = Check_Module_Information();

		if (errorcode != 0)
		{
			MessageBox::Show("System can't use mpm-215 togeter other module.", "", MessageBoxButtons::OK);
			Environment::Exit(0);
		}

		// -----------Reflect instrument parameter to Form
		Referect_EnableCh_for_form();                // mpm Eanble ch
		Referect_EnableRange_for_form();             // mpm selectable range
		Add_TSL_Sweep_Speed();                       // tsl Sweep speed(only tsl-570)
	}

	private:int Check_Module_Information()
	{
		// ------------------------------------------------------------
		// check Module information inside system
		// ------------------------------------------------------------
		int loop1;
		int loop2;
		int counter_215;                           // 215 counter 

												   // mpm device loop
		for (loop1 = 0; loop1 <= mpm->GetUpperBound(0); loop1++)
		{
			// Slot loop
			for (loop2 = 0; loop2 <= 4; loop2++)
			{
				// Enable Slot
				if (mpm[loop1]->Information->ModuleEnable[loop2] == true)
				{

					// Check mpm-215 insert
					if (mpm[loop1]->Information->ModuleType[loop2] == "MPM-215")
					{
						Flag_215 = true;
						counter_215 = counter_215 + 1;
					}

					// Check mpm-213 insert
					if (mpm[loop1]->Information->ModuleType[loop2] == "MPM-213")
						Flag_213 = true;
				}
			}
		}


		// Check mpm-215 count & Module total count
		// STS system can't use 215 together other module.
		int enable_module_count;                      // enable module count

		for (loop1 = 0; loop1 <= mpm->GetUpperBound(0); loop1++)
			enable_module_count = mpm[loop1]->Information->NumberofModule + enable_module_count;// total module count

		if (Flag_215 == true)
		{
			if (enable_module_count != counter_215)
				return -1;
		}



		return 0;
	}

	private: void Referect_EnableCh_for_form()
	{
		// ------------------------------------------------
		// Reflect mpm ch 
		// ------------------------------------------------
		int loop1;
		int loop2;
		cli::array<bool>^enable_slot;
		String^ slot_type;

		for (loop1 = 0; loop1 <= mpm->GetUpperBound(0); loop1++)
		{
			// get insert module count with "mpm Information" class 
			enable_slot = mpm[loop1]->Information->ModuleEnable;

			// modeule loop(Maximum 5 slot)
			for (loop2 = 0; loop2 <= 4; loop2++)
			{
				if (enable_slot[loop2] == true)
				{
					// get module type with "mpm Information" class 
					slot_type = mpm[loop1]->Information->ModuleType[loop2];

					if (slot_type != "MPM-212")
					{
						chklst_ch->Items->Add("mpm" + System::Convert::ToString(loop1 + 1) + " Slot" + System::Convert::ToString(loop2) + " Ch1");
						chklst_ch->Items->Add("mpm" + System::Convert::ToString(loop1 + 1) + " Slot" + System::Convert::ToString(loop2) + " Ch2");
						chklst_ch->Items->Add("mpm" + System::Convert::ToString(loop1 + 1) + " Slot" + System::Convert::ToString(loop2) + " Ch3");
						chklst_ch->Items->Add("mpm" + System::Convert::ToString(loop1 + 1) + " Slot" + System::Convert::ToString(loop2) + " Ch4");
					}
					else
					{
						chklst_ch->Items->Add("mpm" + System::Convert::ToString(loop1 + 1) + " Slot" + System::Convert::ToString(loop2) + " Ch1");
						chklst_ch->Items->Add("mpm" + System::Convert::ToString(loop1 + 1) + " Slot" + System::Convert::ToString(loop2) + " Ch2");
					}
				}
			}
		}
	}

	private: int Add_TSL_Sweep_Speed()
	{
		// ---------------------------------------------------------
		// Add in selectable sweep speed to speed combbox
		// this function can use only tsl-570
		// ----------------------------------------------------------
		int inst_error;                       // instullment error
		cli::array<double>^sweep_table;          // table


												 // Get Sweep speed tabele
												 // Except for tsl-570 "Device Error" occurre when call this function.
		inst_error = tsl.Get_Sweep_Speed_table(sweep_table);

		if (inst_error != 0 & inst_error != System::Convert::ToInt32(ExceptionCode::DeviceError))
			return inst_error;


		// -----Add in combbox when tsl-570
		int loop1;

		if (inst_error != Convert::ToInt32(ExceptionCode::DeviceError))
		{
			for (loop1 = 0; loop1 <= sweep_table->GetUpperBound(0); loop1++)

				cmbspeed->Items->Add(sweep_table[loop1]);
		}
		return 0;
	}

	private:void Referect_EnableRange_for_form()
	{
		// -----------------------------------------------------
		// Refelect mpm Range
		// -------------------------------------------------------


		// mpm-213 can use just 1 to 4 range
		if (Flag_213 == true)
		{
			chklst_range->Items->Add("Range1");
			chklst_range->Items->Add("Range2");
			chklst_range->Items->Add("Range3");
			chklst_range->Items->Add("Range4");
		}
		else
		{
			chklst_range->Items->Add("Range1");
			chklst_range->Items->Add("Range2");
			chklst_range->Items->Add("Range3");
			chklst_range->Items->Add("Range4");
			chklst_range->Items->Add("Range5");
		}

		// mpm-215 can't select range
		if (Flag_215 == true)
			chklst_range->Enabled = false;
	}

	private:void Prepare_dataST()
	{
		// -----------------------------------------------
		// Prepar STS data struct
		// -----------------------------------------------
		int rangecout;                        // number of range
		int chcount;                          // number of ch 
		int loop1;                            // loop count1
		int loop2;                            // loop count2
		String ^text_st;            // text String 
		cli::array<String^>^split_st;             // split string array

												  // List clear 
		Meas_rang.Clear();                               // Measurement Range
		Data_struct.Clear();                             // DataSturct of STS
		Refdata_struct.Clear();                          // Reference data struct
		Ref_monitordata_struct.Clear();            //Reference monitor data struct
		Meas_monitor_struct.Clear();                     // Measurement monitor data struct

		Mergedata_struct.Clear();                        // DataStruct of Merge 

		rangecout = chklst_range->CheckedItems->Count;
		chcount = chklst_ch->CheckedItems->Count;

		if (Flag_215 == true)
			//If mom215 range must be set 1
			Meas_rang.Add(1);
		else
		{
			if (rangecout == 0 | chcount == 0)
			{
				MessageBox::Show("Please check measurement parameters.");
				return;
			}

			// hold range data 
			for (loop1 = 0; loop1 <= chklst_range->Items->Count - 1; loop1++)
			{
				if (chklst_range->GetItemChecked(loop1) == true)
					Meas_rang.Add(loop1 + 1);
			}
		}

		int device_number;
		int slot_number;
		int ch_number;
		STSDataStruct set_struct;
		STSDataStructForMerge set_struct_merge;
		int sweep_count;                          // Sweep count 
												  // --for measurement MPM data
		for (loop2 = 0; loop2 <= Meas_rang.Count - 1; loop2++)
		{
			for (loop1 = 0; loop1 <= chklst_ch->Items->Count - 1; loop1++)
			{
				if (chklst_ch->GetItemChecked(loop1) == true)
				{
					text_st = chklst_ch->Items[loop1]->ToString();
					split_st = text_st->Split(' ');
					// ch parameter
					device_number = System::Convert::ToInt32(split_st[0]->Substring(3));
					slot_number = System::Convert::ToInt32(split_st[1]->Substring(4));
					ch_number = System::Convert::ToInt32(split_st[2]->Substring(2));
					// for data
					set_struct.MPMNumber = device_number;
					set_struct.SlotNumber = slot_number;
					set_struct.ChannelNumber = ch_number;
					set_struct.RangeNumber = Meas_rang[loop2];
					set_struct.SweepCount = loop2 + 1;
					set_struct.SOP = 0;
					Data_struct.Add(set_struct);
				}
			}
		}

		// ---for merasurement Monitor data
		// monitor data need each sweep times data
		STSMonitorStruct set_monitor_struct;              // set struct for monitor
		for (loop2 = 0; loop2 <= Meas_rang.Count - 1; loop2++)
		{
			for (loop1 = 0; loop1 <= chklst_ch->Items->Count - 1; loop1++)
			{
				if (chklst_ch->GetItemChecked(loop1) == true)
				{
					text_st = chklst_ch->Items[loop1]->ToString();
					split_st = text_st->Split(' ');
					// ch parameter
					device_number = System::Convert::ToInt32(split_st[0]->Substring(3));

					set_monitor_struct.MPMNumber = device_number;
					set_monitor_struct.SOP = 0;
					set_monitor_struct.SweepCount = loop2 + 1;

					Meas_monitor_struct.Add(set_monitor_struct);
					if (Meas_monitor_struct.Count == loop2 + 1)
						break;
				}
			}
		}

		// ---for　reference MPM data & merge data
		// reference data need only 1 range data
		for (loop1 = 0; loop1 <= chklst_ch->Items->Count - 1; loop1++)
		{
			if (chklst_ch->GetItemChecked(loop1) == true)
			{
				text_st = chklst_ch->Items[loop1]->ToString();
				split_st = text_st->Split(' ');
				// ch parameter
				device_number = System::Convert::ToInt32(split_st[0]->Substring(3));
				slot_number = System::Convert::ToInt32(split_st[1]->Substring(4));
				ch_number = System::Convert::ToInt32(split_st[2]->Substring(2));

				// for reference data
				set_struct.MPMNumber = device_number;
				set_struct.SlotNumber = slot_number;
				set_struct.ChannelNumber = ch_number;
				set_struct.RangeNumber = 1;
				set_struct.SweepCount = 1;
				set_struct.SOP = 0;

				Refdata_struct.Add(set_struct);

				// for mege
				set_struct_merge.MPMNumber = device_number;
				set_struct_merge.SlotNumber = slot_number;
				set_struct_merge.ChannelNumber = ch_number;
				set_struct_merge.SOP = 0;
				Mergedata_struct.Add(set_struct_merge);
			}
		}

		// ----for referece Monitor data 
		STSDataStruct set_ref_monitor_struct;
		for (loop1 = 0; loop1 <= chklst_ch->Items->Count - 1; loop1++)
		{
			if (chklst_ch->GetItemChecked(loop1) == true)
			{
				text_st = chklst_ch->Items[loop1]->ToString();
				split_st = text_st->Split(' ');
				// Mainframe parameter
				device_number = System::Convert::ToInt32(split_st[0]->Substring(3));
				slot_number = System::Convert::ToInt32(split_st[1]->Substring(4));
				ch_number = System::Convert::ToInt32(split_st[2]->Substring(2));

				// for reference monitor data
				set_ref_monitor_struct.MPMNumber = device_number;
				set_ref_monitor_struct.SlotNumber = slot_number;
				set_ref_monitor_struct.ChannelNumber = ch_number;
				set_ref_monitor_struct.RangeNumber = 1;
				set_ref_monitor_struct.SOP = 0;
				set_ref_monitor_struct.SweepCount = 1;

				Ref_monitordata_struct.Add(set_ref_monitor_struct);
				break;
			}
		}
	}

	private: void Prepare_dataST_Each()
	{
		// -----------------------------------------------
		// Prepar STS data struct
		// -----------------------------------------------
		int rangecout;                        // number of range
		int chcount;                          // number of ch 
		int loop1;                            // loop count1
		int loop2;                            // loop count2
		String ^ text_st;            // text String 
		cli::array < String ^>^ split_st;             // split string array

											   // List clear 
		Meas_rang.Clear();                               // Measurement Range
		Data_struct.Clear();                             // DataSturct of STS
		Refdata_struct.Clear();                          // Reference data struct
		Ref_monitordata_struct.Clear();                  // Reference monitor data struct
		Meas_monitor_struct.Clear();                     // Measurement monitor data struct



		Mergedata_struct.Clear();                        // DataStruct of Merge 

		rangecout = chklst_range->CheckedItems->Count;
		chcount = chklst_ch->CheckedItems->Count;

		if (Flag_215 == true)
			// If mom215 range must be set 1
			Meas_rang.Add(1);
		else
		{
			if (rangecout == 0 | chcount == 0)
			{
				MessageBox::Show("Please check measurement parameters.");
				return;
			}


			// hold range data 
			// hold range data 
			for (loop1 = 0; loop1 <= chklst_range->Items->Count - 1; loop1++)
			{
				if (chklst_range->GetItemChecked(loop1) == true)
					Meas_rang.Add(loop1 + 1);
			}
		}
		int device_number;
		int slot_number;
		int ch_number;
		STSDataStruct set_struct;
		STSDataStructForMerge set_struct_merge;

		// --for measurement MPM data
		for (loop2 = 0; loop2 <= Meas_rang.Count - 1; loop2++)
		{
			for (loop1 = 0; loop1 <= chklst_ch->Items->Count - 1; loop1++)
			{
				if (chklst_ch->GetItemChecked(loop1) == true)
				{
					text_st = chklst_ch->Items[loop1]->ToString();
					split_st = text_st->Split(' ');
					// ch parameter
					device_number = System::Convert::ToInt32(split_st[0]->Substring(3));
					slot_number = System::Convert::ToInt32(split_st[1]->Substring(4));
					ch_number = System::Convert::ToInt32(split_st[2]->Substring(2));
					// for data
					set_struct.MPMNumber = device_number;
					set_struct.SlotNumber = slot_number;
					set_struct.ChannelNumber = ch_number;
					set_struct.RangeNumber = Meas_rang[loop2];
					set_struct.SweepCount = loop2 + 1;
					set_struct.SOP = 0;
					Data_struct.Add(set_struct);
				}
			}
		}

		// ---for merasurement Monitor data
		// monitor data need each sweep times data
		STSMonitorStruct set_monitor_struct;              // set struct for monitor
		for (loop2 = 0; loop2 <= Meas_rang.Count - 1; loop2++)
		{
			for (loop1 = 0; loop1 <= chklst_ch->Items->Count - 1; loop1++)
			{
				if (chklst_ch->GetItemChecked(loop1) == true)
				{
					text_st = chklst_ch->Items[loop1]->ToString();
					split_st = text_st->Split(' ');
					// ch parameter
					device_number = System::Convert::ToInt32(split_st[0]->Substring(3));

					set_monitor_struct.MPMNumber = device_number;
					set_monitor_struct.SOP = 0;
					set_monitor_struct.SweepCount = loop2 + 1;

					Meas_monitor_struct.Add(set_monitor_struct);
					if (Meas_monitor_struct.Count == loop2 + 1)
						break;
				}
			}
		}

		// ---for　reference MPM data & reference monitor data & merge data
		// reference data need only 1 range data
		STSDataStruct set_ref_monitor_struct;
		for (loop1 = 0; loop1 <= chklst_ch->Items->Count - 1; loop1++)
		{
			if (chklst_ch->GetItemChecked(loop1) == true)
			{
				text_st = chklst_ch->Items[loop1]->ToString();
				split_st = text_st->Split(' ');
				// ch parameter
				device_number = System::Convert::ToInt32(split_st[0]->Substring(3));
				slot_number = System::Convert::ToInt32(split_st[1]->Substring(4));
				ch_number = System::Convert::ToInt32(split_st[2]->Substring(2));

				// for reference data
				set_struct.MPMNumber = device_number;
				set_struct.SlotNumber = slot_number;
				set_struct.ChannelNumber = ch_number;
				set_struct.RangeNumber = 1;
				set_struct.SweepCount = 1;
				set_struct.SOP = 0;

				Refdata_struct.Add(set_struct);


				// for reference monitor data
				set_ref_monitor_struct.MPMNumber = device_number;
				set_ref_monitor_struct.SlotNumber = slot_number;
				set_ref_monitor_struct.ChannelNumber = ch_number;
				set_ref_monitor_struct.RangeNumber = 1;
				set_ref_monitor_struct.SweepCount = 1;
				set_ref_monitor_struct.SOP = 0;

				Ref_monitordata_struct.Add(set_ref_monitor_struct);

				// for mege
				set_struct_merge.MPMNumber = device_number;
				set_struct_merge.SlotNumber = slot_number;
				set_struct_merge.ChannelNumber = ch_number;
				set_struct_merge.SOP = 0;
				Mergedata_struct.Add(set_struct_merge);
			}
		}
	}

	private: System::Void btnget_reference_Click(System::Object^  sender, System::EventArgs^  e) {
		// ------------------------------------------------------------------------------
		// Get Reference
		// ------------------------------------------------------------------------------
		int inst_error;                       // Instullment error
		int loop1;

		// ----- mpm setting for selected 1st range
		for (loop1 = 0; loop1 <= mpm->GetUpperBound(0); loop1++)
		{
			// set Range for mpm
			inst_error = mpm[loop1]->Set_Range(Meas_rang[0]);
			if ((inst_error != 0))
			{
				Show_Inst_Error(inst_error);
				return;
			}
		}

		// ----Move to start wavelength with Sweep Start method.
		inst_error = tsl.Sweep_Start();
		if (inst_error != 0)
			Show_Inst_Error(inst_error);


		if (chkeach_ch->Checked)
		{
			// Reference measurement one channel at a time
			for each(STSDataStruct item in Refdata_struct)
			{
				MessageBox::Show("Connect fiber to MPM" + item.MPMNumber + "_Slot" + item.SlotNumber + "_Ch" + item.ChannelNumber + ".");
				// -----Sweep 
				inst_error = Sweep_Process();
				if (inst_error == -9999)
				{
					// MPM logging timeout occurred.
					MessageBox::Show("MPM Trigger receive error! Please check trigger cable connection.");
					return;
				}
				if (inst_error != 0)
				{
					Show_Inst_Error(inst_error);
					return;
				}

				// ---Move to start wavelength with Sweep Start method for next sweep.
				inst_error = tsl.Sweep_Start();
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
				process_error = Cal_STS.Cal_RefData_Rescaling();

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
				MessageBox::Show("MPM Trigger receive error! Please check trigger cable connection.");
				return;
			}
			if (inst_error != 0)
			{
				Show_Inst_Error(inst_error);
				return;
			}

			// ---Move to start wavelength with Sweep Start method for next sweep.
			inst_error = tsl.Sweep_Start();
			if (inst_error != 0)
				Show_Inst_Error(inst_error);

			// ---get logging data & add in STSProcess class
			bool inst_flag = new bool();

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
			process_error = Cal_STS.Cal_RefData_Rescaling();

			if (process_error != 0)
			{
				Show_STS_Error(process_error);
				return;
			}
		}


		// tsl Sweep Stop
		inst_error = tsl.Sweep_Stop();
		if (inst_error != 0)
		{
			Show_Inst_Error(inst_error);
			return;
		}

		MessageBox::Show("Completed.", "", MessageBoxButtons::OK);

	}

	private: int Get_reference_samplingdata(bool inst_flag)
	{
		// ---------------------------------------------------------------
		// Get logging reference data & add in 
		// ---------------------------------------------------------------
		int inst_error;                        // Instullment error
		cli::array<float>^ logg_data = nullptr;              // mpm Logging data
		int cal_error;                         // process error


											   // ----Load　Reference mpm data & add in data for STS Process Class for each channel
		for each(STSDataStruct item in Refdata_struct)
		{

			// Read corresponded mpm data
			inst_error = Get_MPM_Loggdata(item.MPMNumber - 1, item.SlotNumber, item.ChannelNumber, logg_data);

			if (inst_error != 0)
			{
				inst_flag = true;
				return inst_error;
			}

			// Add in to mpm reference data to STS Process Class
			cal_error = Cal_STS.Add_Ref_MPMData_CH(logg_data, item);

			if (cal_error != 0)
			{
				inst_flag = false;
				return cal_error;
			}
		}

		// ------Load Monitor data & add in data for STS Proccsess class with "STS Data Struct"
		cli::array<float>^ triggerdata = nullptr;     // tigger data 
		cli::array<float>^ monitordata = nullptr;     // monitor data

		inst_error = spu.Get_Sampling_Rawdata(triggerdata, monitordata);

		if (inst_error != 0)
		{
			inst_flag = true;
			return inst_error;
		}


		for each(STSDataStruct monitor_item in Ref_monitordata_struct)
		{
			cal_error = Cal_STS.Add_Ref_MonitorData(triggerdata, monitordata, monitor_item);

			if (cal_error != 0)
			{
				inst_flag = false;
				return cal_error;
			}
		}

		return 0;
	}
	private: int Get_Each_channel_reference_samplingdata(bool inst_flag, int currentMPMNumber, int currentSlotNumber, int currentChannelNumber, int currentSweepCount)
	{
		// ---------------------------------------------------------------
		// Get logging reference data & add in 
		// ---------------------------------------------------------------
		int inst_error;                        // Instullment error
		cli::array<float> ^ logg_data = nullptr;              // mpm Logging data
		int cal_error;                         // process error

											   // ----Load　Reference MPM data & add in data for STS Process Class for each channel
		for each(STSDataStruct item in Refdata_struct)
		{
			if ((item.MPMNumber != currentMPMNumber | item.SlotNumber != currentSlotNumber | item.ChannelNumber != currentChannelNumber))
				continue;

			// Read corresponded MPM data
			inst_error = Get_MPM_Loggdata(item.MPMNumber - 1, item.SlotNumber, item.ChannelNumber,  logg_data);

			if (inst_error != 0)
			{
				inst_flag = true;
				return inst_error;
			}

			// Add in to MPM reference data to STS Process Class
			cal_error = Cal_STS.Add_Ref_MPMData_CH(logg_data, item);

			if (cal_error != 0)
			{
				inst_flag = false;
				return cal_error;
			}
		}

		// ------Load Monitor data & add in data for STS Proccsess class with "STS Data Struct"
		cli::array<float> ^ triggerdata = nullptr;     // tigger data 
		cli::array<float> ^ monitordata = nullptr;     // monitor data

		inst_error = spu.Get_Sampling_Rawdata(triggerdata, monitordata);

		if (inst_error != 0)
		{
			inst_flag = true;
			return inst_error;
		}

		for each(STSDataStruct monitor_item in Ref_monitordata_struct)
		{
			cal_error = Cal_STS.Add_Ref_MonitorData(triggerdata, monitordata, monitor_item);
			if (cal_error != 0)
			{
				inst_flag = false;
				return cal_error;
			}
		}

		return 0;
	}

	private:int Get_measurement_samplingdata(int sweepcount, bool inst_flag)
	{
		// ---------------------------------------------------------------
		// Get logging measurement data & add in 
		// ---------------------------------------------------------------
		int inst_error;                        // Instullment error
		cli::array<float>^logg_data = nullptr;              // mpm Logging data
		int cal_error;                        // process error


											  // -- Load mpm Logging data & Add in STS Process class with measurment sts data struct 
		for each(STSDataStruct item in Data_struct)
		{
			if (item.SweepCount != sweepcount)
				continue;

			// Read corresponded mpm data
			inst_error = Get_MPM_Loggdata(item.MPMNumber - 1, item.SlotNumber, item.ChannelNumber, logg_data);

			if (inst_error != 0)
			{
				inst_flag = true;
				return inst_error;
			}

			// Add in to mpm reference data to STS Process Class
			cal_error = Cal_STS.Add_Meas_MPMData_CH(logg_data, item);

			if (cal_error != 0)
			{
				inst_flag = false;
				return cal_error;
			}
		}

		// --Lado spu monitor data & Add in STS Process class with measurement monitor data struct
		cli::array<float>^ triggerdata = nullptr;
		cli::array<float>^ monitordata = nullptr;

		inst_error = spu.Get_Sampling_Rawdata(triggerdata, monitordata);

		if (inst_error != 0)
		{
			inst_flag = true;
			return inst_error;
		}


		// Search item from measurement monitor data structure according to sweep count.

		for each(STSMonitorStruct item in Meas_monitor_struct)
		{
			if (item.SweepCount == sweepcount)
			{
				cal_error = Cal_STS.Add_Meas_MonitorData(triggerdata, monitordata, item);

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

	private:int Get_MPM_Loggdata(int deveice, int slot, int ch, cli::array<float>^ %data)
	{
		// ---------------------------------------------------------------
		// Get mpm Logg data
		// --------------------------------------------------------------
		int inst_error;

		inst_error = mpm[deveice]->Get_Each_Channel_Logdata(slot, ch, data);
		return inst_error;
	}

	private:int Sweep_Process()
	{
		// ------------------------------------------------------------
		// Sweep Process
		// ------------------------------------------------------------
		int inst_error;               // Instullment error
		int loop1;                    // loop count 


									  // mpm sampling start 
		for (loop1 = 0; loop1 <= mpm->GetUpperBound(0); loop1++)
		{
			inst_error = mpm[loop1]->Logging_Start();
			if (inst_error != 0)
				return inst_error;
		}

		// tsl waiting for start status 
		inst_error = tsl.Waiting_For_Sweep_Status(2000, TSL::Sweep_Status::WaitingforTrigger);

		// ---error handling -> mpm Logging Stop
		if (inst_error != 0)
		{
			for (loop1 = 0; loop1 <= mpm->GetUpperBound(0); loop1++)
				mpm[loop1]->Logging_Stop();
			return inst_error;
		}

		// spu sampling start
		inst_error = spu.Sampling_Start(false);
		if (inst_error != 0)
			return inst_error;

		// tsl issue software trigger
		inst_error = tsl.Set_Software_Trigger();

		// ---error handling -> mpm Logging Stop
		if (inst_error != 0)
		{
			for (loop1 = 0; loop1 <= mpm->GetUpperBound(0); loop1++)
				mpm[loop1]->Logging_Stop();
			return inst_error;
		}

		// spu waiting for sampling 
		inst_error = spu.Waiting_for_sampling();

		// ---error handling -> mpm Logging Stop
		if (inst_error != 0)
		{
			for (loop1 = 0; loop1 <= mpm->GetUpperBound(0); loop1++)
				mpm[loop1]->Logging_Stop();
			return inst_error;
		}

		int mpm_stauts;                   // mpm logging status 0:douring measurement 1:Compleated -1:Stopped
		int mpm_count;                    // mpm number of logging completed point  
		System::Diagnostics::Stopwatch st;                     // stopwatch           
		bool mpm_completed_falg = true;    // mpm logging completed flag  F:not completed T:completed    
		bool isSweeping = true;
		// mpm waiting for sampling 
		st.Start();                          // stopwathc start 
		do
		{
			for (loop1 = 0; loop1 <= mpm->GetUpperBound(0); loop1++)
			{
				inst_error = mpm[loop1]->Get_Logging_Status(mpm_stauts, mpm_count);
				if (inst_error != 0)
					return inst_error;
				if (mpm_stauts == 1)
				{
					isSweeping = false;
					break;
				}
				if (st.ElapsedMilliseconds >= 2000)
				{
					//Logging time out(time out = 2sec after from spu sampling  completed.)
					mpm_completed_falg = false;
					isSweeping = false;
					break;
				}
			}
		} while (isSweeping);

		st.Stop();

		// mpm sampling stop
		for (loop1 = 0; loop1 <= mpm->GetUpperBound(0); loop1++)
		{
			inst_error = mpm[loop1]->Logging_Stop();
			if (inst_error != 0)
				return inst_error;
		}


		// tsl Waiting for standby
		inst_error = tsl.Waiting_For_Sweep_Status(5000, TSL::Sweep_Status::Standby);

		if (inst_error != 0)
			return inst_error;

		if (mpm_completed_falg == false)
			// mpm logging timeout occurred.
			return -9999;

		return 0;
	}

	private: int Save_Measurement_data()
	{
		// -------------------------------------------------------
		// Save Measurement data
		// -------------------------------------------------------
		cli::array<double>^ wavelength_table = nullptr;            // Rescaled wavelength table  
		cli::array<cli::array<float>^>^ lstILdata;     // IL data list 
		int process_error;                          // process class error  
		int loop1 = 0;                                  // loop count
		cli::array<float>^ ildata = nullptr;                      // il data arrray

																  // Get Rescaled wavelength tabel 
		process_error = Cal_STS.Get_Target_Wavelength_Table(wavelength_table);

		lstILdata = gcnew cli::array<cli::array<float>^>(Mergedata_struct.Count);

		// Get IL data 
		if (Flag_215 == true)
		{
			for each(STSDataStruct items in Data_struct)
			{
				ildata = gcnew cli::array<float>(0);
				process_error = Cal_STS.Get_IL_Data(ildata, items);
				if (process_error != 0)
					return process_error;

				lstILdata->SetValue(ildata, loop1);
				loop1++;
			}
		}
		else
			for each(STSDataStructForMerge items in Mergedata_struct)
			{
				ildata = gcnew cli::array<float>(0);
				process_error = Cal_STS.Get_IL_Merge_Data(ildata, items);
				if (process_error != 0)
					return process_error;

				lstILdata->SetValue(ildata, loop1);
				loop1++;
			}


		// -----Data Save 
		String ^file_path;

		SaveFileDialog1->Title = "IL data save";
		SaveFileDialog1->Filter = "csv file(*.csv)|*.csv";

		SaveFileDialog1->ShowDialog();

		file_path = SaveFileDialog1->FileName;

		System::IO::StreamWriter ^writer = gcnew System::IO::StreamWriter(file_path, false, System::Text::Encoding::GetEncoding("UTF-8"));
		String ^write_string = nullptr;
		String ^ hedder = String::Empty;
		hedder = "Wavelength(nm)";
		for each(STSDataStruct item in Data_struct)
		{
			if (item.SweepCount != 1)
			{
				continue;
			}
			hedder = hedder + ",MPM" + item.MPMNumber.ToString() + "Slot" + item.SlotNumber.ToString() + "Ch" + item.ChannelNumber.ToString();
		}
		//write hedder
		writer->WriteLine(hedder);

		int loop2;

		for (loop1 = 0; loop1 <= wavelength_table->GetUpperBound(0); loop1++)
		{
			write_string = wavelength_table[loop1].ToString();

			for (loop2 = 0; loop2 <= lstILdata->Length - 1; loop2++)
				write_string = write_string + "," + lstILdata[loop2][loop1];

			writer->WriteLine(write_string);
		}

		writer->Close();

		return 0;
	}

	private: System::Void btnmeas_Click(System::Object^  sender, System::EventArgs^  e) {
		// -------------------------------------------------------------------------
		// Mesurement Process
		// -------------------------------------------------------------------------
		int loop1;                        // loop Count 1
		int loop2;                        // Loop count 2
		int inst_error;                   // instllment error   
		bool inst_flag = new bool();                    // instrment error flag



	    // -------Measurement-----------------------------------------------

		// Move to start wavelength  with Sweep Start method.
		inst_error = tsl.Sweep_Start();
		if (inst_error != 0)
		{
			Show_Inst_Error(inst_error);
			return;
		}

		// --------Rang Loop
		for (loop1 = 0; loop1 <= Meas_rang.Count - 1; loop1++)
		{

			// mpm range Setting 
			for (loop2 = 0; loop2 <= mpm->GetUpperBound(0); loop2++)
			{
				inst_error = mpm[loop2]->Set_Range(Meas_rang[loop1]);

				if (inst_error != 0)
				{
					Show_Inst_Error(inst_error);
					return;
				}
			}

			//Range Set delay
			System::Threading::Thread::Sleep(1);
			// Sweep process
			inst_error = Sweep_Process();
			if (inst_error != 0)
			{
				Show_Inst_Error(inst_error);
				return;
			}

			// Move to start wavelength  with Sweep Start method for next sweep.
			inst_error = tsl.Sweep_Start();
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
		process_error = Cal_STS.Cal_MeasData_Rescaling();

		if (process_error != 0)
		{
			Show_STS_Error(process_error);
			return;
		}

		// merge or IL calculate
		Module_Type merge_type;

		if (Flag_215 == false)
		{
			if (Flag_213 == true)
				merge_type = Module_Type::MPM_213;
			else
				merge_type = Module_Type::MPM_211;

			// Process ranges merge
			process_error = Cal_STS.Cal_IL_Merge(merge_type);
		}
		else
			// just IL process
			process_error = Cal_STS.Cal_IL();

		// data save
		process_error = Save_Measurement_data();
		if (process_error != 0)
			Show_STS_Error(process_error);


		inst_error = tsl.Sweep_Stop();
		if (inst_error != 0)
		{
			Show_Inst_Error(inst_error);
			return;
		}


		MessageBox::Show("Completed.", "", MessageBoxButtons::OK);

	}

	private: System::Void Button1_Click(System::Object^  sender, System::EventArgs^  e) {
		// -----------------------------------------------------------------------------
		// Reference Data Read
		// This function must use after "SET" 
		// -----------------------------------------------------------------------------
		String ^fpath = String::Empty;
		System::IO::StreamReader ^reader;

		// -------Reference file　Read 

		OpenFileDialog1->Title = "Reference Data";
		OpenFileDialog1->ShowDialog();
		fpath = OpenFileDialog1->FileName;

		reader = gcnew System::IO::StreamReader(fpath);

		String ^read_st = String::Empty;                            // Read String 
		cli::array<String^> ^split_st = nullptr;                        // split strin array
		cli::array<cli::array<float>^> ^ lstILdata;
		// hedder Read 
		read_st = reader->ReadLine();
		read_st = read_st->Trim();

		split_st = read_st->Split(',');

		// Check data cout 
		int ch_count ;                    // file data ch count 
		int loop1;                                            // Loop count1
		String ^chk_str = String::Empty;                            // check string
		int mpm_number;                                       // mpm number
		int slot_number;                                      // Slot number
		int ch_number;                                        // ch number 
															  //Check data cout 
		if (chkeach_ch->Checked == true)
		{
			//Reference measurement one channel at a time
			ch_count = (split_st->Length - 1) / 2;
		}
		else
		{
			ch_count = split_st->Length - 2;
		}


		if (ch_count != chklst_ch->CheckedItems->Count)
		{
			MessageBox::Show("Reference data mismatch.Please selecet right data.", "", MessageBoxButtons::OK);
			reader->Close();
			return;
		}

		// -----Check parameter & make reference data struct 
		STSDataStruct refdata_strunct;                        // Data struct for reference
		System::Collections::Generic::List<STSDataStruct>  lst_refdata_struct;    // Data struct for reference List    
		bool match_flag = false;                           // match flag

		for (loop1 = 1; loop1 <= ch_count; loop1++)
		{
			// mpm device number 
			chk_str = split_st[loop1]->Substring(3, 1);
			mpm_number = System::Convert::ToInt32(chk_str);

			// mpm Slot number 
			chk_str = split_st[loop1]->Substring(8, 1);
			slot_number = System::Convert::ToInt32(chk_str);

			// mpm Ch number 
			chk_str = split_st[loop1]->Substring(11, 1);
			ch_number = System::Convert::ToInt32(chk_str);


			// Check exsist data in data struct 
			for each(STSDataStruct item in Data_struct)
			{
				if (item.MPMNumber == mpm_number & item.SlotNumber == slot_number & item.ChannelNumber == ch_number)
				{
					match_flag = true;
					break;
				}
			}

			if (match_flag == false)
			{
				MessageBox::Show("Reference data mismatch.Please selecet right data.", "", MessageBoxButtons::OK);
				reader->Close();
				return;
			}

			// Add reference data struct 
			refdata_strunct.MPMNumber = mpm_number;
			refdata_strunct.SlotNumber = slot_number;
			refdata_strunct.ChannelNumber = ch_number;
			refdata_strunct.RangeNumber = 1;
			refdata_strunct.SweepCount = 1;

			lst_refdata_struct.Add(refdata_strunct);
		}

		// -------Read Reference data
		cli::array<cli::array<float>^> ^power;          // Power data list 
		int counter;                         // Counter
		double wavelength;                       // Read Wavelength 
		bool finish = true;
		if (chkeach_ch->Checked)
		{
			// Reference measurement one channel at a time
			cli::array<cli::array<float>^> ^ monitor;               // Monitordata

			power = gcnew cli::array<cli::array<float>^> (ch_count);
			monitor = gcnew cli::array<cli::array<float>^>(ch_count);
			for (loop1 = 0; loop1 <= ch_count - 1; loop1++)
			{
				power[loop1] = gcnew cli::array<float>(1000000);
				monitor[loop1] = gcnew cli::array<float>(1000000);
			}
			do
			{
				read_st = reader->ReadLine();
				if (read_st == nullptr)
					break;
				read_st = read_st->Trim();
				split_st = read_st->Split(',');

				// Check Start Wavelength 
				if (counter == 0)
				{
					if (split_st[0] != txtstartwave->Text)
					{
						MessageBox::Show("Reference data mismatch.Please selecet right data.");
						reader->Close();
						return;
					}
				}

				// hold wavelength data
				wavelength = Convert::ToDouble(split_st[0]);
				for (loop1 = 0; loop1 <= ch_count - 1; loop1++) {
					power[loop1]->SetValue(Convert::ToSingle(split_st[loop1 + 1]), counter);
				}
				for (loop1 = 0; loop1 <= ch_count - 1; loop1++)
				{
					monitor[loop1]->SetValue(Convert::ToSingle(split_st[ch_count + loop1 + 1]), counter);
				}
				counter = counter + 1;
			} while (true);

			reader->Close();
			for (loop1 = 0; loop1 <= ch_count - 1; loop1++)
			{
				power[loop1]->Resize(power[loop1], counter);
				monitor[loop1]->Resize(monitor[loop1], counter);
			}

			// Check Stop wavelength 
			if (wavelength != Convert::ToDouble(txtstopwave->Text))
			{
				MessageBox::Show("Reference data mismatch.Please selecet right data.");
				return;
			}

			// check number of point 


			int datapoint;                            // number of data point 
			datapoint = (int)(Math::Abs(Convert::ToDouble(txtstopwave->Text) - Convert::ToDouble(txtstartwave->Text)) / Convert::ToDouble(txtstepwave->Text)) + 1;

			if (datapoint != monitor[0]->Length)
			{
				MessageBox::Show("Reference data mismatch.Please selecet right data.");
				return;
			}

			// -------Add in  data to STS Process class
			int errorcode;                            // Errorcode
			counter = 0;

			for each(auto item in lst_refdata_struct)
			{
				// Add in reference data of rescaled.
				errorcode = Cal_STS.Add_Ref_Rawdata(power[counter], monitor[counter], item);

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
			cli::array<float> ^monitor;               // Monitordata
			power = gcnew cli::array<cli::array<float>^>(ch_count);

			for (loop1 = 0; loop1 <= ch_count - 1; loop1++)
				power[loop1] =  gcnew cli::array<float>(1000000);

			do
			{
				read_st = reader->ReadLine();
				if (read_st == nullptr)
					break;
				read_st = read_st->Trim();
				split_st = read_st->Split(',');

				// Check Start Wavelength 
				if (counter == 0)
				{
					if (split_st[0] !=txtstartwave->Text)
					{
						MessageBox::Show("Reference data mismatch.Please selecet right data.");
						reader->Close();
						return;
					}
				}

				// hold wavelength data
				wavelength = Convert::ToDouble(split_st[0]);
				for (loop1 = 0; loop1 <= ch_count - 1; loop1++)
					power[loop1]->SetValue(Convert::ToSingle(split_st[loop1 + 1]), counter);
				monitor->SetValue(Convert::ToSingle(split_st[ch_count + 1]), counter);
				counter = counter + 1;
			} while (true);

			reader->Close();
			for (loop1 = 0; loop1 <= ch_count - 1; loop1++)
				power[loop1]->Resize(power[loop1], counter);

			monitor->Resize(monitor, counter);

			// Check Stop wavelength 
			if (wavelength != Convert::ToDouble(txtstopwave->Text))
			{
				MessageBox::Show("Reference data mismatch.Please selecet right data.");
				return;
			}

			// check number of point 

			int datapoint;                            // number of data point 

			datapoint = (int)(Math::Abs(Convert::ToDouble(txtstopwave->Text) - Convert::ToDouble(txtstartwave->Text)) / Convert::ToDouble(txtstepwave->Text)) + 1;

			if (datapoint != monitor->Length)
			{
				MessageBox::Show("Reference data mismatch.Please selecet right data.");
				return;
			}

			// -------Add in  data to STS Process class
			int errorcode;                            // Errorcode
			counter = 0;

			for each(auto item in lst_refdata_struct)
			{
				// Add in reference data of rescaled.
				errorcode = Cal_STS.Add_Ref_Rawdata(power[counter], monitor, item);

				if (errorcode != 0)
				{
					Show_Inst_Error(errorcode);
					return;
				}
				counter = counter + 1;
			}
		}
		MessageBox::Show("Completed.", "", MessageBoxButtons::OK);

	}

	private: System::Void btnsaveref_rawdata_Click(System::Object^  sender, System::EventArgs^  e) {
		// ---------------------------------------------------------------------------
		// Save reference Raw data
		// ---------------------------------------------------------------------------
		int loop1 = 0;                        // loop count1   
		int process_error;                // process class error
		cli::array<double> ^wavetable = nullptr;         // wavelength table
		cli::array<float> ^powdata = nullptr;        // powerdata  rescaled    
		cli::array<float> ^monitordata = nullptr;      // monitordata rescaled 
		cli::array<cli::array<float>^> ^lstpowdata;    // Power data list 
		cli::array<cli::array<float>^> ^ lstmonitordata;     // monitor data list  

		lstpowdata = gcnew cli::array<cli::array<float>^>(Refdata_struct.Count);
		// split strin array
		// Get reference Raw data (after the rescaling)
		for each(STSDataStruct item in Refdata_struct)
		{
			powdata = gcnew cli::array<float>(0);

			// monitor data is 1 data for each sweep. It can be overwrite.
			process_error = Cal_STS.Get_Ref_Power_Rawdata(item, powdata);
			if (process_error != 0)
			{
				Show_STS_Error(process_error);
				return;
			}

			lstpowdata->SetValue(powdata, loop1);
			loop1++;
		}

		//Get reference Raw monitor data
		STSDataStruct get_struct;                 // struct of get
		STSDataStruct befor_struct;           // befor struct
		loop1 = 0;
		lstmonitordata = gcnew cli::array<cli::array<float>^>(Ref_monitordata_struct.Count);

		for each(STSDataStruct item in Ref_monitordata_struct)
		{
			if (chkeach_ch->Checked)
			{
				// Reference measurement one channel at a time
				if ((item.MPMNumber == befor_struct.MPMNumber) & (item.SlotNumber == befor_struct.SlotNumber) & (item.ChannelNumber == befor_struct.ChannelNumber))
					continue;
			}
			monitordata = gcnew cli::array<float>(0);
			process_error = Cal_STS.Get_Ref_Monitor_Rawdata(item,  monitordata);

			if (process_error != 0)
			{
				Show_STS_Error(process_error);
				return;
			}

			get_struct.MPMNumber = item.MPMNumber;
			get_struct.SlotNumber = item.SlotNumber;
			get_struct.ChannelNumber = item.ChannelNumber;
			// get_struct.SOP = item.SOP

			lstmonitordata->SetValue(monitordata, loop1);
			befor_struct = get_struct;
			loop1++;
		}


		// Get Target wavelengt table
		process_error = Cal_STS.Get_Target_Wavelength_Table(wavetable);
		loop1 = 0;
		if (process_error != 0)
		{
			Show_STS_Error(process_error);
			return;
		}

		// ------File save 

		String ^fpath = String::Empty;                  // file path 

		SaveFileDialog1->Title = "Reference Raw data";
		SaveFileDialog1->Filter = "csv file(*.csv)|*.csv";
		SaveFileDialog1->ShowDialog();
		fpath = SaveFileDialog1->FileName;

		System::IO::StreamWriter ^writer = gcnew System::IO::StreamWriter(fpath, false, System::Text::Encoding::GetEncoding("UTF-8"));

		String ^hedder = String::Empty;                 // file hedder 

		hedder = "Wavelength(nm)";

		for each(STSDataStruct item in Data_struct)
		{
			if (item.SweepCount != 1)
				continue;

			hedder = hedder + ",mpm" + System::Convert::ToString(item.MPMNumber) + "Slot" + System::Convert::ToString(item.SlotNumber) + "Ch" + System::Convert::ToString(item.ChannelNumber);
		}

		if (chkeach_ch->Checked == true)
		{
			//Reference measurement one channel at a time
			for each(STSDataStruct item in Refdata_struct)
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

		// write hedder
		writer->WriteLine(hedder);


		// Write data 
		String ^write_str = String::Empty;                  // write string 
		int loop2;                                    // loop count 2
		int loop3;                                    // loop count 3


		for (loop1 = 0; loop1 <= wavetable->GetUpperBound(0); loop1++)
		{

			// wavelength data
			write_str = System::Convert::ToString(wavetable[loop1]);

			// Power data
			for (loop2 = 0; loop2 <= lstpowdata->Length - 1; loop2++)
				write_str = write_str + "," + lstpowdata[loop2][loop1];


			// monitordata
			for (loop3 = 0; loop3 <= lstmonitordata->Length - 1; loop3++)
			{
				write_str = write_str + "," + lstmonitordata[loop3][loop1];
			}

			writer->WriteLine(write_str);
		}

		writer->Close();
		MessageBox::Show("Completed.", "", MessageBoxButtons::OK);
	}

	private: System::Void btnsaveRawdata_Click(System::Object^  sender, System::EventArgs^  e) {
		// -------------------------------------------------------------------------
		// Save mesurement raw data
		// -------------------------------------------------------------------------
		int loop1;                                        // loop1
		int loop2;                                        // loop2
		int loop3;                                        // loop3
		int errorcode;                                    // Errorcode
		cli::array<double> ^wavelength_table = nullptr;         // wavelength table
		cli::array<float> ^powerdata = nullptr;        // powerdata  rescaled    
		cli::array<float> ^monitordata = nullptr;      // monitordata rescaled 
		cli::array<cli::array<float>^> ^lstpower;    // Power data list 

		lstpower = gcnew cli::array<cli::array<float>^>(chklst_ch->CheckedItems->Count);

		// -- Get Wavelength table
		errorcode = Cal_STS.Get_Target_Wavelength_Table(wavelength_table);

		if (errorcode != 0)
		{
			Show_STS_Error(errorcode);
			return;
		}


		String ^fpath = String::Empty;              // File　path
		System::IO::StreamWriter ^writer;            // Writer 
		String ^write_string = String::Empty;
		String ^hedder = String::Empty;


		for (loop1 = 0; loop1 <= Meas_rang.Count - 1; loop1++)
		{
			loop3 = 0;
			// get raw data same range data
			for each(STSDataStruct item in Data_struct)
			{
				if (item.RangeNumber != Meas_rang[loop1])
					continue;
				powerdata = gcnew cli::array<float>(0);
				errorcode = Cal_STS.Get_Meas_Power_Rawdata(item, powerdata);

				if (errorcode != 0)
				{
					Show_STS_Error(errorcode);
					return;
				}

				lstpower->SetValue(powerdata, loop3);
				loop3++;
			}

			//----get raw monitor data same range
			for each(STSMonitorStruct monitoritem in Meas_monitor_struct)
			{
				if (monitoritem.SweepCount == loop1 + 1)
					errorcode = Cal_STS.Get_Meas_Monitor_Rawdata(monitoritem, monitordata);
				else
					continue;

			}

			// --File save at same range data 
			switch (loop1)
			{
			case 0:
			{
				SaveFileDialog1->Title = "1st Range data";
				break;
			}

			case 1:
			{
				SaveFileDialog1->Title = "2nd Range data";
				break;
			}

			default:
			{
				SaveFileDialog1->Title = System::Convert::ToString(loop1 + 1) + "rd Range data";
				break;
			}
			}

			SaveFileDialog1->Filter = "csv file(*.csv)|*.csv";
			SaveFileDialog1->ShowDialog();
			fpath = SaveFileDialog1->FileName;

			writer = gcnew System::IO::StreamWriter(fpath, false, System::Text::Encoding::GetEncoding("UTF-8"));

			hedder = "wavelength";

			for each(STSDataStruct item in Data_struct)
			{
				if (item.RangeNumber != Meas_rang[loop1])
					continue;

				hedder = hedder + "," + "mpm" + System::Convert::ToString(item.MPMNumber) + "Slot" + System::Convert::ToString(item.SlotNumber) + "Ch" + System::Convert::ToString(item.ChannelNumber);
			}

			hedder = hedder + "," + "Monitordata";

			writer->WriteLine(hedder);

			for (loop2 = 0; loop2 <= wavelength_table->GetUpperBound(0); loop2++)
			{
				write_string = System::Convert::ToString(wavelength_table[loop2]);

				for (loop3 = 0; loop3 <= lstpower->Length - 1; loop3++)
					write_string = write_string + "," + lstpower[loop3][loop2];

				write_string = write_string + "," + monitordata[loop2];


				writer->WriteLine(write_string);
			}

			writer->Close();
			//lstpower = gcnew List<float[]>();
			monitordata = nullptr;
		}

		MessageBox::Show("Completed.", "", MessageBoxButtons::OK);
	}
	};
}
