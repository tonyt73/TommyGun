object frmChangePalette: TfrmChangePalette
  Left = 304
  Top = 582
  BorderStyle = bsDialog
  Caption = 'Change Palette'
  ClientHeight = 101
  ClientWidth = 241
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  DesignSize = (
    241
    101)
  PixelsPerInch = 96
  TextHeight = 13
  object grpNewPaletteType: TGroupBox
    Left = 8
    Top = 8
    Width = 225
    Height = 53
    Anchors = [akLeft, akTop, akRight]
    Caption = 'New Palette Type'
    TabOrder = 0
    DesignSize = (
      225
      53)
    object cmbPalettes: TComboBox
      Left = 9
      Top = 21
      Width = 208
      Height = 21
      Style = csDropDownList
      Anchors = [akLeft, akTop, akRight]
      Color = clWhite
      ItemHeight = 13
      TabOrder = 0
    end
  end
  object cmdCancel: TButton
    Left = 153
    Top = 69
    Width = 80
    Height = 24
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = '&Cancel'
    Default = True
    ModalResult = 2
    TabOrder = 1
  end
  object cmdOk: TButton
    Left = 67
    Top = 69
    Width = 80
    Height = 24
    Anchors = [akRight, akBottom]
    Caption = '&Ok'
    ModalResult = 1
    TabOrder = 2
  end
end
