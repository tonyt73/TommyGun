object frmCharacterType: TfrmCharacterType
  Left = 1366
  Top = 142
  ClientHeight = 874
  ClientWidth = 283
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  PixelsPerInch = 96
  TextHeight = 13
  object panCharacterSet: TPanel
    Left = 0
    Top = 0
    Width = 283
    Height = 874
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
    DesignSize = (
      283
      874)
    object imgIcon: TImage
      Left = 10
      Top = 129
      Width = 16
      Height = 16
      AutoSize = True
      Picture.Data = {
        07544269746D617036030000424D360300000000000036000000280000001000
        000010000000010018000000000000030000130B0000130B0000000000000000
        0000FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
        FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
        FFFF00FFFF00FFFF00FFFF00FF319A3139A64AFF00FFFF00FFFF00FFFF00FFFF
        00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF21BE3121CB42
        31D75231BA4A219A3152D773FF00FFFF00FFFF00FFFF00FF1034CE3961FF7B92
        FF7386E7FF00FFFF00FF21CF3918C33121CB4221CB4231DB5A4AEB735AEF84FF
        00FFFF00FF3145B50838FF214DFF6382FF6B8EFF7382E7FF00FF31D75218C331
        18BE2918C33129CF4239DF634ADB6B52B26BFF00FFFF00FF1045FF1849FF4A71
        FF6382FF6B86FF4A59BD42CB7B31D74A08B61821C73921CB4231D34A39D363FF
        00FFFF00FFFF00FF294DE72151FF3961FF5275FF5A7DFF5265F74296B552F773
        18C33110BA2131D75229CF4A31D352FF00FFFF00FFFF00FFFF00FF3159FF3961
        FF4269FF4A71FF5271FF4259E752CBA55AFF7B18C33118C33121CB4221CB42FF
        00FFFF00FFFF00FFFF00FF3961FF4269FF3961FF3965FF4A6DFF3155FF214DEF
        52C7AD5AFF8C31DB4A10BE2918C331319631FF00FFFF00FFFF00FF5269D64A71
        FF3965FF2959FF3961FF1041FF294DFF425DEF4A8ECE5ACBA552D3734ACF63FF
        00FFFF00FFFF00FFFF00FFFF00FF5A79FF5275FF2151FF2955FF2951FF3159FF
        4269FF4261FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF637D
        FF6B86FF2151FF1845FF2151FF2959FF315DFF395DEFFF00FFFF00FFFF00FFFF
        00FFFF00FFFF00FFFF00FFFF00FF6B7DD67B92FF4269FF0038FF1045FF214DFF
        2151FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
        FF849AFF7392FF1845FF0034FF0038FF1845FFFF00FFFF00FFFF00FFFF00FFFF
        00FFFF00FFFF00FFFF00FFFF00FFFF00FF849AEF94A6FF8CA2FF6B8EFF5275FF
        FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
        FFFF00FFFF00FF8C8EB59C9EC6FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
        00FF}
      Transparent = True
      Visible = False
    end
    object lblCharacterSetName: TLabel
      Left = 12
      Top = 11
      Width = 27
      Height = 13
      Caption = 'Name'
    end
    object lblCharacterSetFormat: TLabel
      Left = 12
      Top = 38
      Width = 34
      Height = 13
      Caption = 'Format'
    end
    object lblCharacterSetWidth: TLabel
      Left = 12
      Top = 65
      Width = 28
      Height = 13
      Caption = 'Width'
    end
    object lblCharacterSetHeight: TLabel
      Left = 155
      Top = 65
      Width = 31
      Height = 13
      Alignment = taRightJustify
      Caption = 'Height'
    end
    object edtCharacterSetName: TEdit
      Left = 52
      Top = 8
      Width = 220
      Height = 21
      Hint = 'Character Set Name|The name of the character set'
      Color = clWhite
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnChange = edtCharacterSetNameChange
    end
    object cmbCharacterSetFormat: TComboBox
      Left = 52
      Top = 35
      Width = 220
      Height = 21
      Hint = 
        'Character Set Format|The graphic format of the character set obj' +
        'ect'
      Style = csDropDownList
      Color = clWhite
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Pitch = fpVariable
      Font.Style = []
      ItemHeight = 13
      ItemIndex = 0
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      Text = 'ZX Spectrum'
      OnChange = cmbCharacterSetFormatChange
      Items.Strings = (
        'ZX Spectrum'
        'Sam Coupe'
        'Amstrad CPC464/6128')
    end
    object cmdCharacterSetAdd: TBitBtn
      Left = 52
      Top = 111
      Width = 80
      Height = 24
      Hint = 
        'Add Character Set|Add the current character set details to the l' +
        'ist'
      Caption = 'Add'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
      OnClick = cmdCharacterSetAddClick
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDDDDDDDDDDDDDDDDDDDDDDDD77777DDDDDDDDDD000007DDDDDDDDDD0AAA07D
        DDDDDDD770AAA07777DDDD0000AAA00007DDDD0AAAAAAAAA07DDDD0AAAAAAAAA
        07DDDD0AAAAAAAAA07DDDD0000AAA0000DDDDDDDD0AAA07DDDDDDDDDD0AAA07D
        DDDDDDDDD00000DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD}
    end
    object cmdCharacterSetRemove: TBitBtn
      Left = 192
      Top = 111
      Width = 80
      Height = 24
      Hint = 
        'Remove Character Set|Remove the selected character set from the ' +
        'list'
      Caption = 'Remove'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 3
      OnClick = cmdCharacterSetRemoveClick
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
        DDDDDDD77777777777DDDD000000000007DDDD099999999907DDDD0999999999
        07DDDD099999999907DDDD00000000000DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
        DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD}
    end
    object cmdCharacterSetRename: TBitBtn
      Left = 192
      Top = 141
      Width = 80
      Height = 24
      Hint = 'Rename Character Set|Rename the current character set'
      Caption = 'Rename'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 4
      OnClick = cmdCharacterSetRenameClick
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD07DDDDDDDDDDDDDD007
        DDDDDDD7777770C07DDDDD00000000CC07DDDD0CCCCCCCCCC07DDD0CCCCCCCCC
        CC0DDD0CCCCCCCCCC0DDDD00000000CC0DDDDDDDDDDDD0C0DDDDDDDDDDDDD00D
        DDDDDDDDDDDDD0DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD}
    end
    object cmdCharacterSetClone: TBitBtn
      Left = 52
      Top = 141
      Width = 80
      Height = 24
      Hint = 
        'Clone Character Set|Clone (Copy) the current character set as a ' +
        'new character set item'
      Caption = 'Clone'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 5
      OnClick = cmdCharacterSetCloneClick
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000010000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDD7777777
        7777DDDD000000000007DDDD033333333307DD77033333333307D00000000000
        3307D0BBBBBBBBB03307D0BBBBBBBBB03307D0BBBBBBBBB03307D0BBBBBBBBB0
        3307D0BBBBBBBBB03307D0BBBBBBBBB03307D0BBBBBBBBB0000DD0BBBBBBBBB0
        7DDDD0BBBBBBBBB07DDDD00000000000DDDDDDDDDDDDDDDDDDDD}
    end
    object edtCharacterSetWidth: KSpinEdit
      Left = 52
      Top = 62
      Width = 80
      Height = 20
      Hint = 'Character Width|The width of the character'
      BevelOuter = bvLowered
      Color = clWhite
      TabOrder = 6
      Value = 8
      Min = 4
      Max = 64
      Step = 8
      DesignSize = (
        80
        20)
    end
    object edtCharacterSetHeight: KSpinEdit
      Left = 192
      Top = 62
      Width = 80
      Height = 20
      Hint = 'Character Height|The height of the character'
      BevelOuter = bvLowered
      Color = clWhite
      TabOrder = 7
      Value = 8
      Min = 8
      Max = 64
      Step = 8
      DesignSize = (
        80
        20)
    end
    object panCharacters: TPanel
      Left = 52
      Top = 473
      Width = 220
      Height = 392
      Anchors = [akLeft, akTop, akBottom]
      Color = clWhite
      ParentBackground = False
      TabOrder = 8
      object sbxCharacters: TScrollBox
        Left = 1
        Top = 1
        Width = 218
        Height = 390
        Hint = 'The characters of the font'
        HorzScrollBar.Smooth = True
        HorzScrollBar.Style = ssFlat
        HorzScrollBar.Tracking = True
        VertScrollBar.Smooth = True
        VertScrollBar.Style = ssFlat
        VertScrollBar.Tracking = True
        Align = alClient
        BevelInner = bvNone
        BevelOuter = bvNone
        BevelKind = bkTile
        BorderStyle = bsNone
        Color = clWhite
        Ctl3D = True
        ParentColor = False
        ParentCtl3D = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        object pbxCharacterSetPreview: TPaintBox
          Left = 0
          Top = 0
          Width = 218
          Height = 390
          Hint = 
            'Font Character Window|Shows all the character that make up the f' +
            'ont'
          Align = alClient
          Color = clWhite
          ParentColor = False
          OnMouseDown = pbxCharacterSetPreviewMouseDown
          OnPaint = pbxCharacterSetPreviewPaint
          ExplicitWidth = 209
          ExplicitHeight = 310
        end
      end
    end
    object lstCharacterSetList: TListBox
      Left = 52
      Top = 176
      Width = 220
      Height = 133
      Hint = 'List of Character Sets'
      BevelKind = bkFlat
      BorderStyle = bsNone
      Color = clWhite
      ItemHeight = 13
      TabOrder = 9
      OnClick = lstCharacterSetListClick
    end
    object chkTileMasked: TCheckBox
      Left = 52
      Top = 89
      Width = 178
      Height = 16
      Caption = 'Font is Masked'
      Color = clWhite
      ParentColor = False
      TabOrder = 10
    end
    object Panel1: TPanel
      Left = 56
      Top = 316
      Width = 212
      Height = 150
      AutoSize = True
      BevelKind = bkFlat
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 11
      object spdCharacterSetSpace: TSpeedButton
        Left = 0
        Top = 0
        Width = 13
        Height = 24
        Caption = ' '
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetExclamation: TSpeedButton
        Tag = 1
        Left = 13
        Top = 0
        Width = 13
        Height = 24
        Caption = '!'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetQuoteDouble: TSpeedButton
        Tag = 2
        Left = 26
        Top = 0
        Width = 13
        Height = 24
        Caption = '"'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetHash: TSpeedButton
        Tag = 3
        Left = 39
        Top = 0
        Width = 13
        Height = 24
        Caption = '#'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetDollar: TSpeedButton
        Tag = 4
        Left = 52
        Top = 0
        Width = 13
        Height = 24
        Caption = '$'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetPercentage: TSpeedButton
        Tag = 5
        Left = 65
        Top = 0
        Width = 13
        Height = 24
        Caption = '%'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetAmpersand: TSpeedButton
        Tag = 6
        Left = 78
        Top = 0
        Width = 13
        Height = 24
        Caption = '&&'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetQuoteSingle: TSpeedButton
        Tag = 7
        Left = 91
        Top = 0
        Width = 13
        Height = 24
        Caption = #39
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetBracketOpen: TSpeedButton
        Tag = 8
        Left = 104
        Top = 0
        Width = 13
        Height = 24
        Caption = '('
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetBracketClosed: TSpeedButton
        Tag = 9
        Left = 117
        Top = 0
        Width = 13
        Height = 24
        Caption = ')'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetAsterix: TSpeedButton
        Tag = 10
        Left = 130
        Top = 0
        Width = 13
        Height = 24
        Caption = '*'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetPlus: TSpeedButton
        Tag = 11
        Left = 143
        Top = 0
        Width = 13
        Height = 24
        Caption = '+'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetComma: TSpeedButton
        Tag = 12
        Left = 156
        Top = 0
        Width = 13
        Height = 24
        Caption = ','
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetMinus: TSpeedButton
        Tag = 13
        Left = 169
        Top = 0
        Width = 13
        Height = 24
        Caption = '-'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetPeriod: TSpeedButton
        Tag = 14
        Left = 182
        Top = 0
        Width = 13
        Height = 24
        Caption = '.'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetSlashForward: TSpeedButton
        Tag = 15
        Left = 195
        Top = 0
        Width = 13
        Height = 24
        Caption = '/'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet0: TSpeedButton
        Tag = 16
        Left = 0
        Top = 24
        Width = 13
        Height = 25
        Caption = '0'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet1: TSpeedButton
        Tag = 17
        Left = 13
        Top = 24
        Width = 13
        Height = 25
        Caption = '1'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet2: TSpeedButton
        Tag = 18
        Left = 26
        Top = 24
        Width = 13
        Height = 25
        Caption = '2'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet3: TSpeedButton
        Tag = 19
        Left = 39
        Top = 24
        Width = 13
        Height = 25
        Caption = '3'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet4: TSpeedButton
        Tag = 20
        Left = 52
        Top = 24
        Width = 13
        Height = 25
        Caption = '4'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet5: TSpeedButton
        Tag = 21
        Left = 65
        Top = 24
        Width = 13
        Height = 25
        Caption = '5'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet6: TSpeedButton
        Tag = 22
        Left = 78
        Top = 24
        Width = 13
        Height = 25
        Caption = '6'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet7: TSpeedButton
        Tag = 23
        Left = 91
        Top = 24
        Width = 13
        Height = 25
        Caption = '7'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet8: TSpeedButton
        Tag = 24
        Left = 104
        Top = 24
        Width = 13
        Height = 25
        Caption = '8'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet9: TSpeedButton
        Tag = 25
        Left = 117
        Top = 24
        Width = 13
        Height = 25
        Caption = '9'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetColon: TSpeedButton
        Tag = 26
        Left = 130
        Top = 24
        Width = 13
        Height = 25
        Caption = ':'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetColonSemi: TSpeedButton
        Tag = 27
        Left = 143
        Top = 24
        Width = 13
        Height = 25
        Caption = ';'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetCompareLessThan: TSpeedButton
        Tag = 28
        Left = 156
        Top = 24
        Width = 13
        Height = 25
        Caption = '<'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetCompareEquals: TSpeedButton
        Tag = 29
        Left = 169
        Top = 24
        Width = 13
        Height = 25
        Caption = '='
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetCompareGreaterThan: TSpeedButton
        Tag = 30
        Left = 182
        Top = 24
        Width = 13
        Height = 25
        Caption = '>'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetQuestionMark: TSpeedButton
        Tag = 31
        Left = 195
        Top = 24
        Width = 13
        Height = 25
        Caption = '?'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetAt: TSpeedButton
        Tag = 32
        Left = 0
        Top = 49
        Width = 13
        Height = 24
        Caption = '@'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__A: TSpeedButton
        Tag = 33
        Left = 13
        Top = 49
        Width = 13
        Height = 24
        Caption = 'A'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__B: TSpeedButton
        Tag = 34
        Left = 26
        Top = 49
        Width = 13
        Height = 24
        Caption = 'B'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__C: TSpeedButton
        Tag = 35
        Left = 39
        Top = 49
        Width = 13
        Height = 24
        Caption = 'C'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__D: TSpeedButton
        Tag = 36
        Left = 52
        Top = 49
        Width = 13
        Height = 24
        Caption = 'D'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__E: TSpeedButton
        Tag = 37
        Left = 65
        Top = 49
        Width = 13
        Height = 24
        Caption = 'E'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__F: TSpeedButton
        Tag = 38
        Left = 78
        Top = 49
        Width = 13
        Height = 24
        Caption = 'F'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__G: TSpeedButton
        Tag = 39
        Left = 91
        Top = 49
        Width = 13
        Height = 24
        Caption = 'G'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__H: TSpeedButton
        Tag = 40
        Left = 104
        Top = 49
        Width = 13
        Height = 24
        Caption = 'H'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__I: TSpeedButton
        Tag = 41
        Left = 117
        Top = 49
        Width = 13
        Height = 24
        Caption = 'I'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__J: TSpeedButton
        Tag = 42
        Left = 130
        Top = 49
        Width = 13
        Height = 24
        Caption = 'J'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__K: TSpeedButton
        Tag = 43
        Left = 143
        Top = 49
        Width = 13
        Height = 24
        Caption = 'K'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__L: TSpeedButton
        Tag = 44
        Left = 156
        Top = 49
        Width = 13
        Height = 24
        Caption = 'L'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__M: TSpeedButton
        Tag = 45
        Left = 169
        Top = 49
        Width = 13
        Height = 24
        Caption = 'M'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__N: TSpeedButton
        Tag = 46
        Left = 182
        Top = 49
        Width = 13
        Height = 24
        Caption = 'N'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__O: TSpeedButton
        Tag = 47
        Left = 195
        Top = 49
        Width = 13
        Height = 24
        Caption = 'O'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__P: TSpeedButton
        Tag = 48
        Left = 0
        Top = 73
        Width = 13
        Height = 25
        Caption = 'P'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__Q: TSpeedButton
        Tag = 49
        Left = 13
        Top = 73
        Width = 13
        Height = 25
        Caption = 'Q'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__R: TSpeedButton
        Tag = 50
        Left = 26
        Top = 73
        Width = 13
        Height = 25
        Caption = 'R'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__S: TSpeedButton
        Tag = 51
        Left = 39
        Top = 73
        Width = 13
        Height = 25
        Caption = 'S'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__T: TSpeedButton
        Tag = 52
        Left = 52
        Top = 73
        Width = 13
        Height = 25
        Caption = 'T'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__U: TSpeedButton
        Tag = 53
        Left = 65
        Top = 73
        Width = 13
        Height = 25
        Caption = 'U'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__V: TSpeedButton
        Tag = 54
        Left = 78
        Top = 73
        Width = 13
        Height = 25
        Caption = 'V'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__W: TSpeedButton
        Tag = 55
        Left = 91
        Top = 73
        Width = 13
        Height = 25
        Caption = 'W'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__X: TSpeedButton
        Tag = 56
        Left = 104
        Top = 73
        Width = 13
        Height = 25
        Caption = 'X'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__Y: TSpeedButton
        Tag = 57
        Left = 117
        Top = 73
        Width = 13
        Height = 25
        Caption = 'Y'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet__Z: TSpeedButton
        Tag = 58
        Left = 130
        Top = 73
        Width = 13
        Height = 25
        Caption = 'Z'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetBraceSquareOpen: TSpeedButton
        Tag = 59
        Left = 143
        Top = 73
        Width = 13
        Height = 25
        Caption = '['
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetSlashBackwards: TSpeedButton
        Tag = 60
        Left = 156
        Top = 73
        Width = 13
        Height = 25
        Caption = '\'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetBraceSquareClosed: TSpeedButton
        Tag = 61
        Left = 169
        Top = 73
        Width = 13
        Height = 25
        Caption = ']'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetHat: TSpeedButton
        Tag = 62
        Left = 182
        Top = 73
        Width = 13
        Height = 25
        Caption = '^'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetUnderline: TSpeedButton
        Tag = 63
        Left = 195
        Top = 73
        Width = 13
        Height = 25
        Caption = '_'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetPound: TSpeedButton
        Tag = 64
        Left = 0
        Top = 98
        Width = 13
        Height = 24
        Caption = #163
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_a: TSpeedButton
        Tag = 65
        Left = 13
        Top = 98
        Width = 13
        Height = 24
        Caption = 'a'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_b: TSpeedButton
        Tag = 66
        Left = 26
        Top = 98
        Width = 13
        Height = 24
        Caption = 'b'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_c: TSpeedButton
        Tag = 67
        Left = 39
        Top = 98
        Width = 13
        Height = 24
        Caption = 'c'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_d: TSpeedButton
        Tag = 68
        Left = 52
        Top = 98
        Width = 13
        Height = 24
        Caption = 'd'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_e: TSpeedButton
        Tag = 69
        Left = 65
        Top = 98
        Width = 13
        Height = 24
        Caption = 'e'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_f: TSpeedButton
        Tag = 70
        Left = 78
        Top = 98
        Width = 13
        Height = 24
        Caption = 'f'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_g: TSpeedButton
        Tag = 71
        Left = 91
        Top = 98
        Width = 13
        Height = 24
        Caption = 'g'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_h: TSpeedButton
        Tag = 72
        Left = 104
        Top = 98
        Width = 13
        Height = 24
        Caption = 'h'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_i: TSpeedButton
        Tag = 73
        Left = 117
        Top = 98
        Width = 13
        Height = 24
        Caption = 'i'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_j: TSpeedButton
        Tag = 74
        Left = 130
        Top = 98
        Width = 13
        Height = 24
        Caption = 'j'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_k: TSpeedButton
        Tag = 75
        Left = 143
        Top = 98
        Width = 13
        Height = 24
        Caption = 'k'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_l: TSpeedButton
        Tag = 76
        Left = 156
        Top = 98
        Width = 13
        Height = 24
        Caption = 'l'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_m: TSpeedButton
        Tag = 77
        Left = 169
        Top = 98
        Width = 13
        Height = 24
        Caption = 'm'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_n: TSpeedButton
        Tag = 78
        Left = 182
        Top = 98
        Width = 13
        Height = 24
        Caption = 'n'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_o: TSpeedButton
        Tag = 79
        Left = 195
        Top = 98
        Width = 13
        Height = 24
        Caption = 'o'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_p: TSpeedButton
        Tag = 80
        Left = 0
        Top = 122
        Width = 13
        Height = 24
        Caption = 'p'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_q: TSpeedButton
        Tag = 81
        Left = 13
        Top = 122
        Width = 13
        Height = 24
        Caption = 'q'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_r: TSpeedButton
        Tag = 82
        Left = 26
        Top = 122
        Width = 13
        Height = 24
        Caption = 'r'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_s: TSpeedButton
        Tag = 83
        Left = 39
        Top = 122
        Width = 13
        Height = 24
        Caption = 's'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_t: TSpeedButton
        Tag = 84
        Left = 52
        Top = 122
        Width = 13
        Height = 24
        Caption = 't'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_u: TSpeedButton
        Tag = 85
        Left = 65
        Top = 122
        Width = 13
        Height = 24
        Caption = 'u'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_v: TSpeedButton
        Tag = 86
        Left = 78
        Top = 122
        Width = 13
        Height = 24
        Caption = 'v'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_w: TSpeedButton
        Tag = 87
        Left = 91
        Top = 122
        Width = 13
        Height = 24
        Caption = 'w'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_x: TSpeedButton
        Tag = 88
        Left = 104
        Top = 122
        Width = 13
        Height = 24
        Caption = 'x'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_y: TSpeedButton
        Tag = 89
        Left = 117
        Top = 122
        Width = 13
        Height = 24
        Caption = 'y'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSet_z: TSpeedButton
        Tag = 90
        Left = 130
        Top = 122
        Width = 13
        Height = 24
        Caption = 'z'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetBraceCurlyOpen: TSpeedButton
        Tag = 91
        Left = 143
        Top = 122
        Width = 13
        Height = 24
        Caption = '{'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetLine: TSpeedButton
        Tag = 92
        Left = 156
        Top = 122
        Width = 13
        Height = 24
        Caption = '|'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetBraceCurlyClosed: TSpeedButton
        Tag = 93
        Left = 169
        Top = 122
        Width = 13
        Height = 24
        Caption = '}'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetTide: TSpeedButton
        Tag = 94
        Left = 182
        Top = 122
        Width = 13
        Height = 24
        Caption = '~'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
      object spdCharacterSetCopyright: TSpeedButton
        Tag = 95
        Left = 195
        Top = 122
        Width = 13
        Height = 24
        Caption = #169
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Pitch = fpVariable
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = spdCharacterSetSpaceClick
      end
    end
  end
end
