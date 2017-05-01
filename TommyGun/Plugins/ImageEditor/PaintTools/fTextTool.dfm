object frmTextDialog: TfrmTextDialog
  Left = 726
  Top = 69
  Caption = 'Text Entry'
  ClientHeight = 413
  ClientWidth = 482
  Color = clWhite
  Constraints.MinHeight = 368
  Constraints.MinWidth = 432
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  DesignSize = (
    482
    413)
  PixelsPerInch = 96
  TextHeight = 13
  object grpFont: TGroupBox
    Left = 8
    Top = 8
    Width = 466
    Height = 117
    Anchors = [akLeft, akTop, akRight]
    Caption = ' Text '
    TabOrder = 0
    DesignSize = (
      466
      117)
    object lblFont: TLabel
      Left = 12
      Top = 44
      Width = 21
      Height = 13
      Caption = 'Font'
    end
    object lblFontName: TLabel
      Left = 48
      Top = 44
      Width = 3
      Height = 13
    end
    object lblSize: TLabel
      Left = 12
      Top = 64
      Width = 20
      Height = 13
      Caption = 'Size'
    end
    object lblSample: TLabel
      Left = 172
      Top = 44
      Width = 35
      Height = 13
      Caption = 'Sample'
    end
    object lblFontSample: TLabel
      Left = 172
      Top = 60
      Width = 90
      Height = 13
      Caption = 'AbBbCc ... XxYyZz'
    end
    object lblFontSize: TLabel
      Left = 48
      Top = 64
      Width = 3
      Height = 13
    end
    object edtText: TEdit
      Left = 8
      Top = 20
      Width = 449
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      Color = clWhite
      TabOrder = 0
      OnChange = slrMagnificationChange
    end
    object cmdFont: TButton
      Left = 8
      Top = 84
      Width = 80
      Height = 24
      Caption = 'Font...'
      TabOrder = 1
      OnClick = cmdFontClick
    end
  end
  object grpPreview: TGroupBox
    Left = 8
    Top = 131
    Width = 466
    Height = 244
    Anchors = [akLeft, akTop, akRight, akBottom]
    Caption = ' Preview '
    TabOrder = 1
    DesignSize = (
      466
      244)
    object lblMagnification: TLabel
      Left = 10
      Top = 16
      Width = 63
      Height = 13
      Caption = 'Magnification'
    end
    object slrMagnification: KSlider
      Left = 4
      Top = 37
      Width = 201
      Height = 16
      Cursor = crArrow
      ColorBackground = clWhite
      ColorShadow = clSilver
      ColorCursorShadow = clSilver
      Position = 1
      Min = 1
      Max = 32
      Flat = True
      OnChange = slrMagnificationChange
    end
    object edtMagnification: KSpinEdit
      Left = 148
      Top = 13
      Width = 52
      Height = 20
      BevelOuter = bvLowered
      ParentColor = True
      TabOrder = 2
      Value = 1
      Min = 1
      Max = 32
      OnChanged = edtMagnificationChange
      DesignSize = (
        52
        20)
    end
    object sbxImagePreview: TScrollBox
      Left = 8
      Top = 52
      Width = 449
      Height = 184
      HorzScrollBar.Smooth = True
      HorzScrollBar.Style = ssFlat
      HorzScrollBar.Tracking = True
      VertScrollBar.Smooth = True
      VertScrollBar.Style = ssFlat
      VertScrollBar.Tracking = True
      Anchors = [akLeft, akTop, akRight, akBottom]
      TabOrder = 1
      object imgPreview: TImage
        Left = 0
        Top = 0
        Width = 32
        Height = 32
      end
    end
    object chkAutoUpdate: TCheckBox
      Left = 236
      Top = 16
      Width = 149
      Height = 17
      Caption = 'Update Preview Window'
      Checked = True
      State = cbChecked
      TabOrder = 0
      OnClick = chkAutoUpdateClick
    end
  end
  object cmdOK: TButton
    Left = 308
    Top = 381
    Width = 80
    Height = 24
    Anchors = [akRight, akBottom]
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 2
  end
  object cmdCancel: TButton
    Left = 394
    Top = 381
    Width = 80
    Height = 24
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 3
  end
  object dlgFont: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Options = [fdEffects, fdApplyButton]
    OnApply = dlgFontApply
    Left = 56
    Top = 52
  end
end
