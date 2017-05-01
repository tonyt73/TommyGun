object frmDebuggerStateView: TfrmDebuggerStateView
  Left = 0
  Top = 0
  AlphaBlend = True
  AlphaBlendValue = 192
  BorderStyle = bsNone
  Caption = 'State View'
  ClientHeight = 1010
  ClientWidth = 286
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  WindowState = wsMaximized
  OnCreate = FormCreate
  OnMouseEnter = FormMouseEnter
  OnMouseLeave = FormMouseLeave
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object pgcRegisters: TPageControl
    Left = 0
    Top = 111
    Width = 286
    Height = 236
    ActivePage = tabRegisters
    Align = alTop
    Constraints.MaxHeight = 236
    Constraints.MinHeight = 236
    Images = imgDebugView
    OwnerDraw = True
    TabHeight = 24
    TabOrder = 0
    TabWidth = 80
    OnDrawTab = pgcRegistersDrawTab
    OnMouseEnter = FormMouseEnter
    object tabRegisters: TTabSheet
      Caption = 'Registers'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = []
      ImageIndex = 1
      ParentFont = False
      OnMouseEnter = FormMouseEnter
      object Panel3: TPanel
        Left = 0
        Top = 0
        Width = 278
        Height = 202
        Align = alClient
        BevelOuter = bvNone
        Color = clWhite
        ParentBackground = False
        TabOrder = 0
        object lblRegsFlags: TLabel
          Left = 3
          Top = 126
          Width = 184
          Height = 16
          Caption = 'Flags   S Z 5 H 3 V N C'
          OnMouseEnter = FormMouseEnter
        end
        object lblRegsInterrupts: TLabel
          Left = 91
          Top = 164
          Width = 80
          Height = 16
          Alignment = taRightJustify
          Caption = 'Interrupts'
          OnMouseEnter = FormMouseEnter
        end
        object lblRegsPC: TLabeledEdit
          Left = 30
          Top = 4
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 24
          EditLabel.Height = 16
          EditLabel.Caption = 'PC '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Courier New'
          Font.Style = []
          LabelPosition = lpLeft
          ParentFont = False
          ReadOnly = True
          TabOrder = 0
          Text = '$0000'
          OnMouseEnter = FormMouseEnter
        end
        object lblRegsAF: TLabeledEdit
          Left = 30
          Top = 20
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 24
          EditLabel.Height = 16
          EditLabel.Caption = 'AF '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'Courier New'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Courier New'
          Font.Style = []
          LabelPosition = lpLeft
          ParentFont = False
          ReadOnly = True
          TabOrder = 1
          Text = '$0000'
          OnMouseEnter = FormMouseEnter
        end
        object lblRegsBC: TLabeledEdit
          Left = 30
          Top = 36
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 24
          EditLabel.Height = 16
          EditLabel.Caption = 'BC '
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 2
          Text = '$0000'
          OnMouseEnter = FormMouseEnter
        end
        object lblRegsDE: TLabeledEdit
          Left = 30
          Top = 52
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 24
          EditLabel.Height = 16
          EditLabel.Caption = 'DE '
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 3
          Text = '$0000'
          OnMouseEnter = FormMouseEnter
        end
        object lblRegsHL: TLabeledEdit
          Left = 30
          Top = 68
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 24
          EditLabel.Height = 16
          EditLabel.Caption = 'HL '
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 4
          Text = '$0000'
          OnMouseEnter = FormMouseEnter
        end
        object lblRegsIX: TLabeledEdit
          Left = 30
          Top = 84
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 24
          EditLabel.Height = 16
          EditLabel.Caption = 'IX '
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 5
          Text = '$0000'
          OnMouseEnter = FormMouseEnter
        end
        object lblRegsSP: TLabeledEdit
          Left = 128
          Top = 4
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 24
          EditLabel.Height = 16
          EditLabel.Caption = 'SP '
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 6
          Text = '$0000'
          OnMouseEnter = FormMouseEnter
        end
        object lblRegsAF_: TLabeledEdit
          Left = 128
          Top = 20
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 24
          EditLabel.Height = 16
          EditLabel.Caption = 'AF'#39
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 7
          Text = '$0000'
          OnMouseEnter = FormMouseEnter
        end
        object lblRegsBC_: TLabeledEdit
          Left = 128
          Top = 36
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 24
          EditLabel.Height = 16
          EditLabel.Caption = 'BC'#39
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 8
          Text = '$0000'
          OnMouseEnter = FormMouseEnter
        end
        object lblRegsDE_: TLabeledEdit
          Left = 128
          Top = 52
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 24
          EditLabel.Height = 16
          EditLabel.Caption = 'DE'#39
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 9
          Text = '$0000'
          OnMouseEnter = FormMouseEnter
        end
        object lblRegsHL_: TLabeledEdit
          Left = 128
          Top = 68
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 24
          EditLabel.Height = 16
          EditLabel.Caption = 'HL'#39
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 10
          Text = '$0000'
          OnMouseEnter = FormMouseEnter
        end
        object lblRegsIY: TLabeledEdit
          Left = 128
          Top = 84
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 24
          EditLabel.Height = 16
          EditLabel.Caption = 'IY '
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 11
          Text = '$0000'
          OnMouseEnter = FormMouseEnter
        end
        object lblRegsI: TLabeledEdit
          Left = 30
          Top = 100
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 16
          EditLabel.Height = 16
          EditLabel.Caption = 'I '
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 12
          Text = '$0000'
          OnMouseEnter = FormMouseEnter
        end
        object lblRegsR: TLabeledEdit
          Left = 128
          Top = 100
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 16
          EditLabel.Height = 16
          EditLabel.Caption = 'R '
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 13
          Text = '$0000'
          OnMouseEnter = FormMouseEnter
        end
        object chkRegsFlags_S: TCheckBox
          Left = 65
          Top = 141
          Width = 13
          Height = 17
          Enabled = False
          TabOrder = 14
          OnMouseEnter = FormMouseEnter
        end
        object chkRegsFlags_Z: TCheckBox
          Left = 81
          Top = 141
          Width = 13
          Height = 17
          Enabled = False
          TabOrder = 15
          OnMouseEnter = FormMouseEnter
        end
        object chkRegsFlags_5: TCheckBox
          Left = 97
          Top = 141
          Width = 13
          Height = 17
          Enabled = False
          TabOrder = 16
          OnMouseEnter = FormMouseEnter
        end
        object chkRegsFlags_H: TCheckBox
          Left = 113
          Top = 141
          Width = 13
          Height = 17
          Enabled = False
          TabOrder = 17
          OnMouseEnter = FormMouseEnter
        end
        object chkRegsFlags_3: TCheckBox
          Left = 129
          Top = 141
          Width = 13
          Height = 17
          Enabled = False
          TabOrder = 18
          OnMouseEnter = FormMouseEnter
        end
        object chkRegsFlags_V: TCheckBox
          Left = 145
          Top = 141
          Width = 13
          Height = 17
          Enabled = False
          TabOrder = 19
          OnMouseEnter = FormMouseEnter
        end
        object chkRegsFlags_N: TCheckBox
          Left = 161
          Top = 141
          Width = 13
          Height = 17
          Enabled = False
          TabOrder = 20
          OnMouseEnter = FormMouseEnter
        end
        object chkRegsFlags_C: TCheckBox
          Left = 177
          Top = 141
          Width = 13
          Height = 17
          Enabled = False
          TabOrder = 21
          OnMouseEnter = FormMouseEnter
        end
        object lblRegsIM: TLabeledEdit
          Left = 30
          Top = 164
          Width = 24
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 24
          EditLabel.Height = 16
          EditLabel.Caption = 'IM '
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 22
          Text = ' 2'
          OnMouseEnter = FormMouseEnter
        end
        object chkRegsInterrupts: TCheckBox
          Left = 177
          Top = 163
          Width = 13
          Height = 17
          Enabled = False
          TabOrder = 23
          OnMouseEnter = FormMouseEnter
        end
        object lblRegsTStates: TLabeledEdit
          Left = 70
          Top = 186
          Width = 24
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 64
          EditLabel.Height = 16
          EditLabel.Caption = 'TStates '
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 24
          Text = '0'
          OnMouseEnter = FormMouseEnter
        end
      end
    end
    object tabAYRegisters: TTabSheet
      Caption = 'AY Registers'
      ImageIndex = 1
      TabVisible = False
      object txtAYRegisters: TMemo
        Left = 0
        Top = 0
        Width = 278
        Height = 202
        Align = alClient
        BorderStyle = bsNone
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Consolas'
        Font.Style = []
        Lines.Strings = (
          'R0 : Ch A Fine Pitch       0000'
          'R1 : Ch A Course Pitch     0000'
          'R2 : Ch B Fine Pitch       0000'
          'R3 : Ch B Course Pitch     0000'
          'R4 : Ch C Fine Pitch       0000'
          'R5 : Ch C Course Pitch     0000'
          'R6 : Noise Pitch           0000'
          'R7 : Mixer             00000000'
          'R8 : Ch A Volume           0000'
          'R9 : Ch B Volume           0000'
          'R10: Ch A Volume           0000'
          'R11: Envelope Fine         0000'
          'R12: Envelope Course       0000'
          'R13: Envelope Sharp        0000'
          'R14: I/O Port A            0000'
          'R15: I/O Port B            0000')
        ParentFont = False
        TabOrder = 0
        OnMouseEnter = FormMouseEnter
      end
    end
  end
  object pgcStack: TPageControl
    Left = 0
    Top = 521
    Width = 286
    Height = 368
    ActivePage = tabStack
    Align = alTop
    Images = imgDebugView
    OwnerDraw = True
    TabHeight = 24
    TabOrder = 1
    TabWidth = 80
    OnDrawTab = pgcRegistersDrawTab
    OnMouseEnter = FormMouseEnter
    object tabStack: TTabSheet
      Caption = 'Stack'
      object txtStack: TMemo
        Left = 0
        Top = 0
        Width = 278
        Height = 334
        Align = alClient
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Consolas'
        Font.Style = []
        Lines.Strings = (
          '$FFFE: '
          '0000')
        ParentFont = False
        ScrollBars = ssVertical
        TabOrder = 0
        OnMouseEnter = FormMouseEnter
      end
    end
  end
  object pgcPorts: TPageControl
    Left = 0
    Top = 347
    Width = 286
    Height = 174
    ActivePage = tabPorts
    Align = alTop
    Constraints.MaxHeight = 174
    Constraints.MinHeight = 174
    Images = imgDebugView
    OwnerDraw = True
    TabHeight = 24
    TabOrder = 2
    TabWidth = 80
    Visible = False
    OnDrawTab = pgcRegistersDrawTab
    OnMouseEnter = FormMouseEnter
    object tabPorts: TTabSheet
      Caption = 'Ports'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = []
      ImageIndex = 2
      ParentFont = False
      OnMouseEnter = FormMouseEnter
      object Panel4: TPanel
        Left = 0
        Top = 0
        Width = 278
        Height = 140
        Align = alClient
        BevelOuter = bvNone
        Color = clWhite
        ParentBackground = False
        TabOrder = 0
        object lblPortsFEdef: TLabel
          Left = 70
          Top = 1
          Width = 64
          Height = 16
          Caption = 'zExSMBdr'
          OnMouseEnter = FormMouseEnter
        end
        object lblPorts7FFDdef: TLabel
          Left = 70
          Top = 33
          Width = 64
          Height = 16
          Caption = 'xxCRSRam'
          OnMouseEnter = FormMouseEnter
        end
        object lblPorts1FFDdef: TLabel
          Left = 70
          Top = 64
          Width = 64
          Height = 16
          Caption = 'xxxSMRxP'
          OnMouseEnter = FormMouseEnter
        end
        object lblPortsFE: TLabeledEdit
          Left = 70
          Top = 17
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 56
          EditLabel.Height = 16
          EditLabel.Caption = '$FE    '
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 0
          Text = '00000000'
          OnMouseEnter = FormMouseEnter
        end
        object lblPorts7FFD: TLabeledEdit
          Left = 70
          Top = 49
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 56
          EditLabel.Height = 16
          EditLabel.Caption = '$7FFD  '
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 1
          Text = '00000000'
          OnMouseEnter = FormMouseEnter
        end
        object lblPorts1FFD: TLabeledEdit
          Left = 70
          Top = 80
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 56
          EditLabel.Height = 16
          EditLabel.Caption = '$1FFD  '
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 2
          Text = '00000000'
          OnMouseEnter = FormMouseEnter
        end
        object lblPorts3FFD: TLabeledEdit
          Left = 70
          Top = 96
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 56
          EditLabel.Height = 16
          EditLabel.Caption = '$3FFD  '
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 3
          Text = '$00'
          OnMouseEnter = FormMouseEnter
        end
        object lblPortsBFFD: TLabeledEdit
          Left = 70
          Top = 112
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 56
          EditLabel.Height = 16
          EditLabel.Caption = '$BFFD  '
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 4
          Text = '$00'
          OnMouseEnter = FormMouseEnter
        end
        object lblPortsFFFD: TLabeledEdit
          Left = 70
          Top = 128
          Width = 64
          Height = 16
          BorderStyle = bsNone
          Color = clWhite
          EditLabel.Width = 56
          EditLabel.Height = 16
          EditLabel.Caption = '$FFFD  '
          LabelPosition = lpLeft
          ReadOnly = True
          TabOrder = 5
          Text = '$00'
          OnMouseEnter = FormMouseEnter
        end
      end
    end
  end
  object panButtons: TPanel
    Left = 247
    Top = 38
    Width = 43
    Height = 22
    BevelOuter = bvNone
    TabOrder = 3
    OnMouseEnter = FormMouseEnter
    object btnCollapse: TSpeedButton
      Left = 43
      Top = 0
      Width = 24
      Height = 21
      AllowAllUp = True
      GroupIndex = 1
      Down = True
      Flat = True
      Glyph.Data = {
        A2010000424DA2010000000000003600000028000000090000000D0000000100
        1800000000006C010000C40E0000C40E00000000000000000000DC00FFDC00FF
        DC00FFE4E4E4202020E4E4E4DC00FFDC00FFDC00FFFFDC00FFDC00FFDC00FF6F
        6F6F3030306F6F6FDC00FFDC00FFDC00FFFFDC00FFDC00FFE4E4E4202020EFEF
        EF202020E4E4E4DC00FFDC00FFFFDC00FFDC00FF6F6F6F8F8F8FFFFFFF8F8F8F
        6F6F6FDC00FFDC00FFFFDC00FFE4E4E4202020F7F7F7FFFFFFF7F7F7202020E4
        E4E4DC00FFFFDC00FF6F6F6F8F8F8FFFFFFFFFFFFFFFFFFF8F8F8F6F6F6FDC00
        FFFFE4E4E4202020F7F7F7FFFFFFFFFFFFFFFFFFF7F7F7202020E4E4E4FF6F6F
        6F8F8F8FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF8F8F8F6F6F6FFF383838000000
        000000000000000000000000000000000000383838FFDC00FFDC00FFDC00FFDC
        00FFDC00FFDC00FFDC00FFDC00FFDC00FFFF0000000000000000000000000000
        00000000000000000000000000FF000000FFFFFF000000FFFFFF000000FFFFFF
        000000FFFFFF000000FF00000000000000000000000000000000000000000000
        0000000000FF}
      Visible = False
      OnClick = btnCollapseClick
      OnMouseEnter = FormMouseEnter
    end
  end
  object panSpeed: TPanel
    Left = 0
    Top = 0
    Width = 286
    Height = 111
    Align = alTop
    BevelOuter = bvNone
    Color = clWhite
    Padding.Bottom = 8
    ParentBackground = False
    TabOrder = 4
    object GroupBox1: TGroupBox
      Left = 0
      Top = 0
      Width = 286
      Height = 40
      Align = alTop
      Caption = ' Speed '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      object rad1pc: TRadioButton
        Left = 23
        Top = 16
        Width = 41
        Height = 17
        Caption = '1%'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = rad100pcClick
      end
      object rad10pc: TRadioButton
        Tag = 1
        Left = 68
        Top = 16
        Width = 41
        Height = 17
        Caption = '10%'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = rad100pcClick
      end
      object rad25pc: TRadioButton
        Tag = 2
        Left = 115
        Top = 16
        Width = 41
        Height = 16
        Caption = '25%'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = rad100pcClick
      end
      object rad50pc: TRadioButton
        Tag = 3
        Left = 162
        Top = 16
        Width = 41
        Height = 17
        Caption = '50%'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnClick = rad100pcClick
      end
      object rad100pc: TRadioButton
        Tag = 4
        Left = 209
        Top = 16
        Width = 51
        Height = 17
        Caption = '100%'
        Checked = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        TabStop = True
        OnClick = rad100pcClick
      end
    end
    object GroupBox2: TGroupBox
      Left = 0
      Top = 40
      Width = 286
      Height = 65
      Align = alTop
      Caption = ' Numerical Format '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      object Panel1: TPanel
        Left = 2
        Top = 15
        Width = 282
        Height = 24
        Align = alTop
        BevelOuter = bvNone
        Color = clWhite
        ParentBackground = False
        TabOrder = 0
        object radHex: TRadioButton
          Left = 113
          Top = 2
          Width = 102
          Height = 17
          Caption = 'Hexidecimal'
          Checked = True
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          TabStop = True
          OnClick = btnHexClick
        end
        object radDecimal: TRadioButton
          Left = 21
          Top = 2
          Width = 70
          Height = 17
          Caption = 'Decimal'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          OnClick = btnHexClick
        end
      end
      object Panel2: TPanel
        Left = 2
        Top = 39
        Width = 282
        Height = 18
        Align = alTop
        BevelOuter = bvNone
        Color = clWhite
        ParentBackground = False
        TabOrder = 1
        object rad16bit: TRadioButton
          Left = 113
          Top = 1
          Width = 102
          Height = 19
          Caption = '16 Bit'
          Checked = True
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          TabStop = True
          OnClick = rad8bitClick
        end
        object rad8bit: TRadioButton
          Left = 21
          Top = 2
          Width = 70
          Height = 17
          Caption = '8 Bit'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          OnClick = rad8bitClick
        end
      end
    end
  end
  object imgDebugView: TImageList
    Left = 108
    Top = 120
    Bitmap = {
      494C010103000800100010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000001000000001002000000000000010
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000084840000FFFF000084840000FFFF000084840000FFFF00008484000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00008F6F1C008F6F1C008F6F1C0000000000000000008F6F1C008F6F1C008F6F
      1C008F6F1C008F6F1C00000000000000000000000000000000000084840000FF
      FF000084840000FFFF00FFFFFF0000000000FFFFFF0000FFFF000084840000FF
      FF00008484000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008F6F
      1C00000000000000000000000000000000008F6F1C00FFE49E00FFE49E00FFE4
      9E00FFE49E00FFE49E008F6F1C00000000000000000000FFFF000084840000FF
      FF00FFFFFF000000000000000000000000000000000000000000FFFFFF0000FF
      FF000084840000FFFF000000000000000000000000000000000000000000FF26
      000000000000000000000000000000000000FF26000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008F6F
      1C00000000000000000000000000000000000000000017941A0017941A001794
      1A0017941A0017941A0000000000000000000000000000FFFF00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF0000FFFF0000000000000000000000000000000000FF2600000000
      00000000000000000000000000000000000000000000FF260000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000008F6F1C008F6F1C008F6F
      1C008F6F1C008F6F1C00000000000000000017941A0041DB450041DB450041DB
      450041DB450041DB450017941A00000000000000000000000000000000000000
      0000000000000000000084000000840000008400000000000000000000000000
      00000000000000000000000000000000000000000000FF260000000000000000
      0000FF9400000000000000000000FF9400000000000000000000FF2600000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000008F6F1C008F6F
      1C008F6F1C0000000000000000000000000041DB450017941A0017941A001794
      1A0017941A0017941A0041DB4500000000008484840000000000000000000000
      0000840000008400000000000000000000000000000084000000840000000000
      000000000000000000008484840000000000FF2600000000000000000000FF94
      000000000000000000000000000000000000FF9400000000000000000000FF26
      0000000000003333330000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008F6F
      1C000000000000000000000000000000000017941A00FFE49E00FFE49E00FFE4
      9E00FFE49E00FFE49E0017941A00000000008484840000000000840000008400
      0000000000000000000084848400848484008484840000000000000000008400
      000084000000000000008484840000000000FF26000000000000FF9400000000
      00000000000000000000000000000000000000000000FF94000000000000FF26
      0000000000003333330033333300000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000008F6F1C008F6F1C008F6F
      1C008F6F1C008F6F1C0000000000000000000000000084848400000000000000
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF00000000
      000000000000848484000000000000000000FF26000000000000FF9400000000
      0000000000000000000033333300333333003333330033333300333333003333
      3300333333003333330033333300333333000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000373737003737
      3700373737003737370037373700000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FF26000000000000FF9400000000
      00000000000000000000000000000000000000000000FF94000000000000FF26
      0000000000003333330033333300000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000037373700C7C8CE00C7C8
      CE00C7C8CE00C7C8CE00C7C8CE00373737000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FF2600000000000000000000FF94
      000000000000000000000000000000000000FF9400000000000000000000FF26
      0000000000003333330000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000373737003737
      3700373737003737370037373700000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF260000000000000000
      0000FF9400000000000000000000FF9400000000000000000000FF2600000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000037373700C7C8CE00C7C8
      CE00C7C8CE00C7C8CE00C7C8CE00373737000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FF2600000000
      00000000000000000000000000000000000000000000FF260000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000373737003737
      3700373737003737370037373700000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FF26
      000000000000000000000000000000000000FF26000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF00FFFFF01FFFFF0000FFFFC007FFFF0000
      F1830001FFFF0000EF010001EF7F0000EF830001DFBF000083010001B6DF0000
      C70100016F6B0000EF0100015FA90000FF8380035C000000C1FFF01F5FA90000
      80FFFFFF6F6B0000C1FF888FB6DF000080FFDBEFDFBF0000C1FFD8CFEF7F0000
      FFFF9EEFFFFF0000FFFFD88FFFFF000000000000000000000000000000000000
      000000000000}
  end
end
