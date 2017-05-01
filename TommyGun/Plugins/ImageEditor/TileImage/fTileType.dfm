object frmTileType: TfrmTileType
  Left = 1278
  Top = 341
  ClientHeight = 700
  ClientWidth = 287
  Color = clWhite
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panTiles: TPanel
    Left = 0
    Top = 0
    Width = 287
    Height = 700
    Align = alClient
    BevelOuter = bvNone
    Color = clWhite
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentBackground = False
    ParentFont = False
    TabOrder = 0
    object imgIcon: TImage
      Left = 12
      Top = 89
      Width = 16
      Height = 16
      AutoSize = True
      Picture.Data = {
        07544269746D617036030000424D360300000000000036000000280000001000
        000010000000010018000000000000030000130B0000130B0000000000000000
        0000FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFA82BE3009CC521BCF32CDAFD
        26E3FF00F2FFCA2DFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
        FFBB1CD7007992108FDC1DAFE727CCFA2DDAFF18E0FF00DAF0D81CFCFF00FFFF
        00FFFF00FFFF00FFFF00FFF30DD6B84B0090402A17669C0D88DD1DA5DE27C4F1
        2CD8FD1FDAFF00ECFFD820FFFF00FFFF00FFEF9A73DD8C69DE754EDF603EDD4E
        26A63A182B567D0087DF199BD927BEF22BD6FD27DDFF0CDFFF00A1C0E90CF8FF
        00FFFFB694FEC29AEB956ADC6741E35329C63C1444485A0080D81393D61DB4E7
        28D0FB26DCFF14DDFF00CBF0E810FDFF00FFFFAE8CFFC69CF49E7CE36F48DF56
        32D5401A6D3F3B0670B7118FDC1DABE727CAFB2DDAFF17DEFF00E0FFE812FFFF
        00FFFFA67BFFC89DF4AB85E47B50DB5C3ADF47199F3A1E0B5F9A0F83D22782A5
        2F8694348E96279DAC00C4C5E811FBFF00FFFF9E7BFFC09DFDB88DEA8359D963
        41E14D23AE3F202B4A622F5363315742287E592A946D23885E088447EA0BF0FF
        00FFFF9A73FFB996FDC498EC8E69E46945E1552ACE4D286B39251B58371A8A59
        21A57327BD8329CB862AC98011AA50FF00FFEF9673FFB587FFCA9BFCA071EE7C
        50EA7750AD70816961772D7349137E5A219B6C27B48029C5862AC67E21BB7129
        4D31FF00FF3A68B87379AA8F82A36D74AC265AD6003FEE515CAD4D765009744D
        1D966427B07629C58329C5862AC178216D4AFF00FF1E75F73490F742A2F72982
        F7105AF50041F34452C55A785D0C71451E8C6120AB7727C08329C8862AC27721
        925AFF00FF166CF73E8EF84CB1FF3992FD1865F30047F32746E064737A247246
        17825B21A26D27B98129C6852AC57D21AE6BFF00FF1E6CF73584F84EACFF439C
        FD1D6BF3034EF1033AEC5E70953F7B460E7A5718996717B47F20C58520C88529
        BE73FF00FF2E6FDE3277F946A8F946A8FF2779F30F5AEF0035F75262B34E7D4F
        269746D42AD7FF00FFFF00FFFF00FFFF00FFFF00FFF206FE1878EE479DFA48AD
        FE3184F61560F40046EC8715F8FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
        00FF}
      Transparent = True
      Visible = False
    end
    object lblTileName: TLabel
      Left = 12
      Top = 11
      Width = 27
      Height = 13
      Caption = 'Name'
    end
    object lblTileFormat: TLabel
      Left = 12
      Top = 38
      Width = 34
      Height = 13
      Caption = 'Format'
    end
    object lblTileWidth: TLabel
      Left = 12
      Top = 65
      Width = 28
      Height = 13
      Caption = 'Width'
    end
    object lblTileHeight: TLabel
      Left = 155
      Top = 65
      Width = 31
      Height = 13
      Alignment = taRightJustify
      Caption = 'Height'
    end
    object lblType: TLabel
      Left = 12
      Top = 174
      Width = 24
      Height = 13
      Caption = 'Type'
    end
    object cmbTileFormat: TComboBox
      Left = 52
      Top = 35
      Width = 220
      Height = 21
      Hint = 'Tile Format|The graphic format of the tile object'
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 13
      ItemIndex = 0
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      Text = 'ZX Spectrum'
      OnChange = cmbTileFormatChange
      Items.Strings = (
        'ZX Spectrum'
        'Sam Coupe'
        'Amstrad CPC464/6128')
    end
    object cmdTileAdd: TBitBtn
      Left = 52
      Top = 111
      Width = 80
      Height = 24
      Hint = 'Add Tile|Add the current tile details to the list'
      Caption = 'Add'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnClick = cmdTileAddClick
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
    object cmdTileRemove: TBitBtn
      Left = 192
      Top = 111
      Width = 80
      Height = 24
      Hint = 'Remove Tile|Remove the selected tile from the list'
      Caption = 'Remove'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
      OnClick = cmdTileRemoveClick
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
    object panTilePreview: TPanel
      Left = 12
      Top = 372
      Width = 260
      Height = 257
      BevelKind = bkFlat
      BevelOuter = bvNone
      Color = clCream
      ParentBackground = False
      TabOrder = 3
      object pbxTilePreview: TPaintBox
        Left = 0
        Top = 0
        Width = 128
        Height = 128
        Hint = 'Tile Window|Shows the tile'
        OnPaint = pbxTilePreviewPaint
      end
    end
    object cmdTileRename: TBitBtn
      Left = 192
      Top = 141
      Width = 80
      Height = 24
      Hint = 'Rename Tile|Rename the current tile'
      Caption = 'Rename'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 4
      OnClick = cmdTileRenameClick
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
    object cmdTileClone: TBitBtn
      Left = 52
      Top = 141
      Width = 80
      Height = 24
      Hint = 'Clone Tile|Clone (Copy) the current tile as a new screen item'
      Caption = 'Clone'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 5
      OnClick = cmdTileCloneClick
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
    object edtTileWidth: KSpinEdit
      Left = 52
      Top = 62
      Width = 80
      Height = 20
      Hint = 'Tile Width|The width of the tile'
      BevelOuter = bvLowered
      Color = clWhite
      TabOrder = 6
      Value = 32
      Min = 4
      Max = 1024
      Step = 8
      DesignSize = (
        80
        20)
    end
    object edtTileHeight: KSpinEdit
      Left = 192
      Top = 62
      Width = 80
      Height = 20
      Hint = 'Tile Height|The height of the tile'
      BevelOuter = bvLowered
      Color = clWhite
      TabOrder = 7
      Value = 32
      Min = 4
      Max = 1024
      Step = 8
      DesignSize = (
        80
        20)
    end
    object lstTileList: TListBox
      Left = 52
      Top = 198
      Width = 220
      Height = 168
      Hint = 'List of Tiles'
      BevelKind = bkFlat
      BorderStyle = bsNone
      Color = clWhite
      ItemHeight = 13
      TabOrder = 8
      OnClick = lstTileListClick
    end
    object edtTileName: TEdit
      Left = 52
      Top = 8
      Width = 220
      Height = 21
      Hint = 'Tile Name|The name of the tile'
      BevelInner = bvNone
      Color = clWhite
      ParentShowHint = False
      ShowHint = True
      TabOrder = 9
      OnChange = edtTileNameChange
      OnEnter = cmbTileFormatChange
    end
    object chkTileMasked: TCheckBox
      Left = 52
      Top = 88
      Width = 220
      Height = 17
      Caption = 'Tile is Masked'
      Color = clWhite
      ParentColor = False
      TabOrder = 10
    end
    object cmbType: TComboBox
      Left = 52
      Top = 172
      Width = 188
      Height = 21
      Hint = 'Tile Type|The type of tile or character block.'
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 13
      ItemIndex = 0
      ParentShowHint = False
      ShowHint = True
      TabOrder = 11
      Text = 'Empty Space'
      OnChange = cmbTypeChange
      Items.Strings = (
        'Empty Space'
        'Normal Platform'
        'Solid Wall'
        'Ladder'
        'Fodder'
        'Deadly')
    end
    object btnType: TButton
      Left = 246
      Top = 172
      Width = 26
      Height = 21
      Hint = 'Define Type values'
      Caption = '...'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 12
    end
  end
end
