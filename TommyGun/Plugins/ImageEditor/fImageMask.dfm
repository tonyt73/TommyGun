object frmImageMask: TfrmImageMask
  Left = 281
  Top = 206
  ActiveControl = radBorderStyleNone
  BorderStyle = bsDialog
  Caption = 'Generate Image Mask'
  ClientHeight = 134
  ClientWidth = 398
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  DesignSize = (
    398
    134)
  PixelsPerInch = 96
  TextHeight = 16
  object grpBorderStyle: TGroupBox
    Left = 10
    Top = 10
    Width = 378
    Height = 70
    Anchors = [akLeft, akTop, akRight]
    Caption = 'Mask Border Style'
    TabOrder = 0
    object imgNone: TImage
      Left = 20
      Top = 30
      Width = 16
      Height = 16
      AutoSize = True
      Picture.Data = {
        07544269746D6170F6000000424DF60000000000000076000000280000001000
        000010000000010004000000000080000000120B0000120B0000100000001000
        000000000000000080000080000000808000800000008000800080800000C0C0
        C000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
        FF00DDDDDDDDDDDDDDDDD8DDD8DDD8DDD8DD888888888888888DD8DDD8DDD8DD
        D8DDD8DDD8DDD8DDD8DDD8DDD8DDD8DDD8DD888888888888888DD8DDD89998DD
        D8DDD8DDD89998DDD8DDD8DDD89998DDD8DD888888888888888DD8DDD8DDD8DD
        D8DDD8DDD8DDD8DDD8DDD8DDD8DDD8DDD8DD888888888888888DD8DDD8DDD8DD
        D8DD}
      Transparent = True
    end
    object imgStar: TImage
      Left = 143
      Top = 30
      Width = 16
      Height = 16
      AutoSize = True
      Picture.Data = {
        07544269746D6170F6000000424DF60000000000000076000000280000001000
        000010000000010004000000000080000000120B0000120B0000100000001000
        000000000000000080000080000000808000800000008000800080800000C0C0
        C000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
        FF00DDDDDDDDDDDDDDDDD8DDD8DDD8DDD8DD888888888888888DD8DDD80008DD
        D8DDD8DDD80008DDD8DDD8DDD80008DDD8DD888888888888888DD80008999800
        08DDD8000899980008DDD8000899980008DD888888888888888DD8DDD80008DD
        D8DDD8DDD80008DDD8DDD8DDD80008DDD8DD888888888888888DD8DDD8DDD8DD
        D8DD}
      Transparent = True
    end
    object imgSquare: TImage
      Left = 261
      Top = 30
      Width = 16
      Height = 16
      AutoSize = True
      Picture.Data = {
        07544269746D6170F6000000424DF60000000000000076000000280000001000
        000010000000010004000000000080000000120B0000120B0000100000001000
        000000000000000080000080000000808000800000008000800080800000C0C0
        C000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
        FF00DDDDDDDDDDDDDDDDD8DDD8DDD8DDD8DD888888888888888DD80008000800
        08DDD8000800080008DDD8000800080008DD888888888888888DD80008999800
        08DDD8000899980008DDD8000899980008DD888888888888888DD80008000800
        08DDD8000800080008DDD8000800080008DD888888888888888DD8DDD8DDD8DD
        D8DD}
      Transparent = True
    end
    object radBorderStyleStar: TRadioButton
      Left = 167
      Top = 30
      Width = 61
      Height = 20
      Caption = 'Star'
      TabOrder = 0
      OnClick = radBorderStyleStarClick
    end
    object radBorderStyleNone: TRadioButton
      Left = 44
      Top = 30
      Width = 66
      Height = 20
      Caption = 'None'
      Checked = True
      TabOrder = 1
      TabStop = True
      OnClick = radBorderStyleNoneClick
    end
    object radBorderStyleSquare: TRadioButton
      Left = 286
      Top = 30
      Width = 75
      Height = 20
      Caption = 'Square'
      TabOrder = 2
      OnClick = radBorderStyleSquareClick
    end
  end
  object grpColour: TGroupBox
    Left = 10
    Top = 87
    Width = 378
    Height = 58
    Anchors = [akLeft, akTop, akRight]
    Caption = 'Background Colour'
    TabOrder = 1
    Visible = False
  end
  object cmdOk: TButton
    Left = 183
    Top = 94
    Width = 99
    Height = 30
    Anchors = [akRight, akBottom]
    Caption = '&Ok'
    ModalResult = 1
    TabOrder = 2
  end
  object cmdCancel: TButton
    Left = 289
    Top = 94
    Width = 99
    Height = 30
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = '&Cancel'
    Default = True
    ModalResult = 2
    TabOrder = 3
  end
end
