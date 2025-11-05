using Santec;
using Santec.STSProcess;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Windows.Forms;

namespace ILSTS_Sample
{
    public partial class Form1 : Form
    {
        private TSL tsl = new TSL();                                              // tsl control class
        private MPM[] mpm;                                                // mpm control class
        private SPU spu = new SPU();                                              // spu control class
        private ILSTS Cal_STS = new ILSTS();                                        // STS calucrate class
        private List<STSDataStruct> Data_struct = new List<STSDataStruct>();                   // STS data Struct 
        private List<STSDataStruct> Refdata_struct = new List<STSDataStruct>();                // Reference data Struct
        private List<STSMonitorStruct> Meas_monitor_struct = new List<STSMonitorStruct>();           // Measurement monitor data struct
        private List<STSDataStruct> Ref_monitordata_struct = new List<STSDataStruct>();                         // Reference monitor data struct
        private List<STSDataStructForMerge> Mergedata_struct = new List<STSDataStructForMerge>();      // Data struct for merge  
        private List<int> Meas_rang = new List<int>();                           // Measurement Range 
        private bool Flag_213;                                         // Exist 213 flag      T: Exist F: nothing
        private bool Flag_215;                                         // Exist 215 flag      T: Exist F: nothing
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, System.EventArgs e)
        {
            // -------------------------------------------------------------------------
            // Form Load    (MainForm)
            // -------------------------------------------------------------------------
            string[] spudev = null;                        // spu device name
            int errorcode;                                // errorcode 
            string[] usb_resource = null;                  // usb communication resource
            // ----Check Connction of spu deviece
            errorcode = spu.Get_Device_ID(ref spudev);

            if (errorcode != 0)
            {
                Show_Inst_Error(errorcode);
                System.Environment.Exit(0);
            }

            // ----Check usb resource
            usb_resource = Santec.Communication.MainCommunication.Get_USB_Resouce();

            // ------show Setting Form
            Instrument_Setting set_form = new Instrument_Setting();

            set_form.Owner = this;
            set_form.SPU_Resource = spudev;
            set_form.USB_Resource = usb_resource;
            set_form.ShowDialog();

            // ---Apply to communication parametere from Instrument setting form
            Santec.Communication.CommunicationMethod tsl_communcation_method;
            Santec.Communication.CommunicationMethod mpm_communcation_method;

            // ----tsl　Communication method
            if (set_form.TSL_Communicater == "GPIB")
            {
                tsl_communcation_method = Santec.Communication.CommunicationMethod.GPIB;
                tsl.Terminator = CommunicationTerminator.CrLf;
                tsl.GPIBAddress = int.Parse(set_form.TSL_Address);
                tsl.GPIBBoard = 0;
                tsl.GPIBConnectType = Santec.Communication.GPIBConnectType.NIVisa;
            }
            else if (set_form.TSL_Communicater == "LAN")
            {
                tsl_communcation_method = Santec.Communication.CommunicationMethod.TCPIP;
                tsl.Terminator = CommunicationTerminator.Cr;
                tsl.IPAddress = set_form.TSL_Address;
                tsl.Port = set_form.TSL_Portnumber;
            }
            else
            {
                // USB 
                tsl_communcation_method = Santec.Communication.CommunicationMethod.USB;
                tsl.DeviceID = System.Convert.ToUInt32(set_form.TSL_Address);
                tsl.Terminator = CommunicationTerminator.Cr;
            }

            // ---mpm Communicatipon method
            int loop1;
            int mpmcount;                     // mpm count

            if (set_form.MPM_Communicater == "GPIB")
                mpm_communcation_method = Santec.Communication.CommunicationMethod.GPIB;
            else
                mpm_communcation_method = Santec.Communication.CommunicationMethod.TCPIP;

            mpmcount = set_form.MPM_Count;

            mpm = new MPM[mpmcount];

            for (loop1 = 0; loop1 <= mpmcount - 1; loop1++)
            {
                mpm[loop1] = new MPM();

                if (set_form.MPM_Communicater == "GPIB")
                {
                    mpm[loop1].GPIBAddress = int.Parse(set_form.MPM_Address[loop1]);
                    mpm[loop1].GPIBConnectType = Santec.Communication.GPIBConnectType.NIVisa;
                }
                else
                {
                    mpm[loop1].IPAddress = set_form.MPM_Address[loop1];
                    mpm[loop1].Port = set_form.MPM_Portnumber[loop1];
                }

                // -------------------------------------------------------------------------
                // mpm muximum logging data read time is 11s
                // communication time out must to set > mpm logging data read time.
                // --------------------------------------------------------------------------
                mpm[loop1].TimeOut = 11000;
            }

            // ----spu Communcation Setting 
            spu.DeviceName = set_form.SPU_DeviveID;

            // -----------Connect------------------------------------------------- 
            // tsl
            errorcode = tsl.Connect(tsl_communcation_method);

            if (errorcode != 0)
            {
                MessageBox.Show("tsl can't connect.Please check connection.", "", MessageBoxButtons.OK);
                System.Environment.Exit(0);
            }

            // mpm
            for (loop1 = 0; loop1 <= mpm.GetUpperBound(0); loop1++)
            {
                errorcode = mpm[loop1].Connect(mpm_communcation_method);

                if (errorcode != 0)
                {
                    MessageBox.Show("mpm Can't connect. Please check connection.", "", MessageBoxButtons.OK);

                    System.Environment.Exit(0);
                }
            }

            // spu(DAQ)
            string ans = string.Empty;
            errorcode = spu.Connect(ref ans);

            if (errorcode != 0)
            {
                MessageBox.Show("spu Can't connect. Please check connection.", "", MessageBoxButtons.OK);

                System.Environment.Exit(0);
            }


            // ------------Check mpm Module information
            errorcode = Check_Module_Information();

            if (errorcode != 0)
            {
                MessageBox.Show("System can't use mpm-215 togeter other module.", "", MessageBoxButtons.OK);
                Environment.Exit(0);
            }

            // -----------Reflect instrument parameter to Form
            Referect_EnableCh_for_form();                // mpm Eanble ch
            Referect_EnableRange_for_form();             // mpm selectable range
            Add_TSL_Sweep_Speed();                       // tsl Sweep speed(only tsl-570)
        }

        private void Show_Inst_Error(int errordata)
        {
            // ------------------------------------
            // Show error code
            // ------------------------------------
            string[] errorstring = Enum.GetNames(typeof(ExceptionCode));
            int[] errorvale = (int[])Enum.GetValues(typeof(ExceptionCode));
            int loop1;

            for (loop1 = 0; loop1 <= errorvale.GetUpperBound(0); loop1++)
            {
                if (errorvale[loop1] == errordata)
                {
                    MessageBox.Show(errorstring[loop1]);
                    break;
                }
            }
        }

        private void Show_STS_Error(int errordata)
        {
            // ------------------------------------
            // Show error code for STS
            // ------------------------------------
            string[] errorstring = Enum.GetNames(typeof(ErrorCode));
            int[] errorvale = (int[])Enum.GetValues(typeof(ErrorCode));
            int loop1;

            for (loop1 = 0; loop1 <= errorvale.GetUpperBound(0); loop1++)
            {
                if (errorvale[loop1] == errordata)
                {
                    MessageBox.Show(errorstring[loop1]);
                    break;
                }
            }
        }

        private int Get_MPM_Loggdata(int deveice, int slot, int ch, ref float[] data)
        {
            // ---------------------------------------------------------------
            // Get mpm Logg data
            // --------------------------------------------------------------
            int inst_error;

            inst_error = mpm[deveice].Get_Each_Channel_Logdata(slot, ch, ref data);
            return inst_error;
        }

        private int Sweep_Process()
        {
            // ------------------------------------------------------------
            // Sweep Process
            // ------------------------------------------------------------
            int inst_error;               // Instullment error
            int loop1;                    // loop count 


            // mpm sampling start 
            for (loop1 = 0; loop1 <= mpm.GetUpperBound(0); loop1++)
            {
                inst_error = mpm[loop1].Logging_Start();
                if (inst_error != 0)
                    return inst_error;
            }

            // tsl waiting for start status 
            inst_error = tsl.Waiting_For_Sweep_Status(2000, TSL.Sweep_Status.WaitingforTrigger);

            // ---error handling -> mpm Logging Stop
            if (inst_error != 0)
            {
                for (loop1 = 0; loop1 <= mpm.GetUpperBound(0); loop1++)
                    mpm[loop1].Logging_Stop();
                return inst_error;
            }

            // spu sampling start
            inst_error = spu.Sampling_Start();
            if (inst_error != 0)
                return inst_error;

            // tsl issue software trigger
            inst_error = tsl.Set_Software_Trigger();

            // ---error handling -> mpm Logging Stop
            if (inst_error != 0)
            {
                for (loop1 = 0; loop1 <= mpm.GetUpperBound(0); loop1++)
                    mpm[loop1].Logging_Stop();
                return inst_error;
            }

            // spu waiting for sampling 
            inst_error = spu.Waiting_for_sampling();

            // ---error handling -> mpm Logging Stop
            if (inst_error != 0)
            {
                for (loop1 = 0; loop1 <= mpm.GetUpperBound(0); loop1++)
                    mpm[loop1].Logging_Stop();
                return inst_error;
            }

            int mpm_stauts = new int();                   // mpm logging status 0:douring measurement 1:Compleated -1:Stopped
            int mpm_count = new int();                    // mpm number of logging completed point  
            Stopwatch st = new Stopwatch();                     // stopwatch           
            bool mpm_completed_falg = true;    // mpm logging completed flag  F:not completed T:completed    
            bool isSweeping = true;
            // mpm waiting for sampling 
            st.Start();                          // stopwathc start 
            do
            {
                for (loop1 = 0; loop1 <= mpm.GetUpperBound(0); loop1++)
                {
                    inst_error = mpm[loop1].Get_Logging_Status(ref mpm_stauts, ref mpm_count);
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
            }
            while (isSweeping);

            st.Stop();

            // mpm sampling stop
            for (loop1 = 0; loop1 <= mpm.GetUpperBound(0); loop1++)
            {
                inst_error = mpm[loop1].Logging_Stop();
                if (inst_error != 0)
                    return inst_error;
            }


            // tsl Waiting for standby
            inst_error = tsl.Waiting_For_Sweep_Status(5000, TSL.Sweep_Status.Standby);

            if (inst_error != 0)
                return inst_error;

            if (mpm_completed_falg == false)
                // mpm logging timeout occurred.
                return -9999;

            return 0;
        }

        private int Save_Measurement_data()
        {
            // -------------------------------------------------------
            // Save Measurement data
            // -------------------------------------------------------
            double[] wavelength_table = null;            // Rescaled wavelength table  
            List<float[]> lstILdata = new List<float[]>();               // IL data list 
            int process_error;                          // process class error  
            int loop1;                                  // loop count
            float[] ildata = null;                      // il data arrray

            // Get Rescaled wavelength tabel 
            process_error = Cal_STS.Get_Target_Wavelength_Table(ref wavelength_table);


            // Get IL data 
            if (Flag_215 == true)
            {
                foreach (STSDataStruct items in Data_struct)
                {
                    process_error = Cal_STS.Get_IL_Data(ref ildata, items);
                    if (process_error != 0)
                        return process_error;

                    lstILdata.Add(ildata.ToArray());
                }
            }
            else
                foreach (STSDataStructForMerge items in Mergedata_struct)
                {
                    process_error = Cal_STS.Get_IL_Merge_Data(ref ildata, items);
                    if (process_error != 0)
                        return process_error;

                    lstILdata.Add(ildata.ToArray());
                }


            // -----Data Save 
            string file_path = string.Empty;

            SaveFileDialog1.Title = "IL data save";
            SaveFileDialog1.Filter = "csv file(*.csv)|*.csv";
            SaveFileDialog1.ShowDialog();

            file_path = SaveFileDialog1.FileName;

            System.IO.StreamWriter writer = new System.IO.StreamWriter(file_path, false, System.Text.Encoding.GetEncoding("UTF-8"));
            string write_string = null;
            string hedder = string.Empty;
            hedder = "Wavelength(nm)";
            foreach (STSDataStruct item in Data_struct)
            {
                if (item.SweepCount != 1)
                {
                    continue;
                }
                hedder = hedder + ",MPM" + item.MPMNumber.ToString() + "Slot" + item.SlotNumber.ToString() + "Ch" + item.ChannelNumber.ToString();
            }
            //write hedder
            writer.WriteLine(hedder);

            int loop2;

            for (loop1 = 0; loop1 <= wavelength_table.GetUpperBound(0); loop1++)
            {
                write_string = wavelength_table[loop1].ToString();

                for (loop2 = 0; loop2 <= lstILdata.Count - 1; loop2++)
                    write_string = write_string + "," + lstILdata[loop2][loop1];

                writer.WriteLine(write_string);
            }

            writer.Close();

            return 0;
        }

        private int Check_Module_Information()
        {
            // ------------------------------------------------------------
            // check Module information inside system
            // ------------------------------------------------------------
            int loop1;
            int loop2;
            int counter_215 = new int();                           // 215 counter 

            // mpm device loop
            for (loop1 = 0; loop1 <= mpm.GetUpperBound(0); loop1++)
            {
                // Slot loop
                for (loop2 = 0; loop2 <= 4; loop2++)
                {
                    // Enable Slot
                    if (mpm[loop1].Information.ModuleEnable[loop2] == true)
                    {

                        // Check mpm-215 insert
                        if (mpm[loop1].Information.ModuleType[loop2] == "MPM-215")
                        {
                            Flag_215 = true;
                            counter_215 = counter_215 + 1;
                        }

                        // Check mpm-213 insert
                        if (mpm[loop1].Information.ModuleType[loop2] == "MPM-213")
                            Flag_213 = true;
                    }
                }
            }

            // Check mpm-215 count & Module total count
            // STS system can't use 215 together other module.
            int enable_module_count = new int();                      // enable module count

            for (loop1 = 0; loop1 <= mpm.GetUpperBound(0); loop1++)
                enable_module_count = mpm[loop1].Information.NumberofModule + enable_module_count;// total module count

            if (Flag_215 == true)
            {
                if (enable_module_count != counter_215)
                    return -1;
            }
            return 0;
        }

        private void Referect_EnableCh_for_form()
        {
            // ------------------------------------------------
            // Reflect mpm ch 
            // ------------------------------------------------
            int loop1;
            int loop2;
            bool[] enable_slot;
            string slot_type;

            for (loop1 = 0; loop1 <= mpm.GetUpperBound(0); loop1++)
            {
                // get insert module count with "mpm Information" class 
                enable_slot = mpm[loop1].Information.ModuleEnable;

                // modeule loop(Maximum 5 slot)
                for (loop2 = 0; loop2 <= 4; loop2++)
                {
                    if (enable_slot[loop2] == true)
                    {
                        // get module type with "mpm Information" class 
                        slot_type = mpm[loop1].Information.ModuleType[loop2];

                        if (slot_type != "MPM-212")
                        {
                            chklst_ch.Items.Add("mpm" + System.Convert.ToString(loop1 + 1) + " Slot" + System.Convert.ToString(loop2) + " Ch1");
                            chklst_ch.Items.Add("mpm" + System.Convert.ToString(loop1 + 1) + " Slot" + System.Convert.ToString(loop2) + " Ch2");
                            chklst_ch.Items.Add("mpm" + System.Convert.ToString(loop1 + 1) + " Slot" + System.Convert.ToString(loop2) + " Ch3");
                            chklst_ch.Items.Add("mpm" + System.Convert.ToString(loop1 + 1) + " Slot" + System.Convert.ToString(loop2) + " Ch4");
                        }
                        else
                        {
                            chklst_ch.Items.Add("mpm" + System.Convert.ToString(loop1 + 1) + " Slot" + System.Convert.ToString(loop2) + " Ch1");
                            chklst_ch.Items.Add("mpm" + System.Convert.ToString(loop1 + 1) + " Slot" + System.Convert.ToString(loop2) + " Ch2");
                        }
                    }
                }
            }
        }

        private int Add_TSL_Sweep_Speed()
        {
            // ---------------------------------------------------------
            // Add in selectable sweep speed to speed combbox
            // this function can use only tsl-570
            // ----------------------------------------------------------
            int inst_error;                       // instullment error
            double[] sweep_table = null;           // table


            // Get Sweep speed tabele
            // Except for tsl-570 "Device Error" occurre when call this function.
            inst_error = tsl.Get_Sweep_Speed_table(ref sweep_table);

            if (inst_error != 0 & inst_error != System.Convert.ToInt32(ExceptionCode.DeviceError))
                return inst_error;


            // -----Add in combbox when tsl-570
            int loop1;

            if (inst_error != Convert.ToInt32(ExceptionCode.DeviceError))
            {
                for (loop1 = 0; loop1 <= sweep_table.GetUpperBound(0); loop1++)

                    cmbspeed.Items.Add(sweep_table[loop1]);
            }
            return 0;
        }

        private void Referect_EnableRange_for_form()
        {
            // -----------------------------------------------------
            // Refelect mpm Range
            // -------------------------------------------------------


            // mpm-213 can use just 1 to 4 range
            if (Flag_213 == true)
            {
                chklst_range.Items.Add("Range1");
                chklst_range.Items.Add("Range2");
                chklst_range.Items.Add("Range3");
                chklst_range.Items.Add("Range4");
            }
            else
            {
                chklst_range.Items.Add("Range1");
                chklst_range.Items.Add("Range2");
                chklst_range.Items.Add("Range3");
                chklst_range.Items.Add("Range4");
                chklst_range.Items.Add("Range5");
            }

            // mpm-215 can't select range
            if (Flag_215 == true)
                chklst_range.Enabled = false;
        }

        private void btnset_Click(object sender, EventArgs e)
        {
            // -------------------------------------------------------------------------
            // Set Parameter
            // --------------------------------------------------------------------------
            double startwave;             // Startwavelength(nm)
            double stopwave;              // Stopwavelength(nm)
            double set_pow;               // Power(dBm)
            double wavestep;              // wavelenthg step(nm)
            double speed;                 // Sweep Speed (nm/sec)
            int inst_error;           // instullment error


            startwave = double.Parse(txtstartwave.Text);
            stopwave = double.Parse(txtstopwave.Text);
            wavestep = double.Parse(txtstepwave.Text);
            speed = double.Parse(cmbspeed.Text);
            set_pow = double.Parse(txtpower.Text);

            // ------------tsl Setting--------------------------------------------------- 
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

            double tsl_acctualstep = new double();          // tsl output trigger step(nm)

            // set Sweep parameter
            inst_error = tsl.Set_Sweep_Parameter_for_STS(startwave, stopwave, speed, wavestep, ref tsl_acctualstep);
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


            // ----------mpm setting ---------------------------------------------------
            int loop1;

            for (loop1 = 0; loop1 <= mpm.GetUpperBound(0); loop1++)
            {
                // Sweep parameter setting 
                inst_error = mpm[loop1].Set_Logging_Paremeter_for_STS(startwave, stopwave, wavestep, speed, Santec.MPM.Measurement_Mode.Freerun);
                if (inst_error != 0)
                {
                    Show_Inst_Error(inst_error);
                    return;
                }
                inst_error = mpm[loop1].Set_Wavelength((startwave+stopwave)/2);
                if (inst_error != 0)
                {
                    Show_Inst_Error(inst_error);
                    return;
                }

            }

            // ---------spu setting------------------------------------------------------ 
            double averaging_time = new double();

            inst_error = mpm[0].Get_Averaging_Time(ref averaging_time);

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
            sts_error = Cal_STS.Set_Rescaling_Setting(RescalingMode.Freerun_SPU, averaging_time, true);

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
            if (chkeach_ch.Checked == true)
            {
                Prepare_dataST_Each();
            }
            else
            {
                Prepare_dataST();
            }
            MessageBox.Show("Completed.", "", MessageBoxButtons.OK);

        }
        private void Prepare_dataST()
        {
            // -----------------------------------------------
            // Prepar STS data struct
            // -----------------------------------------------
            int rangecout;                        // number of range
            int chcount;                          // number of ch 
            int loop1;                            // loop count1
            int loop2;                            // loop count2
            string text_st = string.Empty;            // text String 
            string[] split_st = null;              // split string array

            // List clear 
            Meas_rang.Clear();                               // Measurement Range
            Data_struct.Clear();                             // DataSturct of STS
            Refdata_struct.Clear();                          // Reference data struct
            Ref_monitordata_struct.Clear();            //Reference monitor data struct
            Meas_monitor_struct.Clear();                     // Measurement monitor data struct



            Mergedata_struct.Clear();                        // DataStruct of Merge 

            rangecout = chklst_range.CheckedItems.Count;
            chcount = chklst_ch.CheckedItems.Count;
            if (Flag_215 == true)
                //If mom215 range must be set 1
                Meas_rang.Add(1);
            else
            {
                if (rangecout == 0 | chcount == 0)
                {
                    MessageBox.Show("Please check measurement parameters.");
                    return;
                }

                // hold range data 
                for (loop1 = 0; loop1 <= chklst_range.Items.Count - 1; loop1++)
                {
                    if (chklst_range.GetItemChecked(loop1) == true)
                        Meas_rang.Add(loop1 + 1);
                }
            }
            int device_number;
            int slot_number;
            int ch_number;
            STSDataStruct set_struct = new STSDataStruct();
            STSDataStructForMerge set_struct_merge = new STSDataStructForMerge();
            int sweep_count;                          // Sweep count 
            // --for measurement MPM data
            for (loop2 = 0; loop2 <= Meas_rang.Count - 1; loop2++)
            {
                for (loop1 = 0; loop1 <= chklst_ch.Items.Count - 1; loop1++)
                {
                    if (chklst_ch.GetItemChecked(loop1) == true)
                    {
                        text_st = chklst_ch.Items[loop1].ToString();
                        split_st = text_st.Split(' ');
                        // ch parameter
                        device_number = System.Convert.ToInt32(split_st[0].Substring(3));
                        slot_number = System.Convert.ToInt32(split_st[1].Substring(4));
                        ch_number = System.Convert.ToInt32(split_st[2].Substring(2));
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
            STSMonitorStruct set_monitor_struct = new STSMonitorStruct();              // set struct for monitor
            for (loop2 = 0; loop2 <= Meas_rang.Count - 1; loop2++)
            {
                for (loop1 = 0; loop1 <= chklst_ch.Items.Count - 1; loop1++)
                {
                    if (chklst_ch.GetItemChecked(loop1) == true)
                    {
                        text_st = chklst_ch.Items[loop1].ToString();
                        split_st = text_st.Split(' ');
                        // ch parameter
                        device_number = System.Convert.ToInt32(split_st[0].Substring(3));

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
            for (loop1 = 0; loop1 <= chklst_ch.Items.Count - 1; loop1++)
            {
                if (chklst_ch.GetItemChecked(loop1) == true)
                {
                    text_st = chklst_ch.Items[loop1].ToString();
                    split_st = text_st.Split(' ');
                    // ch parameter
                    device_number = System.Convert.ToInt32(split_st[0].Substring(3));
                    slot_number = System.Convert.ToInt32(split_st[1].Substring(4));
                    ch_number = System.Convert.ToInt32(split_st[2].Substring(2));

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
            STSDataStruct set_ref_monitor_struct = new STSDataStruct();
            for (loop1 = 0; loop1 <= chklst_ch.Items.Count - 1; loop1++)
            {
                if (chklst_ch.GetItemChecked(loop1) == true)
                {
                    text_st = chklst_ch.Items[loop1].ToString();
                    split_st = text_st.Split(' ');
                    // Mainframe parameter
                    device_number = System.Convert.ToInt32(split_st[0].Substring(3));
                    slot_number = System.Convert.ToInt32(split_st[1].Substring(4));
                    ch_number = System.Convert.ToInt32(split_st[2].Substring(2));

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
        private void Prepare_dataST_Each()
        {
            // -----------------------------------------------
            // Prepar STS data struct
            // -----------------------------------------------
            int rangecout;                        // number of range
            int chcount;                          // number of ch 
            int loop1;                            // loop count1
            int loop2;                            // loop count2
            string text_st = string.Empty;            // text String 
            string[] split_st = null;              // split string array

            // List clear 
            Meas_rang.Clear();                               // Measurement Range
            Data_struct.Clear();                             // DataSturct of STS
            Refdata_struct.Clear();                          // Reference data struct
            Ref_monitordata_struct.Clear();                  // Reference monitor data struct
            Meas_monitor_struct.Clear();                     // Measurement monitor data struct



            Mergedata_struct.Clear();                        // DataStruct of Merge 

            rangecout = this.chklst_range.CheckedItems.Count;
            chcount = this.chklst_ch.CheckedItems.Count;

            if (Flag_215 == true)
                // If mom215 range must be set 1
                Meas_rang.Add(1);
            else
            {
                if (rangecout == 0 | chcount == 0)
                {
                    MessageBox.Show("Please check measurement parameters.");
                    return;
                }


                // hold range data 
                for (loop1 = 0; loop1 <= this.chklst_range.Items.Count - 1; loop1++)
                {
                    if (this.chklst_range.GetItemChecked(loop1) == true)
                        Meas_rang.Add(loop1 + 1);
                }
            }
            int device_number;
            int slot_number;
            int ch_number;
            STSDataStruct set_struct = new STSDataStruct();
            STSDataStructForMerge set_struct_merge = new STSDataStructForMerge();

            // --for measurement MPM data
            for (loop2 = 0; loop2 <= Meas_rang.Count - 1; loop2++)
            {
                for (loop1 = 0; loop1 <= this.chklst_ch.Items.Count - 1; loop1++)
                {
                    if (this.chklst_ch.GetItemChecked(loop1) == true)
                    {
                        text_st = chklst_ch.Items[loop1].ToString();
                        split_st = text_st.Split(' ');
                        // ch parameter
                        device_number = System.Convert.ToInt32(split_st[0].Substring(3));
                        slot_number = System.Convert.ToInt32(split_st[1].Substring(4));
                        ch_number = System.Convert.ToInt32(split_st[2].Substring(2));
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
            STSMonitorStruct set_monitor_struct = new STSMonitorStruct();              // set struct for monitor
            for (loop2 = 0; loop2 <= Meas_rang.Count - 1; loop2++)
            {
                for (loop1 = 0; loop1 <= this.chklst_ch.Items.Count - 1; loop1++)
                {
                    if (this.chklst_ch.GetItemChecked(loop1) == true)
                    {
                        text_st = chklst_ch.Items[loop1].ToString();
                        split_st = text_st.Split(' ');
                        // ch parameter
                        device_number = System.Convert.ToInt32(split_st[0].Substring(3));

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
            set_struct = new STSDataStruct();
            STSDataStruct set_ref_monitor_struct = new STSDataStruct();
            for (loop1 = 0; loop1 <= this.chklst_ch.Items.Count - 1; loop1++)
            {
                if (this.chklst_ch.GetItemChecked(loop1) == true)
                {
                    text_st = chklst_ch.Items[loop1].ToString();
                    split_st = text_st.Split(' ');
                    // ch parameter
                    device_number = System.Convert.ToInt32(split_st[0].Substring(3));
                    slot_number = System.Convert.ToInt32(split_st[1].Substring(4));
                    ch_number = System.Convert.ToInt32(split_st[2].Substring(2));

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

        private void btnget_reference_Click(object sender, EventArgs e)
        {

            // ------------------------------------------------------------------------------
            // Get Reference
            // ------------------------------------------------------------------------------
            int inst_error;                       // Instullment error
            int loop1;

            // ----- mpm setting for selected 1st range
            for (loop1 = 0; loop1 <= mpm.GetUpperBound(0); loop1++)
            {
                // set Range for mpm
                inst_error = mpm[loop1].Set_Range(Meas_rang[0]);
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


            if (this.chkeach_ch.Checked)
            {
                // Reference measurement one channel at a time
                foreach (STSDataStruct item in Refdata_struct)
                {
                    MessageBox.Show("Connect fiber to MPM" + item.MPMNumber + "_Slot" + item.SlotNumber + "_Ch" + item.ChannelNumber + ".");
                    // -----Sweep 
                    inst_error = Sweep_Process();
                    if (inst_error == -9999)
                    {
                        // MPM logging timeout occurred.
                        MessageBox.Show("MPM Trigger receive error! Please check trigger cable connection.");
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

                    inst_error = Get_Each_channel_reference_samplingdata(ref inst_flag, item.MPMNumber, item.SlotNumber, item.ChannelNumber, item.SweepCount);

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
                    MessageBox.Show("MPM Trigger receive error! Please check trigger cable connection.");
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

                inst_error = Get_reference_samplingdata(ref inst_flag);

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

            // TSL Sweep Stop
            inst_error = tsl.Sweep_Stop();
            if (inst_error != 0)
            {
                Show_Inst_Error(inst_error);
                return;
            }

            MessageBox.Show("Completed.", "", MessageBoxButtons.OK);
        }
        private int Get_Each_channel_reference_samplingdata(ref bool inst_flag, int currentMPMNumber, int currentSlotNumber, int currentChannelNumber, int currentSweepCount)
        {
            // ---------------------------------------------------------------
            // Get logging reference data & add in 
            // ---------------------------------------------------------------
            int inst_error;                        // Instullment error
            float[] logg_data = null;              // MPM Logging data
            int cal_error;                         // process error

            // ----Load　Reference MPM data & add in data for STS Process Class for each channel
            foreach (STSDataStruct item in Refdata_struct)
            {
                if ((item.MPMNumber != currentMPMNumber | item.SlotNumber != currentSlotNumber | item.ChannelNumber != currentChannelNumber))
                    continue;

                // Read corresponded MPM data
                inst_error = Get_MPM_Loggdata(item.MPMNumber - 1, item.SlotNumber, item.ChannelNumber, ref logg_data);

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
            float[] triggerdata = null;     // tigger data 
            float[] monitordata = null;     // monitor data

            inst_error = spu.Get_Sampling_Rawdata(ref triggerdata, ref monitordata);

            if (inst_error != 0)
            {
                inst_flag = true;
                return inst_error;
            }

            foreach (STSDataStruct monitor_item in Ref_monitordata_struct)
            {
                cal_error = Cal_STS.Add_Ref_MonitorData(triggerdata, monitordata, monitor_item);
                if (cal_error != 0)
                {
                    inst_flag = false;
                    return cal_error;
                }
            }

            // cal_error = Cal_STS.Add_Ref_MonitorData(triggerdata, monitordata, Ref_monitor_struct)

            // If cal_error <> 0 Then
            // inst_flag = False
            // Return cal_error
            // End If

            return 0;
        }

        private int Get_reference_samplingdata(ref bool inst_flag)
        {
            // ---------------------------------------------------------------
            // Get logging reference data & add in 
            // ---------------------------------------------------------------
            int inst_error;                        // Instullment error
            float[] logg_data = null;              // mpm Logging data
            int cal_error;                         // process error


            // ----Load　Reference mpm data & add in data for STS Process Class for each channel
            foreach (STSDataStruct item in Refdata_struct)
            {

                // Read corresponded mpm data
                inst_error = Get_MPM_Loggdata(item.MPMNumber - 1, item.SlotNumber, item.ChannelNumber, ref logg_data);

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
            float[] triggerdata = null;     // tigger data 
            float[] monitordata = null;     // monitor data

            inst_error = spu.Get_Sampling_Rawdata(ref triggerdata, ref monitordata);

            if (inst_error != 0)
            {
                inst_flag = true;
                return inst_error;
            }

            foreach (STSDataStruct monitor_item in Ref_monitordata_struct)
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

        private int Get_measurement_samplingdata(int sweepcount, ref bool inst_flag)
        {
            // ---------------------------------------------------------------
            // Get logging measurement data & add in 
            // ---------------------------------------------------------------
            int inst_error;                        // Instullment error
            float[] logg_data = null;              // mpm Logging data
            int cal_error;                        // process error


            // -- Load mpm Logging data & Add in STS Process class with measurment sts data struct 
            foreach (STSDataStruct item in Data_struct)
            {
                if (item.SweepCount != sweepcount)
                    continue;

                // Read corresponded mpm data
                inst_error = Get_MPM_Loggdata(item.MPMNumber - 1, item.SlotNumber, item.ChannelNumber, ref logg_data);

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
            float[] triggerdata = null;
            float[] monitordata = null;

            inst_error = spu.Get_Sampling_Rawdata(ref triggerdata, ref monitordata);

            if (inst_error != 0)
            {
                inst_flag = true;
                return inst_error;
            }


            // Search item from measurement monitor data structure according to sweep count.

            foreach (STSMonitorStruct item in Meas_monitor_struct)
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

        private void btnmeas_Click(object sender, EventArgs e)
        {
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
                    for (loop2 = 0; loop2 <= mpm.GetUpperBound(0); loop2++)
                    {
                        inst_error = mpm[loop2].Set_Range(Meas_rang[loop1]);

                        if (inst_error != 0)
                        {
                            Show_Inst_Error(inst_error);
                            return;
                        }
                    }
                    //Range Set delay
                    System.Threading.Thread.Sleep(1);
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
                    inst_error = Get_measurement_samplingdata(loop1 + 1, ref inst_flag);

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
                        merge_type = Module_Type.MPM_213;
                    else
                        merge_type = Module_Type.MPM_211;

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

            MessageBox.Show("Completed.", "", MessageBoxButtons.OK);
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            // -----------------------------------------------------------------------------
            // Reference Data Read
            // This function must use after "SET" 
            // -----------------------------------------------------------------------------
            string fpath = string.Empty;
            System.IO.StreamReader reader;

            // -------Reference file　Read 

            OpenFileDialog1.Title = "Reference Data";
            OpenFileDialog1.ShowDialog();
            fpath = OpenFileDialog1.FileName;

            reader = new System.IO.StreamReader(fpath);

            string read_st = string.Empty;                            // Read String 
            string[] split_st = null;                             // split strin array

            // hedder Read 
            read_st = reader.ReadLine();
            read_st = read_st.Trim();

            split_st = read_st.Split(',');


            // Check data cout 
            int ch_count;                    // file data ch count 
            int loop1;                                            // Loop count1
            string chk_str = string.Empty;                            // check string
            int mpm_number = new int();                                       // mpm number
            int slot_number;                                      // Slot number
            int ch_number;                                        // ch number 
            //Check data cout 
            if (chkeach_ch.Checked == true)
            {
                //Reference measurement one channel at a time
                ch_count = (split_st.Count() - 1) / 2;
            }
            else
            {
                ch_count = split_st.Count() - 2;
            }

            if (ch_count != chklst_ch.CheckedItems.Count)
            {
                MessageBox.Show("Reference data mismatch.Please selecet right data.", "", MessageBoxButtons.OK);
                reader.Close();
                return;
            }

            // -----Check parameter & make reference data struct 
            STSDataStruct refdata_strunct = new STSDataStruct();                        // Data struct for reference
            List<STSDataStruct> lst_refdata_struct = new List<STSDataStruct>();        // Data struct for reference List    
            bool match_flag = false;                           // match flag


            for (loop1 = 1; loop1 <= ch_count; loop1++)
            {
                // mpm device number 
                chk_str = split_st[loop1].Substring(3, 1);
                mpm_number = System.Convert.ToInt32(chk_str);

                // mpm Slot number 
                chk_str = split_st[loop1].Substring(8, 1);
                slot_number = System.Convert.ToInt32(chk_str);

                // mpm Ch number 
                chk_str = split_st[loop1].Substring(11, 1);
                ch_number = System.Convert.ToInt32(chk_str);


                // Check exsist data in data struct 
                foreach (STSDataStruct item in Data_struct)
                {
                    if (item.MPMNumber == mpm_number & item.SlotNumber == slot_number & item.ChannelNumber == ch_number)
                    {
                        match_flag = true;
                        break;
                    }
                }

                if (match_flag == false)
                {
                    MessageBox.Show("Reference data mismatch.Please selecet right data.", "", MessageBoxButtons.OK);
                    reader.Close();
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
            List<float>[] power;                 // Power data list 

            int counter = new int();                         // Counter
            double wavelength = new double();                       // Read Wavelength 

            if (chkeach_ch.Checked)
            {

                // Reference measurement one channel at a time
                List<float>[] monitor;               // Monitordata

                power = new List<float>[ch_count];
                monitor = new List<float>[ch_count];


                for (loop1 = 0; loop1 <= ch_count - 1; loop1++)
                {
                    power[loop1] = new List<float>();
                    monitor[loop1] = new List<float>();
                }
                do
                {
                    read_st = reader.ReadLine();
                    if (read_st == "")
                        break;
                    read_st = read_st.Trim();
                    split_st = read_st.Split(',');

                    // Check Start Wavelength 
                    if (counter == 0)
                    {
                        if (split_st[0] != this.txtstartwave.Text)
                        {
                            MessageBox.Show("Reference data mismatch.Please selecet right data.");
                            reader.Close();
                            return;
                        }
                    }

                    // hold wavelength data
                    wavelength = System.Convert.ToDouble(split_st[0]);
                    for (loop1 = 0; loop1 <= ch_count - 1; loop1++)
                        power[loop1].Add(System.Convert.ToSingle(split_st[loop1 + 1]));
                    for (loop1 = 0; loop1 <= ch_count - 1; loop1++)
                        monitor[loop1].Add(System.Convert.ToSingle(split_st[ch_count + loop1 + 1]));
                    counter = counter + 1;
                }
                while (true);

                reader.Close();

                // Check Stop wavelength 
                if (wavelength != System.Convert.ToDouble(this.txtstopwave.Text))
                {
                    MessageBox.Show("Reference data mismatch.Please selecet right data.");
                    return;
                }

                // check number of point 


                int datapoint;                            // number of data point 
                datapoint = (int)(Math.Abs(Convert.ToDouble(txtstopwave.Text) - Convert.ToDouble(txtstartwave.Text)) / Convert.ToDouble(txtstepwave.Text)) + 1;

                if (datapoint != monitor[0].Count)
                {
                    MessageBox.Show("Reference data mismatch.Please selecet right data.");
                    return;
                }

                // -------Add in  data to STS Process class
                int errorcode;                            // Errorcode
                counter = 0;

                foreach (var item in lst_refdata_struct)
                {
                    // Add in reference data of rescaled.
                    errorcode = Cal_STS.Add_Ref_Rawdata(power[counter].ToArray(), monitor[counter].ToArray(), item);

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
                List<float> monitor = new List<float>();             // Monitordata

                power = new List<float>[ch_count];

                for (loop1 = 0; loop1 <= ch_count - 1; loop1++)
                    power[loop1] = new List<float>();

                do
                {
                    read_st = reader.ReadLine();
                    if (read_st == "")
                        break;
                    read_st = read_st.Trim();
                    split_st = read_st.Split(',');

                    // Check Start Wavelength 
                    if (counter == 0)
                    {
                        if (split_st[0] != this.txtstartwave.Text)
                        {
                            MessageBox.Show("Reference data mismatch.Please selecet right data.");
                            reader.Close();
                            return;
                        }
                    }

                    // hold wavelength data
                    wavelength = System.Convert.ToDouble(split_st[0]);
                    for (loop1 = 0; loop1 <= ch_count - 1; loop1++)
                        power[loop1].Add(System.Convert.ToSingle(split_st[loop1 + 1]));
                    monitor.Add(System.Convert.ToSingle(split_st[ch_count + 1]));
                    counter = counter + 1;
                }
                while (true);

                reader.Close();

                // Check Stop wavelength 
                if (wavelength != System.Convert.ToDouble(this.txtstopwave.Text))
                {
                    MessageBox.Show("Reference data mismatch.Please selecet right data.");
                    return;
                }

                // check number of point 

                int datapoint;                            // number of data point 

                datapoint = (int)(Math.Abs(Convert.ToDouble(txtstopwave.Text) - Convert.ToDouble(txtstartwave.Text)) / Convert.ToDouble(txtstepwave.Text)) + 1;

                if (datapoint != monitor.Count)
                {
                    MessageBox.Show("Reference data mismatch.Please selecet right data.");
                    return;
                }

                // -------Add in  data to STS Process class
                int errorcode;                            // Errorcode
                counter = 0;

                foreach (var item in lst_refdata_struct)
                {
                    // Add in reference data of rescaled.
                    errorcode = Cal_STS.Add_Ref_Rawdata(power[counter].ToArray(), monitor.ToArray(), item);

                    if (errorcode != 0)
                    {
                        Show_Inst_Error(errorcode);
                        return;
                    }
                    counter = counter + 1;
                }
            }
            MessageBox.Show("Completed.", "", MessageBoxButtons.OK);
        }

        private void btnsaveref_rawdata_Click(object sender, EventArgs e)
        {
            // ---------------------------------------------------------------------------
            // Save reference Raw data
            // ---------------------------------------------------------------------------
            int loop1 = new int();                        // loop count1   
            int process_error;                // process class error
            double[] wavetable = null;         // wavelength table
            float[] powdata = null;           // powerdata  rescaled    
            float[] monitordata = null;       // monitordata rescaled 
            List<float[]> lstpowdata = new List<float[]>();     // Power data list 
            List<float[]> lstmonitordata = new List<float[]>();     // monitor data list  

            // Get reference Raw data (after the rescaling)
            foreach (STSDataStruct item in Refdata_struct)
            {
                // monitor data is 1 data for each sweep. It can be overwrite.
                process_error = Cal_STS.Get_Ref_Power_Rawdata(item, ref powdata);
                if (process_error != 0)
                {
                    Show_STS_Error(process_error);
                    return;
                }

                lstpowdata.Add(powdata.ToArray());
            }

            // Get reference Raw monitor data
            STSDataStruct get_struct = new STSDataStruct();                 // struct of get
            STSDataStruct befor_struct = new STSDataStruct();           // befor struct

            foreach (STSDataStruct item in Ref_monitordata_struct)
            {
                if (this.chkeach_ch.Checked)
                {
                    // Reference measurement one channel at a time
                    if ((item.MPMNumber == befor_struct.MPMNumber) & (item.SlotNumber == befor_struct.SlotNumber) & (item.ChannelNumber == befor_struct.ChannelNumber))
                        continue;
                }

                process_error = Cal_STS.Get_Ref_Monitor_Rawdata(item, ref monitordata);
                
                if (process_error != 0)
                {
                    Show_STS_Error(process_error);
                    return;
                }

                get_struct.MPMNumber = item.MPMNumber;
                get_struct.SlotNumber = item.SlotNumber;
                get_struct.ChannelNumber = item.ChannelNumber;
                // get_struct.SOP = item.SOP

                lstmonitordata.Add(monitordata.ToArray());
                befor_struct = get_struct;
            }

            // Get Target wavelengt table
            process_error = Cal_STS.Get_Target_Wavelength_Table(ref wavetable);

            if (process_error != 0)
            {
                Show_STS_Error(process_error);
                return;
            }

            // ------File save 

            string fpath = string.Empty;                  // file path 

            SaveFileDialog1.Title = "Reference Raw data";
            SaveFileDialog1.Filter = "csv file(*.csv)|*.csv";
            SaveFileDialog1.ShowDialog();
            fpath = SaveFileDialog1.FileName;

            System.IO.StreamWriter writer = new System.IO.StreamWriter(fpath, false, System.Text.Encoding.GetEncoding("UTF-8"));

            string hedder = string.Empty;                 // file hedder 

            hedder = "Wavelength(nm)";

            foreach (STSDataStruct item in Data_struct)
            {
                if (item.SweepCount != 1)
                    continue;

                hedder = hedder + ",mpm" + System.Convert.ToString(item.MPMNumber) + "Slot" + System.Convert.ToString(item.SlotNumber) + "Ch" + System.Convert.ToString(item.ChannelNumber);
            }
            if (chkeach_ch.Checked == true)
            {
                //Reference measurement one channel at a time
                foreach (STSDataStruct item in Refdata_struct)
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
            writer.WriteLine(hedder);


            // Write data 
            string write_str = string.Empty;                  // write string 
            int loop2;                                    // loop count 2
            int loop3;// loop count 3

            for (loop1 = 0; loop1 <= wavetable.GetUpperBound(0); loop1++)
            {

                // wavelength data
                write_str = System.Convert.ToString(wavetable[loop1]);

                // Power data
                for (loop2 = 0; loop2 <= lstpowdata.Count - 1; loop2++)
                    write_str = write_str + "," + lstpowdata[loop2][loop1];


                // monitordata
                for (loop3 = 0; loop3 <= lstmonitordata.Count - 1; loop3++)
                {
                    write_str = write_str + "," + lstmonitordata[loop3][loop1];
                }

                writer.WriteLine(write_str);
            }

            writer.Close();
            MessageBox.Show("Completed.");
        }

        private void btnsaveRawdata_Click(object sender, EventArgs e)
        {

            // -------------------------------------------------------------------------
            // Save mesurement raw data
            // -------------------------------------------------------------------------
            int loop1;                                        // loop1
            int loop2;                                        // loop2
            int loop3;                                        // loop3
            double[] wavelength_table = null;                  // Wavelength table
            float[] monitordata = null;
            float[] powerdata = null;
            int errorcode;                                    // Errorcode
            List<float[]> lstpower = new List<float[]>();


            // -- Get Wavelength table
            errorcode = Cal_STS.Get_Target_Wavelength_Table(ref wavelength_table);

            if (errorcode != 0)
            {
                Show_STS_Error(errorcode);
                return;
            }


            string fpath = string.Empty;              // File　path
            System.IO.StreamWriter writer;            // Writer 
            string write_string = string.Empty;
            string hedder = string.Empty;


            for (loop1 = 0; loop1 <= Meas_rang.Count - 1; loop1++)
            {

                // get raw data same range data
                foreach (STSDataStruct item in Data_struct)
                {
                    if (item.RangeNumber != Meas_rang[loop1])
                        continue;

                    errorcode = Cal_STS.Get_Meas_Power_Rawdata(item, ref powerdata);

                    if (errorcode != 0)
                    {
                        Show_STS_Error(errorcode);
                        return;
                    }

                    lstpower.Add(powerdata.ToArray());
                }
                //----get raw monitor data same range
                foreach (STSMonitorStruct monitoritem in Meas_monitor_struct)
                {
                    if (monitoritem.SweepCount == loop1 + 1)
                        errorcode = Cal_STS.Get_Meas_Monitor_Rawdata(monitoritem, ref monitordata);
                    else
                        continue;

                }

                // --File save at same range data 
                switch (loop1)
                {
                    case 0:
                        {
                            SaveFileDialog1.Title = "1st Range data";
                            break;
                        }

                    case 1:
                        {
                            SaveFileDialog1.Title = "2nd Range data";
                            break;
                        }

                    default:
                        {
                            SaveFileDialog1.Title = System.Convert.ToString(loop1 + 1) + "rd Range data";
                            break;
                        }
                }

                SaveFileDialog1.Filter = "csv file(*.csv)|*.csv";
                SaveFileDialog1.ShowDialog();
                fpath = SaveFileDialog1.FileName;

                writer = new System.IO.StreamWriter(fpath, false, System.Text.Encoding.GetEncoding("UTF-8"));

                hedder = "wavelength";

                foreach (STSDataStruct item in Data_struct)
                {
                    if (item.RangeNumber != Meas_rang[loop1])
                        continue;

                    hedder = hedder + "," + "mpm" + System.Convert.ToString(item.MPMNumber) + "Slot" + System.Convert.ToString(item.SlotNumber) + "Ch" + System.Convert.ToString(item.ChannelNumber);
                }
                 
                hedder = hedder + "," + "Monitordata";

                writer.WriteLine(hedder);

                for (loop2 = 0; loop2 <= wavelength_table.GetUpperBound(0); loop2++)
                {
                    write_string = System.Convert.ToString(wavelength_table[loop2]);

                    for (loop3 = 0; loop3 <= lstpower.Count - 1; loop3++)
                        write_string = write_string + "," + lstpower[loop3][loop2];

                    write_string = write_string + "," + monitordata[loop2];


                    writer.WriteLine(write_string);
                }

                writer.Close();
                lstpower = new List<float[]>();
                monitordata = null;
            }

            MessageBox.Show("Completed.", "", MessageBoxButtons.OK);
        }
    }
}
