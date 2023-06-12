#pragma once

namespace ILSTS_Sample_CPP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class Instrument_Setting : public System::Windows::Forms::Form
	{
	public:
		Instrument_Setting(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		cli::array<String^> ^SPU_Resource;                 // SPU resource name array
		cli::array<String^> ^USB_Resource;                 // USB resource name array
		String^ TSL_Communicater;               // TSL Communicator name
		String^ MPM_Communicater;               // MPM Communicator name
		String^ TSL_Address;                    // TSL address
		int TSL_Portnumber;                // TSL LAN port number
		int MPM_Count;                     // MPM number of device 
		cli::array<String^> ^MPM_Address = gcnew  cli::array<String^>(2);                 // MPM address 
		cli::array<int> ^ MPM_Portnumber = gcnew cli::array<int>(2);             // MPM LAN port number
		String^ SPU_DeviveID;                   // SPU Deviece resource

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Instrument_Setting()
		{
			if (components)
			{
				delete components;
			}
		}
	internal: System::Windows::Forms::GroupBox^  grp_mpmdev2;
	protected:
	internal: System::Windows::Forms::Label^  Label9;
	internal: System::Windows::Forms::TextBox^  txtmpm_lanport2;
	internal: System::Windows::Forms::Label^  Label10;
	internal: System::Windows::Forms::TextBox^  txtmpm_ipadd2;
	internal: System::Windows::Forms::Label^  Label11;
	internal: System::Windows::Forms::TextBox^  txtmpm_gpibadd2;
	internal: System::Windows::Forms::ComboBox^  cmbspu_dev;
	internal: System::Windows::Forms::CheckBox^  chkmulti_dev;
	internal: System::Windows::Forms::GroupBox^  GroupBox8;
	internal: System::Windows::Forms::RadioButton^  rdo_mpmtcpip;
	internal: System::Windows::Forms::RadioButton^  rdo_mpmgpib;
	internal: System::Windows::Forms::GroupBox^  grp_mpmdev1;
	internal: System::Windows::Forms::Label^  Label7;
	internal: System::Windows::Forms::TextBox^  txtmpm_lanport1;
	internal: System::Windows::Forms::Label^  Label8;
	internal: System::Windows::Forms::TextBox^  txtmpm_ipadd1;
	internal: System::Windows::Forms::Label^  Label6;
	internal: System::Windows::Forms::TextBox^  txtmpm_gpibadd1;
	internal: System::Windows::Forms::GroupBox^  GroupBox3;
	internal: System::Windows::Forms::Label^  Label1;
	internal: System::Windows::Forms::Button^  btnconnect;
	internal: System::Windows::Forms::GroupBox^  GroupBox1;
	internal: System::Windows::Forms::Label^  Label5;
	internal: System::Windows::Forms::ComboBox^  cmbtsl_usb;
	internal: System::Windows::Forms::Label^  Label4;
	internal: System::Windows::Forms::TextBox^  txttsl_lanport;
	internal: System::Windows::Forms::Label^  Label3;
	internal: System::Windows::Forms::GroupBox^  GroupBox5;
	internal: System::Windows::Forms::RadioButton^  rdo_tslusb;
	internal: System::Windows::Forms::RadioButton^  rdo_tsltcpip;
	internal: System::Windows::Forms::RadioButton^  rdotsl_gpib;
	internal: System::Windows::Forms::GroupBox^  GroupBox4;
	internal: System::Windows::Forms::RadioButton^  rdo570;
	internal: System::Windows::Forms::RadioButton^  rdo550;
	internal: System::Windows::Forms::Label^  Label2;
	internal: System::Windows::Forms::TextBox^  txttsl_ipadd;
	internal: System::Windows::Forms::TextBox^  txttsl_gpibadd;
	internal: System::Windows::Forms::GroupBox^  GroupBox2;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Instrument_Setting::typeid));
			this->grp_mpmdev2 = (gcnew System::Windows::Forms::GroupBox());
			this->Label9 = (gcnew System::Windows::Forms::Label());
			this->txtmpm_lanport2 = (gcnew System::Windows::Forms::TextBox());
			this->Label10 = (gcnew System::Windows::Forms::Label());
			this->txtmpm_ipadd2 = (gcnew System::Windows::Forms::TextBox());
			this->Label11 = (gcnew System::Windows::Forms::Label());
			this->txtmpm_gpibadd2 = (gcnew System::Windows::Forms::TextBox());
			this->cmbspu_dev = (gcnew System::Windows::Forms::ComboBox());
			this->chkmulti_dev = (gcnew System::Windows::Forms::CheckBox());
			this->GroupBox8 = (gcnew System::Windows::Forms::GroupBox());
			this->rdo_mpmtcpip = (gcnew System::Windows::Forms::RadioButton());
			this->rdo_mpmgpib = (gcnew System::Windows::Forms::RadioButton());
			this->grp_mpmdev1 = (gcnew System::Windows::Forms::GroupBox());
			this->Label7 = (gcnew System::Windows::Forms::Label());
			this->txtmpm_lanport1 = (gcnew System::Windows::Forms::TextBox());
			this->Label8 = (gcnew System::Windows::Forms::Label());
			this->txtmpm_ipadd1 = (gcnew System::Windows::Forms::TextBox());
			this->Label6 = (gcnew System::Windows::Forms::Label());
			this->txtmpm_gpibadd1 = (gcnew System::Windows::Forms::TextBox());
			this->GroupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->Label1 = (gcnew System::Windows::Forms::Label());
			this->btnconnect = (gcnew System::Windows::Forms::Button());
			this->GroupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->Label5 = (gcnew System::Windows::Forms::Label());
			this->cmbtsl_usb = (gcnew System::Windows::Forms::ComboBox());
			this->Label4 = (gcnew System::Windows::Forms::Label());
			this->txttsl_lanport = (gcnew System::Windows::Forms::TextBox());
			this->Label3 = (gcnew System::Windows::Forms::Label());
			this->GroupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->rdo_tslusb = (gcnew System::Windows::Forms::RadioButton());
			this->rdo_tsltcpip = (gcnew System::Windows::Forms::RadioButton());
			this->rdotsl_gpib = (gcnew System::Windows::Forms::RadioButton());
			this->GroupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->rdo570 = (gcnew System::Windows::Forms::RadioButton());
			this->rdo550 = (gcnew System::Windows::Forms::RadioButton());
			this->Label2 = (gcnew System::Windows::Forms::Label());
			this->txttsl_ipadd = (gcnew System::Windows::Forms::TextBox());
			this->txttsl_gpibadd = (gcnew System::Windows::Forms::TextBox());
			this->GroupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->grp_mpmdev2->SuspendLayout();
			this->GroupBox8->SuspendLayout();
			this->grp_mpmdev1->SuspendLayout();
			this->GroupBox3->SuspendLayout();
			this->GroupBox1->SuspendLayout();
			this->GroupBox5->SuspendLayout();
			this->GroupBox4->SuspendLayout();
			this->GroupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// grp_mpmdev2
			// 
			this->grp_mpmdev2->Controls->Add(this->Label9);
			this->grp_mpmdev2->Controls->Add(this->txtmpm_lanport2);
			this->grp_mpmdev2->Controls->Add(this->Label10);
			this->grp_mpmdev2->Controls->Add(this->txtmpm_ipadd2);
			this->grp_mpmdev2->Controls->Add(this->Label11);
			this->grp_mpmdev2->Controls->Add(this->txtmpm_gpibadd2);
			this->grp_mpmdev2->Enabled = false;
			this->grp_mpmdev2->Location = System::Drawing::Point(335, 20);
			this->grp_mpmdev2->Name = L"grp_mpmdev2";
			this->grp_mpmdev2->Size = System::Drawing::Size(184, 141);
			this->grp_mpmdev2->TabIndex = 6;
			this->grp_mpmdev2->TabStop = false;
			this->grp_mpmdev2->Text = L"Device1";
			// 
			// Label9
			// 
			this->Label9->AutoSize = true;
			this->Label9->Location = System::Drawing::Point(118, 72);
			this->Label9->Name = L"Label9";
			this->Label9->Size = System::Drawing::Size(50, 13);
			this->Label9->TabIndex = 13;
			this->Label9->Text = L"LAN Port";
			// 
			// txtmpm_lanport2
			// 
			this->txtmpm_lanport2->Enabled = false;
			this->txtmpm_lanport2->Location = System::Drawing::Point(120, 88);
			this->txtmpm_lanport2->Name = L"txtmpm_lanport2";
			this->txtmpm_lanport2->Size = System::Drawing::Size(50, 20);
			this->txtmpm_lanport2->TabIndex = 12;
			this->txtmpm_lanport2->Text = L"5000";
			// 
			// Label10
			// 
			this->Label10->AutoSize = true;
			this->Label10->Location = System::Drawing::Point(15, 72);
			this->Label10->Name = L"Label10";
			this->Label10->Size = System::Drawing::Size(58, 13);
			this->Label10->TabIndex = 11;
			this->Label10->Text = L"IP Address";
			// 
			// txtmpm_ipadd2
			// 
			this->txtmpm_ipadd2->Enabled = false;
			this->txtmpm_ipadd2->Location = System::Drawing::Point(17, 88);
			this->txtmpm_ipadd2->Name = L"txtmpm_ipadd2";
			this->txtmpm_ipadd2->Size = System::Drawing::Size(86, 20);
			this->txtmpm_ipadd2->TabIndex = 10;
			this->txtmpm_ipadd2->Text = L"192.168.1.161";
			// 
			// Label11
			// 
			this->Label11->AutoSize = true;
			this->Label11->Location = System::Drawing::Point(15, 24);
			this->Label11->Name = L"Label11";
			this->Label11->Size = System::Drawing::Size(73, 13);
			this->Label11->TabIndex = 6;
			this->Label11->Text = L"GPIB Address";
			// 
			// txtmpm_gpibadd2
			// 
			this->txtmpm_gpibadd2->Location = System::Drawing::Point(17, 40);
			this->txtmpm_gpibadd2->Name = L"txtmpm_gpibadd2";
			this->txtmpm_gpibadd2->Size = System::Drawing::Size(75, 20);
			this->txtmpm_gpibadd2->TabIndex = 5;
			this->txtmpm_gpibadd2->Text = L"15";
			// 
			// cmbspu_dev
			// 
			this->cmbspu_dev->FormattingEnabled = true;
			this->cmbspu_dev->Location = System::Drawing::Point(40, 35);
			this->cmbspu_dev->Name = L"cmbspu_dev";
			this->cmbspu_dev->Size = System::Drawing::Size(113, 21);
			this->cmbspu_dev->TabIndex = 0;
			// 
			// chkmulti_dev
			// 
			this->chkmulti_dev->AutoSize = true;
			this->chkmulti_dev->Location = System::Drawing::Point(16, 107);
			this->chkmulti_dev->Name = L"chkmulti_dev";
			this->chkmulti_dev->Size = System::Drawing::Size(85, 17);
			this->chkmulti_dev->TabIndex = 5;
			this->chkmulti_dev->Text = L"Multi Device";
			this->chkmulti_dev->UseVisualStyleBackColor = true;
			this->chkmulti_dev->CheckedChanged += gcnew System::EventHandler(this, &Instrument_Setting::chkmulti_dev_CheckedChanged);
			// 
			// GroupBox8
			// 
			this->GroupBox8->Controls->Add(this->rdo_mpmtcpip);
			this->GroupBox8->Controls->Add(this->rdo_mpmgpib);
			this->GroupBox8->Location = System::Drawing::Point(16, 20);
			this->GroupBox8->Name = L"GroupBox8";
			this->GroupBox8->Size = System::Drawing::Size(123, 69);
			this->GroupBox8->TabIndex = 4;
			this->GroupBox8->TabStop = false;
			this->GroupBox8->Text = L"Communication";
			// 
			// rdo_mpmtcpip
			// 
			this->rdo_mpmtcpip->AutoSize = true;
			this->rdo_mpmtcpip->Location = System::Drawing::Point(24, 43);
			this->rdo_mpmtcpip->Name = L"rdo_mpmtcpip";
			this->rdo_mpmtcpip->Size = System::Drawing::Size(61, 17);
			this->rdo_mpmtcpip->TabIndex = 3;
			this->rdo_mpmtcpip->Text = L"TCP/IP";
			this->rdo_mpmtcpip->UseVisualStyleBackColor = true;
			// 
			// rdo_mpmgpib
			// 
			this->rdo_mpmgpib->AutoSize = true;
			this->rdo_mpmgpib->Checked = true;
			this->rdo_mpmgpib->Location = System::Drawing::Point(24, 20);
			this->rdo_mpmgpib->Name = L"rdo_mpmgpib";
			this->rdo_mpmgpib->Size = System::Drawing::Size(50, 17);
			this->rdo_mpmgpib->TabIndex = 2;
			this->rdo_mpmgpib->TabStop = true;
			this->rdo_mpmgpib->Text = L"GPIB";
			this->rdo_mpmgpib->UseVisualStyleBackColor = true;
			this->rdo_mpmgpib->CheckedChanged += gcnew System::EventHandler(this, &Instrument_Setting::rdo_mpmgpib_CheckedChanged);
			// 
			// grp_mpmdev1
			// 
			this->grp_mpmdev1->Controls->Add(this->Label7);
			this->grp_mpmdev1->Controls->Add(this->txtmpm_lanport1);
			this->grp_mpmdev1->Controls->Add(this->Label8);
			this->grp_mpmdev1->Controls->Add(this->txtmpm_ipadd1);
			this->grp_mpmdev1->Controls->Add(this->Label6);
			this->grp_mpmdev1->Controls->Add(this->txtmpm_gpibadd1);
			this->grp_mpmdev1->Location = System::Drawing::Point(145, 20);
			this->grp_mpmdev1->Name = L"grp_mpmdev1";
			this->grp_mpmdev1->Size = System::Drawing::Size(184, 141);
			this->grp_mpmdev1->TabIndex = 0;
			this->grp_mpmdev1->TabStop = false;
			this->grp_mpmdev1->Text = L"Device1";
			// 
			// Label7
			// 
			this->Label7->AutoSize = true;
			this->Label7->Location = System::Drawing::Point(118, 72);
			this->Label7->Name = L"Label7";
			this->Label7->Size = System::Drawing::Size(50, 13);
			this->Label7->TabIndex = 13;
			this->Label7->Text = L"LAN Port";
			// 
			// txtmpm_lanport1
			// 
			this->txtmpm_lanport1->Enabled = false;
			this->txtmpm_lanport1->Location = System::Drawing::Point(120, 88);
			this->txtmpm_lanport1->Name = L"txtmpm_lanport1";
			this->txtmpm_lanport1->Size = System::Drawing::Size(50, 20);
			this->txtmpm_lanport1->TabIndex = 12;
			this->txtmpm_lanport1->Text = L"5000";
			// 
			// Label8
			// 
			this->Label8->AutoSize = true;
			this->Label8->Location = System::Drawing::Point(15, 72);
			this->Label8->Name = L"Label8";
			this->Label8->Size = System::Drawing::Size(58, 13);
			this->Label8->TabIndex = 11;
			this->Label8->Text = L"IP Address";
			// 
			// txtmpm_ipadd1
			// 
			this->txtmpm_ipadd1->Enabled = false;
			this->txtmpm_ipadd1->Location = System::Drawing::Point(17, 88);
			this->txtmpm_ipadd1->Name = L"txtmpm_ipadd1";
			this->txtmpm_ipadd1->Size = System::Drawing::Size(86, 20);
			this->txtmpm_ipadd1->TabIndex = 10;
			this->txtmpm_ipadd1->Text = L"192.168.1.161";
			// 
			// Label6
			// 
			this->Label6->AutoSize = true;
			this->Label6->Location = System::Drawing::Point(15, 24);
			this->Label6->Name = L"Label6";
			this->Label6->Size = System::Drawing::Size(73, 13);
			this->Label6->TabIndex = 6;
			this->Label6->Text = L"GPIB Address";
			// 
			// txtmpm_gpibadd1
			// 
			this->txtmpm_gpibadd1->Location = System::Drawing::Point(17, 40);
			this->txtmpm_gpibadd1->Name = L"txtmpm_gpibadd1";
			this->txtmpm_gpibadd1->Size = System::Drawing::Size(75, 20);
			this->txtmpm_gpibadd1->TabIndex = 5;
			this->txtmpm_gpibadd1->Text = L"16";
			// 
			// GroupBox3
			// 
			this->GroupBox3->Controls->Add(this->Label1);
			this->GroupBox3->Controls->Add(this->cmbspu_dev);
			this->GroupBox3->Location = System::Drawing::Point(23, 374);
			this->GroupBox3->Name = L"GroupBox3";
			this->GroupBox3->Size = System::Drawing::Size(329, 70);
			this->GroupBox3->TabIndex = 6;
			this->GroupBox3->TabStop = false;
			this->GroupBox3->Text = L"SPU";
			// 
			// Label1
			// 
			this->Label1->AutoSize = true;
			this->Label1->Location = System::Drawing::Point(38, 18);
			this->Label1->Name = L"Label1";
			this->Label1->Size = System::Drawing::Size(41, 13);
			this->Label1->TabIndex = 1;
			this->Label1->Text = L"Device";
			// 
			// btnconnect
			// 
			this->btnconnect->Location = System::Drawing::Point(403, 393);
			this->btnconnect->Name = L"btnconnect";
			this->btnconnect->Size = System::Drawing::Size(166, 38);
			this->btnconnect->TabIndex = 7;
			this->btnconnect->Text = L"Connect";
			this->btnconnect->UseVisualStyleBackColor = true;
			this->btnconnect->Click += gcnew System::EventHandler(this, &Instrument_Setting::btnconnect_Click);
			// 
			// GroupBox1
			// 
			this->GroupBox1->Controls->Add(this->Label5);
			this->GroupBox1->Controls->Add(this->cmbtsl_usb);
			this->GroupBox1->Controls->Add(this->Label4);
			this->GroupBox1->Controls->Add(this->txttsl_lanport);
			this->GroupBox1->Controls->Add(this->Label3);
			this->GroupBox1->Controls->Add(this->GroupBox5);
			this->GroupBox1->Controls->Add(this->GroupBox4);
			this->GroupBox1->Controls->Add(this->Label2);
			this->GroupBox1->Controls->Add(this->txttsl_ipadd);
			this->GroupBox1->Controls->Add(this->txttsl_gpibadd);
			this->GroupBox1->Location = System::Drawing::Point(23, 22);
			this->GroupBox1->Name = L"GroupBox1";
			this->GroupBox1->Size = System::Drawing::Size(546, 159);
			this->GroupBox1->TabIndex = 4;
			this->GroupBox1->TabStop = false;
			this->GroupBox1->Text = L"TSL ";
			// 
			// Label5
			// 
			this->Label5->AutoSize = true;
			this->Label5->Location = System::Drawing::Point(292, 82);
			this->Label5->Name = L"Label5";
			this->Label5->Size = System::Drawing::Size(78, 13);
			this->Label5->TabIndex = 11;
			this->Label5->Text = L"USB Resource";
			// 
			// cmbtsl_usb
			// 
			this->cmbtsl_usb->Enabled = false;
			this->cmbtsl_usb->FormattingEnabled = true;
			this->cmbtsl_usb->Location = System::Drawing::Point(294, 102);
			this->cmbtsl_usb->Name = L"cmbtsl_usb";
			this->cmbtsl_usb->Size = System::Drawing::Size(172, 21);
			this->cmbtsl_usb->TabIndex = 10;
			// 
			// Label4
			// 
			this->Label4->AutoSize = true;
			this->Label4->Location = System::Drawing::Point(481, 24);
			this->Label4->Name = L"Label4";
			this->Label4->Size = System::Drawing::Size(50, 13);
			this->Label4->TabIndex = 9;
			this->Label4->Text = L"LAN Port";
			// 
			// txttsl_lanport
			// 
			this->txttsl_lanport->Enabled = false;
			this->txttsl_lanport->Location = System::Drawing::Point(483, 40);
			this->txttsl_lanport->Name = L"txttsl_lanport";
			this->txttsl_lanport->Size = System::Drawing::Size(50, 20);
			this->txttsl_lanport->TabIndex = 8;
			this->txttsl_lanport->Text = L"5000";
			// 
			// Label3
			// 
			this->Label3->AutoSize = true;
			this->Label3->Location = System::Drawing::Point(378, 24);
			this->Label3->Name = L"Label3";
			this->Label3->Size = System::Drawing::Size(58, 13);
			this->Label3->TabIndex = 7;
			this->Label3->Text = L"IP Address";
			// 
			// GroupBox5
			// 
			this->GroupBox5->Controls->Add(this->rdo_tslusb);
			this->GroupBox5->Controls->Add(this->rdo_tsltcpip);
			this->GroupBox5->Controls->Add(this->rdotsl_gpib);
			this->GroupBox5->Location = System::Drawing::Point(145, 24);
			this->GroupBox5->Name = L"GroupBox5";
			this->GroupBox5->Size = System::Drawing::Size(132, 115);
			this->GroupBox5->TabIndex = 6;
			this->GroupBox5->TabStop = false;
			this->GroupBox5->Text = L"Communication";
			// 
			// rdo_tslusb
			// 
			this->rdo_tslusb->AutoSize = true;
			this->rdo_tslusb->Location = System::Drawing::Point(17, 82);
			this->rdo_tslusb->Name = L"rdo_tslusb";
			this->rdo_tslusb->Size = System::Drawing::Size(47, 17);
			this->rdo_tslusb->TabIndex = 3;
			this->rdo_tslusb->Text = L"USB";
			this->rdo_tslusb->UseVisualStyleBackColor = true;
			this->rdo_tslusb->CheckedChanged += gcnew System::EventHandler(this, &Instrument_Setting::rdo_tslusb_CheckedChanged);
			// 
			// rdo_tsltcpip
			// 
			this->rdo_tsltcpip->AutoSize = true;
			this->rdo_tsltcpip->Location = System::Drawing::Point(17, 54);
			this->rdo_tsltcpip->Name = L"rdo_tsltcpip";
			this->rdo_tsltcpip->Size = System::Drawing::Size(61, 17);
			this->rdo_tsltcpip->TabIndex = 2;
			this->rdo_tsltcpip->Text = L"TCP/IP";
			this->rdo_tsltcpip->UseVisualStyleBackColor = true;
			this->rdo_tsltcpip->CheckedChanged += gcnew System::EventHandler(this, &Instrument_Setting::rdo_tsltcpip_CheckedChanged);
			// 
			// rdotsl_gpib
			// 
			this->rdotsl_gpib->AutoSize = true;
			this->rdotsl_gpib->Checked = true;
			this->rdotsl_gpib->Location = System::Drawing::Point(17, 20);
			this->rdotsl_gpib->Name = L"rdotsl_gpib";
			this->rdotsl_gpib->Size = System::Drawing::Size(50, 17);
			this->rdotsl_gpib->TabIndex = 1;
			this->rdotsl_gpib->TabStop = true;
			this->rdotsl_gpib->Text = L"GPIB";
			this->rdotsl_gpib->UseVisualStyleBackColor = true;
			this->rdotsl_gpib->CheckedChanged += gcnew System::EventHandler(this, &Instrument_Setting::rdotsl_gpib_CheckedChanged);
			// 
			// GroupBox4
			// 
			this->GroupBox4->Controls->Add(this->rdo570);
			this->GroupBox4->Controls->Add(this->rdo550);
			this->GroupBox4->Location = System::Drawing::Point(16, 24);
			this->GroupBox4->Name = L"GroupBox4";
			this->GroupBox4->Size = System::Drawing::Size(123, 115);
			this->GroupBox4->TabIndex = 5;
			this->GroupBox4->TabStop = false;
			this->GroupBox4->Text = L"Product";
			// 
			// rdo570
			// 
			this->rdo570->AutoSize = true;
			this->rdo570->Checked = true;
			this->rdo570->Location = System::Drawing::Point(15, 33);
			this->rdo570->Name = L"rdo570";
			this->rdo570->Size = System::Drawing::Size(89, 17);
			this->rdo570->TabIndex = 0;
			this->rdo570->TabStop = true;
			this->rdo570->Text = L"TSL-570/770";
			this->rdo570->UseVisualStyleBackColor = true;
			this->rdo570->CheckedChanged += gcnew System::EventHandler(this, &Instrument_Setting::rdo570_CheckedChanged);
			// 
			// rdo550
			// 
			this->rdo550->AutoSize = true;
			this->rdo550->Location = System::Drawing::Point(15, 67);
			this->rdo550->Name = L"rdo550";
			this->rdo550->Size = System::Drawing::Size(89, 17);
			this->rdo550->TabIndex = 1;
			this->rdo550->Text = L"TSL-550/710";
			this->rdo550->UseVisualStyleBackColor = true;
			// 
			// Label2
			// 
			this->Label2->AutoSize = true;
			this->Label2->Location = System::Drawing::Point(292, 24);
			this->Label2->Name = L"Label2";
			this->Label2->Size = System::Drawing::Size(73, 13);
			this->Label2->TabIndex = 4;
			this->Label2->Text = L"GPIB Address";
			// 
			// txttsl_ipadd
			// 
			this->txttsl_ipadd->Enabled = false;
			this->txttsl_ipadd->Location = System::Drawing::Point(380, 40);
			this->txttsl_ipadd->Name = L"txttsl_ipadd";
			this->txttsl_ipadd->Size = System::Drawing::Size(86, 20);
			this->txttsl_ipadd->TabIndex = 3;
			this->txttsl_ipadd->Text = L"192.168.1.100";
			// 
			// txttsl_gpibadd
			// 
			this->txttsl_gpibadd->Location = System::Drawing::Point(294, 40);
			this->txttsl_gpibadd->Name = L"txttsl_gpibadd";
			this->txttsl_gpibadd->Size = System::Drawing::Size(75, 20);
			this->txttsl_gpibadd->TabIndex = 2;
			this->txttsl_gpibadd->Text = L"1";
			// 
			// GroupBox2
			// 
			this->GroupBox2->Controls->Add(this->grp_mpmdev2);
			this->GroupBox2->Controls->Add(this->chkmulti_dev);
			this->GroupBox2->Controls->Add(this->GroupBox8);
			this->GroupBox2->Controls->Add(this->grp_mpmdev1);
			this->GroupBox2->Location = System::Drawing::Point(23, 188);
			this->GroupBox2->Name = L"GroupBox2";
			this->GroupBox2->Size = System::Drawing::Size(546, 180);
			this->GroupBox2->TabIndex = 5;
			this->GroupBox2->TabStop = false;
			this->GroupBox2->Text = L"MPM";
			// 
			// Instrument_Setting
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(593, 467);
			this->Controls->Add(this->GroupBox3);
			this->Controls->Add(this->btnconnect);
			this->Controls->Add(this->GroupBox1);
			this->Controls->Add(this->GroupBox2);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Instrument_Setting";
			this->Text = L"Instrument_Setting";
			this->Load += gcnew System::EventHandler(this, &Instrument_Setting::MyForm_Load);
			this->grp_mpmdev2->ResumeLayout(false);
			this->grp_mpmdev2->PerformLayout();
			this->GroupBox8->ResumeLayout(false);
			this->GroupBox8->PerformLayout();
			this->grp_mpmdev1->ResumeLayout(false);
			this->grp_mpmdev1->PerformLayout();
			this->GroupBox3->ResumeLayout(false);
			this->GroupBox3->PerformLayout();
			this->GroupBox1->ResumeLayout(false);
			this->GroupBox1->PerformLayout();
			this->GroupBox5->ResumeLayout(false);
			this->GroupBox5->PerformLayout();
			this->GroupBox4->ResumeLayout(false);
			this->GroupBox4->PerformLayout();
			this->GroupBox2->ResumeLayout(false);
			this->GroupBox2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		// ---------------------------------------------------------------
		// Sub Form Load
		// ---------------------------------------------------------------
		int loop1;

		// ---Add in SPU resource to comboboxfrom main form
		for (loop1 = 0; loop1 <= SPU_Resource->GetUpperBound(0); loop1++)
			cmbspu_dev->Items->Add(SPU_Resource[loop1]);

		// ----Add in USB resource to combobox from main form
		for (loop1 = 0; loop1 <= USB_Resource->GetUpperBound(0); loop1++)
			cmbtsl_usb->Items->Add(USB_Resource[loop1]);

	}
	private: System::Void btnconnect_Click(System::Object^  sender, System::EventArgs^  e) {
		// ----------------------------------------------------------
		// Connect       
		// ----------------------------------------------------------


		// ----TSL Communication diteal

		// GPIB Communcation?
		if (rdotsl_gpib->Checked == true)
		{
			TSL_Communicater = "GPIB";
			TSL_Address = txttsl_gpibadd->Text;
			TSL_Portnumber = 0;
		}

		// TCP/IP Communciation?
		if (rdo_tsltcpip->Checked == true)
		{
			TSL_Communicater = "LAN";
			TSL_Address = txttsl_ipadd->Text;
			TSL_Portnumber = int::Parse(txttsl_lanport->Text);
		}

		// USB Communcation?
		if (rdo_tslusb->Checked == true)
		{
			TSL_Communicater = "USB";
			TSL_Address = cmbtsl_usb->SelectedIndex.ToString();
			TSL_Portnumber = 0;
		}

		// -----MPM Communcation diteal

		// Multi Device?
		if (chkmulti_dev->Checked == true)
		{
			MPM_Count = 2;

			// GPIB communcation?
			if (rdo_mpmgpib->Checked == true)
			{
				MPM_Address[0] = txtmpm_gpibadd1->Text;
				MPM_Address[1] = txtmpm_gpibadd2->Text;
				MPM_Portnumber[0] = 0;
				MPM_Portnumber[1] = 0;

				MPM_Communicater = "GPIB";
			}
			else
			{
				// TCL/IP communcation?
				MPM_Address[0] = txtmpm_ipadd1->Text;
				MPM_Address[1] = txtmpm_ipadd2->Text;
				MPM_Portnumber[0] = int::Parse(txtmpm_lanport1->Text);
				MPM_Portnumber[1] = int::Parse(txtmpm_lanport2->Text);

				MPM_Communicater = "LAN";
			}
		}
		else
		{
			MPM_Count = 1;

			// GPIB communcation?
			if (rdo_mpmgpib->Checked == true)
			{
				MPM_Address[0] = txtmpm_gpibadd1->Text;
				MPM_Address[1] = "";
				MPM_Portnumber[0] = 0;
				MPM_Portnumber[1] = 0;

				MPM_Communicater = "GPIB";
			}
			else
			{
				// TCL/IP communcation?
				MPM_Address[0] = txtmpm_ipadd1->Text;
				MPM_Address[1] = "";
				MPM_Portnumber[0] = int::Parse(txtmpm_lanport1->Text);
				MPM_Portnumber[1] = 0;

				MPM_Communicater = "LAN";
			}
		}


		// SPU Resouce

		if (cmbspu_dev->Text == "")
		{
			MessageBox::Show("", "Please enter to the SPU device resouce", MessageBoxButtons::OK);
			return;
		}

		SPU_DeviveID = cmbspu_dev->Text;
		Instrument_Setting::Close();
	}

	private: System::Void rdo570_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		// -----------------------------------------------------
		// 570 Checked
		// -----------------------------------------------------

		if (rdo570->Checked == true)
		{
			// TSL-570
			rdo_tsltcpip->Enabled = true;
			rdo_tslusb->Enabled = true;
		}
		else
		{
			// TSL-550/710
			// There can control only GPIB
			rdo_tslusb->Enabled = false;
			rdo_tsltcpip->Enabled = false;
			rdotsl_gpib->Checked = true;
		}
	}

	private: System::Void rdotsl_gpib_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		// ------------------------------------------------------
		// TSL Control GPIB
		// ------------------------------------------------------

		if (rdotsl_gpib->Checked == true)
		{
			txttsl_gpibadd->Enabled = true;
			txttsl_ipadd->Enabled = false;
			txttsl_lanport->Enabled = false;
			cmbtsl_usb->Enabled = false;
		}
	}

	private: System::Void rdo_tsltcpip_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		// ------------------------------------------------------
		// TSL Control TCP/IP
		// ------------------------------------------------------

		if (rdo_tsltcpip->Checked == true)
		{
			txttsl_gpibadd->Enabled = false;
			txttsl_ipadd->Enabled = true;
			txttsl_lanport->Enabled = true;
			cmbtsl_usb->Enabled = false;
		}
	}

	private: System::Void rdo_tslusb_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		// ------------------------------------------------------
		// TSL Control USB
		// ------------------------------------------------------

		if (rdo_tslusb->Checked == true)
		{
			txttsl_gpibadd->Enabled = false;
			txttsl_ipadd->Enabled = false;
			txttsl_lanport->Enabled = false;
			cmbtsl_usb->Enabled = true;
		}
	}

	private: System::Void chkmulti_dev_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		// ------------------------------------------------------------------
		// Selecet MPM Multi-Device
		// -------------------------------------------------------------------

		grp_mpmdev2->Enabled = chkmulti_dev->Checked;
	}

	private: System::Void rdo_mpmgpib_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		// --------------------------------------------------------------------
		// MPM Control GPIB
		// --------------------------------------------------------------------

		if (rdo_mpmgpib->Checked == true)
		{
			txtmpm_gpibadd1->Enabled = true;
			txtmpm_gpibadd2->Enabled = true;
			txtmpm_ipadd1->Enabled = false;
			txtmpm_ipadd2->Enabled = false;
			txtmpm_lanport1->Enabled = false;
			txtmpm_lanport2->Enabled = false;
		}
		else
		{
			txtmpm_gpibadd1->Enabled = false;
			txtmpm_gpibadd2->Enabled = false;
			txtmpm_ipadd1->Enabled = true;
			txtmpm_ipadd2->Enabled = true;
			txtmpm_lanport1->Enabled = true;
			txtmpm_lanport2->Enabled = true;
		}
	}
	};
}
