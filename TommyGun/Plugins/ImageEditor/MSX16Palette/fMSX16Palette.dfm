object frmMSX16Palette: TfrmMSX16Palette
  Left = 359
  Top = 261
  ClientHeight = 110
  ClientWidth = 456
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panMSX16Palette: TPanel
    Left = 0
    Top = 16
    Width = 456
    Height = 94
    Align = alBottom
    BevelOuter = bvNone
    Constraints.MaxHeight = 94
    Constraints.MinHeight = 94
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    ExplicitTop = 18
    DesignSize = (
      456
      94)
    object lblMSXPalette: TLabel
      Left = 80
      Top = 12
      Width = 124
      Height = 13
      Caption = 'MSX 16 Colour Palette'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lblPaletteInk: TLabel
      Left = 8
      Top = 40
      Width = 22
      Height = 13
      Caption = 'Fore'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object lblPalettePaper: TLabel
      Left = 8
      Top = 68
      Width = 22
      Height = 13
      Caption = 'Back'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object spdInkBlack: TSpeedButton
      Left = 40
      Top = 36
      Width = 24
      Height = 24
      Hint = 'Color - Attribute will be set the selected color'
      GroupIndex = 1
      Flat = True
      Glyph.Data = {
        FE000000424DFE00000000000000760000002800000010000000110000000100
        0400000000008800000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDD000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000}
      ParentShowHint = False
      ShowHint = True
      OnClick = spdInkBlackClick
    end
    object spdInkBlue: TSpeedButton
      Tag = 1
      Left = 64
      Top = 36
      Width = 24
      Height = 24
      Hint = 'Color - Attribute will be set the selected color'
      GroupIndex = 1
      Flat = True
      Glyph.Data = {
        FE000000424DFE00000000000000760000002800000010000000110000000100
        0400000000008800000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDDCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
        CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
        CCCC444444444444444444444444444444444444444444444444444444444444
        4444444444444444444444444444444444444444444444444444444444444444
        4444}
      ParentShowHint = False
      ShowHint = True
      OnClick = spdInkBlackClick
    end
    object spdInkRed: TSpeedButton
      Tag = 2
      Left = 88
      Top = 36
      Width = 24
      Height = 24
      Hint = 'Color - Attribute will be set the selected color'
      GroupIndex = 1
      Flat = True
      Glyph.Data = {
        FE000000424DFE00000000000000760000002800000010000000110000000100
        0400000000008800000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDD999999999999999999999999999999999999999999999999999999999999
        9999999999999999999999999999999999999999999999999999999999999999
        9999111111111111111111111111111111111111111111111111111111111111
        1111111111111111111111111111111111111111111111111111111111111111
        1111}
      ParentShowHint = False
      ShowHint = True
      OnClick = spdInkBlackClick
    end
    object spdInkPurple: TSpeedButton
      Tag = 3
      Left = 112
      Top = 36
      Width = 24
      Height = 24
      Hint = 'Color - Attribute will be set the selected color'
      GroupIndex = 1
      Flat = True
      Glyph.Data = {
        FE000000424DFE00000000000000760000002800000010000000110000000100
        0400000000008800000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
        FFFFDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
        DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
        DDDD555555555555555555555555555555555555555555555555555555555555
        5555555555555555555555555555555555555555555555555555555555555555
        5555}
      ParentShowHint = False
      ShowHint = True
      OnClick = spdInkBlackClick
    end
    object spdInkGreen: TSpeedButton
      Tag = 4
      Left = 136
      Top = 36
      Width = 24
      Height = 24
      Hint = 'Color - Attribute will be set the selected color'
      GroupIndex = 1
      Flat = True
      Glyph.Data = {
        FE000000424DFE00000000000000760000002800000010000000110000000100
        0400000000008800000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDDAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        AAAA222222222222222222222222222222222222222222222222222222222222
        2222222222222222222222222222222222222222222222222222222222222222
        2222}
      ParentShowHint = False
      ShowHint = True
      OnClick = spdInkBlackClick
    end
    object spdInkCyan: TSpeedButton
      Tag = 5
      Left = 160
      Top = 36
      Width = 24
      Height = 24
      Hint = 'Color - Attribute will be set the selected color'
      GroupIndex = 1
      Flat = True
      Glyph.Data = {
        FE000000424DFE00000000000000760000002800000010000000110000000100
        0400000000008800000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDDEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
        EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
        EEEE666666666666666666666666666666666666666666666666666666666666
        6666666666666666666666666666666666666666666666666666666666666666
        6666}
      ParentShowHint = False
      ShowHint = True
      OnClick = spdInkBlackClick
    end
    object spdInkYellow: TSpeedButton
      Tag = 6
      Left = 184
      Top = 36
      Width = 24
      Height = 24
      Hint = 'Color - Attribute will be set the selected color'
      GroupIndex = 1
      Flat = True
      Glyph.Data = {
        FE000000424DFE00000000000000760000002800000010000000110000000100
        0400000000008800000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDDBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
        BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
        BBBB333333333333333333333333333333333333333333333333333333333333
        3333333333333333333333333333333333333333333333333333333333333333
        3333}
      ParentShowHint = False
      ShowHint = True
      OnClick = spdInkBlackClick
    end
    object spdInkWhite: TSpeedButton
      Tag = 7
      Left = 208
      Top = 36
      Width = 24
      Height = 24
      Hint = 'Color - Attribute will be set the selected color'
      GroupIndex = 1
      Down = True
      Flat = True
      Glyph.Data = {
        FE000000424DFE00000000000000760000002800000010000000110000000100
        0400000000008800000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDDFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFF777777777777777777777777777777777777777777777777777777777777
        7777777777777777777777777777777777777777777777777777777777777777
        7777}
      ParentShowHint = False
      ShowHint = True
      OnClick = spdInkBlackClick
    end
    object spdInkTransparent: TSpeedButton
      Tag = 8
      Left = 232
      Top = 36
      Width = 24
      Height = 24
      Hint = 'Transparent - attribute will remain unchanged'
      GroupIndex = 1
      Flat = True
      Glyph.Data = {
        FE000000424DFE00000000000000760000002800000010000000110000000100
        0400000000008800000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
        DDDDDDDDDDD00DDDDDDDDDDDDDD00DDDDDDDDDDDDDD00DDDDDDDDDDDDDD00DDD
        DDDDDDDDDDD00DDDDDDDDDDDDDD00DDDDDDDDDDDDDD00DDDDDDDDDDDDD0000DD
        DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
        DDDD}
      ParentShowHint = False
      ShowHint = True
      OnClick = spdInkBlackClick
    end
    object spdPaperBlack: TSpeedButton
      Left = 40
      Top = 64
      Width = 24
      Height = 24
      Hint = 'Color - Attribute will be set the selected color'
      GroupIndex = 2
      Down = True
      Flat = True
      Glyph.Data = {
        FE000000424DFE00000000000000760000002800000010000000110000000100
        0400000000008800000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDD000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000}
      ParentShowHint = False
      ShowHint = True
      OnClick = spdPaperBlackClick
    end
    object spdPaperBlue: TSpeedButton
      Tag = 1
      Left = 64
      Top = 64
      Width = 24
      Height = 24
      Hint = 'Color - Attribute will be set the selected color'
      GroupIndex = 2
      Flat = True
      Glyph.Data = {
        FE000000424DFE00000000000000760000002800000010000000110000000100
        0400000000008800000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDDCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
        CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
        CCCC444444444444444444444444444444444444444444444444444444444444
        4444444444444444444444444444444444444444444444444444444444444444
        4444}
      ParentShowHint = False
      ShowHint = True
      OnClick = spdPaperBlackClick
    end
    object spdPaperRed: TSpeedButton
      Tag = 2
      Left = 88
      Top = 64
      Width = 24
      Height = 24
      Hint = 'Color - Attribute will be set the selected color'
      GroupIndex = 2
      Flat = True
      Glyph.Data = {
        FE000000424DFE00000000000000760000002800000010000000110000000100
        0400000000008800000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDD999999999999999999999999999999999999999999999999999999999999
        9999999999999999999999999999999999999999999999999999999999999999
        9999111111111111111111111111111111111111111111111111111111111111
        1111111111111111111111111111111111111111111111111111111111111111
        1111}
      ParentShowHint = False
      ShowHint = True
      OnClick = spdPaperBlackClick
    end
    object spdPaperPurple: TSpeedButton
      Tag = 3
      Left = 112
      Top = 64
      Width = 24
      Height = 24
      Hint = 'Color - Attribute will be set the selected color'
      GroupIndex = 2
      Flat = True
      Glyph.Data = {
        FE000000424DFE00000000000000760000002800000010000000110000000100
        0400000000008800000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
        FFFFDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
        DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
        DDDD555555555555555555555555555555555555555555555555555555555555
        5555555555555555555555555555555555555555555555555555555555555555
        5555}
      ParentShowHint = False
      ShowHint = True
      OnClick = spdPaperBlackClick
    end
    object spdPaperGreen: TSpeedButton
      Tag = 4
      Left = 136
      Top = 64
      Width = 24
      Height = 24
      Hint = 'Color - Attribute will be set the selected color'
      GroupIndex = 2
      Flat = True
      Glyph.Data = {
        FE000000424DFE00000000000000760000002800000010000000110000000100
        0400000000008800000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDDAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        AAAA222222222222222222222222222222222222222222222222222222222222
        2222222222222222222222222222222222222222222222222222222222222222
        2222}
      ParentShowHint = False
      ShowHint = True
      OnClick = spdPaperBlackClick
    end
    object spdPaperCyan: TSpeedButton
      Tag = 5
      Left = 160
      Top = 64
      Width = 24
      Height = 24
      Hint = 'Color - Attribute will be set the selected color'
      GroupIndex = 2
      Flat = True
      Glyph.Data = {
        FE000000424DFE00000000000000760000002800000010000000110000000100
        0400000000008800000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDDEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
        EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
        EEEE666666666666666666666666666666666666666666666666666666666666
        6666666666666666666666666666666666666666666666666666666666666666
        6666}
      ParentShowHint = False
      ShowHint = True
      OnClick = spdPaperBlackClick
    end
    object spdPaperYellow: TSpeedButton
      Tag = 6
      Left = 184
      Top = 64
      Width = 24
      Height = 24
      Hint = 'Color - Attribute will be set the selected color'
      GroupIndex = 2
      Flat = True
      Glyph.Data = {
        FE000000424DFE00000000000000760000002800000010000000110000000100
        0400000000008800000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDDBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
        BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
        BBBB333333333333333333333333333333333333333333333333333333333333
        3333333333333333333333333333333333333333333333333333333333333333
        3333}
      ParentShowHint = False
      ShowHint = True
      OnClick = spdPaperBlackClick
    end
    object spdPaperWhite: TSpeedButton
      Tag = 7
      Left = 208
      Top = 64
      Width = 24
      Height = 24
      Hint = 'Color - Attribute will be set the selected color'
      GroupIndex = 2
      Flat = True
      Glyph.Data = {
        FE000000424DFE00000000000000760000002800000010000000110000000100
        0400000000008800000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDDFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFF777777777777777777777777777777777777777777777777777777777777
        7777777777777777777777777777777777777777777777777777777777777777
        7777}
      ParentShowHint = False
      ShowHint = True
      OnClick = spdPaperBlackClick
    end
    object spdPaperTransparent: TSpeedButton
      Tag = 8
      Left = 232
      Top = 64
      Width = 24
      Height = 24
      Hint = 'Transparent - attribute will remain unchanged'
      GroupIndex = 2
      Flat = True
      Glyph.Data = {
        FE000000424DFE00000000000000760000002800000010000000110000000100
        0400000000008800000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
        DDDDDDDDDDD00DDDDDDDDDDDDDD00DDDDDDDDDDDDDD00DDDDDDDDDDDDDD00DDD
        DDDDDDDDDDD00DDDDDDDDDDDDDD00DDDDDDDDDDDDDD00DDDDDDDDDDDDD0000DD
        DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
        DDDD}
      ParentShowHint = False
      ShowHint = True
      OnClick = spdPaperBlackClick
    end
    object imgPaletteTransparent: TImage
      Left = 364
      Top = 11
      Width = 16
      Height = 17
      Anchors = [akTop, akRight]
      AutoSize = True
      Picture.Data = {
        07544269746D6170FE000000424DFE0000000000000076000000280000001000
        0000110000000100040000000000880000000000000000000000100000001000
        000000000000000080000080000000808000800000008000800080800000C0C0
        C000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
        FF00DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
        DDDDDDDDDDDDDDDDDDDDDDDDDDD00DDDDDDDDDDDDDD00DDDDDDDDDDDDDD00DDD
        DDDDDDDDDDD00DDDDDDDDDDDDDD00DDDDDDDDDDDDDD00DDDDDDDDDDDDDD00DDD
        DDDDDDDDD000000DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
        DDDDDDDDDDDDDDDDDDDD}
      Transparent = True
    end
    object lblPaletteTransparent: TLabel
      Left = 385
      Top = 12
      Width = 69
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'is Transparent'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object imgLogo: TImage
      Left = 4
      Top = 4
      Width = 68
      Height = 28
      AutoSize = True
      Picture.Data = {
        07544269746D617066040000424D660400000000000076000000280000004400
        00001C0000000100040000000000F0030000120B0000120B0000100000001000
        000000000000000080000080000000808000800000008000800080800000C0C0
        C000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
        FF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFF0000FFFF7777777FFF7777777FFF777777777777
        7777FF77777777FFFFFFF7777777FFFF0000FFFF7000007FFF8000007FF70000
        00000000000008780000007FFFFF70000008FFFF0000FFFFF0000007FF800000
        8FF70000000000000000000700000087FFF700000007FFFF0000FFFFF8000007
        F70000008FF80000000000000000000080000008FFF80000007FFFFF0000FFFF
        F7000008F700000007F000000000000000000000880000007F70000008FFFFFF
        0000FFFFF7000000780000000770000000000000000000000700000007000000
        07FFFFFF0000FFFFFF8000007800000008800000888888888880000007800000
        000000007FFFFFFF0000FFFFFF80000080000000008000007FFFFFFFFFF80000
        07F8000000000008FFFFFFFF0000FFFFFF70000000000000000000007F788888
        8800000007F7000000000007FFFFFFFF0000FFFFFF7000000000000000000008
        F7000000000000000FFF70000000007FFFFFFFFF0000FFFFFFF8000000000000
        0000000870000000000000007FFFF800000008FFFFFFFFFF0000FFFFFFF70000
        00000000000000070000000000000008FFFFF700000007FFFFFFFFFF0000FFFF
        FFF7000000000000000000070000000000000087FFFF7800000008FFFFFFFFFF
        0000FFFFFFFF8000000008000000008800000088888887FFFFFF80000000007F
        FFFFFFFF0000FFFFFFFF80000000070000000078000007FFFFFFFFFFFFF70000
        00000007FFFFFFFF0000FFFFFFFF700000008700000000780000088888888888
        88800000000000087FFFFFFF0000FFFFFFFF700000008F80000008F800000000
        0000000000000000080000008FFFFFFF0000FFFFFFFFF80000007F70000008F7
        0000000000000000000000008780000007FFFFFF0000FFFFFFFFF80000007F70
        000007FF8000000000000000000000007F700000087FFFFF0000FFFFFFFFF700
        0008FFF8000007FFF80000000000000000000007FFF70000008FFFFF0000FFFF
        FFFFFF000008FFF800008FFFFF780000000000000000008FFFFF80000007FFFF
        0000FFFFFFFFFF777777FFF777777FFFFFFF7777777777777777777FFFFF7777
        7777FFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000}
    end
  end
end
