<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'フォームがコンポーネントの一覧をクリーンアップするために dispose をオーバーライドします。
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Windows フォーム デザイナーで必要です。
    Private components As System.ComponentModel.IContainer

    'メモ: 以下のプロシージャは Windows フォーム デザイナーで必要です。
    'Windows フォーム デザイナーを使用して変更できます。  
    'コード エディターを使って変更しないでください。
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.txtpower = New System.Windows.Forms.TextBox()
        Me.cmbspeed = New System.Windows.Forms.ComboBox()
        Me.txtstepwave = New System.Windows.Forms.TextBox()
        Me.txtstopwave = New System.Windows.Forms.TextBox()
        Me.txtstartwave = New System.Windows.Forms.TextBox()
        Me.GroupBox2 = New System.Windows.Forms.GroupBox()
        Me.Label7 = New System.Windows.Forms.Label()
        Me.Label6 = New System.Windows.Forms.Label()
        Me.chklst_range = New System.Windows.Forms.CheckedListBox()
        Me.chklst_ch = New System.Windows.Forms.CheckedListBox()
        Me.btnset = New System.Windows.Forms.Button()
        Me.btnget_reference = New System.Windows.Forms.Button()
        Me.btnmeas = New System.Windows.Forms.Button()
        Me.btnsaveref_rawdata = New System.Windows.Forms.Button()
        Me.SaveFileDialog1 = New System.Windows.Forms.SaveFileDialog()
        Me.btnsaveRawdata = New System.Windows.Forms.Button()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.OpenFileDialog1 = New System.Windows.Forms.OpenFileDialog()
        Me.chkeach_ch = New System.Windows.Forms.CheckBox()
        Me.GroupBox1.SuspendLayout()
        Me.GroupBox2.SuspendLayout()
        Me.SuspendLayout()
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.Label5)
        Me.GroupBox1.Controls.Add(Me.Label4)
        Me.GroupBox1.Controls.Add(Me.Label3)
        Me.GroupBox1.Controls.Add(Me.Label2)
        Me.GroupBox1.Controls.Add(Me.Label1)
        Me.GroupBox1.Controls.Add(Me.txtpower)
        Me.GroupBox1.Controls.Add(Me.cmbspeed)
        Me.GroupBox1.Controls.Add(Me.txtstepwave)
        Me.GroupBox1.Controls.Add(Me.txtstopwave)
        Me.GroupBox1.Controls.Add(Me.txtstartwave)
        Me.GroupBox1.Location = New System.Drawing.Point(21, 35)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(709, 101)
        Me.GroupBox1.TabIndex = 0
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Sweep Setting"
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(560, 37)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(87, 13)
        Me.Label5.TabIndex = 9
        Me.Label5.Text = "TSL Power(dBm)"
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(435, 37)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(113, 13)
        Me.Label4.TabIndex = 8
        Me.Label4.Text = "SweepSpeed(nm/sec)"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(312, 38)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(107, 13)
        Me.Label3.TabIndex = 7
        Me.Label3.Text = "WavelengthStep(nm)"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(176, 38)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(107, 13)
        Me.Label2.TabIndex = 6
        Me.Label2.Text = "StopWavelength(nm)"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(25, 37)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(107, 13)
        Me.Label1.TabIndex = 5
        Me.Label1.Text = "StartWavelength(nm)"
        '
        'txtpower
        '
        Me.txtpower.Location = New System.Drawing.Point(562, 53)
        Me.txtpower.Name = "txtpower"
        Me.txtpower.Size = New System.Drawing.Size(117, 20)
        Me.txtpower.TabIndex = 4
        Me.txtpower.Text = "0"
        '
        'cmbspeed
        '
        Me.cmbspeed.FormattingEnabled = True
        Me.cmbspeed.Location = New System.Drawing.Point(437, 53)
        Me.cmbspeed.Name = "cmbspeed"
        Me.cmbspeed.Size = New System.Drawing.Size(102, 21)
        Me.cmbspeed.TabIndex = 3
        '
        'txtstepwave
        '
        Me.txtstepwave.Location = New System.Drawing.Point(314, 54)
        Me.txtstepwave.Name = "txtstepwave"
        Me.txtstepwave.Size = New System.Drawing.Size(100, 20)
        Me.txtstepwave.TabIndex = 2
        Me.txtstepwave.Text = "0.01"
        '
        'txtstopwave
        '
        Me.txtstopwave.Location = New System.Drawing.Point(178, 54)
        Me.txtstopwave.Name = "txtstopwave"
        Me.txtstopwave.Size = New System.Drawing.Size(117, 20)
        Me.txtstopwave.TabIndex = 1
        Me.txtstopwave.Text = "1600"
        '
        'txtstartwave
        '
        Me.txtstartwave.Location = New System.Drawing.Point(27, 54)
        Me.txtstartwave.Name = "txtstartwave"
        Me.txtstartwave.Size = New System.Drawing.Size(117, 20)
        Me.txtstartwave.TabIndex = 0
        Me.txtstartwave.Text = "1500"
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.Label7)
        Me.GroupBox2.Controls.Add(Me.Label6)
        Me.GroupBox2.Controls.Add(Me.chklst_range)
        Me.GroupBox2.Controls.Add(Me.chklst_ch)
        Me.GroupBox2.Location = New System.Drawing.Point(21, 153)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(332, 89)
        Me.GroupBox2.TabIndex = 1
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = "Measurement ch And Range"
        '
        'Label7
        '
        Me.Label7.AutoSize = True
        Me.Label7.Location = New System.Drawing.Point(176, 21)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(106, 13)
        Me.Label7.TabIndex = 3
        Me.Label7.Text = "Measurement Range"
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.Location = New System.Drawing.Point(10, 21)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(86, 13)
        Me.Label6.TabIndex = 2
        Me.Label6.Text = "Measurement ch"
        '
        'chklst_range
        '
        Me.chklst_range.FormattingEnabled = True
        Me.chklst_range.Location = New System.Drawing.Point(177, 37)
        Me.chklst_range.Name = "chklst_range"
        Me.chklst_range.Size = New System.Drawing.Size(118, 34)
        Me.chklst_range.TabIndex = 1
        '
        'chklst_ch
        '
        Me.chklst_ch.FormattingEnabled = True
        Me.chklst_ch.Location = New System.Drawing.Point(12, 37)
        Me.chklst_ch.Name = "chklst_ch"
        Me.chklst_ch.Size = New System.Drawing.Size(135, 34)
        Me.chklst_ch.TabIndex = 0
        '
        'btnset
        '
        Me.btnset.Location = New System.Drawing.Point(380, 163)
        Me.btnset.Name = "btnset"
        Me.btnset.Size = New System.Drawing.Size(83, 35)
        Me.btnset.TabIndex = 2
        Me.btnset.Text = "SET"
        Me.btnset.UseVisualStyleBackColor = True
        '
        'btnget_reference
        '
        Me.btnget_reference.Location = New System.Drawing.Point(481, 163)
        Me.btnget_reference.Name = "btnget_reference"
        Me.btnget_reference.Size = New System.Drawing.Size(102, 35)
        Me.btnget_reference.TabIndex = 3
        Me.btnget_reference.Text = "Reference"
        Me.btnget_reference.UseVisualStyleBackColor = True
        '
        'btnmeas
        '
        Me.btnmeas.Location = New System.Drawing.Point(605, 163)
        Me.btnmeas.Name = "btnmeas"
        Me.btnmeas.Size = New System.Drawing.Size(106, 35)
        Me.btnmeas.TabIndex = 4
        Me.btnmeas.Text = "Measurement"
        Me.btnmeas.UseVisualStyleBackColor = True
        '
        'btnsaveref_rawdata
        '
        Me.btnsaveref_rawdata.Location = New System.Drawing.Point(33, 274)
        Me.btnsaveref_rawdata.Name = "btnsaveref_rawdata"
        Me.btnsaveref_rawdata.Size = New System.Drawing.Size(132, 35)
        Me.btnsaveref_rawdata.TabIndex = 5
        Me.btnsaveref_rawdata.Text = "Save Reference Rawdata"
        Me.btnsaveref_rawdata.UseVisualStyleBackColor = True
        '
        'btnsaveRawdata
        '
        Me.btnsaveRawdata.Location = New System.Drawing.Point(184, 274)
        Me.btnsaveRawdata.Name = "btnsaveRawdata"
        Me.btnsaveRawdata.Size = New System.Drawing.Size(132, 35)
        Me.btnsaveRawdata.TabIndex = 6
        Me.btnsaveRawdata.Text = "Save Rawdata"
        Me.btnsaveRawdata.UseVisualStyleBackColor = True
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(380, 274)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(132, 35)
        Me.Button1.TabIndex = 7
        Me.Button1.Text = "Read Reference Data"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'OpenFileDialog1
        '
        Me.OpenFileDialog1.FileName = "OpenFileDialog1"
        '
        'chkeach_ch
        '
        Me.chkeach_ch.AutoSize = True
        Me.chkeach_ch.Location = New System.Drawing.Point(380, 207)
        Me.chkeach_ch.Name = "chkeach_ch"
        Me.chkeach_ch.Size = New System.Drawing.Size(145, 17)
        Me.chkeach_ch.TabIndex = 15
        Me.chkeach_ch.Text = "each channel individually"
        Me.chkeach_ch.UseVisualStyleBackColor = True
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(758, 348)
        Me.Controls.Add(Me.chkeach_ch)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.btnsaveRawdata)
        Me.Controls.Add(Me.btnsaveref_rawdata)
        Me.Controls.Add(Me.btnmeas)
        Me.Controls.Add(Me.btnget_reference)
        Me.Controls.Add(Me.btnset)
        Me.Controls.Add(Me.GroupBox2)
        Me.Controls.Add(Me.GroupBox1)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Name = "Form1"
        Me.Text = "STS IL sample software"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
        Me.GroupBox2.ResumeLayout(False)
        Me.GroupBox2.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents GroupBox1 As GroupBox
    Friend WithEvents Label5 As Label
    Friend WithEvents Label4 As Label
    Friend WithEvents Label3 As Label
    Friend WithEvents Label2 As Label
    Friend WithEvents Label1 As Label
    Friend WithEvents txtpower As TextBox
    Friend WithEvents cmbspeed As ComboBox
    Friend WithEvents txtstepwave As TextBox
    Friend WithEvents txtstopwave As TextBox
    Friend WithEvents txtstartwave As TextBox
    Friend WithEvents GroupBox2 As GroupBox
    Friend WithEvents Label6 As Label
    Friend WithEvents chklst_range As CheckedListBox
    Friend WithEvents chklst_ch As CheckedListBox
    Friend WithEvents Label7 As Label
    Friend WithEvents btnset As Button
    Friend WithEvents btnget_reference As Button
    Friend WithEvents btnmeas As Button
    Friend WithEvents btnsaveref_rawdata As Button
    Friend WithEvents SaveFileDialog1 As SaveFileDialog
    Friend WithEvents btnsaveRawdata As Button
    Friend WithEvents Button1 As Button
    Friend WithEvents OpenFileDialog1 As OpenFileDialog
    Friend WithEvents chkeach_ch As CheckBox
End Class
