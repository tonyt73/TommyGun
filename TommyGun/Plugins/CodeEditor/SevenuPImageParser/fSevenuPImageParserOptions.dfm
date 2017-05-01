object frmSevenuPImageParserOptions: TfrmSevenuPImageParserOptions
  Left = 1328
  Top = 24
  ClientHeight = 808
  ClientWidth = 350
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panSevenuPImageParser: TPanel
    Left = 0
    Top = 0
    Width = 350
    Height = 808
    Align = alClient
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 0
    object scpSevenuPImageParser: TScrollBox
      Left = 0
      Top = 64
      Width = 350
      Height = 744
      VertScrollBar.Smooth = True
      VertScrollBar.Tracking = True
      Align = alClient
      Color = clWhite
      ParentColor = False
      TabOrder = 0
      object panOptions: TPanel
        Left = 0
        Top = 0
        Width = 346
        Height = 731
        Align = alTop
        Color = clWhite
        ParentBackground = False
        TabOrder = 0
        DesignSize = (
          346
          731)
        object grpSourceCode: TGroupBox
          Left = 6
          Top = 6
          Width = 334
          Height = 198
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Source Code'
          Color = clWhite
          ParentBackground = False
          ParentColor = False
          TabOrder = 0
          object lblPrefix: TLabel
            Left = 64
            Top = 128
            Width = 70
            Height = 13
            Caption = 'Byte Definition'
          end
          object lblLabelPrefix: TLabel
            Left = 64
            Top = 64
            Width = 56
            Height = 13
            Caption = 'Label Prefix'
          end
          object lblLabelPostfix: TLabel
            Left = 64
            Top = 88
            Width = 61
            Height = 13
            Caption = 'Label Postfix'
          end
          object lblExample: TLabel
            Left = 140
            Top = 104
            Width = 43
            Height = 13
            Caption = 'MyLabel:'
          end
          object imgZXImageParserZigZag: TImage
            Left = 140
            Top = 151
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
          object radSourceCodeAsm: TRadioButton
            Left = 8
            Top = 16
            Width = 101
            Height = 17
            Caption = 'Z80 Assembler'
            Checked = True
            TabOrder = 0
            TabStop = True
            OnClick = radSourceCodeAsmClick
          end
          object radSourceCodeC: TRadioButton
            Left = 140
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
            Left = 140
            Top = 124
            Width = 73
            Height = 21
            ParentColor = True
            TabOrder = 3
            Text = 'DEFB'
          end
          object edtLabelPrefix: TEdit
            Left = 140
            Top = 60
            Width = 72
            Height = 21
            ParentColor = True
            TabOrder = 4
            OnChange = edtLabelPostfixChange
          end
          object edtLabelPostfix: TEdit
            Left = 140
            Top = 82
            Width = 72
            Height = 21
            ParentColor = True
            TabOrder = 5
            Text = ':'
            OnChange = edtLabelPostfixChange
          end
          object chkSourceCodeZ88DK: TCheckBox
            Left = 24
            Top = 175
            Width = 97
            Height = 17
            Caption = 'Add Z88DK Info'
            Checked = True
            State = cbChecked
            TabOrder = 6
          end
          object chkMiscZigZag: TCheckBox
            Left = 24
            Top = 152
            Width = 110
            Height = 17
            Caption = 'Horizontal Zig Zag'
            TabOrder = 7
          end
        end
        object grpDataOutputted: TGroupBox
          Left = 6
          Top = 210
          Width = 334
          Height = 62
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Data Outputted'
          TabOrder = 1
          object radDataGraphicsAttributes: TRadioButton
            Left = 8
            Top = 15
            Width = 126
            Height = 17
            Caption = 'Graphics + Attributes'
            Checked = True
            TabOrder = 0
            TabStop = True
            OnClick = radDataGraphicsAttributesClick
          end
          object radDataAttributesGraphics: TRadioButton
            Tag = 1
            Left = 8
            Top = 38
            Width = 126
            Height = 17
            Caption = 'Attributes + Graphics'
            TabOrder = 1
            OnClick = radDataGraphicsAttributesClick
          end
          object radDataGraphics: TRadioButton
            Tag = 2
            Left = 140
            Top = 15
            Width = 61
            Height = 17
            Caption = 'Graphics'
            TabOrder = 2
            OnClick = radDataGraphicsAttributesClick
          end
          object radDataAttributes: TRadioButton
            Tag = 3
            Left = 140
            Top = 38
            Width = 73
            Height = 17
            Caption = 'Attributes'
            TabOrder = 3
            OnClick = radDataGraphicsAttributesClick
          end
        end
        object grpMasking: TGroupBox
          Left = 6
          Top = 278
          Width = 334
          Height = 132
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Masking'
          TabOrder = 2
          object imgSevenuPImageParserMaskOutlines: TImage
            Left = 140
            Top = 108
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
          object imgSevenuPImageParserMaskCovers: TImage
            Left = 140
            Top = 85
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
          object radMaskingMaskCovers: TRadioButton
            Left = 8
            Top = 85
            Width = 126
            Height = 17
            Caption = 'Mask COVERS Image'
            Checked = True
            TabOrder = 6
            TabStop = True
          end
          object chkMaskingBeforeGraphics: TCheckBox
            Left = 8
            Top = 16
            Width = 126
            Height = 16
            Caption = 'Mask Before Graphics'
            TabOrder = 0
            OnClick = chkMaskingBeforeGraphicsClick
          end
          object chkMaskingAttributeMask: TCheckBox
            Left = 140
            Top = 16
            Width = 97
            Height = 17
            Caption = 'Attribute Mask'
            TabOrder = 1
            OnClick = chkMaskingAttributeMaskClick
          end
          object chkMaskingAttributeInk: TCheckBox
            Left = 156
            Top = 39
            Width = 37
            Height = 17
            Caption = 'Ink'
            Checked = True
            Enabled = False
            State = cbChecked
            TabOrder = 2
            OnClick = chkMaskingAttributeInkClick
          end
          object chkMaskingAttributePaper: TCheckBox
            Left = 212
            Top = 39
            Width = 50
            Height = 17
            Caption = 'Paper'
            Checked = True
            Enabled = False
            State = cbChecked
            TabOrder = 3
            OnClick = chkMaskingAttributeInkClick
          end
          object chkMaskingAttributeBright: TCheckBox
            Left = 156
            Top = 62
            Width = 50
            Height = 17
            Caption = 'Bright'
            Checked = True
            Enabled = False
            State = cbChecked
            TabOrder = 4
            OnClick = chkMaskingAttributeInkClick
          end
          object chkMaskingAttributeFlash: TCheckBox
            Left = 212
            Top = 62
            Width = 50
            Height = 17
            Caption = 'Flash'
            Checked = True
            Enabled = False
            State = cbChecked
            TabOrder = 5
            OnClick = chkMaskingAttributeInkClick
          end
          object radMaskingMaskOutlines: TRadioButton
            Left = 8
            Top = 108
            Width = 131
            Height = 17
            Caption = 'Mask OUTLINES Image'
            TabOrder = 7
          end
        end
        object grpInterleave: TGroupBox
          Left = 6
          Top = 416
          Width = 334
          Height = 62
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Interleave'
          Enabled = False
          TabOrder = 3
          object radInterleaveLine: TRadioButton
            Left = 8
            Top = 16
            Width = 41
            Height = 17
            Caption = 'Line'
            Enabled = False
            TabOrder = 0
            OnClick = radInterleaveLineClick
          end
          object radInterleaveCharacter: TRadioButton
            Tag = 1
            Left = 8
            Top = 39
            Width = 69
            Height = 17
            Caption = 'Character'
            Enabled = False
            TabOrder = 1
            OnClick = radInterleaveLineClick
          end
          object radInterleaveColumn: TRadioButton
            Tag = 2
            Left = 92
            Top = 16
            Width = 57
            Height = 17
            Caption = 'Column'
            Enabled = False
            TabOrder = 2
            OnClick = radInterleaveLineClick
          end
          object radInterleaveFrames: TRadioButton
            Tag = 3
            Left = 92
            Top = 39
            Width = 57
            Height = 17
            Caption = 'Frames'
            Enabled = False
            TabOrder = 3
            OnClick = radInterleaveLineClick
          end
          object radInterleaveSprite: TRadioButton
            Tag = 4
            Left = 160
            Top = 16
            Width = 53
            Height = 17
            Caption = 'Sprite'
            Checked = True
            Enabled = False
            TabOrder = 4
            TabStop = True
            OnClick = radInterleaveLineClick
          end
        end
        object grpByteSortPriority: TGroupBox
          Left = 6
          Top = 484
          Width = 334
          Height = 122
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Byte Sort Priority'
          TabOrder = 4
          object lstByteSortPriority: TListBox
            Left = 8
            Top = 16
            Width = 149
            Height = 99
            Color = clWhite
            ItemHeight = 13
            Items.Strings = (
              'X Char'
              'Char Line'
              'Y Char'
              'Mask'
              'Frame Number')
            TabOrder = 0
            OnClick = lstByteSortPriorityClick
          end
          object cmdSortListMoveUp: TBitBtn
            Left = 163
            Top = 16
            Width = 32
            Height = 16
            Hint = 'Move File Up|Move the selected file up to the previous position'
            Enabled = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 1
            OnClick = cmdSortListMoveUpClick
            Glyph.Data = {
              AE000000424DAE00000000000000760000002800000009000000070000000100
              0400000000003800000000000000000000001000000010000000000000000000
              80000080000000808000800000008000800080800000C0C0C000808080000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDD000
              00000000000000000000D0000000D0000000DD00000DD0000000DDD000DDD000
              0000DDDD0DDDD0000000DDDDDDDDD0000000}
          end
          object cmdSortListMoveDown: TBitBtn
            Left = 163
            Top = 38
            Width = 32
            Height = 16
            Hint = 'Move File Down|Move the selected file down to the next position'
            Enabled = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 2
            OnClick = cmdSortListMoveDownClick
            Glyph.Data = {
              AE000000424DAE00000000000000760000002800000009000000070000000100
              0400000000003800000000000000000000001000000010000000000000000000
              80000080000000808000800000008000800080800000C0C0C000808080000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDD000
              0000DDDD0DDDD0000000DDD000DDD0000000DD00000DD0000000D0000000D000
              00000000000000000000DDDDDDDDD0000000}
          end
          object cmdListDefault: TButton
            Left = 163
            Top = 89
            Width = 69
            Height = 23
            Hint = 'Move File Down|Move the selected file down to the next position'
            Caption = 'Reset'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 3
            OnClick = cmdListDefaultClick
          end
        end
        object grpNumberBase: TGroupBox
          Left = 6
          Top = 612
          Width = 334
          Height = 112
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Number Base'
          TabOrder = 5
          object lblNumberBasePrefix: TLabel
            Left = 12
            Top = 66
            Width = 28
            Height = 13
            Caption = 'Prefix'
          end
          object lblNumberBasePostfix: TLabel
            Left = 160
            Top = 66
            Width = 33
            Height = 13
            Caption = 'Postfix'
          end
          object lblExampleIs: TLabel
            Left = 12
            Top = 90
            Width = 113
            Height = 13
            Caption = 'Example: 123 decimal is'
          end
          object lblExampleValue: TLabel
            Left = 132
            Top = 90
            Width = 24
            Height = 13
            Caption = '0x7B'
          end
          object radDecimal: TRadioButton
            Left = 8
            Top = 16
            Width = 61
            Height = 17
            Caption = 'Decimal'
            TabOrder = 0
            OnClick = radDecimalClick
          end
          object radBinary: TRadioButton
            Tag = 2
            Left = 160
            Top = 16
            Width = 53
            Height = 17
            Caption = 'Binary'
            TabOrder = 1
            OnClick = radDecimalClick
          end
          object radOctal: TRadioButton
            Tag = 3
            Left = 160
            Top = 39
            Width = 45
            Height = 17
            Caption = 'Octal'
            TabOrder = 2
            OnClick = radDecimalClick
          end
          object edtNumberBasePrefix: TEdit
            Left = 44
            Top = 62
            Width = 53
            Height = 21
            ParentColor = True
            TabOrder = 3
            Text = '0x'
            OnChange = edtNumberBasePrefixChange
          end
          object edtNumberBasePostfix: TEdit
            Left = 200
            Top = 62
            Width = 53
            Height = 21
            ParentColor = True
            TabOrder = 4
            OnChange = edtNumberBasePostfixChange
          end
          object radHexidecimal: TRadioButton
            Tag = 1
            Left = 8
            Top = 39
            Width = 81
            Height = 17
            Caption = 'Hexadecimal'
            Checked = True
            TabOrder = 5
            TabStop = True
            OnClick = radDecimalClick
          end
        end
      end
    end
    object panTitle: TPanel
      Left = 0
      Top = 0
      Width = 350
      Height = 64
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      DesignSize = (
        350
        64)
      object lblZXImagesParser: TLabel
        Left = 4
        Top = 4
        Width = 141
        Height = 13
        Caption = 'SevenuP Graphics Parser'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lblSevenuPImageParserDescription: TLabel
        Left = 8
        Top = 20
        Width = 332
        Height = 39
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'Parses ZX Spectrum Images into assembly code or C  code using th' +
          'e same options as the SevenuP graphics application.  Also contai' +
          'ns a few extra options for masking and number base output.'
        WordWrap = True
      end
    end
  end
end
