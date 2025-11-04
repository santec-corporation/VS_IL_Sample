Imports Santec
Imports Santec.STSProcess
Public Class Form1
    Private TSL As New TSL                                              'TSL control class
    Private MPM() As MPM                                                'MPM control class
    Private SPU As New SPU                                              'SPU control class
    Private Cal_STS As New ILSTS                                        'STS calucrate class
    Private Data_struct As New List(Of STSDataStruct)                   'STS data Struct 
    Private Refdata_struct As New List(Of STSDataStruct)                'Reference data Struct
    Private Meas_monitor_struct As New List(Of STSMonitorStruct)           'Measurement monitor data struct
    Private Ref_monitordata_struct As New List(Of STSDataStruct)        'STS Monitor data Struct for Reference
    Private Mergedata_struct As New List(Of STSDataStructForMerge)      'Data struct for merge  
    Private Meas_rang As New List(Of Integer)                           'Measurement Range 
    Private Flag_213 As Boolean                                         'Exist 213 flag      T: Exist F: nothing
    Private Flag_215 As Boolean                                         'Exist 215 flag      T: Exist F: nothing 

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        '-------------------------------------------------------------------------
        '       Form Load    (MainForm)
        '-------------------------------------------------------------------------
        Dim spudev() As String = Nothing                        'SPU device name
        Dim errorcode As Integer                                'errorcode 
        Dim usb_resource() As String = Nothing                  'usb communication resource



        '----Check Connction of spu deviece
        errorcode = SPU.Get_Device_ID(spudev)

        If errorcode <> 0 Then
            Show_Inst_Error(errorcode)
            End
        End If


        '----Check usb resource
        usb_resource = Communication.MainCommunication.Get_USB_Resouce()


        '------show Setting Form
        Dim set_form As New Instrument_Setting

        set_form.Owner = Me
        set_form.SPU_Resource = spudev
        set_form.USB_Resource = usb_resource
        set_form.ShowDialog()

        '---Apply to communication parametere from Instrument setting form
        Dim tsl_communcation_method As Communication.CommunicationMethod
        Dim mpm_communcation_method As Communication.CommunicationMethod


        '----TSL　Communication method
        If set_form.TSL_Communicater = "GPIB" Then

            tsl_communcation_method = Communication.CommunicationMethod.GPIB
            TSL.Terminator = CommunicationTerminator.CrLf
            TSL.GPIBAddress = set_form.TSL_Address
            TSL.GPIBBoard = 0
            TSL.GPIBConnectType = Communication.GPIBConnectType.NI4882


        ElseIf set_form.TSL_Communicater = "LAN" Then

            tsl_communcation_method = Communication.CommunicationMethod.TCPIP
            TSL.Terminator = CommunicationTerminator.Cr
            TSL.IPAddress = set_form.TSL_Address
            TSL.Port = set_form.TSL_Portnumber
        Else
            'USB 
            tsl_communcation_method = Communication.CommunicationMethod.USB
            TSL.DeviceID = CInt(set_form.TSL_Address)
            TSL.Terminator = CommunicationTerminator.Cr
        End If


        '---MPM Communicatipon method
        Dim loop1 As Integer
        Dim mpmcount As Integer                     'MPM count


        If set_form.MPM_Communicater = "GPIB" Then
            mpm_communcation_method = Communication.CommunicationMethod.GPIB
        Else
            mpm_communcation_method = Communication.CommunicationMethod.TCPIP
        End If

        mpmcount = set_form.MPM_Count
        ReDim MPM(mpmcount - 1)

        For loop1 = 0 To mpmcount - 1

            MPM(loop1) = New MPM

            If set_form.MPM_Communicater = "GPIB" Then
                MPM(loop1).GPIBAddress = set_form.MPM_Address(loop1)
            Else
                MPM(loop1).IPAddress = set_form.MPM_Address(loop1)
                MPM(loop1).Port = set_form.MPM_Portnumber(loop1)
            End If

            '-------------------------------------------------------------------------
            '  MPM muximum logging data read time is 11s
            '  communication time out must to set > mpm logging data read time.
            '--------------------------------------------------------------------------
            MPM(loop1).TimeOut = 11000

        Next

        '----SPU Communcation Setting 
        SPU.DeviceName = set_form.SPU_DeviveID


        '-----------Connect------------------------------------------------- 
        'TSL
        errorcode = TSL.Connect(tsl_communcation_method)

        If errorcode <> 0 Then
            MsgBox("TSL can't connect.Please check connection.", vbOKOnly)
            End
        End If

        'MPM
        For loop1 = 0 To UBound(MPM)
            errorcode = MPM(loop1).Connect(mpm_communcation_method)

            If errorcode <> 0 Then
                MsgBox("MPM can't connect.Please check connection.", vbOKOnly)
                End
            End If
        Next

        'SPU(DAQ)
        Dim ans As String = String.Empty
        errorcode = SPU.Connect(ans)

        If errorcode <> 0 Then
            MsgBox("SPU Can't connect. Please check connection.", vbOKOnly)
            End
        End If


        '------------Check MPM Module information
        errorcode = Check_Module_Information()

        If errorcode <> 0 Then
            MsgBox("System can't use MPM-215 togeter other module", vbOKOnly)
            End
        End If

        '-----------Reflect instrument parameter to Form
        Referect_EnableCh_for_form()                'MPM Eanble ch
        Referect_EnableRange_for_form()             'MPM selectable range
        Add_TSL_Sweep_Speed()                       'TSL Sweep speed(only TSL-570)

    End Sub
    Private Function Add_TSL_Sweep_Speed() As Integer
        '---------------------------------------------------------
        '       Add in selectable sweep speed to speed combbox
        '       this function can use only TSL-570
        '----------------------------------------------------------
        Dim inst_error As Integer                       'instullment error
        Dim sweep_table() As Double = Nothing           'table


        ' Get Sweep speed tabele
        'Except for TSL-570 "Device Error" occurre when call this function.
        inst_error = TSL.Get_Sweep_Speed_table(sweep_table)

        If inst_error <> 0 And inst_error <> CInt(ExceptionCode.DeviceError) Then
            Return inst_error
        End If


        '-----Add in combbox when TSL-570
        Dim loop1 As Integer

        If inst_error <> CInt(ExceptionCode.DeviceError) Then

            For loop1 = 0 To UBound(sweep_table)

                Me.cmbspeed.Items.Add(sweep_table(loop1))
            Next
        End If
        Return 0

    End Function

    Private Function Check_Module_Information() As Integer
        '------------------------------------------------------------
        '       check Module information inside system
        '------------------------------------------------------------
        Dim loop1 As Integer
        Dim loop2 As Integer
        Dim counter_215 As Integer                           '215 counter 

        'MPM device loop
        For loop1 = 0 To UBound(MPM)
            'Slot loop
            For loop2 = 0 To 4
                'Enable Slot
                If MPM(loop1).Information.ModuleEnable(loop2) = True Then

                    'Check MPM-215 insert
                    If MPM(loop1).Information.ModuleType(loop2) = "MPM-215" Then
                        Flag_215 = True
                        counter_215 = counter_215 + 1
                    End If

                    'Check MPM-213 insert
                    If MPM(loop1).Information.ModuleType(loop2) = "MPM-213" Then
                        Flag_213 = True
                    End If

                End If
            Next

        Next


        'Check MPM-215 count & Module total count
        'STS system can't use 215 together other module.
        Dim enable_module_count As Integer                      'enable module count

        For loop1 = 0 To UBound(MPM)
            enable_module_count = MPM(loop1).Information.NumberofModule + enable_module_count       'total module count
        Next

        If Flag_215 = True Then
            If enable_module_count <> counter_215 Then
                Return -1
            End If
        End If



        Return 0

    End Function
    Private Sub Referect_EnableCh_for_form()
        '------------------------------------------------
        '       Reflect mpm ch 
        '------------------------------------------------
        Dim loop1 As Integer
        Dim loop2 As Integer
        Dim enable_slot() As Boolean
        Dim slot_type As String

        For loop1 = 0 To UBound(MPM)
            'get insert module count with "MPM Information" class 
            enable_slot = MPM(loop1).Information.ModuleEnable

            'modeule loop(Maximum 5 slot)
            For loop2 = 0 To 4
                If enable_slot(loop2) = True Then
                    'get module type with "MPM Information" class 
                    slot_type = MPM(loop1).Information.ModuleType(loop2)

                    If slot_type <> "MPM-212" Then
                        Me.chklst_ch.Items.Add("MPM" & CStr(loop1 + 1) & " Slot" & CStr(loop2) & " Ch1")
                        Me.chklst_ch.Items.Add("MPM" & CStr(loop1 + 1) & " Slot" & CStr(loop2) & " Ch2")
                        Me.chklst_ch.Items.Add("MPM" & CStr(loop1 + 1) & " Slot" & CStr(loop2) & " Ch3")
                        Me.chklst_ch.Items.Add("MPM" & CStr(loop1 + 1) & " Slot" & CStr(loop2) & " Ch4")
                    Else
                        Me.chklst_ch.Items.Add("MPM" & CStr(loop1 + 1) & " Slot" & CStr(loop2) & " Ch1")
                        Me.chklst_ch.Items.Add("MPM" & CStr(loop1 + 1) & " Slot" & CStr(loop2) & " Ch2")
                    End If

                End If
            Next
        Next
    End Sub
    Private Sub Referect_EnableRange_for_form()
        '-----------------------------------------------------
        '       Refelect MPM Range
        '-------------------------------------------------------


        ' MPM-213 can use just 1 to 4 range
        If Flag_213 = True Then
            Me.chklst_range.Items.Add("Range1")
            Me.chklst_range.Items.Add("Range2")
            Me.chklst_range.Items.Add("Range3")
            Me.chklst_range.Items.Add("Range4")
        Else
            Me.chklst_range.Items.Add("Range1")
            Me.chklst_range.Items.Add("Range2")
            Me.chklst_range.Items.Add("Range3")
            Me.chklst_range.Items.Add("Range4")
            Me.chklst_range.Items.Add("Range5")
        End If

        ' MPM-215 can't select range
        If Flag_215 = True Then
            Me.chklst_range.Enabled = False
        End If

    End Sub

    Private Sub btnset_Click(sender As Object, e As EventArgs) Handles btnset.Click
        '-------------------------------------------------------------------------
        '           Set Parameter
        '--------------------------------------------------------------------------
        Dim startwave As Double             'Startwavelength(nm)
        Dim stopwave As Double              'Stopwavelength(nm)
        Dim set_pow As Double               'Power(dBm)
        Dim wavestep As Double              'wavelenthg step(nm)
        Dim speed As Double                 'Sweep Speed (nm/sec)
        Dim inst_error As Integer           'instullment error


        startwave = Me.txtstartwave.Text
        stopwave = Me.txtstopwave.Text
        wavestep = Me.txtstepwave.Text
        speed = Me.cmbspeed.Text
        set_pow = Me.txtpower.Text

        '------------TSL Setting--------------------------------------------------- 
        ' set Power
        inst_error = TSL.Set_APC_Power_dBm(set_pow)
        If inst_error <> 0 Then
            Show_Inst_Error(inst_error)
            Exit Sub
        End If

        'busy check
        inst_error = TSL.TSL_Busy_Check(3000)
        If inst_error <> 0 Then
            Show_Inst_Error(inst_error)
            Exit Sub
        End If

        Dim tsl_acctualstep As Double          ' TSL output trigger step(nm)

        'set Sweep parameter
        inst_error = TSL.Set_Sweep_Parameter_for_STS(startwave, stopwave, speed, wavestep, tsl_acctualstep)
        If inst_error <> 0 Then
            Show_Inst_Error(inst_error)
            Exit Sub
        End If

        'wavelength -> start wavelength
        inst_error = TSL.Set_Wavelength(startwave)
        If inst_error <> 0 Then
            Show_Inst_Error(inst_error)
            Exit Sub
        End If

        'busy check
        inst_error = TSL.TSL_Busy_Check(3000)
        If inst_error <> 0 Then
            Show_Inst_Error(inst_error)
            Exit Sub
        End If


        '----------MPM setting ---------------------------------------------------
        Dim loop1 As Integer

        For loop1 = 0 To UBound(MPM)
            'Sweep parameter setting 
            inst_error = MPM(loop1).Set_Logging_Paremeter_for_STS(startwave, stopwave, wavestep, speed, Santec.MPM.Measurement_Mode.Freerun)
            If inst_error <> 0 Then
                Show_Inst_Error(inst_error)
                Exit Sub
            End If
            inst_error = MPM(loop1).Set_Wavelength((startwave + stopwave) / 2)
            If inst_error <> 0 Then
                Show_Inst_Error(inst_error)
                Exit Sub
            End If

        Next

        '---------SPU setting------------------------------------------------------ 
        Dim averaging_time As Double

        inst_error = MPM(0).Get_Averaging_Time(averaging_time)

        If inst_error <> 0 Then
            Show_Inst_Error(inst_error)
            Exit Sub
        End If

        'parameter setting 
        inst_error = SPU.Set_Sampling_Parameter(startwave, stopwave, speed, tsl_acctualstep)

        If inst_error <> 0 Then
            Show_Inst_Error(inst_error)
            Exit Sub
        End If

        'mpm averageing time-> spu
        SPU.AveragingTime = averaging_time


        '-------------set STS Process parameter-----------------------------------

        Dim sts_error As Integer            'sts process class error

        'data Clear 
        sts_error = Cal_STS.Clear_Measdata()

        If sts_error <> 0 Then
            Show_STS_Error(sts_error)
            Exit Sub
        End If

        sts_error = Cal_STS.Clear_Refdata

        If sts_error <> 0 Then
            Show_STS_Error(sts_error)
            Exit Sub
        End If

        'Setting for STS rescaling mode
        sts_error = Cal_STS.Set_Rescaling_Setting(RescalingMode.Freerun_SPU, averaging_time, True)

        If sts_error <> 0 Then
            Show_STS_Error(sts_error)
            Exit Sub
        End If

        'Make acctual wavelength step table
        sts_error = Cal_STS.Make_Sweep_Wavelength_Table(startwave, stopwave, tsl_acctualstep)

        If sts_error <> 0 Then
            Show_STS_Error(sts_error)
            Exit Sub
        End If

        'Make rescaling wavelength step table
        sts_error = Cal_STS.Make_Target_Wavelength_Table(startwave, stopwave, wavestep)

        If sts_error <> 0 Then
            Show_STS_Error(sts_error)
            Exit Sub
        End If

        '----prepare data struct & hold instrument condition
        If Me.chkeach_ch.Checked Then
            Prepare_dataST_Each()
        Else
            Prepare_dataST()
        End If

        MsgBox("Completed.", vbOKOnly)
    End Sub

    Private Sub Prepare_dataST()
        '-----------------------------------------------
        '       Prepar STS data struct
        '-----------------------------------------------
        Dim rangecout As Integer                        'number of range
        Dim chcount As Integer                          'number of ch 
        Dim loop1 As Integer                            'loop count1
        Dim loop2 As Integer                            'loop count2
        Dim text_st As String = String.Empty            'text String 
        Dim split_st() As String = Nothing              'split string array

        'List clear 
        Meas_rang.Clear()                               'Measurement Range
        Data_struct.Clear()                             'DataSturct of STS
        Refdata_struct.Clear()                          'Reference data struct
        Ref_monitordata_struct.Clear()                  'Reference monitor data struct
        Meas_monitor_struct.Clear()                     'Measurement monitor data struct



        Mergedata_struct.Clear()                        'DataStruct of Merge 

        rangecout = Me.chklst_range.CheckedItems.Count
        chcount = Me.chklst_ch.CheckedItems.Count

        If Flag_215 = True Then
            'If mom215 range must be set 1
            Meas_rang.Add(1)
        Else
            If rangecout = 0 Or chcount = 0 Then
                MsgBox("Please check measurement parameters.", vbOKOnly)
                Exit Sub
            End If


            'hold range data 
            For loop1 = 0 To Me.chklst_range.Items.Count - 1
                If Me.chklst_range.GetItemChecked(loop1) = True Then
                    Meas_rang.Add(loop1 + 1)
                End If
            Next
        End If
        Dim device_number As Integer
        Dim slot_number As Integer
        Dim ch_number As Integer
        Dim set_struct As STSDataStruct
        Dim set_struct_merge As STSDataStructForMerge
        Dim sweep_count As Integer                          'Sweep count 

        '--for measurement MPM data
        For loop2 = 0 To Meas_rang.Count - 1
            For loop1 = 0 To Me.chklst_ch.Items.Count - 1

                If Me.chklst_ch.GetItemChecked(loop1) = True Then
                    text_st = Me.chklst_ch.Items(loop1)
                    split_st = Split(text_st, " ")
                    'ch parameter
                    device_number = CInt(split_st(0).Substring(3))
                    slot_number = CInt(split_st(1).Substring(4))
                    ch_number = CInt(split_st(2).Substring(2))
                    'for data
                    set_struct.MPMNumber = device_number
                    set_struct.SlotNumber = slot_number
                    set_struct.ChannelNumber = ch_number
                    set_struct.RangeNumber = Meas_rang(loop2)
                    set_struct.SweepCount = loop2 + 1
                    set_struct.SOP = 0
                    Data_struct.Add(set_struct)
                End If

            Next
        Next

        '---for merasurement Monitor data
        ' monitor data need each sweep times data
        Dim set_monitor_struct As STSMonitorStruct              'set struct for monitor
        For loop2 = 0 To Meas_rang.Count - 1
            For loop1 = 0 To Me.chklst_ch.Items.Count - 1

                If Me.chklst_ch.GetItemChecked(loop1) = True Then
                    text_st = Me.chklst_ch.Items(loop1)
                    split_st = Split(text_st, " ")
                    'ch parameter
                    device_number = CInt(split_st(0).Substring(3))

                    set_monitor_struct.MPMNumber = device_number
                    set_monitor_struct.SOP = 0
                    set_monitor_struct.SweepCount = loop2 + 1

                    Meas_monitor_struct.Add(set_monitor_struct)
                    If Meas_monitor_struct.Count = loop2 + 1 Then
                        Exit For
                    End If
                End If
            Next
        Next

        '---for　reference MPM data & merge data
        '   reference data need only 1 range data
        For loop1 = 0 To Me.chklst_ch.Items.Count - 1

            If Me.chklst_ch.GetItemChecked(loop1) = True Then
                text_st = Me.chklst_ch.Items(loop1)
                split_st = Split(text_st, " ")
                'ch parameter
                device_number = CInt(split_st(0).Substring(3))
                slot_number = CInt(split_st(1).Substring(4))
                ch_number = CInt(split_st(2).Substring(2))

                'for reference data
                set_struct.MPMNumber = device_number
                set_struct.SlotNumber = slot_number
                set_struct.ChannelNumber = ch_number
                set_struct.RangeNumber = 1
                set_struct.SweepCount = 1
                set_struct.SOP = 0

                Refdata_struct.Add(set_struct)

                'for mege
                set_struct_merge.MPMNumber = device_number
                set_struct_merge.SlotNumber = slot_number
                set_struct_merge.ChannelNumber = ch_number
                set_struct_merge.SOP = 0
                Mergedata_struct.Add(set_struct_merge)

            End If
        Next

        '----for referece Monitor data 
        Dim set_ref_monitor_struct = New STSDataStruct
        For loop1 = 0 To Me.chklst_ch.Items.Count - 1

            If Me.chklst_ch.GetItemChecked(loop1) = True Then
                text_st = Me.chklst_ch.Items(loop1)
                split_st = Split(text_st, " ")
                'Mainframe parameter
                device_number = CInt(split_st(0).Substring(3))
                slot_number = CInt(split_st(1).Substring(4))
                ch_number = CInt(split_st(2).Substring(2))

                ' for reference monitor data
                set_ref_monitor_struct.MPMNumber = device_number
                set_ref_monitor_struct.SlotNumber = slot_number
                set_ref_monitor_struct.ChannelNumber = ch_number
                set_ref_monitor_struct.RangeNumber = 1
                set_ref_monitor_struct.SOP = 0
                set_ref_monitor_struct.SweepCount = 1

                Ref_monitordata_struct.Add(set_ref_monitor_struct)
                Exit For
            End If
        Next


    End Sub
    Private Sub Prepare_dataST_Each()
        '-----------------------------------------------
        '       Prepar STS data struct
        '-----------------------------------------------
        Dim rangecout As Integer                        'number of range
        Dim chcount As Integer                          'number of ch 
        Dim loop1 As Integer                            'loop count1
        Dim loop2 As Integer                            'loop count2
        Dim text_st As String = String.Empty            'text String 
        Dim split_st() As String = Nothing              'split string array

        'List clear 
        Meas_rang.Clear()                               'Measurement Range
        Data_struct.Clear()                             'DataSturct of STS
        Refdata_struct.Clear()                          'Reference data struct
        Ref_monitordata_struct.Clear()                  'Reference monitor data struct
        Meas_monitor_struct.Clear()                     'Measurement monitor data struct



        Mergedata_struct.Clear()                        'DataStruct of Merge 

        rangecout = Me.chklst_range.CheckedItems.Count
        chcount = Me.chklst_ch.CheckedItems.Count

        If Flag_215 = True Then
            'If mom215 range must be set 1
            Meas_rang.Add(1)
        Else
            If rangecout = 0 Or chcount = 0 Then
                MsgBox("Please check measurement parameters.", vbOKOnly)
                Exit Sub
            End If


            'hold range data 
            For loop1 = 0 To Me.chklst_range.Items.Count - 1
                If Me.chklst_range.GetItemChecked(loop1) = True Then
                    Meas_rang.Add(loop1 + 1)
                End If
            Next
        End If
        Dim device_number As Integer
        Dim slot_number As Integer
        Dim ch_number As Integer
        Dim set_struct As STSDataStruct
        Dim set_struct_merge As STSDataStructForMerge
        Dim sweep_count As Integer                          'Sweep count 

        '--for measurement MPM data
        For loop2 = 0 To Meas_rang.Count - 1
            For loop1 = 0 To Me.chklst_ch.Items.Count - 1

                If Me.chklst_ch.GetItemChecked(loop1) = True Then
                    text_st = Me.chklst_ch.Items(loop1)
                    split_st = Split(text_st, " ")
                    'ch parameter
                    device_number = CInt(split_st(0).Substring(3))
                    slot_number = CInt(split_st(1).Substring(4))
                    ch_number = CInt(split_st(2).Substring(2))
                    'for data
                    set_struct.MPMNumber = device_number
                    set_struct.SlotNumber = slot_number
                    set_struct.ChannelNumber = ch_number
                    set_struct.RangeNumber = Meas_rang(loop2)
                    set_struct.SweepCount = loop2 + 1
                    set_struct.SOP = 0
                    Data_struct.Add(set_struct)
                End If

            Next
        Next

        '---for merasurement Monitor data
        ' monitor data need each sweep times data
        Dim set_monitor_struct As STSMonitorStruct              'set struct for monitor
        For loop2 = 0 To Meas_rang.Count - 1
            For loop1 = 0 To Me.chklst_ch.Items.Count - 1

                If Me.chklst_ch.GetItemChecked(loop1) = True Then
                    text_st = Me.chklst_ch.Items(loop1)
                    split_st = Split(text_st, " ")
                    'ch parameter
                    device_number = CInt(split_st(0).Substring(3))

                    set_monitor_struct.MPMNumber = device_number
                    set_monitor_struct.SOP = 0
                    set_monitor_struct.SweepCount = loop2 + 1

                    Meas_monitor_struct.Add(set_monitor_struct)
                    If Meas_monitor_struct.Count = loop2 + 1 Then
                        Exit For
                    End If
                End If
            Next
        Next

        '---for　reference MPM data & reference monitor data & merge data
        '   reference data need only 1 range data
        set_struct = New STSDataStruct
        Dim set_ref_monitor_struct As STSDataStruct
        For loop1 = 0 To Me.chklst_ch.Items.Count - 1

            If Me.chklst_ch.GetItemChecked(loop1) = True Then
                text_st = Me.chklst_ch.Items(loop1)
                split_st = Split(text_st, " ")
                'ch parameter
                device_number = CInt(split_st(0).Substring(3))
                slot_number = CInt(split_st(1).Substring(4))
                ch_number = CInt(split_st(2).Substring(2))

                'for reference data
                set_struct.MPMNumber = device_number
                set_struct.SlotNumber = slot_number
                set_struct.ChannelNumber = ch_number
                set_struct.RangeNumber = 1
                set_struct.SweepCount = 1
                set_struct.SOP = 0

                Refdata_struct.Add(set_struct)


                'for reference monitor data
                set_ref_monitor_struct.MPMNumber = device_number
                set_ref_monitor_struct.SlotNumber = slot_number
                set_ref_monitor_struct.ChannelNumber = ch_number
                set_ref_monitor_struct.RangeNumber = 1
                set_ref_monitor_struct.SweepCount = 1
                set_ref_monitor_struct.SOP = 0

                Ref_monitordata_struct.Add(set_ref_monitor_struct)

                'for mege
                set_struct_merge.MPMNumber = device_number
                set_struct_merge.SlotNumber = slot_number
                set_struct_merge.ChannelNumber = ch_number
                set_struct_merge.SOP = 0
                Mergedata_struct.Add(set_struct_merge)

            End If
        Next


    End Sub

    Private Sub Show_Inst_Error(ByVal errordata As Integer)
        '------------------------------------
        '       Show error code
        '------------------------------------


        Dim errorstring() As String = [Enum].GetNames(GetType(Santec.ExceptionCode))
        Dim errorvale() As Integer = [Enum].GetValues(GetType(Santec.ExceptionCode))
        Dim loop1 As Integer

        For loop1 = 0 To UBound(errorvale)

            If errorvale(loop1) = errordata Then
                MsgBox(errorstring(loop1))
                Exit For
            End If

        Next

    End Sub


    Private Sub Show_STS_Error(ByVal errordata As Integer)
        '------------------------------------
        '       Show error code for STS
        '------------------------------------


        Dim errorstring() As String = [Enum].GetNames(GetType(Santec.STSProcess.ErrorCode))
        Dim errorvale() As Integer = [Enum].GetValues(GetType(Santec.STSProcess.ErrorCode))
        Dim loop1 As Integer

        For loop1 = 0 To UBound(errorvale)

            If errorvale(loop1) = errordata Then
                MsgBox(errorstring(loop1))
                Exit For
            End If

        Next

    End Sub

    Private Sub btnget_reference_Click(sender As Object, e As EventArgs) Handles btnget_reference.Click

        '------------------------------------------------------------------------------
        '           Get Reference
        '------------------------------------------------------------------------------
        Dim inst_error As Integer                       'Instullment error
        Dim loop1 As Integer

        '----- MPM setting for selected 1st range
        For loop1 = 0 To UBound(MPM)
            'set Range for MPM
            inst_error = MPM(loop1).Set_Range(Meas_rang(0))
            If (inst_error <> 0) Then
                Show_Inst_Error(inst_error)
                Exit Sub
            End If
        Next

        '----Move to start wavelength with Sweep Start method.
        inst_error = TSL.Sweep_Start()
        If inst_error <> 0 Then
            Show_Inst_Error(inst_error)
        End If


        If Me.chkeach_ch.Checked Then
            'Reference measurement one channel at a time
            For Each item As STSDataStruct In Refdata_struct
                MsgBox("Connect fiber to MPM" & item.MPMNumber & "_Slot" & item.SlotNumber & "_Ch" & item.ChannelNumber & ".", vbOKOnly)
                '-----Sweep 
                inst_error = Sweep_Process()
                If inst_error = -9999 Then
                    'MPM logging timeout occurred.
                    MsgBox("MPM Trigger receive error! Please check trigger cable connection.", vbOKOnly)
                    Exit Sub
                End If
                If inst_error <> 0 Then
                    Show_Inst_Error(inst_error)
                    Exit Sub
                End If

                '---Move to start wavelength with Sweep Start method for next sweep.
                inst_error = TSL.Sweep_Start()
                If inst_error <> 0 Then
                    Show_Inst_Error(inst_error)
                End If

                '---get logging data & add in STSProcess class
                Dim inst_flag As Boolean

                inst_error = Get_Each_channel_reference_samplingdata(inst_flag, item.MPMNumber, item.SlotNumber, item.ChannelNumber, item.SweepCount)

                If inst_error <> 0 Then
                    If inst_flag = True Then
                        Show_Inst_Error(inst_error)             'Instullment error
                    Else
                        Show_STS_Error(inst_error)              'Processing error
                    End If
                    Exit Sub
                End If

                '------Reference data rescaling 
                Dim process_error As Integer
                process_error = Cal_STS.Cal_RefData_Rescaling()

                If process_error <> 0 Then
                    Show_STS_Error(process_error)
                    Exit Sub
                End If
            Next

        Else

            '-----Sweep 
            inst_error = Sweep_Process()
            If inst_error = -9999 Then
                'MPM logging timeout occurred.
                MsgBox("MPM Trigger receive error! Please check trigger cable connection.", vbOKOnly)
                Exit Sub
            End If
            If inst_error <> 0 Then
                Show_Inst_Error(inst_error)
                Exit Sub
            End If

            '---Move to start wavelength with Sweep Start method for next sweep.
            inst_error = TSL.Sweep_Start()
            If inst_error <> 0 Then
                Show_Inst_Error(inst_error)
            End If

            '---get logging data & add in STSProcess class
            Dim inst_flag As Boolean

            inst_error = Get_reference_samplingdata(inst_flag)

            If inst_error <> 0 Then
                If inst_flag = True Then
                    Show_Inst_Error(inst_error)             'Instullment error
                Else
                    Show_STS_Error(inst_error)              'Processing error
                End If
                Exit Sub
            End If

            '------Reference data rescaling 
            Dim process_error As Integer
            process_error = Cal_STS.Cal_RefData_Rescaling()

            If process_error <> 0 Then
                Show_STS_Error(process_error)
                Exit Sub
            End If
        End If

        'TSL Sweep Stop
        inst_error = TSL.Sweep_Stop()
        If inst_error <> 0 Then
            Show_Inst_Error(inst_error)
            Exit Sub
        End If
        MsgBox("Completed.", vbOKOnly)

    End Sub
    Private Function Get_reference_samplingdata(ByRef inst_flag As Boolean) As Integer
        '---------------------------------------------------------------
        '       Get logging reference data & add in 
        '---------------------------------------------------------------
        Dim inst_error As Integer                        ' Instullment error
        Dim logg_data() As Single = Nothing              'MPM Logging data
        Dim cal_error As Integer                         'process error


        '----Load　Reference MPM data & add in data for STS Process Class for each channel
        For Each item As STSDataStruct In Refdata_struct

            ' Read corresponded MPM data
            inst_error = Get_MPM_Loggdata(item.MPMNumber - 1, item.SlotNumber, item.ChannelNumber, logg_data)

            If inst_error <> 0 Then
                inst_flag = True
                Return inst_error
            End If

            'Add in to MPM reference data to STS Process Class
            cal_error = Cal_STS.Add_Ref_MPMData_CH(logg_data, item)

            If cal_error <> 0 Then
                inst_flag = False
                Return cal_error
            End If
        Next

        '------Load Monitor data & add in data for STS Proccsess class with "STS Data Struct"
        Dim triggerdata() As Single = Nothing     'tigger data 
        Dim monitordata() As Single = Nothing     'monitor data

        inst_error = SPU.Get_Sampling_Rawdata(triggerdata, monitordata)

        If inst_error <> 0 Then
            inst_flag = True
            Return inst_error
        End If


        For Each monitor_item As STSDataStruct In Ref_monitordata_struct

            cal_error = Cal_STS.Add_Ref_MonitorData(triggerdata, monitordata, monitor_item)
            If cal_error <> 0 Then
                inst_flag = False
                Return cal_error
            End If
        Next

        Return 0


    End Function

    Private Function Get_Each_channel_reference_samplingdata(ByRef inst_flag As Boolean, ByVal currentMPMNumber As Integer, ByVal currentSlotNumber As Integer, ByVal currentChannelNumber As Integer, ByVal currentSweepCount As Integer) As Integer
        '---------------------------------------------------------------
        '       Get logging reference data & add in 
        '---------------------------------------------------------------
        Dim inst_error As Integer                        ' Instullment error
        Dim logg_data() As Single = Nothing              'MPM Logging data
        Dim cal_error As Integer                         'process error

        '----Load　Reference MPM data & add in data for STS Process Class for each channel
        For Each item As STSDataStruct In Refdata_struct

            If (item.MPMNumber <> currentMPMNumber Or item.SlotNumber <> currentSlotNumber Or item.ChannelNumber <> currentChannelNumber) Then
                Continue For
            End If

            ' Read corresponded MPM data
            inst_error = Get_MPM_Loggdata(item.MPMNumber - 1, item.SlotNumber, item.ChannelNumber, logg_data)

            If inst_error <> 0 Then
                inst_flag = True
                Return inst_error
            End If

            'Add in to MPM reference data to STS Process Class
            cal_error = Cal_STS.Add_Ref_MPMData_CH(logg_data, item)

            If cal_error <> 0 Then
                inst_flag = False
                Return cal_error
            End If
        Next

        '------Load Monitor data & add in data for STS Proccsess class with "STS Data Struct"
        Dim triggerdata() As Single = Nothing     'tigger data 
        Dim monitordata() As Single = Nothing     'monitor data

        inst_error = SPU.Get_Sampling_Rawdata(triggerdata, monitordata)

        If inst_error <> 0 Then
            inst_flag = True
            Return inst_error
        End If

        For Each monitor_item As STSDataStruct In Ref_monitordata_struct

            cal_error = Cal_STS.Add_Ref_MonitorData(triggerdata, monitordata, monitor_item)
            If cal_error <> 0 Then
                inst_flag = False
                Return cal_error
            End If
        Next

        'cal_error = Cal_STS.Add_Ref_MonitorData(triggerdata, monitordata, Ref_monitor_struct)

        'If cal_error <> 0 Then
        '    inst_flag = False
        '    Return cal_error
        'End If

        Return 0


    End Function
    Private Function Get_measurement_samplingdata(ByVal sweepcount As Integer, ByRef inst_flag As Boolean) As Integer
        '---------------------------------------------------------------
        '       Get logging measurement data & add in 
        '---------------------------------------------------------------
        Dim inst_error As Integer                        ' Instullment error
        Dim logg_data() As Single = Nothing              'MPM Logging data
        Dim cal_error As Integer                        'process error


        '-- Load MPM Logging data & Add in STS Process class with measurment sts data struct 
        For Each item As STSDataStruct In Data_struct

            If item.SweepCount <> sweepcount Then
                Continue For
            End If

            ' Read corresponded MPM data
            inst_error = Get_MPM_Loggdata(item.MPMNumber - 1, item.SlotNumber, item.ChannelNumber, logg_data)

            If inst_error <> 0 Then
                inst_flag = True
                Return inst_error
            End If

            'Add in to MPM reference data to STS Process Class
            cal_error = Cal_STS.Add_Meas_MPMData_CH(logg_data, item)

            If cal_error <> 0 Then
                inst_flag = False
                Return cal_error
            End If
        Next

        '--Lado SPU monitor data & Add in STS Process class with measurement monitor data struct
        Dim triggerdata() As Single = Nothing
        Dim monitordata() As Single = Nothing

        inst_error = SPU.Get_Sampling_Rawdata(triggerdata, monitordata)

        If inst_error <> 0 Then
            inst_flag = True
            Return inst_error
        End If


        'Search item from measurement monitor data structure according to sweep count.

        For Each item As STSMonitorStruct In Meas_monitor_struct

            If item.SweepCount = sweepcount Then
                cal_error = Cal_STS.Add_Meas_MonitorData(triggerdata, monitordata, item)

                If cal_error <> 0 Then
                    inst_flag = False
                    Return cal_error
                End If
                Exit For

            End If
        Next
        Return 0


    End Function
    Private Function Get_MPM_Loggdata(ByVal deveice As Integer, ByVal slot As Integer, ByVal ch As Integer, ByRef data() As Single)
        '---------------------------------------------------------------
        '       Get MPM Logg data
        '--------------------------------------------------------------
        Dim inst_error As Integer

        inst_error = MPM(deveice).Get_Each_Channel_Logdata(slot, ch, data)
        Return inst_error

    End Function

    Private Function Sweep_Process() As Integer
        '------------------------------------------------------------
        '       Sweep Process
        '------------------------------------------------------------
        Dim inst_error As Integer               'Instullment error
        Dim loop1 As Integer                    'loop count 


        'MPM sampling start 
        For loop1 = 0 To UBound(MPM)
            inst_error = MPM(loop1).Logging_Start
            If inst_error <> 0 Then
                Return inst_error
            End If
        Next

        'TSL waiting for start status 
        inst_error = TSL.Waiting_For_Sweep_Status(2000, TSL.Sweep_Status.WaitingforTrigger)

        '---error handling -> MPM Logging Stop
        If inst_error <> 0 Then
            For loop1 = 0 To UBound(MPM)
                MPM(loop1).Logging_Stop()
            Next
            Return inst_error
        End If

        'SPU sampling start
        inst_error = SPU.Sampling_Start()
        If inst_error <> 0 Then
            Return inst_error
        End If

        'TSL issue software trigger
        inst_error = TSL.Set_Software_Trigger()

        '---error handling -> MPM Logging Stop
        If inst_error <> 0 Then
            For loop1 = 0 To UBound(MPM)
                MPM(loop1).Logging_Stop()
            Next
            Return inst_error
        End If

        'SPU waiting for sampling 
        inst_error = SPU.Waiting_for_sampling()

        '---error handling -> MPM Logging Stop
        If inst_error <> 0 Then
            For loop1 = 0 To UBound(MPM)
                MPM(loop1).Logging_Stop()
            Next
            Return inst_error
        End If

        Dim mpm_stauts As Integer                   'mpm logging status 0:douring measurement 1:Compleated -1:Stopped
        Dim mpm_count As Integer                    'mpm number of logging completed point  
        Dim st As New Stopwatch                     'stopwatch           
        Dim mpm_completed_falg As Boolean = True    'mpm logging completed flag  F:not completed T:completed    

        'MPM waiting for sampling 
        st.Start()                          'stopwathc start 
        Do
            For loop1 = 0 To UBound(MPM)

                inst_error = MPM(loop1).Get_Logging_Status(mpm_stauts, mpm_count)
                If inst_error <> 0 Then
                    Return inst_error
                End If

                If mpm_stauts = 1 Then
                    Exit Do
                End If

                If st.ElapsedMilliseconds >= 2000 Then
                    'Logging time out(time out = 2sec after from SPU sampling  completed.)
                    mpm_completed_falg = False
                    Exit Do
                End If
            Next
        Loop

        st.Stop()

        ' MPM sampling stop
        For loop1 = 0 To UBound(MPM)
            inst_error = MPM(loop1).Logging_Stop()
            If inst_error <> 0 Then
                Return inst_error
            End If
        Next


        'TSL Waiting for standby
        inst_error = TSL.Waiting_For_Sweep_Status(5000, TSL.Sweep_Status.Standby)

        If inst_error <> 0 Then
            Return inst_error
        End If

        If mpm_completed_falg = False Then
            'mpm logging timeout occurred.
            Return -9999
        End If

        Return 0

    End Function

    Private Sub btnmeas_Click(sender As Object, e As EventArgs) Handles btnmeas.Click
        '-------------------------------------------------------------------------
        '           Mesurement Process
        '-------------------------------------------------------------------------
        Dim loop1 As Integer                        'loop Count 1
        Dim loop2 As Integer                        'Loop count 2
        Dim inst_error As Integer                   'instllment error   
        Dim inst_flag As Boolean                    'instrment error flag



        '-------Measurement-----------------------------------------------

        'Move to start wavelength  with Sweep Start method.
        inst_error = TSL.Sweep_Start
        If inst_error <> 0 Then
            Show_Inst_Error(inst_error)
            Exit Sub
        End If

        '--------Rang Loop
        For loop1 = 0 To Meas_rang.Count - 1

            'MPM range Setting 
            For loop2 = 0 To UBound(MPM)
                inst_error = MPM(loop2).Set_Range(Meas_rang(loop1))

                If inst_error <> 0 Then
                    Show_Inst_Error(inst_error)
                    Exit Sub
                End If
            Next
            'Range Set delay
            System.Threading.Thread.Sleep(1)
            ' Sweep process
            inst_error = Sweep_Process()
            If inst_error <> 0 Then
                Show_Inst_Error(inst_error)
                Exit Sub
            End If

            'Move to start wavelength  with Sweep Start method for next sweep.
            inst_error = TSL.Sweep_Start
            If inst_error <> 0 Then
                Show_Inst_Error(inst_error)
                Exit Sub
            End If

            ' get loggging data & Add in STS Process class
            inst_error = Get_measurement_samplingdata(loop1 + 1, inst_flag)

            If inst_error <> 0 Then
                If inst_flag = True Then
                    Show_Inst_Error(inst_error)
                Else
                    Show_STS_Error(inst_error)
                End If

                Exit Sub
            End If

        Next

        '----------STS Process-------------------------------------------------

        Dim process_error As Integer                    'STS　Process error

        'Rescaling
        process_error = Cal_STS.Cal_MeasData_Rescaling()

        If process_error <> 0 Then
            Show_STS_Error(process_error)
            Exit Sub
        End If

        'merge or IL calculate
        Dim merge_type As Module_Type

        If Flag_215 = False Then
            If Flag_213 = True Then
                merge_type = Module_Type.MPM_213
            Else
                merge_type = Module_Type.MPM_211
            End If

            'Process ranges merge
            process_error = Cal_STS.Cal_IL_Merge(merge_type)
        Else
            'just IL process
            process_error = Cal_STS.Cal_IL()
        End If

        ' data save
        process_error = Save_Measurement_data()
        If process_error <> 0 Then
            Show_STS_Error(process_error)
        End If


        inst_error = TSL.Sweep_Stop()
        If inst_error <> 0 Then
            Show_Inst_Error(inst_error)
            Exit Sub
        End If


        MsgBox("Completed.", vbOKOnly)

    End Sub

    Private Function Save_Measurement_data() As Integer
        '-------------------------------------------------------
        '       Save Measurement data
        '-------------------------------------------------------
        Dim wavelength_table() As Double = Nothing            'Rescaled wavelength table  
        Dim lstILdata As New List(Of Single())               'IL data list 
        Dim process_error As Integer                          'process class error  
        Dim loop1 As Integer                                  'loop count
        Dim ildata() As Single = Nothing                      'il data arrray

        'Get Rescaled wavelength tabel 
        process_error = Cal_STS.Get_Target_Wavelength_Table(wavelength_table)


        'Get IL data 
        If Flag_215 = True Then
            For Each items As STSDataStruct In Data_struct

                process_error = Cal_STS.Get_IL_Data(ildata, items)
                If process_error <> 0 Then
                    Return process_error
                End If

                lstILdata.Add(ildata.ToArray)
            Next

        Else

            For Each items As STSDataStructForMerge In Mergedata_struct

                process_error = Cal_STS.Get_IL_Merge_Data(ildata, items)
                If process_error <> 0 Then
                    Return process_error
                End If

                lstILdata.Add(ildata.ToArray)
            Next
        End If


        '-----Data Save 
        Dim file_path As String = String.Empty

        Me.SaveFileDialog1.Title = "IL data save"
        Me.SaveFileDialog1.Filter = "csv file(*.csv)|*.csv"
        Me.SaveFileDialog1.ShowDialog()

        file_path = Me.SaveFileDialog1.FileName

        Dim writer As New System.IO.StreamWriter(file_path, False, System.Text.Encoding.GetEncoding("UTF-8"))
        Dim write_string As String = Nothing
        Dim hedder As String = String.Empty                 'file hedder 

        hedder = "Wavelength(nm)"

        For Each item As STSDataStruct In Data_struct
            If item.SweepCount <> 1 Then
                Continue For
            End If

            hedder = hedder & ",MPM" & CStr(item.MPMNumber) & "Slot" & CStr(item.SlotNumber) & "Ch" & CStr(item.ChannelNumber)
        Next

        'write hedder
        writer.WriteLine(hedder)

        Dim loop2 As Integer

        For loop1 = 0 To UBound(wavelength_table)

            write_string = wavelength_table(loop1)

            For loop2 = 0 To lstILdata.Count - 1
                write_string = write_string & "," & lstILdata(loop2)(loop1)
            Next

            writer.WriteLine(write_string)

        Next

        writer.Close()

        Return 0

    End Function

    Private Sub btnsaveref_rawdata_Click(sender As Object, e As EventArgs) Handles btnsaveref_rawdata.Click
        '---------------------------------------------------------------------------
        '           Save reference Raw data
        '---------------------------------------------------------------------------
        Dim loop1 As Integer                        'loop count1   
        Dim process_error As Integer                'process class error
        Dim wavetable() As Double = Nothing         'wavelength table
        Dim powdata() As Single = Nothing           'powerdata  rescaled    
        Dim monitordata() As Single = Nothing       'monitordata rescaled 
        Dim lstpowdata As New List(Of Single())     'Power data list
        Dim lstmonitordata As New List(Of Single()) 'monitor data list 


        ' Get reference Raw data (after the rescaling)
        For Each item As STSDataStruct In Refdata_struct

            ' monitor data is 1 data for each sweep. It can be overwrite.
            process_error = Cal_STS.Get_Ref_Power_Rawdata(item, powdata)
            If process_error <> 0 Then
                Show_STS_Error(process_error)
                Exit Sub
            End If

            lstpowdata.Add(powdata.ToArray)
        Next

        'Get reference Raw monitor data
        Dim get_struct As STSDataStruct                 'struct of get
        Dim befor_struct As New STSDataStruct           'befor struct

        For Each item As STSDataStruct In Ref_monitordata_struct

            If Me.chkeach_ch.Checked Then
                'Reference measurement one channel at a time
                If (item.MPMNumber = befor_struct.MPMNumber) _
                    And (item.SlotNumber = befor_struct.SlotNumber) _
                    And (item.ChannelNumber = befor_struct.ChannelNumber) Then
                    Continue For
                End If
            End If

            process_error = Cal_STS.Get_Ref_Monitor_Rawdata(item, monitordata)

            If process_error <> 0 Then
                Show_STS_Error(process_error)
                Exit Sub
            End If

            get_struct.MPMNumber = item.MPMNumber
            get_struct.SlotNumber = item.SlotNumber
            get_struct.ChannelNumber = item.ChannelNumber
            'get_struct.SOP = item.SOP

            lstmonitordata.Add(monitordata.ToArray)
            befor_struct = get_struct
        Next

        'Get Target wavelengt table
        process_error = Cal_STS.Get_Target_Wavelength_Table(wavetable)

        If process_error <> 0 Then
            Show_STS_Error(process_error)
            Exit Sub
        End If


        '------File save 

        Dim fpath As String = String.Empty                  'file path 

        Me.SaveFileDialog1.Title = "Reference Raw data"
        Me.SaveFileDialog1.Filter = "csv file(*.csv)|*.csv"
        Me.SaveFileDialog1.ShowDialog()
        fpath = Me.SaveFileDialog1.FileName

        Dim writer As New System.IO.StreamWriter(fpath, False, System.Text.Encoding.GetEncoding("UTF-8"))

        Dim hedder As String = String.Empty                 'file hedder 

        hedder = "Wavelength(nm)"

        For Each item As STSDataStruct In Data_struct
            If item.SweepCount <> 1 Then
                Continue For
            End If

            hedder = hedder & ",MPM" & CStr(item.MPMNumber) & "Slot" & CStr(item.SlotNumber) & "Ch" & CStr(item.ChannelNumber)
        Next

        If Me.chkeach_ch.Checked Then
            'Reference measurement one channel at a time
            For Each item As STSDataStruct In Refdata_struct
                If item.SOP <> loop1 Then
                    Continue For
                End If
                hedder = hedder & ",monitordata_MPM" & CStr(item.MPMNumber) & "Slot" & CStr(item.SlotNumber) & "Ch" & CStr(item.ChannelNumber)
            Next
        Else
            hedder = hedder & ",monitordata"
        End If

        'write hedder
        writer.WriteLine(hedder)


        'Write data 
        Dim write_str As String = String.Empty                  'write string 
        Dim loop2 As Integer                                    'loop count 2
        Dim loop3 As Integer                                    'loop count 3


        For loop1 = 0 To UBound(wavetable)

            'wavelength data
            write_str = CStr(wavetable(loop1))

            'Power data
            For loop2 = 0 To lstpowdata.Count - 1
                write_str = write_str & "," & lstpowdata(loop2)(loop1)
            Next


            'monitordata
            For loop3 = 0 To lstmonitordata.Count - 1
                write_str = write_str & "," & lstmonitordata(loop3)(loop1)
            Next

            writer.WriteLine(write_str)
        Next

        writer.Close()
        MsgBox("Completed.", vbOKOnly)


    End Sub

    Private Sub btnsaveRawdata_Click(sender As Object, e As EventArgs) Handles btnsaveRawdata.Click
        '-------------------------------------------------------------------------
        '       Save mesurement raw data
        '-------------------------------------------------------------------------
        Dim loop1 As Integer                                        'loop1
        Dim loop2 As Integer                                        'loop2
        Dim loop3 As Integer                                        'loop3
        Dim wavelength_table() As Double = Nothing                  'Wavelength table
        Dim monitordata() As Single = Nothing
        Dim powerdata() As Single = Nothing
        Dim errorcode As Integer                                    'Errorcode
        Dim lstpower As New List(Of Single())

        '-- Get Wavelength table
        errorcode = Cal_STS.Get_Target_Wavelength_Table(wavelength_table)

        If errorcode <> 0 Then
            Show_STS_Error(errorcode)
            Exit Sub
        End If


        Dim fpath As String = String.Empty              'File　path
        Dim writer As System.IO.StreamWriter            'Writer 
        Dim write_string As String = String.Empty
        Dim hedder As String = String.Empty


        For loop1 = 0 To Meas_rang.Count - 1

            ' get raw data same range data
            For Each item As STSDataStruct In Data_struct

                If item.RangeNumber <> Meas_rang(loop1) Then
                    Continue For
                End If

                errorcode = Cal_STS.Get_Meas_Power_Rawdata(item, powerdata)

                If errorcode <> 0 Then
                    Show_STS_Error(errorcode)
                    Exit Sub
                End If

                lstpower.Add(powerdata.ToArray)
            Next

            '----get raw monitor data same range
            For Each monitoritem As STSMonitorStruct In Meas_monitor_struct

                If monitoritem.SweepCount = loop1 + 1 Then
                    errorcode = Cal_STS.Get_Meas_Monitor_Rawdata(monitoritem, monitordata)
                Else
                    Continue For
                End If

            Next

            '--File save at same range data 
            Select Case loop1
                Case 0
                    Me.SaveFileDialog1.Title = "1st Range data"
                Case 1
                    Me.SaveFileDialog1.Title = "2nd Range data"
                Case Else
                    Me.SaveFileDialog1.Title = CStr(loop1 + 1) & "rd Range data"
            End Select

            Me.SaveFileDialog1.Filter = "csv file(*.csv)|*.csv"
            Me.SaveFileDialog1.ShowDialog()
            fpath = Me.SaveFileDialog1.FileName

            writer = New System.IO.StreamWriter(fpath, False, System.Text.Encoding.GetEncoding("UTF-8"))

            hedder = "wavelength"

            For Each item As STSDataStruct In Data_struct
                If item.RangeNumber <> Meas_rang(loop1) Then
                    Continue For
                End If

                hedder = hedder & "," & "MPM" & CStr(item.MPMNumber) & "Slot" & CStr(item.SlotNumber) & "Ch" & CStr(item.ChannelNumber)
            Next

            hedder = hedder & "," & "Monitordata"

            writer.WriteLine(hedder)

            For loop2 = 0 To UBound(wavelength_table)
                write_string = CStr(wavelength_table(loop2))

                For loop3 = 0 To lstpower.Count - 1
                    write_string = write_string & "," & lstpower(loop3)(loop2)
                Next

                write_string = write_string & "," & monitordata(loop2)


                writer.WriteLine(write_string)

            Next

            writer.Close()
            lstpower = New List(Of Single())
            monitordata = Nothing

        Next

        MsgBox("Completed.", vbOKOnly)

    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        '-----------------------------------------------------------------------------
        '       Reference Data Read
        '       This function must use after "SET" 
        '-----------------------------------------------------------------------------
        Dim fpath As String = String.Empty
        Dim reader As System.IO.StreamReader



        '-------Reference file　Read 

        Me.OpenFileDialog1.Title = "Reference Data"
        Me.OpenFileDialog1.ShowDialog()
        fpath = Me.OpenFileDialog1.FileName

        reader = New System.IO.StreamReader(fpath)

        Dim read_st As String = String.Empty                            'Read String 
        Dim split_st() As String = Nothing                             'split strin array

        'hedder Read 
        read_st = reader.ReadLine
        read_st = read_st.Trim()

        split_st = Split(read_st, ",")


        'Check data cout 
        Dim ch_count As Integer                                         'file data ch count
        Dim loop1 As Integer                                            'Loop count1
        Dim chk_str As String = String.Empty                            'check string
        Dim mpm_number As Integer                                       'MPM number
        Dim slot_number As Integer                                      'Slot number
        Dim ch_number As Integer                                        'ch number 

        'Check data cout 
        If Me.chkeach_ch.Checked Then
            'Reference measurement one channel at a time
            ch_count = (split_st.Count - 1) / 2
        Else
            ch_count = split_st.Count - 2
        End If

        If ch_count <> Me.chklst_ch.CheckedItems.Count Then

            MsgBox("Reference data mismatch.Please selecet right data.", vbOKOnly)
            reader.Close()
            Exit Sub
        End If

        '-----Check parameter & make reference data struct 
        Dim refdata_strunct As STSDataStruct                        'Data struct for reference
        Dim lst_refdata_struct As New List(Of STSDataStruct)        'Data struct for reference List    
        Dim match_flag As Boolean = False                           'match flag


        For loop1 = 1 To ch_count
            'MPM device number 
            chk_str = split_st(loop1).Substring(3, 1)
            mpm_number = CInt(chk_str)

            'MPM Slot number 
            chk_str = split_st(loop1).Substring(8, 1)
            slot_number = CInt(chk_str)

            'MPM Ch number 
            chk_str = split_st(loop1).Substring(11, 1)
            ch_number = CInt(chk_str)


            ' Check exsist data in data struct 
            For Each item As STSDataStruct In Data_struct

                If item.MPMNumber = mpm_number And item.SlotNumber = slot_number And item.ChannelNumber = ch_number Then
                    match_flag = True
                    Exit For
                End If
            Next

            If match_flag = False Then
                MsgBox("Reference data mismatch.Please selecet right data.", vbOKOnly)
                reader.Close()
                Exit Sub
            End If

            'Add reference data struct 
            refdata_strunct.MPMNumber = mpm_number
            refdata_strunct.SlotNumber = slot_number
            refdata_strunct.ChannelNumber = ch_number
            refdata_strunct.RangeNumber = 1
            refdata_strunct.SweepCount = 1

            lst_refdata_struct.Add(refdata_strunct)

        Next

        '-------Read Reference data
        Dim power() As List(Of Single)                 'Power data list 

        Dim counter As Integer                         'Counter
        Dim wavelength As Double                       'Read Wavelength 

        If Me.chkeach_ch.Checked Then

            'Reference measurement one channel at a time
            Dim monitor() As List(Of Single)               'Monitordata

            ReDim power(ch_count - 1)
            ReDim monitor(ch_count - 1)


            For loop1 = 0 To ch_count - 1
                power(loop1) = New List(Of Single)
                monitor(loop1) = New List(Of Single)
            Next




            Do
                read_st = reader.ReadLine()

                If read_st = "" Then
                    Exit Do
                End If

                read_st = read_st.Trim()
                split_st = Split(read_st, ",")

                'Check Start Wavelength 
                If counter = 0 Then
                    If CDbl(split_st(0)) <> Me.txtstartwave.Text Then
                        MsgBox("Reference data mismatch.Please selecet right data.", vbOKOnly)
                        reader.Close()
                        Exit Sub
                    End If
                End If

                'hold wavelength data
                wavelength = CDbl(split_st(0))

                For loop1 = 0 To ch_count - 1
                    power(loop1).Add(CDbl(split_st(loop1 + 1)))
                Next

                For loop1 = 0 To ch_count - 1
                    monitor(loop1).Add(CDbl(split_st(ch_count + loop1 + 1)))
                Next

                counter = counter + 1

            Loop

            reader.Close()

            'Check Stop wavelength 
            If wavelength <> CStr(Me.txtstopwave.Text) Then
                MsgBox("Reference data mismatch.Please selecet right data.", vbOKOnly)
                Exit Sub
            End If

            'check number of point 


            Dim datapoint As Integer                            'number of data point 

            datapoint = (Math.Abs(Me.txtstopwave.Text - Me.txtstartwave.Text) / Me.txtstepwave.Text) + 1

            If datapoint <> monitor(0).Count Then
                MsgBox("Reference data mismatch.Please selecet right data.", vbOKOnly)
                Exit Sub
            End If



            '-------Add in  data to STS Process class
            Dim errorcode As Integer                            'Errorcode
            counter = 0

            For Each item In lst_refdata_struct
                'Add in reference data of rescaled.
                errorcode = Cal_STS.Add_Ref_Rawdata(power(counter).ToArray, monitor(counter).ToArray, item)

                If errorcode <> 0 Then
                    Show_Inst_Error(errorcode)
                    Exit Sub
                End If
                counter = counter + 1
            Next

        Else


            '-------Read Reference data
            Dim monitor As New List(Of Single)             'Monitordata

            ReDim power(ch_count - 1)

            For loop1 = 0 To ch_count - 1
                power(loop1) = New List(Of Single)
            Next



            Do
                read_st = reader.ReadLine()

                If read_st = "" Then
                    Exit Do
                End If

                read_st = read_st.Trim()
                split_st = Split(read_st, ",")

                'Check Start Wavelength 
                If counter = 0 Then
                    If CDbl(split_st(0)) <> Me.txtstartwave.Text Then
                        MsgBox("Reference data mismatch.Please selecet right data.", vbOKOnly)
                        reader.Close()
                        Exit Sub
                    End If
                End If

                'hold wavelength data
                wavelength = CDbl(split_st(0))

                For loop1 = 0 To ch_count - 1
                    power(loop1).Add(CDbl(split_st(loop1 + 1)))
                Next

                monitor.Add(CDbl(split_st(ch_count + 1)))

                counter = counter + 1




            Loop

            reader.Close()

            'Check Stop wavelength 
            If wavelength <> CStr(Me.txtstopwave.Text) Then
                MsgBox("Reference data mismatch.Please selecet right data.", vbOKOnly)
                Exit Sub
            End If

            'check number of point 



            Dim datapoint As Integer                            'number of data point 

            datapoint = (Math.Abs(Me.txtstopwave.Text - Me.txtstartwave.Text) / Me.txtstepwave.Text) + 1

            If datapoint <> monitor.Count Then
                MsgBox("Reference data mismatch.Please selecet right data.", vbOKOnly)
                Exit Sub
            End If





            '-------Add in  data to STS Process class
            Dim errorcode As Integer                            'Errorcode
            counter = 0

            For Each item In lst_refdata_struct
                'Add in reference data of rescaled.
                errorcode = Cal_STS.Add_Ref_Rawdata(power(counter).ToArray, monitor.ToArray, item)

                If errorcode <> 0 Then
                    Show_Inst_Error(errorcode)
                    Exit Sub
                End If
                counter = counter + 1
            Next

        End If


        MsgBox("Completed.", vbOKOnly)


    End Sub
End Class
