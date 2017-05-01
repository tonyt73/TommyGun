object frmImageParserOptions: TfrmImageParserOptions
  Left = 1924
  Top = 118
  Width = 268
  Height = 318
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panImageParser: TPanel
    Left = 0
    Top = 0
    Width = 260
    Height = 284
    Align = alClient
    BevelOuter = bvNone
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object lblImagesParser: TLabel
      Left = 4
      Top = 4
      Width = 83
      Height = 13
      Caption = 'Images Parser'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lblImageParserDescription: TLabel
      Left = 8
      Top = 20
      Width = 235
      Height = 13
      Caption = 'Parsers images into Assembly, C, C++ or BASIC.'
      WordWrap = True
    end
    object pgcImageParserOptions: TPageControl
      Left = 0
      Top = 44
      Width = 260
      Height = 240
      ActivePage = tabImageParserDataFormat
      Align = alBottom
      Style = tsFlatButtons
      TabIndex = 0
      TabOrder = 0
      object tabImageParserDataFormat: TTabSheet
        Caption = 'Data Format'
      end
      object tabImageParserFileOutput: TTabSheet
        Caption = 'File Output'
        ImageIndex = 2
        object lblImageParserFile: TLabel
          Left = 28
          Top = 112
          Width = 16
          Height = 13
          Caption = 'File'
        end
        object Label2: TLabel
          Left = 28
          Top = 136
          Width = 221
          Height = 69
          AutoSize = False
          Caption = 
            'This option inserts the source code into either an existing file' +
            ' or a new file. An include statement is added to current file at' +
            ' the current cursor position that references the new file create' +
            'd.'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          WordWrap = True
        end
        object Label3: TLabel
          Left = 28
          Top = 28
          Width = 217
          Height = 57
          AutoSize = False
          Caption = 
            'Inserts the Source Code into the current file at the current cur' +
            'sor position. If no Resources Section is defined then one is add' +
            'ed around the new code.'
          WordWrap = True
        end
        object radImageParserCurrentFile: TRadioButton
          Left = 12
          Top = 8
          Width = 181
          Height = 17
          Caption = 'Current File at Current Position'
          Checked = True
          ColorDown = clWhite
          ColorBorder = clBtnShadow
          ColorInner = clWhite
          ColorInnerShadow = clWhite
          TabOrder = 0
          TabStop = True
        end
        object radImageParserExistingOrNewFile: TRadioButton
          Left = 12
          Top = 88
          Width = 181
          Height = 17
          Caption = 'In an Existing or New File'
          ColorDown = clWhite
          ColorBorder = clBtnShadow
          ColorInner = clWhite
          ColorInnerShadow = clWhite
          TabOrder = 1
        end
        object cmbImageParserFile: TComboBox
          Left = 52
          Top = 108
          Width = 196
          Height = 21
          Color = clWhite
          ColorInnerShadow = 14805739
          ItemHeight = 13
          TabOrder = 2
          ItemIndex = -1
        end
      end
      object tabImageParserLanguage: TTabSheet
        Caption = 'Language'
        ImageIndex = 1
        DesignSize = (
          252
          209)
        object Label1: TLabel
          Left = 4
          Top = 8
          Width = 47
          Height = 13
          Caption = 'Language'
        end
        object Label4: TLabel
          Left = 4
          Top = 44
          Width = 48
          Height = 13
          Caption = 'Separator'
        end
        object Bevel1: TBevel
          Left = 0
          Top = 33
          Width = 252
          Height = 2
          Anchors = [akLeft, akTop, akRight]
        end
        object Label5: TLabel
          Left = 4
          Top = 68
          Width = 48
          Height = 13
          Caption = 'Separator'
        end
        object FlatComboBox1: TComboBox
          Left = 60
          Top = 4
          Width = 188
          Height = 21
          Color = clWhite
          ColorInnerShadow = 14805739
          ItemHeight = 13
          Items.Strings = (
            'Assembly'
            'C/C++'
            'BASIC'
            'Custom')
          TabOrder = 0
          ItemIndex = -1
        end
        object FlatEdit1: TEdit
          Left = 60
          Top = 40
          Width = 189
          Height = 19
          ColorFlat = clWhite
          ColorInnerShadow = 14805739
          ParentColor = True
          TabOrder = 1
          Text = ', '
        end
        object FlatEdit2: TEdit
          Left = 59
          Top = 64
          Width = 189
          Height = 19
          ColorFlat = clWhite
          ColorInnerShadow = 14805739
          ParentColor = True
          TabOrder = 2
          Text = ', '
        end
      end
    end
  end
end
