object frmBreakpointProperties: TfrmBreakpointProperties
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Breakpoint Properties'
  ClientHeight = 134
  ClientWidth = 271
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  DesignSize = (
    271
    134)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 12
    Width = 11
    Height = 13
    Anchors = [akLeft, akTop, akRight]
    Caption = 'File'
    ExplicitWidth = 16
  end
  object Label2: TLabel
    Left = 8
    Top = 40
    Width = 19
    Height = 13
    Caption = 'Line'
  end
  object Label3: TLabel
    Left = 8
    Top = 67
    Width = 54
    Height = 13
    Caption = 'Pass Count'
  end
  object btnCancel: TButton
    Left = 188
    Top = 101
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 0
    ExplicitLeft = 193
    ExplicitTop = 115
  end
  object btnOk: TButton
    Left = 107
    Top = 101
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 1
    ExplicitLeft = 112
    ExplicitTop = 115
  end
  object cmbFiles: TComboBox
    Left = 68
    Top = 9
    Width = 195
    Height = 21
    Style = csDropDownList
    Anchors = [akLeft, akTop, akRight]
    ItemHeight = 13
    TabOrder = 2
    OnChange = cmbFilesChange
  end
  object spnLine: KSpinEdit
    Left = 68
    Top = 36
    Width = 195
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    BevelOuter = bvLowered
    Caption = '2'
    Color = clWhite
    ParentBackground = False
    TabOrder = 3
    DesignSize = (
      195
      21)
  end
  object spnPassCount: KSpinEdit
    Left = 68
    Top = 63
    Width = 195
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    BevelOuter = bvLowered
    Color = clWhite
    ParentBackground = False
    TabOrder = 4
    Max = 10000
    DesignSize = (
      195
      21)
  end
end
