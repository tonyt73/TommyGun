object frmZXImageParserOptions: TfrmZXImageParserOptions
  Left = 1146
  Top = 73
  ClientHeight = 767
  ClientWidth = 355
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panZXImageParser: TPanel
    Left = 0
    Top = 0
    Width = 355
    Height = 767
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object scpZXImageParser: TScrollBox
      Left = 0
      Top = 57
      Width = 355
      Height = 710
      VertScrollBar.Smooth = True
      VertScrollBar.Tracking = True
      Align = alClient
      TabOrder = 0
      object panOptions: TPanel
        Left = 0
        Top = 0
        Width = 334
        Height = 859
        Align = alTop
        BevelOuter = bvNone
        Color = clWhite
        ParentBackground = False
        TabOrder = 0
        DesignSize = (
          334
          859)
        object grpZXImageParserPixelOrder: TGroupBox
          Left = 4
          Top = 4
          Width = 324
          Height = 62
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Pixel Order'
          TabOrder = 0
          object radZXImageParserPixelsRowColumn: TRadioButton
            Left = 8
            Top = 16
            Width = 153
            Height = 17
            Caption = 'Scanlines by Row / Column'
            Checked = True
            TabOrder = 0
            TabStop = True
            OnClick = radZXImageParserPixelsRowColumnClick
          end
          object radZXImageParserPixelCharacterBlock: TRadioButton
            Left = 8
            Top = 39
            Width = 189
            Height = 17
            Caption = 'Character Blocks by Row / Column'
            TabOrder = 1
            OnClick = radZXImageParserPixelsRowColumnClick
          end
        end
        object grpZXImageParserPixelRowOrder: TGroupBox
          Left = 4
          Top = 72
          Width = 324
          Height = 62
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Pixel Row Order'
          TabOrder = 1
          object imgZXImageParserClassic: TImage
            Left = 267
            Top = 17
            Width = 16
            Height = 16
            AutoSize = True
            Picture.Data = {
              07544269746D6170F6000000424DF60000000000000076000000280000001000
              000010000000010004000000000080000000120B0000120B0000100000001000
              000000000000000080000080000000808000800000008000800080800000C0C0
              C000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
              FF00DDDDDDDDDDDDDDDD0000000000000000000000000000000000DDDDDDDDDD
              DDDD00DDDDDDDDDDDDDD0000000000000000000000000000000000DDDDDDDDDD
              DDDD00DDDDDDDDDDDDDD0000000000000000000000000000000000DDDDDDDDDD
              DDDD00DDDDDDDDDDDDDD00000000000000000000000000000000DDDDDDDDDDDD
              DDDD}
            Transparent = True
          end
          object imgZXImageParserZigZag: TImage
            Left = 267
            Top = 39
            Width = 16
            Height = 16
            AutoSize = True
            Picture.Data = {
              07544269746D6170F6000000424DF60000000000000076000000280000001000
              000010000000010004000000000080000000120B0000120B0000100000001000
              000000000000000080000080000000808000800000008000800080800000C0C0
              C000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
              FF00DDDDDDDDDDDDDDDD00000000000000000000000000000000DDDDDDDDDDDD
              DD00DDDDDDDDDDDDDD000000000000000000000000000000000000DDDDDDDDDD
              DDDD00DDDDDDDDDDDDDD00000000000000000000000000000000DDDDDDDDDDDD
              DD00DDDDDDDDDDDDDD0000000000000000000000000000000000DDDDDDDDDDDD
              DDDD}
            Transparent = True
          end
          object radZXImageParserRowOrderClassic: TRadioButton
            Left = 8
            Top = 16
            Width = 253
            Height = 17
            Caption = 'Even: Left to Right, Odd: Left to Right (Classic)'
            Checked = True
            TabOrder = 0
            TabStop = True
            OnClick = radZXImageParserPixelsRowColumnClick
          end
          object radZXImageParserRowOrderZigZag: TRadioButton
            Left = 8
            Top = 39
            Width = 253
            Height = 17
            Caption = 'Even: Left to Right , Odd: Right to Left (Zig Zag)'
            TabOrder = 1
            OnClick = radZXImageParserPixelsRowColumnClick
          end
        end
        object grpZXImageParserAttributeOrder: TGroupBox
          Left = 4
          Top = 140
          Width = 324
          Height = 84
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Attribute Order'
          TabOrder = 2
          DesignSize = (
            324
            84)
          object radZXImageParserAttributesEnd: TRadioButton
            Left = 28
            Top = 39
            Width = 121
            Height = 17
            Caption = 'At End of Pixel Data'
            Checked = True
            TabOrder = 0
            TabStop = True
            OnClick = radZXImageParserPixelsRowColumnClick
          end
          object radZXImageParserAttributesInterleaved: TRadioButton
            Left = 28
            Top = 62
            Width = 189
            Height = 17
            Caption = 'Interleaved with Character Blocks'
            TabOrder = 1
            OnClick = radZXImageParserPixelsRowColumnClick
          end
          object chkUseAttributes: TCheckBox
            Left = 8
            Top = 16
            Width = 190
            Height = 17
            Anchors = [akLeft, akTop, akRight]
            Caption = 'Use the Attributes'
            Checked = True
            State = cbChecked
            TabOrder = 2
            OnClick = radZXImageParserPixelsRowColumnClick
          end
        end
        object grpZXImageParserMaskOrder: TGroupBox
          Left = 4
          Top = 230
          Width = 324
          Height = 84
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Mask Order'
          TabOrder = 3
          object radZXImageParserMaskBytePairs: TRadioButton
            Left = 8
            Top = 16
            Width = 193
            Height = 17
            Caption = 'Pixel / Mask byte pairs'
            Checked = True
            TabOrder = 0
            TabStop = True
            OnClick = radZXImageParserPixelsRowColumnClick
          end
          object radZXImageParserAfterPixels: TRadioButton
            Left = 8
            Top = 62
            Width = 229
            Height = 17
            Caption = 'After Pixels (but before Attributes)'
            TabOrder = 1
            OnClick = radZXImageParserPixelsRowColumnClick
          end
          object panMaskOrder: TPanel
            Left = 24
            Top = 32
            Width = 309
            Height = 21
            BevelOuter = bvNone
            TabOrder = 2
            object radZXImageParserMaskAfter: TRadioButton
              Left = 4
              Top = 7
              Width = 117
              Height = 17
              Caption = 'Mask AFTER pixels'
              Checked = True
              Color = clWhite
              ParentColor = False
              TabOrder = 0
              TabStop = True
              OnClick = radZXImageParserPixelsRowColumnClick
            end
            object radZXImageParserMaskBefore: TRadioButton
              Left = 132
              Top = 7
              Width = 121
              Height = 17
              Caption = 'Mask BEFORE pixels'
              Color = clWhite
              ParentColor = False
              TabOrder = 1
              OnClick = radZXImageParserPixelsRowColumnClick
            end
          end
        end
        object grpZXImageParserMaskType: TGroupBox
          Left = 4
          Top = 320
          Width = 324
          Height = 62
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Mask Type'
          TabOrder = 4
          object imgZXImageParserMaskCovers: TImage
            Left = 175
            Top = 17
            Width = 32
            Height = 16
            AutoSize = True
            Picture.Data = {
              07544269746D617076010000424D760100000000000076000000280000002000
              000010000000010004000000000000010000120B0000120B0000100000001000
              000000000000000080000080000000808000800000008000800080800000C0C0
              C000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
              FF00DDDDD0000000DDDDDDDDD9999999DDDDDDDDD000000DDDDDDDDDD999999D
              DDDDDDDDD000000DDDDDDDDDD999999DDDDDDDDDDD0000DDDDDDDDDDDD9999DD
              DDDDDDDD00000000DDDDDDDD99999999DDDDDDDD00000000DDDDDDDD99999999
              DDDDDDDDD000000DDDDDDDDDD999999DDDDDDDDDD000000DDDDDDDDDD999999D
              DDDDDDDDDD0000DDDDDDDDDDDD9999DDDDDDDDDDDDD00DDDDDDDDDDDDDD99DDD
              DDDDDDDDDD0000DDDDDDDDDDDD9999DDDDDDDDDDDD00000DDDDDDDDDDD99999D
              DDDDDDDDDD0000DDDDDDDDDDDD9999DDDDDDDDDDD00000DDDDDDDDDDD99999DD
              DDDDDDDDDD00000DDDDDDDDDDD99999DDDDDDDDDDDDDD00DDDDDDDDDDDDDD99D
              DDDD}
            Transparent = True
          end
          object imgZXImageParserMaskOutlines: TImage
            Left = 175
            Top = 39
            Width = 32
            Height = 16
            AutoSize = True
            Picture.Data = {
              07544269746D617076010000424D760100000000000076000000280000002000
              000010000000010004000000000000010000120B0000120B0000100000001000
              000000000000000080000080000000808000800000008000800080800000C0C0
              C000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
              FF00DDDDD0000000DDDD9999900000009999DDDDD000000DDDDD999990000009
              9999DDDDD000000DDDDD9999900000099999DDDDDD0000DDDDDD999999000099
              9999DDDD00000000DDDD9999000000009999DDDD00000000DDDD999900000000
              9999DDDDD000000DDDDD9999900000099999DDDDD000000DDDDD999990000009
              9999DDDDDD0000DDDDDD9999990000999999DDDDDDD00DDDDDDD999999900999
              9999DDDDDD0000DDDDDD9999990000999999DDDDDD00000DDDDD999999000009
              9999DDDDDD0000DDDDDD9999990000999999DDDDD00000DDDDDD999990000099
              9999DDDDDD00000DDDDD9999990000099999DDDDDDDDD00DDDDD999999999009
              9999}
            Transparent = True
          end
          object radZXImageParserMaskCovers: TRadioButton
            Left = 8
            Top = 16
            Width = 161
            Height = 17
            Caption = 'My mask COVERS my image'
            Checked = True
            TabOrder = 0
            TabStop = True
            OnClick = radZXImageParserPixelsRowColumnClick
          end
          object radZXImageParserMaskOutlines: TRadioButton
            Left = 8
            Top = 39
            Width = 173
            Height = 17
            Caption = 'My mask OUTLINES my image'
            TabOrder = 1
            OnClick = radZXImageParserPixelsRowColumnClick
          end
        end
        object grpZXImageParserImageSize: TGroupBox
          Left = 4
          Top = 388
          Width = 324
          Height = 88
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Image Size'
          TabOrder = 5
          object chkPlaceSize: TCheckBox
            Left = 8
            Top = 16
            Width = 213
            Height = 17
            Caption = 'Place image size at start of image data'
            Checked = True
            State = cbChecked
            TabOrder = 0
            OnClick = radZXImageParserPixelsRowColumnClick
          end
          object chkConvertX: TCheckBox
            Left = 24
            Top = 39
            Width = 205
            Height = 17
            Caption = 'Convert Pixel Width to Width in Bytes'
            Checked = True
            State = cbChecked
            TabOrder = 1
            OnClick = radZXImageParserPixelsRowColumnClick
          end
          object chkConvertY: TCheckBox
            Left = 24
            Top = 62
            Width = 237
            Height = 17
            Caption = 'Convert Pixel Height to Height in Characters'
            Checked = True
            State = cbChecked
            TabOrder = 2
            OnClick = radZXImageParserPixelsRowColumnClick
          end
        end
        object grpNumberBase: TGroupBox
          Left = 4
          Top = 482
          Width = 324
          Height = 62
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Number Base'
          TabOrder = 6
          object radZXImageParserDecimal: TRadioButton
            Left = 8
            Top = 16
            Width = 69
            Height = 17
            Caption = 'Decimal'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object radZXImageParserHexidecimal: TRadioButton
            Left = 8
            Top = 39
            Width = 85
            Height = 17
            Caption = 'Hexidecimal'
            TabOrder = 1
          end
          object radZXImageParserBinary: TRadioButton
            Left = 120
            Top = 16
            Width = 57
            Height = 17
            Caption = 'Binary'
            TabOrder = 2
          end
          object radZXImageParserOctal: TRadioButton
            Left = 120
            Top = 39
            Width = 57
            Height = 17
            Caption = 'Octal'
            TabOrder = 3
          end
        end
        object GroupBox1: TGroupBox
          Left = 4
          Top = 550
          Width = 324
          Height = 304
          Anchors = [akLeft, akTop, akRight]
          Caption = ' Preview '
          TabOrder = 7
          DesignSize = (
            324
            304)
          object imgZXImageParserPreview: TImage
            Left = 8
            Top = 18
            Width = 32
            Height = 32
            Picture.Data = {
              07544269746D6170F6000000424DF60000000000000076000000280000001000
              0000100000000100040000000000800000000000000000000000100000000000
              0000000000000000800000800000008080008000000080008000808000008080
              8000C0C0C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
              FF00AAAAAAAAEEEEEEEEAA0000AAE00000EEA0AAAA0AE0EEEE0EA0AAAAAAE0EE
              EE0EA0AAAAAAE0EEEE0EA0AAAA0AE0EEEE0EAA0000AAE00000EEAAAAAAAAEEEE
              EEEE99999999BBBBBBBB90999909B00000BB90999909B0BBBB0B90000009B0BB
              BB0B90999909B00000BB90999909B0BBBB0B99000099B00000BB99999999BBBB
              BBBB}
            Stretch = True
          end
          object rdtZXImageParserPreview: TRichEdit
            Left = 46
            Top = 16
            Width = 270
            Height = 280
            Anchors = [akLeft, akTop, akRight, akBottom]
            Color = clBlack
            Font.Charset = OEM_CHARSET
            Font.Color = clWhite
            Font.Height = -8
            Font.Name = 'Terminal'
            Font.Style = []
            Lines.Strings = (
              'Image:'
              '; pixels'
              'defb 000000000, 00000000'
              'defb 001111100, 01111100'
              'defb 010000010, 01000010'
              'defb 011111110, 01111100'
              'defb 010000010, 01000010'
              '...'
              '; attributes'
              'defb ')
            ParentFont = False
            ReadOnly = True
            ScrollBars = ssBoth
            TabOrder = 0
          end
        end
      end
    end
    object panTitle: TPanel
      Left = 0
      Top = 0
      Width = 355
      Height = 57
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      DesignSize = (
        355
        57)
      object lblZXImagesParser: TLabel
        Left = 4
        Top = 4
        Width = 158
        Height = 13
        Caption = 'ZX Spectrum Images Parser'
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
        Width = 348
        Height = 39
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'Parses ZX Spectrum Images into assembly code.  Including being a' +
          'ble to create image tables for the images.'
        WordWrap = True
        ExplicitWidth = 351
      end
    end
  end
end
