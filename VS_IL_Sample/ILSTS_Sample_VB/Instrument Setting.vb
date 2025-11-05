Public Class Instrument_Setting

    Public SPU_Resource() As String                 'SPU resource name array
    Public USB_Resource() As String                 'USB resource name array

    Public TSL_Communicater As String               'TSL Communicator name
    Public MPM_Communicater As String               'MPM Communicator name

    Public TSL_Address As String                    'TSL address
    Public TSL_Portnumber As Integer                'TSL LAN port number

    Public MPM_Count As Integer                     'MPM number of device 
    Public MPM_Address(1) As String                 'MPM address 
    Public MPM_Portnumber(1) As Integer             'MPM LAN port number

    Public SPU_DeviveID As String                   'SPU Deviece resource
    Private Sub Instrument_Seting_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        '---------------------------------------------------------------
        '       Sub Form Load
        '---------------------------------------------------------------
        Dim loop1 As Integer

        '---Add in SPU resource to comboboxfrom main form
        For loop1 = 0 To UBound(SPU_Resource)
            Me.cmbspu_dev.Items.Add(SPU_Resource(loop1))
        Next

        '----Add in USB resource to combobox from main form
        For loop1 = 0 To UBound(USB_Resource)
            Me.cmbtsl_usb.Items.Add(USB_Resource(loop1))
        Next

    End Sub

    Private Sub rdo570_CheckedChanged(sender As Object, e As EventArgs) Handles rdo570.CheckedChanged
        '-----------------------------------------------------
        '       570 Checked
        '       
        '-----------------------------------------------------

        If Me.rdo570.Checked = True Then
            'TSL-570
            Me.rdo_tsltcpip.Enabled = True
            Me.rdo_tslusb.Enabled = True
        Else
            'TSL-550/710
            ' There can control only GPIB
            Me.rdo_tslusb.Enabled = False
            Me.rdo_tsltcpip.Enabled = False
            Me.rdotsl_gpib.Checked = True
        End If


    End Sub

    Private Sub rdotsl_gpib_CheckedChanged(sender As Object, e As EventArgs) Handles rdotsl_gpib.CheckedChanged
        '------------------------------------------------------
        '       TSL Control GPIB
        '------------------------------------------------------

        If Me.rdotsl_gpib.Checked = True Then
            Me.txttsl_gpibadd.Enabled = True
            Me.txttsl_ipadd.Enabled = False
            Me.txttsl_lanport.Enabled = False
            Me.cmbtsl_usb.Enabled = False

        End If

    End Sub

    Private Sub rdo_tsltcpip_CheckedChanged(sender As Object, e As EventArgs) Handles rdo_tsltcpip.CheckedChanged
        '------------------------------------------------------
        '       TSL Control TCP/IP
        '------------------------------------------------------

        If Me.rdo_tsltcpip.Checked = True Then
            Me.txttsl_gpibadd.Enabled = False
            Me.txttsl_ipadd.Enabled = True
            Me.txttsl_lanport.Enabled = True
            Me.cmbtsl_usb.Enabled = False

        End If

    End Sub

    Private Sub rdo_tslusb_CheckedChanged(sender As Object, e As EventArgs) Handles rdo_tslusb.CheckedChanged
        '------------------------------------------------------
        '       TSL Control USB
        '------------------------------------------------------

        If Me.rdo_tslusb.Checked = True Then
            Me.txttsl_gpibadd.Enabled = False
            Me.txttsl_ipadd.Enabled = False
            Me.txttsl_lanport.Enabled = False
            Me.cmbtsl_usb.Enabled = True

        End If

    End Sub

    Private Sub btnconnect_Click(sender As Object, e As EventArgs) Handles btnconnect.Click
        '----------------------------------------------------------
        '           Connect       
        '----------------------------------------------------------


        ' ----TSL Communication diteal

        'GPIB Communcation?
        If Me.rdotsl_gpib.Checked = True Then

            TSL_Communicater = "GPIB"
            TSL_Address = Me.txttsl_gpibadd.Text
            TSL_Portnumber = 0
        End If

        'TCP/IP Communciation?
        If Me.rdo_tsltcpip.Checked = True Then
            TSL_Communicater = "LAN"
            TSL_Address = Me.txttsl_ipadd.Text
            TSL_Portnumber = Me.txttsl_lanport.Text
        End If

        'USB Communcation?
        If Me.rdo_tslusb.Checked = True Then
            TSL_Communicater = "USB"
            TSL_Address = Me.cmbtsl_usb.SelectedIndex
            TSL_Portnumber = 0
        End If

        '-----MPM Communcation diteal

        'Multi Device?
        If Me.chkmulti_dev.Checked = True Then
            MPM_Count = 2

            'GPIB communcation?
            If Me.rdo_mpmgpib.Checked = True Then
                MPM_Address(0) = Me.txtmpm_gpibadd1.Text
                MPM_Address(1) = Me.txtmpm_gpibadd2.Text
                MPM_Portnumber(0) = 0
                MPM_Portnumber(1) = 0

                MPM_Communicater = "GPIB"
            Else
                ' TCL/IP communcation?
                MPM_Address(0) = Me.txtmpm_ipadd1.Text
                MPM_Address(1) = Me.txtmpm_ipadd2.Text
                MPM_Portnumber(0) = Me.txtmpm_lanport1.Text
                MPM_Portnumber(1) = Me.txtmpm_lanport2.Text

                MPM_Communicater = "LAN"
            End If
        Else

            MPM_Count = 1

            'GPIB communcation?
            If Me.rdo_mpmgpib.Checked = True Then
                MPM_Address(0) = Me.txtmpm_gpibadd1.Text
                MPM_Address(1) = ""
                MPM_Portnumber(0) = 0
                MPM_Portnumber(1) = 0

                MPM_Communicater = "GPIB"
            Else
                ' TCL/IP communcation?
                MPM_Address(0) = Me.txtmpm_ipadd1.Text
                MPM_Address(1) = ""
                MPM_Portnumber(0) = Me.txtmpm_lanport1.Text
                MPM_Portnumber(1) = 0

                MPM_Communicater = "LAN"
            End If
        End If


        ' SPU Resouce

        If Me.cmbspu_dev.Text = "" Then

            MsgBox("Please enter to the SPU device resouce", vbOKOnly)
            Exit Sub

        End If

        SPU_DeviveID = Me.cmbspu_dev.Text


        Me.Dispose()

    End Sub

    Private Sub chkmulti_dev_CheckedChanged(sender As Object, e As EventArgs) Handles chkmulti_dev.CheckedChanged
        '------------------------------------------------------------------
        '           Selecet MPM Multi-Device
        '-------------------------------------------------------------------

        Me.grp_mpmdev2.Enabled = Me.chkmulti_dev.Checked

    End Sub

    Private Sub rdo_mpmgpib_CheckedChanged(sender As Object, e As EventArgs) Handles rdo_mpmgpib.CheckedChanged
        '--------------------------------------------------------------------
        '           MPM Control GPIB
        '--------------------------------------------------------------------

        If Me.rdo_mpmgpib.Checked = True Then
            Me.txtmpm_gpibadd1.Enabled = True
            Me.txtmpm_gpibadd2.Enabled = True
            Me.txtmpm_ipadd1.Enabled = False
            Me.txtmpm_ipadd2.Enabled = False
            Me.txtmpm_lanport1.Enabled = False
            Me.txtmpm_lanport2.Enabled = False
        Else
            Me.txtmpm_gpibadd1.Enabled = False
            Me.txtmpm_gpibadd2.Enabled = False
            Me.txtmpm_ipadd1.Enabled = True
            Me.txtmpm_ipadd2.Enabled = True
            Me.txtmpm_lanport1.Enabled = True
            Me.txtmpm_lanport2.Enabled = True

        End If

    End Sub
End Class