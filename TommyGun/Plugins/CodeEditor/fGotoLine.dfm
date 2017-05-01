object frmGotoLine: TfrmGotoLine
  Left = 1298
  Top = 451
  ActiveControl = edtLineNumber
  AlphaBlendValue = 200
  BorderStyle = bsDialog
  Caption = 'Goto Line Number'
  ClientHeight = 89
  ClientWidth = 257
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
    257
    89)
  PixelsPerInch = 96
  TextHeight = 13
  object lblEnterNewLineNumber: TLabel
    Left = 8
    Top = 20
    Width = 107
    Height = 13
    Caption = 'Enter new line number'
  end
  object cmdOK: TButton
    Left = 83
    Top = 57
    Width = 80
    Height = 24
    Anchors = [akRight, akBottom]
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object cmdCancel: TButton
    Left = 169
    Top = 57
    Width = 80
    Height = 24
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object edtLineNumber: TEdit
    Left = 121
    Top = 17
    Width = 128
    Height = 21
    Color = clWhite
    TabOrder = 2
    Text = '1'
    OnChange = edtLineNumberChange
  end
end
