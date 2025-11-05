
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ILSTS_Sample
{
    public partial class Instrument_Setting : Form
    {
        public Instrument_Setting()
        {
            InitializeComponent();
        }
        public string[] SPU_Resource;                 // SPU resource name array
        public string[] USB_Resource;                 // USB resource name array

        public string TSL_Communicater;               // TSL Communicator name
        public string MPM_Communicater;               // MPM Communicator name

        public string TSL_Address;                    // TSL address
        public int TSL_Portnumber;                // TSL LAN port number

        public int MPM_Count;                     // MPM number of device 
        public string[] MPM_Address = new string[2];                 // MPM address 
        public int[] MPM_Portnumber = new int[2];             // MPM LAN port number

        public string SPU_DeviveID;                   // SPU Deviece resource
        private void btnconnect_Click(object sender, EventArgs e)
        {
            // ----------------------------------------------------------
            // Connect       
            // ----------------------------------------------------------


            // ----TSL Communication diteal

            // GPIB Communcation?
            if (rdotsl_gpib.Checked == true)
            {
                TSL_Communicater = "GPIB";
                TSL_Address = txttsl_gpibadd.Text;
                TSL_Portnumber = 0;
            }

            // TCP/IP Communciation?
            if (rdo_tsltcpip.Checked == true)
            {
                TSL_Communicater = "LAN";
                TSL_Address = txttsl_ipadd.Text;
                TSL_Portnumber = int.Parse(txttsl_lanport.Text);
            }

            // USB Communcation?
            if (rdo_tslusb.Checked == true)
            {
                TSL_Communicater = "USB";
                TSL_Address = cmbtsl_usb.SelectedIndex.ToString();
                TSL_Portnumber = 0;
            }

            // -----MPM Communcation diteal

            // Multi Device?
            if (chkmulti_dev.Checked == true)
            {
                MPM_Count = 2;

                // GPIB communcation?
                if (rdo_mpmgpib.Checked == true)
                {
                    MPM_Address[0] = txtmpm_gpibadd1.Text;
                    MPM_Address[1] = txtmpm_gpibadd2.Text;
                    MPM_Portnumber[0] = 0;
                    MPM_Portnumber[1] = 0;

                    MPM_Communicater = "GPIB";
                }
                else
                {
                    // TCL/IP communcation?
                    MPM_Address[0] = txtmpm_ipadd1.Text;
                    MPM_Address[1] = txtmpm_ipadd2.Text;
                    MPM_Portnumber[0] = int.Parse(txtmpm_lanport1.Text);
                    MPM_Portnumber[1] = int.Parse(txtmpm_lanport2.Text);

                    MPM_Communicater = "LAN";
                }
            }
            else
            {
                MPM_Count = 1;

                // GPIB communcation?
                if (rdo_mpmgpib.Checked == true)
                {
                    MPM_Address[0] = txtmpm_gpibadd1.Text;
                    MPM_Address[1] = "";
                    MPM_Portnumber[0]= 0;
                    MPM_Portnumber[1] = 0;

                    MPM_Communicater = "GPIB";
                }
                else
                {
                    // TCL/IP communcation?
                    MPM_Address[0] = txtmpm_ipadd1.Text;
                    MPM_Address[1] = "";
                    MPM_Portnumber[0] = int.Parse(txtmpm_lanport1.Text);
                    MPM_Portnumber[1] = 0;

                    MPM_Communicater = "LAN";
                }
            }


            // SPU Resouce

            if (cmbspu_dev.Text == "")
            {
                MessageBox.Show("","Please enter to the SPU device resouce", MessageBoxButtons.OK);
                return;
            }

            SPU_DeviveID = cmbspu_dev.Text;


            Dispose();
        }

        private void Instrument_Setting_Load(object sender, EventArgs e)
        {
            // ---------------------------------------------------------------
            // Sub Form Load
            // ---------------------------------------------------------------
            int loop1;

            // ---Add in SPU resource to comboboxfrom main form
            for (loop1 = 0; loop1 <= SPU_Resource.GetUpperBound(0); loop1++)
                cmbspu_dev.Items.Add(SPU_Resource[loop1]);

            // ----Add in USB resource to combobox from main form
            for (loop1 = 0; loop1 <= USB_Resource.GetUpperBound(0); loop1++)
                cmbtsl_usb.Items.Add(USB_Resource[loop1]);
        }

        private void rdo570_CheckedChanged(object sender, EventArgs e)
        {
            // -----------------------------------------------------
            // 570 Checked
            // -----------------------------------------------------

            if (rdo570.Checked == true)
            {
                // TSL-570
                rdo_tsltcpip.Enabled = true;
                rdo_tslusb.Enabled = true;
            }
            else
            {
                // TSL-550/710
                // There can control only GPIB
                rdo_tslusb.Enabled = false;
                rdo_tsltcpip.Enabled = false;
                rdotsl_gpib.Checked = true;
            }
        }

        private void rdotsl_gpib_CheckedChanged(object sender, EventArgs e)
        {
            // ------------------------------------------------------
            // TSL Control GPIB
            // ------------------------------------------------------

            if (rdotsl_gpib.Checked == true)
            {
                txttsl_gpibadd.Enabled = true;
                txttsl_ipadd.Enabled = false;
                txttsl_lanport.Enabled = false;
                cmbtsl_usb.Enabled = false;
            }
        }

        private void rdo_tsltcpip_CheckedChanged(object sender, EventArgs e)
        {
            // ------------------------------------------------------
            // TSL Control TCP/IP
            // ------------------------------------------------------

            if (rdo_tsltcpip.Checked == true)
            {
                txttsl_gpibadd.Enabled = false;
                txttsl_ipadd.Enabled = true;
                txttsl_lanport.Enabled = true;
                cmbtsl_usb.Enabled = false;
            }
        }

        private void rdo_tslusb_CheckedChanged(object sender, EventArgs e)
        {
            // ------------------------------------------------------
            // TSL Control USB
            // ------------------------------------------------------

            if (rdo_tslusb.Checked == true)
            {
                txttsl_gpibadd.Enabled = false;
                txttsl_ipadd.Enabled = false;
                txttsl_lanport.Enabled = false;
                cmbtsl_usb.Enabled = true;
            }
        }

        private void chkmulti_dev_CheckedChanged(object sender, EventArgs e)
        {
            // ------------------------------------------------------------------
            // Selecet MPM Multi-Device
            // -------------------------------------------------------------------

            grp_mpmdev2.Enabled = chkmulti_dev.Checked;
        }

        private void rdo_mpmgpib_CheckedChanged(object sender, EventArgs e)
        {
            // --------------------------------------------------------------------
            // MPM Control GPIB
            // --------------------------------------------------------------------

            if (rdo_mpmgpib.Checked == true)
            {
                txtmpm_gpibadd1.Enabled = true;
                txtmpm_gpibadd2.Enabled = true;
                txtmpm_ipadd1.Enabled = false;
                txtmpm_ipadd2.Enabled = false;
                txtmpm_lanport1.Enabled = false;
                txtmpm_lanport2.Enabled = false;
            }
            else
            {
                txtmpm_gpibadd1.Enabled = false;
                txtmpm_gpibadd2.Enabled = false;
                txtmpm_ipadd1.Enabled = true;
                txtmpm_ipadd2.Enabled = true;
                txtmpm_lanport1.Enabled = true;
                txtmpm_lanport2.Enabled = true;
            }
        }
    }
}
