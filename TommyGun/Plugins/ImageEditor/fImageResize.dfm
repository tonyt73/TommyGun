object frmImageResize: TfrmImageResize
  Left = 1107
  Top = 348
  ActiveControl = radHLeft
  BorderStyle = bsDialog
  Caption = 'Resize Image'
  ClientHeight = 462
  ClientWidth = 448
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  DesignSize = (
    448
    462)
  PixelsPerInch = 96
  TextHeight = 13
  object grpDimensions: TGroupBox
    Left = 8
    Top = 8
    Width = 434
    Height = 129
    Anchors = [akLeft, akTop, akRight]
    Caption = 'Dimensions'
    TabOrder = 0
    object lblNewWidth: TLabel
      Left = 88
      Top = 20
      Width = 52
      Height = 13
      Caption = 'New Width'
    end
    object lblNewHeight: TLabel
      Left = 88
      Top = 48
      Width = 55
      Height = 13
      Caption = 'New Height'
    end
    object lblCurrWidth: TLabel
      Left = 88
      Top = 76
      Width = 68
      Height = 13
      Caption = 'Current Width'
    end
    object lblCurrHeight: TLabel
      Left = 88
      Top = 108
      Width = 71
      Height = 13
      Caption = 'Current Height'
    end
    object lblCurrentWidth: TLabel
      Left = 164
      Top = 76
      Width = 24
      Height = 13
      Caption = '0000'
    end
    object lblCurrentHeight: TLabel
      Left = 164
      Top = 108
      Width = 24
      Height = 13
      Caption = '0000'
    end
    object lblNewImageDimension: TLabel
      Left = 288
      Top = 32
      Width = 107
      Height = 13
      Caption = 'New image dimensions'
    end
    object lblExistingImageDimension: TLabel
      Left = 288
      Top = 92
      Width = 123
      Height = 13
      Caption = 'Existing image dimensions'
    end
    object edtNewWidth: KSpinEdit
      Left = 164
      Top = 16
      Width = 69
      Height = 20
      BevelOuter = bvLowered
      Color = clWhite
      TabOrder = 0
      Value = 8
      Min = 8
      Max = 1024
      OnChanged = radHLeftClick
      DesignSize = (
        69
        20)
    end
    object edtNewHeight: KSpinEdit
      Left = 164
      Top = 40
      Width = 69
      Height = 20
      BevelOuter = bvLowered
      Color = clWhite
      TabOrder = 1
      Value = 1
      Min = 1
      Max = 1024
      OnChanged = radHLeftClick
      DesignSize = (
        69
        20)
    end
    object panNewIndicator: TPanel
      Left = 264
      Top = 14
      Width = 8
      Height = 48
      Color = clBlue
      ParentBackground = False
      TabOrder = 2
    end
    object panCurIndicator: TPanel
      Left = 264
      Top = 74
      Width = 8
      Height = 48
      Color = clRed
      ParentBackground = False
      TabOrder = 3
    end
  end
  object grpImagePlacement: TGroupBox
    Left = 8
    Top = 144
    Width = 434
    Height = 277
    Anchors = [akLeft, akTop, akRight]
    Caption = 'Image Placement'
    TabOrder = 1
    object grpHorizontalAlignment: TGroupBox
      Left = 12
      Top = 20
      Width = 188
      Height = 124
      Caption = 'Horizontal Alignment'
      TabOrder = 0
      object lblLeft: TLabel
        Left = 26
        Top = 72
        Width = 19
        Height = 13
        Caption = 'Left'
        Enabled = False
      end
      object lblRight: TLabel
        Left = 26
        Top = 100
        Width = 25
        Height = 13
        Caption = 'Right'
        Enabled = False
      end
      object edtLeft: KSpinEdit
        Left = 68
        Top = 68
        Width = 69
        Height = 20
        BevelOuter = bvLowered
        Color = clWhite
        Enabled = False
        TabOrder = 0
        Max = 0
        OnChanged = edtLeftChange
        DesignSize = (
          69
          20)
      end
      object edtRight: KSpinEdit
        Left = 68
        Top = 96
        Width = 69
        Height = 20
        BevelOuter = bvLowered
        Color = clWhite
        Enabled = False
        TabOrder = 1
        Max = 0
        OnChanged = edtRightChange
        DesignSize = (
          69
          20)
      end
      object radHLeft: TRadioButton
        Left = 8
        Top = 20
        Width = 52
        Height = 17
        Caption = 'Left'
        Checked = True
        TabOrder = 2
        TabStop = True
        OnClick = radHLeftClick
      end
      object radHCentre: TRadioButton
        Left = 60
        Top = 20
        Width = 52
        Height = 17
        Caption = 'Centre'
        TabOrder = 3
        OnClick = radHLeftClick
      end
      object radHRight: TRadioButton
        Left = 120
        Top = 20
        Width = 52
        Height = 17
        Caption = 'Right'
        TabOrder = 4
        OnClick = radHLeftClick
      end
      object radHCustom: TRadioButton
        Left = 8
        Top = 44
        Width = 65
        Height = 17
        Caption = 'Custom'
        TabOrder = 5
        OnClick = radHLeftClick
      end
    end
    object grpVerticalAlignment: TGroupBox
      Left = 12
      Top = 148
      Width = 188
      Height = 124
      Caption = 'Vertical Alignment'
      TabOrder = 1
      object lblTop: TLabel
        Left = 26
        Top = 72
        Width = 18
        Height = 13
        Caption = 'Top'
        Enabled = False
      end
      object lblBottom: TLabel
        Left = 26
        Top = 100
        Width = 34
        Height = 13
        Caption = 'Bottom'
        Enabled = False
      end
      object edtTop: KSpinEdit
        Left = 68
        Top = 68
        Width = 69
        Height = 20
        BevelOuter = bvLowered
        Color = clWhite
        Enabled = False
        TabOrder = 0
        Max = 0
        OnChanged = edtTopChange
        DesignSize = (
          69
          20)
      end
      object edtBottom: KSpinEdit
        Left = 68
        Top = 94
        Width = 69
        Height = 20
        BevelOuter = bvLowered
        Color = clWhite
        Enabled = False
        TabOrder = 1
        Max = 0
        OnChanged = edtBottomChange
        DesignSize = (
          69
          20)
      end
      object radVTop: TRadioButton
        Left = 8
        Top = 20
        Width = 52
        Height = 17
        Caption = 'Top'
        Checked = True
        TabOrder = 2
        TabStop = True
        OnClick = radHLeftClick
      end
      object radVCentre: TRadioButton
        Left = 60
        Top = 20
        Width = 52
        Height = 17
        Caption = 'Centre'
        TabOrder = 3
        OnClick = radHLeftClick
      end
      object radVBottom: TRadioButton
        Left = 120
        Top = 20
        Width = 52
        Height = 17
        Caption = 'Bottom'
        TabOrder = 4
        OnClick = radHLeftClick
      end
      object radVCustom: TRadioButton
        Left = 8
        Top = 44
        Width = 65
        Height = 17
        Caption = 'Custom'
        TabOrder = 5
        OnClick = radHLeftClick
      end
    end
    object grpImageRelationship: TGroupBox
      Left = 208
      Top = 20
      Width = 220
      Height = 252
      Caption = 'Image Placement Relationship'
      TabOrder = 2
      object lblNote: TLabel
        Left = 12
        Top = 216
        Width = 197
        Height = 33
        AutoSize = False
        Caption = 
          'note: Aspect ratios are ignored. Diagram shows relationship betw' +
          'een the existing (red) image the new (blue) image.'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -9
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        WordWrap = True
      end
      object panExampleArea: TPanel
        Left = 11
        Top = 19
        Width = 198
        Height = 198
        Color = clWhite
        TabOrder = 0
        object panBotBox: TPanel
          Left = 66
          Top = 66
          Width = 66
          Height = 66
          Color = clRed
          ParentBackground = False
          TabOrder = 1
        end
        object panTopBox: TPanel
          Left = 65
          Top = 65
          Width = 33
          Height = 33
          Color = clBlue
          ParentBackground = False
          TabOrder = 0
        end
      end
    end
  end
  object cmdOk: TButton
    Left = 274
    Top = 430
    Width = 80
    Height = 24
    Anchors = [akRight, akBottom]
    Caption = '&Ok'
    ModalResult = 1
    TabOrder = 2
  end
  object cmdCancel: TButton
    Left = 360
    Top = 430
    Width = 80
    Height = 24
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = '&Cancel'
    Default = True
    ModalResult = 2
    TabOrder = 3
  end
end
