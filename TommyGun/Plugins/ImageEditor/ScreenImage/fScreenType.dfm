object frmScreenType: TfrmScreenType
  Left = 1338
  Top = 111
  ClientHeight = 580
  ClientWidth = 283
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panScreens: TPanel
    Left = 0
    Top = 0
    Width = 283
    Height = 580
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
    object imgIcon: TImage
      Left = 11
      Top = 96
      Width = 16
      Height = 16
      AutoSize = True
      Picture.Data = {
        07544269746D617036030000424D360300000000000036000000280000001000
        000010000000010018000000000000030000130B0000130B0000000000000000
        0000FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
        FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFC6AA
        A5BDAAA5BDA29CA58A849C8A849C868484716BFF00FFFF00FFFF00FFFF00FFFF
        00FFFF00FFFF00FFFF00FFFF00FFEFDBDEF7EBEFE7CFCEEFDFDEE7D7D6E7D7D6
        DECBCEDECBCEA58E8CFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
        FF94756BC6A6A5E7D7DECEAAADDEC7C6E7CFCEEFDFDEF7EFEFB5968CFF00FFFF
        00FFFF00FFFF00FFFF00FFC69E9CC6A6A5947973BD9694CEA6ADAD8A84BD9694
        B5928C8C756B847163FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFD6C3C6E7C3
        B5EFC3B5EFCFC6E7CFCEDEC7C6CEAEADC6AAAD9C827BFF00FFFF00FFFF00FFFF
        00FFFF00FFFF00FFFF00FFDECFCEEFA28CFFAA84FFCBA5FFDFBDFFE7CEF7EBD6
        F7DFD6CECFB59CBA94CEB2ADFF00FFFF00FFFF00FFFF00FFFF00FFE7CBC6EF92
        7BFFA284FFC39CFFD7ADFFE7BDFFEBC6FFE7BDFFDFBDFFD3B5FFC7B5FF00FFFF
        00FFFF00FFFF00FFC6AEADDEC3BDF77963FF9A7BFFB294FFCBA5FFD7ADFFDBB5
        FFD7ADFFCBA5FFB294FFA284FF00FFFF00FFFF00FFFF00FFD6C7C6DEA69CFF69
        52FF866BFF9E84FFAE8CFFBA94FFC39CFFBE9CFFB294FF9E7BFFA28CFF00FFFF
        00FFFF00FFFF00FFE7DFDEDE7D73FF594AFF7563FF8A73FF9E8CFFAE94FFB69C
        FFB29CFFAA94FF9A84F7AA9CFF00FFFF00FFFF00FFFF00FFE7D7D6DE867BFF96
        94FF9E94FFAA9CFFB2A5FFB6ADFFB6ADFFB2A5FFAAA5FF9E94EFB2ADFF00FFFF
        00FFFF00FFFF00FFE7D3CEE78E8CFFA6A5FFB2ADFFB6B5FFB6B5FFBAB5FFB6B5
        FFB2ADFFAEADFFA6A5DEB2ADFF00FFFF00FFFF00FFFF00FFDEC7C6CE9A94DEA6
        9CDE9A94DE968CE79E9CEFAAA5EFB2ADFFB6B5FFB6B5F7AAA5FF00FFFF00FFFF
        00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
        FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
        FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
        00FF}
      Transparent = True
      Visible = False
    end
    object lblScreenName: TLabel
      Left = 12
      Top = 11
      Width = 27
      Height = 13
      Caption = 'Name'
    end
    object lblScreenFormat: TLabel
      Left = 12
      Top = 38
      Width = 34
      Height = 13
      Caption = 'Format'
    end
    object lblScreensHeight: TLabel
      Left = 155
      Top = 65
      Width = 31
      Height = 13
      Alignment = taRightJustify
      Caption = 'Height'
    end
    object lblScreensWidth: TLabel
      Left = 12
      Top = 65
      Width = 28
      Height = 13
      Caption = 'Width'
    end
    object edtScreenName: TEdit
      Left = 52
      Top = 8
      Width = 220
      Height = 21
      Hint = 'Screen Name|The name of the screen'
      Color = clWhite
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnChange = edtScreenNameChange
    end
    object cmbScreenFormat: TComboBox
      Left = 52
      Top = 35
      Width = 220
      Height = 21
      Hint = 'Screen Format|The graphic format of the screen object'
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 13
      ItemIndex = 0
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      Text = 'ZX Spectrum'
      OnChange = cmbScreenFormatChange
      Items.Strings = (
        'ZX Spectrum'
        'Sam Coupe'
        'Amstrad CPC464/6128')
    end
    object cmdScreenAdd: TBitBtn
      Left = 52
      Top = 111
      Width = 80
      Height = 24
      Hint = 'Add Screen|Add the current screen details to the list'
      Caption = 'Add'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
      OnClick = cmdScreenAddClick
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
    object cmdScreenRemove: TBitBtn
      Left = 192
      Top = 111
      Width = 80
      Height = 24
      Hint = 'Remove Screen|Remove the selected screen from the list'
      Caption = 'Remove'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 3
      OnClick = cmdScreenRemoveClick
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
    object panScreenPreview: TPanel
      Left = 12
      Top = 376
      Width = 260
      Height = 196
      BevelKind = bkTile
      BevelOuter = bvNone
      Color = clWhite
      TabOrder = 4
      object pbxScreenPreview: TPaintBox
        Left = 0
        Top = 0
        Width = 256
        Height = 192
        Hint = 'Animation Window|Shows the sprite animation'
        Align = alClient
        OnPaint = pbxScreenPreviewPaint
        ExplicitTop = 1
        ExplicitHeight = 190
      end
    end
    object cmdScreenRename: TBitBtn
      Left = 192
      Top = 141
      Width = 80
      Height = 24
      Hint = 'Rename Screen|Rename the current screen'
      Caption = 'Rename'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 5
      OnClick = cmdScreenRenameClick
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
    object cmdScreenClone: TBitBtn
      Left = 52
      Top = 141
      Width = 80
      Height = 24
      Hint = 
        'Clone Screen|Clone (Copy) the current screen as a new screen ite' +
        'm'
      Caption = 'Clone'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 6
      OnClick = cmdScreenCloneClick
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
    object lstScreenList: TListBox
      Left = 52
      Top = 199
      Width = 220
      Height = 166
      Hint = 'List of Screens'
      BevelKind = bkFlat
      BorderStyle = bsNone
      Color = clWhite
      ItemHeight = 13
      TabOrder = 7
      OnClick = lstScreenListClick
    end
    object edtScreensWidth: KSpinEdit
      Left = 52
      Top = 62
      Width = 80
      Height = 20
      BevelOuter = bvLowered
      Color = clWhite
      TabOrder = 8
      Max = 1024
      DesignSize = (
        80
        20)
    end
    object edtScreensHeight: KSpinEdit
      Left = 192
      Top = 62
      Width = 80
      Height = 20
      BevelOuter = bvLowered
      Color = clWhite
      TabOrder = 9
      Max = 1024
      DesignSize = (
        80
        20)
    end
  end
end
