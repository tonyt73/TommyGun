object frmAGDParserOptions: TfrmAGDParserOptions
  Left = 1230
  Top = -2
  ClientHeight = 412
  ClientWidth = 299
  Color = clWindow
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panAGDParser: TPanel
    Left = 0
    Top = 0
    Width = 299
    Height = 412
    Align = alClient
    BevelOuter = bvNone
    Color = clWindow
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
      Width = 299
      Height = 412
      Align = alClient
      BevelOuter = bvNone
      ParentBackground = False
      TabOrder = 0
      DesignSize = (
        299
        412)
      object lblAGDParser: TLabel
        Left = 4
        Top = 4
        Width = 129
        Height = 13
        Caption = 'Arcade Game Designer'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Panel1: TPanel
        Left = 4
        Top = 23
        Width = 283
        Height = 66
        Anchors = [akLeft, akTop, akRight]
        BevelOuter = bvNone
        TabOrder = 0
        object lblAGDParserDescription: TLabel
          Left = 0
          Top = 40
          Width = 283
          Height = 26
          Align = alBottom
          Caption = 'Note: There are no options required for this code generator.'
          WordWrap = True
          ExplicitWidth = 239
        end
        object Label1: TLabel
          Left = 0
          Top = 0
          Width = 283
          Height = 26
          Align = alTop
          Caption = 
            'Updates the Arcade Game Designer game engine with the game resou' +
            'rces.'
          WordWrap = True
          ExplicitWidth = 280
        end
      end
    end
  end
end
