object frmPaletteParserOptions: TfrmPaletteParserOptions
  Left = 1237
  Top = 37
  ClientHeight = 332
  ClientWidth = 348
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panPaletteParser: TPanel
    Left = 0
    Top = 0
    Width = 348
    Height = 332
    Align = alClient
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 0
    ExplicitHeight = 1022
    object scpZXPaletteParser: TScrollBox
      Left = 0
      Top = 65
      Width = 348
      Height = 267
      VertScrollBar.Smooth = True
      VertScrollBar.Tracking = True
      Align = alClient
      Color = clWhite
      ParentColor = False
      TabOrder = 0
      ExplicitHeight = 957
      object panOptions: TPanel
        Left = 0
        Top = 0
        Width = 327
        Height = 949
        Align = alTop
        Color = clWhite
        ParentBackground = False
        TabOrder = 0
        ExplicitWidth = 344
        DesignSize = (
          327
          949)
        object grpSourceCode: TGroupBox
          Left = 6
          Top = 6
          Width = 315
          Height = 159
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Source Code'
          TabOrder = 0
          object lblPrefix: TLabel
            Left = 48
            Top = 129
            Width = 70
            Height = 13
            Caption = 'Byte Definition'
          end
          object lblLabelPrefix: TLabel
            Left = 52
            Top = 65
            Width = 56
            Height = 13
            Caption = 'Label Prefix'
          end
          object lblLabelPostfix: TLabel
            Left = 52
            Top = 89
            Width = 61
            Height = 13
            Caption = 'Label Postfix'
          end
          object lblExample: TLabel
            Left = 124
            Top = 109
            Width = 43
            Height = 13
            Caption = 'MyLabel:'
          end
          object radSourceCodeAsm: TRadioButton
            Left = 8
            Top = 16
            Width = 98
            Height = 17
            Caption = 'Z80 Assembler'
            Checked = True
            TabOrder = 0
            TabStop = True
            OnClick = radSourceCodeAsmClick
          end
          object radSourceCodeC: TRadioButton
            Left = 124
            Top = 16
            Width = 69
            Height = 17
            Caption = 'C Source'
            TabOrder = 2
            OnClick = radSourceCodeAsmClick
          end
          object chkSourceCodeUseLabel: TCheckBox
            Left = 24
            Top = 39
            Width = 85
            Height = 17
            Caption = 'Use Label'
            Checked = True
            State = cbChecked
            TabOrder = 1
            OnClick = radSourceCodeAsmClick
          end
          object edtPrefix: TEdit
            Left = 124
            Top = 125
            Width = 73
            Height = 21
            ParentColor = True
            TabOrder = 3
            Text = 'DEFB'
          end
          object edtLabelPrefix: TEdit
            Left = 124
            Top = 60
            Width = 72
            Height = 21
            ParentColor = True
            TabOrder = 4
            OnChange = edtLabelPrefixChange
          end
          object edtLabelPostfix: TEdit
            Left = 124
            Top = 87
            Width = 72
            Height = 21
            ParentColor = True
            TabOrder = 5
            Text = ':'
            OnChange = edtLabelPrefixChange
          end
        end
        object grpNumberBase: TGroupBox
          Left = 6
          Top = 171
          Width = 315
          Height = 84
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Number Base'
          TabOrder = 1
          object lblNumerialPrefix: TLabel
            Left = 131
            Top = 17
            Width = 72
            Height = 13
            Caption = 'Numerial Prefix'
          end
          object radZXPaletteParserDecimal: TRadioButton
            Left = 8
            Top = 16
            Width = 73
            Height = 17
            Caption = 'Decimal'
            TabOrder = 0
            OnClick = radZXPaletteParserDecimalClick
          end
          object radZXPaletteParserHexidecimal: TRadioButton
            Left = 8
            Top = 39
            Width = 81
            Height = 17
            Caption = 'Hexidecimal'
            Checked = True
            TabOrder = 1
            TabStop = True
            OnClick = radZXPaletteParserHexidecimalClick
          end
          object radZXPaletteParserBinary: TRadioButton
            Left = 8
            Top = 62
            Width = 57
            Height = 17
            Caption = 'Binary'
            TabOrder = 2
            OnClick = radZXPaletteParserBinaryClick
          end
          object edtNumericalPrefix: TEdit
            Left = 131
            Top = 36
            Width = 73
            Height = 21
            ParentColor = True
            TabOrder = 3
            Text = '$'
            OnChange = edtNumericalPrefixChange
          end
        end
      end
    end
    object panTitle: TPanel
      Left = 0
      Top = 0
      Width = 348
      Height = 65
      Align = alTop
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 1
      DesignSize = (
        348
        65)
      object lblZXImagesParser: TLabel
        Left = 4
        Top = 4
        Width = 81
        Height = 13
        Caption = 'Palette Parser'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lblZXPaletteParserDescription: TLabel
        Left = 8
        Top = 21
        Width = 329
        Height = 38
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 'Parsers Palette data into assembly code.'
        WordWrap = True
      end
    end
  end
  object regScorpio: KRegistry
    Section = 'TommyGun'
    RootKey = rkHKEY_CURRENT_USER
    SoftwareKey = '\Software\Scorpio\'
    Left = 188
    Top = 4
  end
end
