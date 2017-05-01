object frmSearching: TfrmSearching
  Left = 1123
  Top = 135
  BorderStyle = bsDialog
  Caption = 'Searching'
  ClientHeight = 109
  ClientWidth = 401
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poMainFormCenter
  DesignSize = (
    401
    109)
  PixelsPerInch = 96
  TextHeight = 13
  object lblSearchText: TLabel
    Left = 8
    Top = 12
    Width = 389
    Height = 13
    Alignment = taCenter
    Anchors = [akLeft, akTop, akRight]
    AutoSize = False
    Caption = 'Text: '
  end
  object lblFile: TLabel
    Left = 4
    Top = 32
    Width = 393
    Height = 37
    Anchors = [akLeft, akTop, akRight]
    AutoSize = False
    Caption = 'File'
    WordWrap = True
  end
  object cmdClose: TButton
    Left = 164
    Top = 76
    Width = 80
    Height = 24
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 0
  end
end
