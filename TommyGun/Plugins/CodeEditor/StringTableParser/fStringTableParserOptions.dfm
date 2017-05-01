object frmStringTableParserOptions: TfrmStringTableParserOptions
  Left = 311
  Top = 207
  ClientHeight = 544
  ClientWidth = 263
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panStringTableParser: TPanel
    Left = 0
    Top = 0
    Width = 263
    Height = 544
    Align = alClient
    BevelOuter = bvNone
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentBackground = False
    ParentFont = False
    TabOrder = 0
    object panTitle: TPanel
      Left = 0
      Top = 0
      Width = 263
      Height = 41
      Align = alTop
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 0
      object lblStringTableParserDescription: TLabel
        Left = 8
        Top = 20
        Width = 226
        Height = 13
        AutoSize = False
        Caption = 'Parses String Tables into Assembly.'
      end
      object lblStringTableParser: TLabel
        Left = 4
        Top = 4
        Width = 114
        Height = 13
        Caption = 'String Tables Parser'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
  end
end
