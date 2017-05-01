object frmZXScreenParserOptions: TfrmZXScreenParserOptions
  Left = 1304
  Top = 268
  ClientHeight = 695
  ClientWidth = 358
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panZXScreenParser: TPanel
    Left = 0
    Top = 0
    Width = 358
    Height = 695
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object scpZXImageParser: TScrollBox
      Left = 0
      Top = 57
      Width = 358
      Height = 638
      Align = alClient
      Color = clWhite
      ParentColor = False
      TabOrder = 0
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 354
        Height = 197
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        DesignSize = (
          354
          197)
        object grpZXScreenParserAddress: TGroupBox
          Left = 6
          Top = 6
          Width = 341
          Height = 114
          Anchors = [akLeft, akTop, akRight]
          Caption = 'ORG Statement'
          Color = clWhite
          ParentBackground = False
          ParentColor = False
          TabOrder = 0
          object radZXScreenParserOrgDefault: TRadioButton
            Tag = 1
            Left = 8
            Top = 16
            Width = 269
            Height = 17
            Caption = 'Use default Screen Address (16384, 0x4000)'
            Checked = True
            TabOrder = 0
            TabStop = True
            OnClick = radZXScreenParserOrgDefaultClick
          end
          object radZXScreenParserOrgNone: TRadioButton
            Tag = 2
            Left = 8
            Top = 39
            Width = 174
            Height = 17
            Caption = 'Do not use an ORG statement'
            TabOrder = 1
            OnClick = radZXScreenParserOrgDefaultClick
          end
          object radZXScreenParserOrgUser: TRadioButton
            Tag = 3
            Left = 8
            Top = 62
            Width = 166
            Height = 17
            Caption = 'User defined ORG statement'
            TabOrder = 2
            OnClick = radZXScreenParserOrgDefaultClick
          end
          object edtZXScreenParserOrgValue: TEdit
            Left = 24
            Top = 85
            Width = 121
            Height = 21
            Enabled = False
            ParentColor = True
            TabOrder = 3
            Text = '0x4000'
            OnKeyPress = edtZXScreenParserOrgValueKeyPress
          end
        end
        object grpZXScreensParserAttributes: TGroupBox
          Left = 6
          Top = 126
          Width = 341
          Height = 62
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Attributes'
          Color = clWhite
          ParentBackground = False
          ParentColor = False
          TabOrder = 1
          object radZXScreenParserInclude: TRadioButton
            Left = 8
            Top = 16
            Width = 116
            Height = 17
            Caption = 'Include Attributes'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object radZXScreenParserExclude: TRadioButton
            Left = 8
            Top = 39
            Width = 153
            Height = 17
            Caption = 'Do not include Atttributes'
            TabOrder = 1
          end
        end
      end
    end
    object panTitle: TPanel
      Left = 0
      Top = 0
      Width = 358
      Height = 57
      Align = alTop
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 1
      DesignSize = (
        358
        57)
      object lblZXImagesParser: TLabel
        Left = 4
        Top = 4
        Width = 163
        Height = 13
        Caption = 'ZX Spectrum SCREEN$ Parser'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lblZXImageParserDescription: TLabel
        Left = 8
        Top = 20
        Width = 343
        Height = 37
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'Parses ZX Spectrum Screen$ into assembly code.  Formats the imag' +
          'e data into the ZX Spectrum specific screen format.'
        WordWrap = True
        ExplicitWidth = 351
      end
    end
  end
end
