object frmPaletteImageParserOptions: TfrmPaletteImageParserOptions
  Left = 1237
  Top = 37
  ClientHeight = 1022
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
  object panPaletteImageParser: TPanel
    Left = 0
    Top = 0
    Width = 348
    Height = 1022
    Align = alClient
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 0
    object scpZXImageParser: TScrollBox
      Left = 0
      Top = 65
      Width = 348
      Height = 957
      VertScrollBar.Smooth = True
      VertScrollBar.Tracking = True
      Align = alClient
      Color = clWhite
      ParentColor = False
      TabOrder = 0
      object panOptions: TPanel
        Left = 0
        Top = 0
        Width = 344
        Height = 949
        Align = alTop
        Color = clWhite
        ParentBackground = False
        TabOrder = 0
        DesignSize = (
          344
          949)
        object grpSourceCode: TGroupBox
          Left = 6
          Top = 6
          Width = 332
          Height = 200
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
          object imgZXImageParserZigZag: TImage
            Left = 287
            Top = 175
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
          object imgZXImageParserClassic: TImage
            Left = 287
            Top = 153
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
          object radZXImageParserRowOrderClassic: TRadioButton
            Left = 24
            Top = 152
            Width = 249
            Height = 17
            Caption = 'Even: Left to Right, Odd: Left to Right (Classic)'
            TabOrder = 6
          end
          object radZXImageParserRowOrderZigZag: TRadioButton
            Left = 24
            Top = 175
            Width = 257
            Height = 17
            Caption = 'Even: Left to Right , Odd: Right to Left (Zig Zag)'
            TabOrder = 7
          end
        end
        object grpZXImageParserMaskOrder: TGroupBox
          Left = 6
          Top = 212
          Width = 332
          Height = 130
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Mask Order'
          TabOrder = 1
          object radZXImageParserPixelMaskBytePairs: TRadioButton
            Left = 9
            Top = 40
            Width = 133
            Height = 17
            Caption = 'Pixel / Mask byte pairs'
            TabOrder = 0
          end
          object radZXImageParserAfterPixels: TRadioButton
            Left = 9
            Top = 109
            Width = 81
            Height = 17
            Caption = 'After Pixels'
            TabOrder = 1
          end
          object radZXImageParserMaskPixelBytePairs: TRadioButton
            Left = 9
            Top = 63
            Width = 133
            Height = 17
            Caption = 'Mask / Pixel byte pairs'
            TabOrder = 2
          end
          object radZXImageParserBeforePixels: TRadioButton
            Left = 9
            Top = 86
            Width = 89
            Height = 17
            Caption = 'Before Pixels'
            TabOrder = 3
          end
          object radZXImageParserPixelMaskNone: TRadioButton
            Left = 9
            Top = 17
            Width = 161
            Height = 17
            Caption = 'Don'#39't include Mask data'
            Checked = True
            TabOrder = 4
            TabStop = True
          end
        end
        object grpZXImageParserMaskType: TGroupBox
          Left = 6
          Top = 348
          Width = 332
          Height = 61
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Mask Type'
          TabOrder = 2
          object imgZXImageParserMaskCovers: TImage
            Left = 181
            Top = 16
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
            Left = 181
            Top = 38
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
            Top = 15
            Width = 161
            Height = 17
            Caption = 'My mask COVERS my image'
            TabOrder = 0
          end
          object radZXImageParserMaskOutlines: TRadioButton
            Left = 8
            Top = 38
            Width = 167
            Height = 17
            Caption = 'My mask OUTLINES my image'
            TabOrder = 1
          end
        end
        object grpImageSize: TGroupBox
          Left = 6
          Top = 415
          Width = 332
          Height = 150
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Image Size'
          TabOrder = 3
          DesignSize = (
            332
            150)
          object lblSizeOrder: TLabel
            Left = 24
            Top = 85
            Width = 84
            Height = 13
            Caption = 'Dimensions Order'
          end
          object chkPlaceSize: TCheckBox
            Left = 8
            Top = 16
            Width = 244
            Height = 17
            Anchors = [akLeft, akTop, akRight]
            Caption = 'Place image size at start of image data'
            Checked = True
            State = cbChecked
            TabOrder = 0
            OnClick = chkPlaceSizeClick
          end
          object chkConvertX: TCheckBox
            Left = 24
            Top = 39
            Width = 286
            Height = 17
            Anchors = [akLeft, akTop, akRight]
            Caption = 'Convert Pixel Width to Width in Bytes'
            Checked = True
            State = cbChecked
            TabOrder = 1
          end
          object chkConvertY: TCheckBox
            Left = 24
            Top = 62
            Width = 286
            Height = 17
            Anchors = [akLeft, akTop, akRight]
            Caption = 'Convert Pixel Height to Height in Characters'
            TabOrder = 2
          end
          object radSizeWidthHeight: TRadioButton
            Left = 45
            Top = 104
            Width = 97
            Height = 17
            Caption = 'Width x Height'
            Checked = True
            TabOrder = 3
            TabStop = True
          end
          object radSizeHeightWidth: TRadioButton
            Left = 45
            Top = 127
            Width = 97
            Height = 17
            Caption = 'Height x Width'
            TabOrder = 4
          end
        end
        object grpNumberBase: TGroupBox
          Left = 6
          Top = 571
          Width = 332
          Height = 84
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Number Base'
          TabOrder = 4
          object lblNumerialPrefix: TLabel
            Left = 131
            Top = 17
            Width = 72
            Height = 13
            Caption = 'Numerial Prefix'
          end
          object radZXImageParserDecimal: TRadioButton
            Left = 8
            Top = 16
            Width = 73
            Height = 17
            Caption = 'Decimal'
            TabOrder = 0
            OnClick = radZXImageParserDecimalClick
          end
          object radZXImageParserHexidecimal: TRadioButton
            Left = 8
            Top = 39
            Width = 81
            Height = 17
            Caption = 'Hexidecimal'
            Checked = True
            TabOrder = 1
            TabStop = True
            OnClick = radZXImageParserHexidecimalClick
          end
          object radZXImageParserBinary: TRadioButton
            Left = 8
            Top = 62
            Width = 57
            Height = 17
            Caption = 'Binary'
            TabOrder = 2
            OnClick = radZXImageParserBinaryClick
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
        object grpPixelBitRemapping: TGroupBox
          Left = 6
          Top = 661
          Width = 332
          Height = 277
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Pixel Bit Remapping'
          TabOrder = 5
          object lblBit7: TLabel
            Left = 48
            Top = 84
            Width = 21
            Height = 13
            Caption = 'Bit 7'
            Enabled = False
          end
          object lblBit6: TLabel
            Left = 48
            Top = 108
            Width = 21
            Height = 13
            Caption = 'Bit 6'
            Enabled = False
          end
          object lblBit5: TLabel
            Left = 48
            Top = 132
            Width = 21
            Height = 13
            Caption = 'Bit 5'
            Enabled = False
          end
          object lblBit4: TLabel
            Left = 48
            Top = 156
            Width = 21
            Height = 13
            Caption = 'Bit 4'
            Enabled = False
          end
          object lblBit3: TLabel
            Left = 48
            Top = 180
            Width = 21
            Height = 13
            Caption = 'Bit 3'
            Enabled = False
          end
          object lblBit2: TLabel
            Left = 48
            Top = 204
            Width = 21
            Height = 13
            Caption = 'Bit 2'
            Enabled = False
          end
          object lblBit1: TLabel
            Left = 48
            Top = 228
            Width = 21
            Height = 13
            Caption = 'Bit 1'
            Enabled = False
          end
          object lblBit0: TLabel
            Left = 48
            Top = 252
            Width = 21
            Height = 13
            Caption = 'Bit 0'
            Enabled = False
          end
          object lblTestValue: TLabel
            Left = 140
            Top = 84
            Width = 50
            Height = 13
            Caption = 'Test Value'
            Enabled = False
          end
          object lblResult: TLabel
            Left = 140
            Top = 128
            Width = 30
            Height = 13
            Caption = 'Result'
            Enabled = False
          end
          object lblRemapResult: TLabel
            Left = 204
            Top = 128
            Width = 6
            Height = 13
            Caption = '0'
            Enabled = False
          end
          object spdRemapPresetSave: TSpeedButton
            Left = 208
            Top = 52
            Width = 23
            Height = 22
            Hint = 'Save or Update the current presets'
            Enabled = False
            Flat = True
            Glyph.Data = {
              F6000000424DF600000000000000760000002800000010000000100000000100
              04000000000080000000C30E0000C30E00001000000010000000000000000000
              80000080000000808000800000008000800080800000C0C0C000808080000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
              DDDDDD0000000000000DD03300000077030DD03300000077030DD03300000077
              030DD03300000000030DD03333333333330DD03300000000330DD03077777777
              030DD03077777777030DD03077777777030DD03077777777030DD03077777777
              000DD03077777777070DD00000000000000DDDDDDDDDDDDDDDDD}
            ParentShowHint = False
            ShowHint = True
          end
          object spdRemapPresetDelete: TSpeedButton
            Left = 232
            Top = 52
            Width = 23
            Height = 22
            Hint = 'Delete current preset from the list'
            Enabled = False
            Flat = True
            Glyph.Data = {
              CA010000424DCA01000000000000760000002800000022000000110000000100
              04000000000054010000C40E0000C40E00001000000000000000000000000000
              80000080000000808000800000008000800080800000C0C0C000808080000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00666666666666
              66666666666666666666660000006666666666666666666666666666666F6600
              000066666666666661F666666F6666666686660000006661F666666666666666
              8FF6666666F66600000066111F6666661F66666888F666666866660000006611
              1F666661F666666888FF66668F6666000000666111F66611F6666666888FF668
              8666660000006666111F611F666666666888FF886666660000006666611111F6
              6666666666888886666666000000666666111F6666666666666888FF66666600
              00006666611111F6666666666688888F6666660000006666111F61F666666666
              F8886686FF6666000000661111F66611F6666668888666688FF6660000006111
              1F6666611F6666888866666688FF66000000611F6666666611F6668866666666
              6886660000006666666666666666666666666666666666000000666666666666
              6666666666666666666666000000}
            NumGlyphs = 2
            ParentShowHint = False
            ShowHint = True
          end
          object lblRemappingPresets: TLabel
            Left = 36
            Top = 36
            Width = 92
            Height = 13
            Caption = 'Remapping Presets'
            Enabled = False
          end
          object lblValue: TLabel
            Left = 140
            Top = 108
            Width = 26
            Height = 13
            Caption = 'Value'
            Enabled = False
          end
          object lblRemapValue: TLabel
            Left = 204
            Top = 108
            Width = 6
            Height = 13
            Caption = '0'
            Enabled = False
          end
          object chkEnabledRemap: TCheckBox
            Left = 20
            Top = 18
            Width = 161
            Height = 17
            Caption = 'Enable pixel bit remapping'
            Enabled = False
            TabOrder = 0
            OnClick = chkEnabledRemapClick
          end
          object edtBit7: KSpinEdit
            Left = 76
            Top = 80
            Width = 49
            Height = 20
            BevelOuter = bvLowered
            Color = clWhite
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBtnShadow
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            Value = 7
            Max = 7
            OnChanged = edtBit7Change
            DesignSize = (
              49
              20)
          end
          object edtBit6: KSpinEdit
            Left = 76
            Top = 104
            Width = 49
            Height = 20
            BevelOuter = bvLowered
            Color = clWhite
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBtnShadow
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 2
            Value = 6
            Max = 7
            OnChanged = edtBit7Change
            DesignSize = (
              49
              20)
          end
          object edtBit5: KSpinEdit
            Left = 76
            Top = 128
            Width = 49
            Height = 20
            BevelOuter = bvLowered
            Color = clWhite
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBtnShadow
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 3
            Value = 5
            Max = 7
            OnChanged = edtBit7Change
            DesignSize = (
              49
              20)
          end
          object edtBit4: KSpinEdit
            Left = 76
            Top = 152
            Width = 49
            Height = 20
            BevelOuter = bvLowered
            Color = clWhite
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBtnShadow
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 4
            Value = 4
            Max = 7
            OnChanged = edtBit7Change
            DesignSize = (
              49
              20)
          end
          object edtBit3: KSpinEdit
            Left = 76
            Top = 176
            Width = 49
            Height = 20
            BevelOuter = bvLowered
            Color = clWhite
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBtnShadow
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 5
            Value = 3
            Max = 7
            OnChanged = edtBit7Change
            DesignSize = (
              49
              20)
          end
          object edtBit2: KSpinEdit
            Left = 76
            Top = 200
            Width = 49
            Height = 20
            BevelOuter = bvLowered
            Color = clWhite
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBtnShadow
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 6
            Value = 2
            Max = 7
            OnChanged = edtBit7Change
            DesignSize = (
              49
              20)
          end
          object edtBit1: KSpinEdit
            Left = 76
            Top = 224
            Width = 49
            Height = 20
            BevelOuter = bvLowered
            Color = clWhite
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBtnShadow
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 7
            Value = 1
            Max = 7
            OnChanged = edtBit7Change
            DesignSize = (
              49
              20)
          end
          object edtBit0: KSpinEdit
            Left = 76
            Top = 248
            Width = 49
            Height = 20
            BevelOuter = bvLowered
            Color = clWhite
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBtnShadow
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 8
            Max = 7
            OnChanged = edtBit7Change
            DesignSize = (
              49
              20)
          end
          object edtTestValue: KSpinEdit
            Left = 204
            Top = 80
            Width = 53
            Height = 20
            BevelOuter = bvLowered
            Color = clWhite
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBtnShadow
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 9
            Max = 255
            OnChanged = edtBit7Change
            DesignSize = (
              53
              20)
          end
          object cmbRemapPreset: TComboBox
            Left = 36
            Top = 52
            Width = 169
            Height = 21
            Color = clWhite
            Enabled = False
            ItemHeight = 0
            TabOrder = 10
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
        Width = 164
        Height = 13
        Caption = 'Palette Based Images Parser'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lblZXImageParserDescription: TLabel
        Left = 8
        Top = 21
        Width = 341
        Height = 44
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'Parsers Images that are based on palettes into assembly code. Th' +
          'is includes machines such as the Amstrad CPC, Enterprise 64/128,' +
          ' Commodore 64 etc.'
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
