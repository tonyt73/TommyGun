object dlgAmstradColors: TdlgAmstradColors
  Left = 529
  Top = 186
  BorderStyle = bsDialog
  Caption = 'Colours'
  ClientHeight = 349
  ClientWidth = 321
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  DesignSize = (
    321
    349)
  PixelsPerInch = 96
  TextHeight = 13
  object panButtons: TPanel
    Left = 0
    Top = 311
    Width = 321
    Height = 38
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      321
      38)
    object bvlButtons: TBevel
      Left = 0
      Top = 0
      Width = 321
      Height = 2
      Align = alTop
    end
    object cmdCancel: TButton
      Left = 234
      Top = 8
      Width = 80
      Height = 24
      Anchors = [akTop, akRight]
      Cancel = True
      Caption = '&Cancel'
      ModalResult = 2
      TabOrder = 0
    end
    object cmdOK: TButton
      Left = 150
      Top = 8
      Width = 80
      Height = 24
      Anchors = [akTop, akRight]
      Caption = '&OK'
      Default = True
      ModalResult = 1
      TabOrder = 1
    end
  end
  object Panel1: TPanel
    Left = 4
    Top = 44
    Width = 312
    Height = 261
    Anchors = [akLeft, akTop, akRight, akBottom]
    BevelOuter = bvNone
    Caption = 'Panel1'
    TabOrder = 1
    object PageControl1: TPageControl
      Left = 0
      Top = 0
      Width = 312
      Height = 261
      ActivePage = TabSheet4
      Align = alClient
      Style = tsFlatButtons
      TabIndex = 0
      TabOrder = 0
      object TabSheet4: TTabSheet
        Caption = 'Manual'
        object Panel78: TPanel
          Tag = 2
          Left = 0
          Top = 40
          Width = 96
          Height = 20
          Caption = 'Blue'
          Color = clNavy
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          OnClick = panC64BlackClick
        end
        object Panel79: TPanel
          Tag = 8
          Left = 0
          Top = 184
          Width = 96
          Height = 20
          Caption = 'Purple'
          Color = 8388863
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          OnClick = panC64BlackClick
        end
        object Panel80: TPanel
          Tag = 7
          Left = 0
          Top = 160
          Width = 96
          Height = 20
          Caption = 'Bright Red'
          Color = clRed
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          OnClick = panC64BlackClick
        end
        object Panel81: TPanel
          Tag = 14
          Left = 100
          Top = 112
          Width = 96
          Height = 20
          Caption = 'White'
          Color = clGray
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
          OnClick = panC64BlackClick
        end
        object Panel84: TPanel
          Tag = 9
          Left = 0
          Top = 208
          Width = 96
          Height = 20
          Caption = 'Bright Magenta'
          Color = clFuchsia
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
          OnClick = panC64BlackClick
        end
        object Panel85: TPanel
          Tag = 20
          Left = 200
          Top = 40
          Width = 96
          Height = 20
          Caption = 'Sea Green'
          Color = 8453888
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 5
          OnClick = panC64BlackClick
        end
        object Panel86: TPanel
          Tag = 11
          Left = 100
          Top = 40
          Width = 96
          Height = 20
          Caption = 'Cyan'
          Color = clTeal
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 6
          OnClick = panC64BlackClick
        end
        object Panel87: TPanel
          Tag = 25
          Left = 200
          Top = 160
          Width = 96
          Height = 20
          Caption = 'Bright Yellow'
          Color = clYellow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 7
          OnClick = panC64BlackClick
        end
        object Panel88: TPanel
          Tag = 16
          Left = 100
          Top = 160
          Width = 96
          Height = 20
          Caption = 'Orange'
          Color = 33023
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 8
          OnClick = panC64BlackClick
        end
        object Panel89: TPanel
          Tag = 26
          Left = 200
          Top = 184
          Width = 96
          Height = 20
          Caption = 'Pastel Yellow'
          Color = 8454143
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 9
          OnClick = panC64BlackClick
        end
        object Panel90: TPanel
          Tag = 17
          Left = 100
          Top = 184
          Width = 96
          Height = 20
          Caption = 'Pink'
          Color = 8421631
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 10
          OnClick = panC64BlackClick
        end
        object Panel91: TPanel
          Tag = 27
          Left = 200
          Top = 208
          Width = 96
          Height = 20
          Caption = 'Bright White'
          Color = clWhite
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 11
          OnClick = panC64BlackClick
        end
        object Panel92: TPanel
          Tag = 18
          Left = 100
          Top = 208
          Width = 96
          Height = 20
          Caption = 'Pastel Magenta'
          Color = 16744703
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 12
          OnClick = panC64BlackClick
        end
        object Panel94: TPanel
          Tag = 1
          Left = 0
          Top = 16
          Width = 96
          Height = 20
          Caption = 'Black'
          Color = clBlack
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 13
          OnClick = panC64BlackClick
        end
        object Panel95: TPanel
          Tag = 5
          Left = 0
          Top = 112
          Width = 96
          Height = 20
          Caption = 'Magenta'
          Color = clPurple
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 14
          OnClick = panC64BlackClick
        end
        object Panel96: TPanel
          Tag = 4
          Left = 0
          Top = 88
          Width = 96
          Height = 20
          Caption = 'Red'
          Color = clMaroon
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 15
          OnClick = panC64BlackClick
        end
        object Panel98: TPanel
          Tag = 3
          Left = 0
          Top = 64
          Width = 96
          Height = 20
          Caption = 'Bright Blue'
          Color = clBlue
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 16
          OnClick = panC64BlackClick
        end
        object Panel99: TPanel
          Tag = 23
          Left = 200
          Top = 112
          Width = 96
          Height = 20
          Caption = 'Pastel Green'
          Color = 8454016
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 17
          OnClick = panC64BlackClick
        end
        object Panel100: TPanel
          Tag = 6
          Left = 0
          Top = 136
          Width = 96
          Height = 20
          Caption = 'Mauve'
          Color = 16711808
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 18
          OnClick = panC64BlackClick
        end
        object Panel101: TPanel
          Tag = 19
          Left = 200
          Top = 16
          Width = 96
          Height = 20
          Caption = 'Bright Green'
          Color = clLime
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 19
          OnClick = panC64BlackClick
        end
        object Panel102: TPanel
          Tag = 10
          Left = 100
          Top = 16
          Width = 96
          Height = 20
          Caption = 'Green'
          Color = clGreen
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 20
          OnClick = panC64BlackClick
        end
        object Panel103: TPanel
          Tag = 22
          Left = 200
          Top = 88
          Width = 96
          Height = 20
          Caption = 'Lime Green'
          Color = 65408
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 21
          OnClick = panC64BlackClick
        end
        object Panel104: TPanel
          Tag = 13
          Left = 100
          Top = 88
          Width = 96
          Height = 20
          Caption = 'Yellow'
          Color = clOlive
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 22
          OnClick = panC64BlackClick
        end
        object Panel105: TPanel
          Tag = 21
          Left = 200
          Top = 64
          Width = 96
          Height = 20
          Caption = 'Bright Cyan'
          Color = clAqua
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 23
          OnClick = panC64BlackClick
        end
        object Panel106: TPanel
          Tag = 12
          Left = 100
          Top = 64
          Width = 96
          Height = 20
          Caption = 'Sky Blue'
          Color = 16744448
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 24
          OnClick = panC64BlackClick
        end
        object Panel107: TPanel
          Tag = 24
          Left = 200
          Top = 136
          Width = 96
          Height = 20
          Caption = 'Pastel Cyan'
          Color = 16777088
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 25
          OnClick = panC64BlackClick
        end
        object Panel108: TPanel
          Tag = 15
          Left = 100
          Top = 136
          Width = 96
          Height = 20
          Caption = 'Pastel Blue'
          Color = 16744576
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 26
          OnClick = panC64BlackClick
        end
      end
      object TabSheet1: TTabSheet
        Caption = 'Hardware'
        object panC64Black: TPanel
          Tag = 14
          Left = 0
          Top = 16
          Width = 96
          Height = 20
          Caption = 'White'
          Color = clGray
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          OnClick = panC64BlackClick
        end
        object panC64White: TPanel
          Tag = 2
          Left = 0
          Top = 40
          Width = 96
          Height = 20
          Caption = 'Blue'
          Color = clNavy
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          OnClick = panC64BlackClick
        end
        object panC64Red: TPanel
          Tag = 8
          Left = 0
          Top = 64
          Width = 96
          Height = 20
          Caption = 'Purple'
          Color = 8388863
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          OnClick = panC64BlackClick
        end
        object panC64Cyan: TPanel
          Tag = 7
          Left = 0
          Top = 88
          Width = 96
          Height = 20
          Caption = 'Bright Red'
          Color = clRed
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
          OnClick = panC64BlackClick
        end
        object panC64Purple: TPanel
          Tag = 14
          Left = 100
          Top = 16
          Width = 96
          Height = 20
          Caption = 'White'
          Color = clGray
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
          OnClick = panC64BlackClick
        end
        object panC64Green: TPanel
          Tag = 8
          Left = 100
          Top = 40
          Width = 96
          Height = 20
          Caption = 'Purple'
          Color = 8388863
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 5
          OnClick = panC64BlackClick
        end
        object panC64Blue: TPanel
          Tag = 26
          Left = 100
          Top = 64
          Width = 96
          Height = 20
          Caption = 'Pastel Yellow'
          Color = 8454143
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 6
          OnClick = panC64BlackClick
        end
        object panC64Yellow: TPanel
          Tag = 9
          Left = 100
          Top = 88
          Width = 96
          Height = 20
          Caption = 'Bright Magenta'
          Color = clFuchsia
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 7
          OnClick = panC64BlackClick
        end
        object panC64Orange: TPanel
          Tag = 20
          Left = 200
          Top = 16
          Width = 96
          Height = 20
          Caption = 'Sea Green'
          Color = 8453888
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 8
          OnClick = panC64BlackClick
        end
        object panC64Brown: TPanel
          Tag = 11
          Left = 200
          Top = 40
          Width = 96
          Height = 20
          Caption = 'Cyan'
          Color = clTeal
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 9
          OnClick = panC64BlackClick
        end
        object panC64LtRed: TPanel
          Tag = 25
          Left = 200
          Top = 64
          Width = 96
          Height = 20
          Caption = 'Bright Yellow'
          Color = clYellow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 10
          OnClick = panC64BlackClick
        end
        object panC64DarkGray: TPanel
          Tag = 16
          Left = 200
          Top = 88
          Width = 96
          Height = 20
          Caption = 'Orange'
          Color = 33023
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 11
          OnClick = panC64BlackClick
        end
        object panC64MedGray: TPanel
          Tag = 26
          Left = 297
          Top = 16
          Width = 96
          Height = 20
          Caption = 'Pastel Yellow'
          Color = 8454143
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 12
          OnClick = panC64BlackClick
        end
        object panC64LtGreen: TPanel
          Tag = 17
          Left = 297
          Top = 40
          Width = 96
          Height = 20
          Caption = 'Pink'
          Color = 8421631
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 13
          OnClick = panC64BlackClick
        end
        object panC64LtBlue: TPanel
          Tag = 27
          Left = 297
          Top = 64
          Width = 96
          Height = 20
          Caption = 'Bright White'
          Color = clWhite
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 14
          OnClick = panC64BlackClick
        end
        object panC64LtGray: TPanel
          Tag = 18
          Left = 297
          Top = 88
          Width = 96
          Height = 20
          Caption = 'Pastel Magenta'
          Color = 16744703
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 15
          OnClick = panC64BlackClick
        end
        object Panel2: TPanel
          Tag = 2
          Left = 0
          Top = 112
          Width = 96
          Height = 20
          Caption = 'Blue'
          Color = clNavy
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 16
          OnClick = panC64BlackClick
        end
        object Panel3: TPanel
          Tag = 1
          Left = 0
          Top = 136
          Width = 96
          Height = 20
          Caption = 'Black'
          Color = clBlack
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 17
          OnClick = panC64BlackClick
        end
        object Panel4: TPanel
          Tag = 5
          Left = 0
          Top = 160
          Width = 96
          Height = 20
          Caption = 'Magenta'
          Color = clPurple
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 18
          OnClick = panC64BlackClick
        end
        object Panel5: TPanel
          Tag = 4
          Left = 0
          Top = 184
          Width = 96
          Height = 20
          Caption = 'Red'
          Color = clMaroon
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 19
          OnClick = panC64BlackClick
        end
        object Panel6: TPanel
          Tag = 20
          Left = 100
          Top = 112
          Width = 96
          Height = 20
          Caption = 'Sea Green'
          Color = 8453888
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 20
          OnClick = panC64BlackClick
        end
        object Panel7: TPanel
          Tag = 3
          Left = 100
          Top = 136
          Width = 96
          Height = 20
          Caption = 'Bright Blue'
          Color = clBlue
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 21
          OnClick = panC64BlackClick
        end
        object Panel8: TPanel
          Tag = 23
          Left = 100
          Top = 160
          Width = 96
          Height = 20
          Caption = 'Pastel Green'
          Color = 8454016
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 22
          OnClick = panC64BlackClick
        end
        object Panel9: TPanel
          Tag = 6
          Left = 100
          Top = 184
          Width = 96
          Height = 20
          Caption = 'Mauve'
          Color = 16711808
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 23
          OnClick = panC64BlackClick
        end
        object Panel10: TPanel
          Tag = 21
          Left = 200
          Top = 112
          Width = 96
          Height = 20
          Caption = 'Bright Green'
          Color = clLime
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 24
          OnClick = panC64BlackClick
        end
        object Panel11: TPanel
          Tag = 10
          Left = 200
          Top = 136
          Width = 96
          Height = 20
          Caption = 'Green'
          Color = clGreen
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 25
          OnClick = panC64BlackClick
        end
        object Panel12: TPanel
          Tag = 22
          Left = 200
          Top = 160
          Width = 96
          Height = 20
          Caption = 'Lime Green'
          Color = 65408
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 26
          OnClick = panC64BlackClick
        end
        object Panel13: TPanel
          Tag = 13
          Left = 200
          Top = 184
          Width = 96
          Height = 20
          Caption = 'Yellow'
          Color = clOlive
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 27
          OnClick = panC64BlackClick
        end
        object Panel14: TPanel
          Tag = 21
          Left = 297
          Top = 112
          Width = 96
          Height = 20
          Caption = 'Bright Cyan'
          Color = clAqua
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 28
          OnClick = panC64BlackClick
        end
        object Panel15: TPanel
          Tag = 12
          Left = 297
          Top = 136
          Width = 96
          Height = 20
          Caption = 'Sky Blue'
          Color = 16744448
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 29
          OnClick = panC64BlackClick
        end
        object Panel16: TPanel
          Tag = 23
          Left = 297
          Top = 160
          Width = 96
          Height = 20
          Caption = 'Pastel Cyan'
          Color = 16777088
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 30
          OnClick = panC64BlackClick
        end
        object Panel17: TPanel
          Tag = 15
          Left = 297
          Top = 184
          Width = 96
          Height = 20
          Caption = 'Pastel Blue'
          Color = 16744576
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 31
          OnClick = panC64BlackClick
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'RGB'
        ImageIndex = 1
        object Panel20: TPanel
          Tag = 14
          Left = 100
          Top = 160
          Width = 96
          Height = 20
          Caption = 'White'
          Color = clGray
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          OnClick = panC64BlackClick
        end
        object Panel22: TPanel
          Tag = 2
          Left = 0
          Top = 40
          Width = 96
          Height = 20
          Caption = 'Blue'
          Color = clNavy
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          OnClick = panC64BlackClick
        end
        object Panel34: TPanel
          Tag = 7
          Left = 200
          Top = 112
          Width = 96
          Height = 20
          Caption = 'Bright Red'
          Color = clRed
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          OnClick = panC64BlackClick
        end
        object Panel50: TPanel
          Tag = 8
          Left = 200
          Top = 136
          Width = 96
          Height = 20
          Caption = 'Purple'
          Color = 8388863
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
          OnClick = panC64BlackClick
        end
        object Panel52: TPanel
          Tag = 9
          Left = 200
          Top = 160
          Width = 96
          Height = 20
          Caption = 'Bright Magenta'
          Color = clFuchsia
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
          OnClick = panC64BlackClick
        end
        object Panel54: TPanel
          Tag = 11
          Left = 0
          Top = 112
          Width = 96
          Height = 20
          Caption = 'Cyan'
          Color = clTeal
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 5
          OnClick = panC64BlackClick
        end
        object Panel55: TPanel
          Tag = 25
          Left = 300
          Top = 88
          Width = 96
          Height = 20
          Caption = 'Bright Yellow'
          Color = clYellow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 6
          OnClick = panC64BlackClick
        end
        object Panel56: TPanel
          Tag = 16
          Left = 300
          Top = 16
          Width = 96
          Height = 20
          Caption = 'Orange'
          Color = 33023
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 7
          OnClick = panC64BlackClick
        end
        object Panel57: TPanel
          Tag = 26
          Left = 300
          Top = 112
          Width = 96
          Height = 20
          Caption = 'Pastel Yellow'
          Color = 8454143
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 8
          OnClick = panC64BlackClick
        end
        object Panel58: TPanel
          Tag = 17
          Left = 300
          Top = 40
          Width = 96
          Height = 20
          Caption = 'Pink'
          Color = 8421631
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 9
          OnClick = panC64BlackClick
        end
        object Panel59: TPanel
          Tag = 27
          Left = 300
          Top = 136
          Width = 96
          Height = 20
          Caption = 'Bright White'
          Color = clWhite
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 10
          OnClick = panC64BlackClick
        end
        object Panel60: TPanel
          Tag = 18
          Left = 300
          Top = 64
          Width = 96
          Height = 20
          Caption = 'Pastel Magenta'
          Color = 16744703
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 11
          OnClick = panC64BlackClick
        end
        object Panel62: TPanel
          Tag = 1
          Left = 0
          Top = 16
          Width = 96
          Height = 20
          Caption = 'Black'
          Color = clBlack
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 12
          OnClick = panC64BlackClick
        end
        object Panel63: TPanel
          Tag = 5
          Left = 100
          Top = 88
          Width = 96
          Height = 20
          Caption = 'Magenta'
          Color = clPurple
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 13
          OnClick = panC64BlackClick
        end
        object Panel64: TPanel
          Tag = 4
          Left = 100
          Top = 64
          Width = 96
          Height = 20
          Caption = 'Red'
          Color = clMaroon
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 14
          OnClick = panC64BlackClick
        end
        object Panel65: TPanel
          Tag = 20
          Left = 100
          Top = 16
          Width = 96
          Height = 20
          Caption = 'Sea Green'
          Color = 8453888
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 15
          OnClick = panC64BlackClick
        end
        object Panel66: TPanel
          Tag = 3
          Left = 0
          Top = 64
          Width = 96
          Height = 20
          Caption = 'Bright Blue'
          Color = clBlue
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 16
          OnClick = panC64BlackClick
        end
        object Panel67: TPanel
          Tag = 23
          Left = 200
          Top = 64
          Width = 96
          Height = 20
          Caption = 'Pastel Green'
          Color = 8454016
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 17
          OnClick = panC64BlackClick
        end
        object Panel68: TPanel
          Tag = 6
          Left = 100
          Top = 112
          Width = 96
          Height = 20
          Caption = 'Mauve'
          Color = 16711808
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 18
          OnClick = panC64BlackClick
        end
        object Panel69: TPanel
          Tag = 19
          Left = 0
          Top = 160
          Width = 96
          Height = 20
          Caption = 'Bright Green'
          Color = clLime
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 19
          OnClick = panC64BlackClick
        end
        object Panel70: TPanel
          Tag = 10
          Left = 0
          Top = 88
          Width = 96
          Height = 20
          Caption = 'Green'
          Color = clGreen
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 20
          OnClick = panC64BlackClick
        end
        object Panel71: TPanel
          Tag = 22
          Left = 200
          Top = 40
          Width = 96
          Height = 20
          Caption = 'Lime Green'
          Color = 65408
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 21
          OnClick = panC64BlackClick
        end
        object Panel72: TPanel
          Tag = 13
          Left = 100
          Top = 136
          Width = 96
          Height = 20
          Caption = 'Yellow'
          Color = clOlive
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 22
          OnClick = panC64BlackClick
        end
        object Panel73: TPanel
          Tag = 21
          Left = 100
          Top = 40
          Width = 96
          Height = 20
          Caption = 'Bright Cyan'
          Color = clAqua
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 23
          OnClick = panC64BlackClick
        end
        object Panel74: TPanel
          Tag = 12
          Left = 0
          Top = 136
          Width = 96
          Height = 20
          Caption = 'Sky Blue'
          Color = 16744448
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 24
          OnClick = panC64BlackClick
        end
        object Panel75: TPanel
          Tag = 24
          Left = 200
          Top = 88
          Width = 96
          Height = 20
          Caption = 'Pastel Cyan'
          Color = 16777088
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 25
          OnClick = panC64BlackClick
        end
        object Panel76: TPanel
          Tag = 15
          Left = 200
          Top = 16
          Width = 96
          Height = 20
          Caption = 'Pastel Blue'
          Color = 16744576
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 26
          OnClick = panC64BlackClick
        end
      end
      object TabSheet3: TTabSheet
        Caption = 'Groups'
        ImageIndex = 2
        object Label1: TLabel
          Left = 4
          Top = 0
          Width = 40
          Height = 13
          Caption = 'Brights'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label2: TLabel
          Left = 104
          Top = 0
          Width = 33
          Height = 13
          Caption = 'Darks'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label3: TLabel
          Left = 208
          Top = 0
          Width = 34
          Height = 13
          Caption = 'Lights'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label4: TLabel
          Left = 304
          Top = 0
          Width = 41
          Height = 13
          Caption = 'Pastels'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Panel18: TPanel
          Tag = 14
          Left = 200
          Top = 160
          Width = 96
          Height = 20
          Caption = 'White'
          Color = clGray
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          OnClick = panC64BlackClick
        end
        object Panel19: TPanel
          Tag = 2
          Left = 100
          Top = 16
          Width = 96
          Height = 20
          Caption = 'Blue'
          Color = clNavy
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          OnClick = panC64BlackClick
        end
        object Panel21: TPanel
          Tag = 4
          Left = 0
          Top = 40
          Width = 96
          Height = 20
          Caption = 'Bright Red'
          Color = clRed
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          OnClick = panC64BlackClick
        end
        object Panel23: TPanel
          Tag = 8
          Left = 200
          Top = 64
          Width = 96
          Height = 20
          Caption = 'Purple'
          Color = 8388863
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
          OnClick = panC64BlackClick
        end
        object Panel25: TPanel
          Tag = 5
          Left = 0
          Top = 64
          Width = 96
          Height = 20
          Caption = 'Bright Magenta'
          Color = clFuchsia
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
          OnClick = panC64BlackClick
        end
        object Panel26: TPanel
          Tag = 20
          Left = 200
          Top = 88
          Width = 96
          Height = 20
          Caption = 'Sea Green'
          Color = 8453888
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 5
          OnClick = panC64BlackClick
        end
        object Panel27: TPanel
          Tag = 11
          Left = 100
          Top = 112
          Width = 96
          Height = 20
          Caption = 'Cyan'
          Color = clTeal
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 6
          OnClick = panC64BlackClick
        end
        object Panel28: TPanel
          Tag = 25
          Left = 0
          Top = 136
          Width = 96
          Height = 20
          Caption = 'Bright Yellow'
          Color = clYellow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 7
          OnClick = panC64BlackClick
        end
        object Panel29: TPanel
          Tag = 16
          Left = 200
          Top = 136
          Width = 96
          Height = 20
          Caption = 'Orange'
          Color = 33023
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 8
          OnClick = panC64BlackClick
        end
        object Panel30: TPanel
          Tag = 26
          Left = 300
          Top = 136
          Width = 96
          Height = 20
          Caption = 'Pastel Yellow'
          Color = 8454143
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 9
          OnClick = panC64BlackClick
        end
        object Panel31: TPanel
          Tag = 17
          Left = 200
          Top = 40
          Width = 96
          Height = 20
          Caption = 'Pink'
          Color = 8421631
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 10
          OnClick = panC64BlackClick
        end
        object Panel32: TPanel
          Tag = 27
          Left = 0
          Top = 160
          Width = 96
          Height = 20
          Caption = 'Bright White'
          Color = clWhite
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 11
          OnClick = panC64BlackClick
        end
        object Panel33: TPanel
          Tag = 18
          Left = 300
          Top = 64
          Width = 96
          Height = 20
          Caption = 'Pastel Magenta'
          Color = 16744703
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 12
          OnClick = panC64BlackClick
        end
        object Panel35: TPanel
          Tag = 1
          Left = 100
          Top = 160
          Width = 96
          Height = 20
          Caption = 'Black'
          Color = clBlack
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 13
          OnClick = panC64BlackClick
        end
        object Panel36: TPanel
          Tag = 5
          Left = 100
          Top = 64
          Width = 96
          Height = 20
          Caption = 'Magenta'
          Color = clPurple
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 14
          OnClick = panC64BlackClick
        end
        object Panel37: TPanel
          Tag = 4
          Left = 100
          Top = 40
          Width = 96
          Height = 20
          Caption = 'Red'
          Color = clMaroon
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 15
          OnClick = panC64BlackClick
        end
        object Panel39: TPanel
          Tag = 3
          Left = 0
          Top = 16
          Width = 96
          Height = 20
          Caption = 'Bright Blue'
          Color = clBlue
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 16
          OnClick = panC64BlackClick
        end
        object Panel40: TPanel
          Tag = 23
          Left = 300
          Top = 88
          Width = 96
          Height = 20
          Caption = 'Pastel Green'
          Color = 8454016
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 17
          OnClick = panC64BlackClick
        end
        object Panel41: TPanel
          Tag = 6
          Left = 200
          Top = 112
          Width = 96
          Height = 20
          Caption = 'Mauve'
          Color = 16711808
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 18
          OnClick = panC64BlackClick
        end
        object Panel42: TPanel
          Tag = 19
          Left = 0
          Top = 88
          Width = 96
          Height = 20
          Caption = 'Bright Green'
          Color = clLime
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 19
          OnClick = panC64BlackClick
        end
        object Panel43: TPanel
          Tag = 10
          Left = 100
          Top = 88
          Width = 96
          Height = 20
          Caption = 'Green'
          Color = clGreen
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 20
          OnClick = panC64BlackClick
        end
        object Panel45: TPanel
          Tag = 13
          Left = 100
          Top = 136
          Width = 96
          Height = 20
          Caption = 'Yellow'
          Color = clOlive
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 21
          OnClick = panC64BlackClick
        end
        object Panel46: TPanel
          Tag = 21
          Left = 0
          Top = 112
          Width = 96
          Height = 20
          Caption = 'Bright Cyan'
          Color = clAqua
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 22
          OnClick = panC64BlackClick
        end
        object Panel47: TPanel
          Tag = 12
          Left = 200
          Top = 16
          Width = 96
          Height = 20
          Caption = 'Sky Blue'
          Color = 16744448
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 23
          OnClick = panC64BlackClick
        end
        object Panel48: TPanel
          Tag = 24
          Left = 300
          Top = 112
          Width = 96
          Height = 20
          Caption = 'Pastel Cyan'
          Color = 16777088
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 24
          OnClick = panC64BlackClick
        end
        object Panel49: TPanel
          Tag = 15
          Left = 300
          Top = 16
          Width = 96
          Height = 20
          Caption = 'Pastel Blue'
          Color = 16744576
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 25
          OnClick = panC64BlackClick
        end
        object Panel44: TPanel
          Tag = 22
          Left = 0
          Top = 184
          Width = 96
          Height = 20
          Caption = 'Lime Green'
          Color = 65408
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 26
          OnClick = panC64BlackClick
        end
      end
    end
  end
  object panMessageHeader: TPanel
    Left = 0
    Top = 0
    Width = 321
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    Color = 8675650
    TabOrder = 2
    DesignSize = (
      321
      41)
    object bvlMessageTop: TBevel
      Left = 0
      Top = 39
      Width = 321
      Height = 2
      Align = alBottom
    end
    object imgMessageIcon: TImage
      Left = 284
      Top = 4
      Width = 32
      Height = 32
      Anchors = [akTop, akRight]
      AutoSize = True
      Picture.Data = {
        055449636F6E0000010002002020100000000000E80200002600000010101000
        00000000280100000E0300002800000020000000400000000100040000000000
        8002000000000000000000000000000000000000000000000000800000800000
        0080800080000000800080008080000080808000C0C0C0000000FF0000FF0000
        00FFFF00FF000000FF00FF00FFFF0000FFFFFF00000000000000000000000000
        000000000FFFFFFF0F0F0000F0FFFFFF0FFFFFF00F00F00F0F0F0000F000000F
        0F0000000F00F00F0F0F0000F00FFFFF0FFFFFF00F00000F0F0F0000F000000F
        000000F00F00000F0F0FFFFFF0FFFFFF0FFFFFF0000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000099999999BBBBBBBBAAAAAAAEEEEEEE0099999999BBBBBBBBAAAAAAA
        EEEEEEE000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000004444440044444444444444
        4000000078FFF87478FFFFFFFFFFFFF874000000078FFF87478FF874000078FF
        874000000078FFF87478FF874000078FF874000000078FFF87478FF874000478
        FF874000000078FFF87478FF8740FFFFFFF700000000078FFF87478FF8740000
        0000000000000078FFF87478FF84400000000000000000078FFF87478FF84444
        444444400000000078FFF8747FFFFFFFFFFFF84000044444478FFF8744444444
        44444444008FFFFFFFFFFFFFFFFFFFFFFFFFFF80000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000280000001000000020000000
        0100040000000000C00000000000000000000000000000000000000000000000
        00008000008000000080800080000000800080008080000080808000C0C0C000
        0000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000FFFFFFF
        0FFFFFF00000000F0F00000000FFFFFF0FFFFFF00000000F000000F00FFFFFFF
        0FFFFFF0000000000000000009999BBBAAAEEEE0000000000000000004400444
        444400008F848FFFFFF8400008F848F7007F8400008F848F700000000008F848
        FFFFF80000008F847777770000FFFFFFFFFFFFF0000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000000000000000000000000000000000000000000000000}
    end
    object imgLogo: TImage
      Left = 8
      Top = 5
      Width = 72
      Height = 20
      AutoSize = True
      Picture.Data = {
        07544269746D617016110000424D161100000000000036000000280000004800
        0000140000000100180000000000E0100000120B0000120B0000000000000000
        0000F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8
        F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809
        F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F8
        09F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8
        F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809
        F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F8
        09F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F80008C60008C6
        0008C60008C6F809F80008C60008C60008C60008C6F809F80008C60008C60008
        C60008C6F809F80008C60008C60008C6F809F80008C60008C60008C60008C6F8
        09F8F809F80008C60008C60008C60008C60008C60008C60008C6F809F8F809F8
        F809F8F809F80008C60008C60008C6F809F8F809F8F809F80008C60008C60008
        C60008C6F809F80008C60008C60008C60008C6F809F80008C60008C60008C600
        08C6F809F80008C60008C60008C60008C6F809F80008C60008C60008C60008C6
        0008C60008C60008C60008C6F809F8F809F80008C60008C60008C60008C6F809
        F80008C60008C60008C60008C6F809F80008C60008C60008C60008C6F809F800
        08C60008C60008C6F809F80008C60008C60008C60008C6F809F80008C60008C6
        0008C60008C60008C60008C60008C60008C60008C6F809F8F809F8F809F80008
        C60008C60008C6F809F8F809F8F809F80008C60008C60008C60008C6F809F800
        08C60008C60008C60008C6F809F80008C60008C60008C60008C6F809F80008C6
        0008C60008C60008C6F809F80008C60008C60008C60008C60008C60008C60008
        C60008C60008C6F809F80008C60008C60008C60008C6F809F80008C60008C600
        08C60008C6F809F80008C60008C60008C60008C6F809F80008C60008C60008C6
        F809F80008C60008C60008C60008C6F809F80008C60008C60008C60008C60008
        C60008C60008C60008C60008C6F809F8F809F8F809F80008C60008C60008C6F8
        09F8F809F8F809F80008C60008C60008C60008C6F809F80008C60008C60008C6
        0008C6F809F80008C60008C60008C60008C6F809F80008C60008C60008C60008
        C6F809F80008C60008C60008C60008C60008C60008C60008C60008C60008C6F8
        09F80008C60008C60008C60008C60008C60008C60008C60008C60008C6F809F8
        0008C60008C60008C60008C6F809F80008C60008C60008C6F809F80008C60008
        C60008C60008C6F809F80008C60008C60008C60008C6F809F80008C60008C600
        08C60008C6F809F8F809F8F809F80008C60008C60008C6F809F8F809F8F809F8
        0008C60008C60008C60008C6F809F80008C60008C60008C60008C6F809F80008
        C60008C60008C60008C6F809F80008C60008C60008C60008C6F809F80008C600
        08C60008C60008C6F809F80008C60008C60008C60008C6F809F80008C60008C6
        0008C60008C60008C60008C60008C60008C60008C6F809F80008C60008C60008
        C60008C6F809F80008C60008C60008C6F809F80008C60008C60008C60008C6F8
        09F80008C60008C60008C60008C6F809F80008C60008C60008C60008C6F809F8
        F809F8F809F80008C60008C60008C6F809F8F809F8F809F80008C60008C60008
        C60008C6F809F80008C60008C60008C60008C6F809F80008C60008C60008C600
        08C60008C60008C60008C60008C60008C6F809F80008C60008C60008C60008C6
        F809F80008C60008C60008C60008C6F809F80008C60008C60008C60008C60008
        C60008C60008C60008C60008C6F809F80008C60008C60008C60008C6F809F800
        08C60008C60008C6F809F80008C60008C60008C60008C6F809F80008C60008C6
        0008C60008C6F809F80008C60008C60008C60008C6F809F8F809F8F809F80008
        C60008C60008C6F809F8F809F8F809F80008C60008C60008C60008C6F809F800
        08C60008C60008C60008C6F809F80008C60008C60008C60008C60008C60008C6
        0008C60008C60008C6F809F80008C60008C60008C60008C6F809F80008C60008
        C60008C60008C6F809F80008C60008C60008C60008C6F809F80008C60008C600
        08C60008C6F809F80008C60008C60008C60008C6F809F80008C60008C60008C6
        0008C60008C60008C60008C60008C6F809F80008C60008C60008C60008C6F809
        F80008C60008C60008C60008C6F809F8F809F8F809F80008C60008C60008C6F8
        09F8F809F8F809F80008C60008C60008C60008C6F809F80008C60008C60008C6
        0008C6F809F80008C60008C60008C60008C6F809F80008C60008C60008C60008
        C6F809F80008C60008C60008C60008C6F809F80008C60008C60008C60008C6F8
        09F80008C60008C60008C60008C6F809F80008C60008C60008C60008C6F809F8
        0008C60008C60008C60008C60008C60008C60008C60008C60008C60008C60008
        C60008C60008C6F809F8F809F8F809F8F809F8F809F8F809F80008C60008C600
        08C60008C6F809F8F809F8F809F80008C60008C60008C6F809F8F809F8F809F8
        0008C60008C60008C60008C60008C60008C60008C60008C60008C6F809F80008
        C60008C60008C60008C6F809F80008C60008C60008C60008C6F809F80008C600
        08C60008C60008C6F809F80008C60008C60008C60008C6F809F80008C60008C6
        0008C60008C6F809F80008C60008C60008C60008C6F809F80008C60008C60008
        C60008C60008C60008C60008C60008C60008C60008C60008C60008C60008C6F8
        09F8F809F8F809F8F809F80008C60008C60008C60008C60008C60008C6F809F8
        F809F8F809F80008C60008C60008C6F809F8F809F8F809F80008C60008C60008
        C60008C60008C60008C60008C60008C6F809F8F809F80008C60008C60008C600
        08C6F809F80008C60008C60008C60008C6F809F80008C60008C60008C60008C6
        F809F80008C60008C60008C60008C6F809F80008C60008C60008C60008C6F809
        F80008C60008C60008C60008C6F809F80008C60008C60008C60008C60008C600
        08C60008C60008C60008C60008C60008C60008C60008C6F809F8F809F80008C6
        0008C60008C60008C60008C60008C60008C6F809F8F809F8F809F8F809F80008
        C60008C60008C6F809F8F809F8F809F80008C60008C60008C60008C60008C600
        08C60008C60008C6F809F8F809F80008C60008C60008C60008C6F809F80008C6
        0008C60008C60008C6F809F80008C60008C60008C60008C6F809F80008C60008
        C60008C60008C6F809F80008C60008C60008C60008C6F809F80008C60008C600
        08C60008C6F809F80008C60008C60008C60008C60008C60008C60008C60008C6
        0008C60008C60008C60008C60008C6F809F80008C60008C60008C60008C60008
        C60008C6F809F8F809F8F809F8F809F8F809F8F809F80008C60008C60008C6F8
        09F8F809F8F809F80008C60008C60008C60008C60008C60008C60008C60008C6
        0008C6F809F80008C60008C60008C60008C6F809F80008C60008C60008C60008
        C6F809F80008C60008C60008C60008C6F809F80008C60008C60008C60008C6F8
        09F80008C60008C60008C60008C6F809F80008C60008C60008C60008C6F809F8
        0008C60008C60008C60008C60008C60008C60008C60008C60008C60008C60008
        C60008C60008C6F809F80008C60008C60008C60008C6F809F8F809F8F809F8F8
        09F8F809F8F809F8F809F8F809F80008C60008C60008C6F809F8F809F8F809F8
        0008C60008C60008C60008C6F809F80008C60008C60008C60008C6F809F80008
        C60008C60008C60008C6F809F80008C60008C60008C60008C6F809F80008C600
        08C60008C60008C6F809F80008C60008C60008C60008C6F809F80008C60008C6
        0008C60008C6F809F80008C60008C60008C60008C6F809F80008C60008C60008
        C60008C60008C60008C6F809F80008C60008C60008C60008C60008C60008C6F8
        09F80008C60008C60008C60008C6F809F80008C60008C60008C60008C6F809F8
        F809F8F809F80008C60008C60008C6F809F8F809F8F809F80008C60008C60008
        C60008C6F809F80008C60008C60008C60008C6F809F80008C60008C60008C600
        08C60008C60008C60008C60008C60008C6F809F80008C60008C60008C60008C6
        F809F80008C60008C60008C60008C6F809F8F809F80008C60008C60008C60008
        C60008C60008C60008C6F809F8F809F80008C60008C60008C60008C60008C600
        08C6F809F80008C60008C60008C60008C60008C60008C6F809F80008C60008C6
        0008C60008C6F809F80008C60008C60008C60008C6F809F8F809F8F809F80008
        C60008C60008C6F809F8F809F8F809F80008C60008C60008C60008C6F809F800
        08C60008C60008C60008C6F809F8F809F80008C60008C60008C60008C60008C6
        0008C60008C6F809F8F809F80008C60008C60008C60008C6F809F80008C60008
        C60008C60008C6F809F8F809F80008C60008C60008C60008C60008C60008C600
        08C6F809F8F809F80008C60008C60008C60008C60008C60008C6F809F80008C6
        0008C60008C60008C60008C60008C6F809F80008C60008C60008C60008C6F809
        F80008C60008C60008C60008C6F809F8F809F8F809F80008C60008C60008C6F8
        09F8F809F8F809F80008C60008C60008C60008C6F809F80008C60008C60008C6
        0008C6F809F8F809F80008C60008C60008C60008C60008C60008C60008C6F809
        F8F809F80008C60008C60008C60008C6F809F80008C60008C60008C60008C6F8
        09F8F809F80008C60008C60008C60008C60008C60008C60008C6F809F8F809F8
        0008C60008C60008C60008C60008C6F809F8F809F8F809F80008C60008C60008
        C60008C60008C6F809F80008C60008C60008C60008C60008C60008C60008C600
        08C60008C6F809F80008C60008C60008C60008C60008C60008C60008C6F809F8
        0008C60008C60008C60008C60008C60008C60008C60008C60008C6F809F8F809
        F80008C60008C60008C60008C60008C60008C60008C6F809F8F809F80008C600
        08C60008C60008C60008C60008C60008C60008C60008C6F809F8F809F8F809F8
        0008C60008C60008C60008C60008C6F809F8F809F8F809F80008C60008C60008
        C60008C60008C6F809F8F809F8F809F80008C60008C60008C60008C60008C6F8
        09F80008C60008C60008C60008C60008C60008C60008C60008C60008C6F809F8
        0008C60008C60008C60008C60008C60008C60008C6F809F80008C60008C60008
        C60008C60008C60008C60008C60008C60008C6F809F8F809F8F809F80008C600
        08C60008C60008C60008C6F809F8F809F8F809F80008C60008C60008C60008C6
        0008C60008C60008C60008C60008C6F809F8F809F8F809F80008C60008C60008
        C60008C60008C6F809F8F809F8F809F80008C60008C60008C60008C60008C6F8
        09F8F809F8F809F80008C60008C60008C60008C60008C6F809F8F809F80008C6
        0008C60008C60008C60008C60008C60008C6F809F8F809F80008C60008C60008
        C60008C60008C60008C60008C6F809F80008C60008C60008C60008C60008C600
        08C60008C60008C6F809F8F809F8F809F8F809F80008C60008C60008C60008C6
        0008C6F809F8F809F8F809F80008C60008C60008C60008C60008C60008C60008
        C60008C6F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F8
        09F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8
        F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809
        F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F8
        09F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8
        F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809
        F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F809F8F8
        09F8}
      Transparent = True
    end
    object Label5: TLabel
      Left = 96
      Top = 8
      Width = 97
      Height = 13
      Caption = '27 Colour Palette'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Panel24: TPanel
      Left = 4
      Top = 34
      Width = 64
      Height = 2
      BevelOuter = bvNone
      Color = clRed
      TabOrder = 0
    end
    object Panel38: TPanel
      Left = 68
      Top = 34
      Width = 64
      Height = 2
      BevelOuter = bvNone
      Color = clYellow
      TabOrder = 1
    end
    object Panel51: TPanel
      Left = 132
      Top = 34
      Width = 64
      Height = 2
      BevelOuter = bvNone
      Color = clLime
      TabOrder = 2
    end
    object Panel53: TPanel
      Left = 196
      Top = 34
      Width = 64
      Height = 2
      BevelOuter = bvNone
      Color = clAqua
      TabOrder = 3
    end
  end
end
