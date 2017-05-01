object frmMSXSpritePalette: TfrmMSXSpritePalette
  Left = 1025
  Top = 573
  ClientHeight = 173
  ClientWidth = 479
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panPalette: TPanel
    Tag = -1
    Left = 0
    Top = 113
    Width = 479
    Height = 60
    Align = alBottom
    BevelOuter = bvNone
    Constraints.MaxHeight = 60
    Constraints.MinHeight = 60
    TabOrder = 0
    object lblPalette: TLabel
      Left = 80
      Top = 12
      Width = 155
      Height = 13
      Caption = 'Monochrome Sprite Palette'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lblPen: TLabel
      Left = 8
      Top = 40
      Width = 18
      Height = 13
      Cursor = crHandPoint
      Hint = 'Click to change the colour of the pen'
      Caption = 'Pen'
      Font.Charset = ANSI_CHARSET
      Font.Color = clHotLight
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
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
    object panPen: TPanel
      Left = 36
      Top = 36
      Width = 20
      Height = 20
      BevelOuter = bvLowered
      Color = clWhite
      ParentBackground = False
      TabOrder = 0
    end
    object panColor01: TPanel
      Tag = 1
      Left = 72
      Top = 36
      Width = 16
      Height = 20
      Color = clBlack
      ParentBackground = False
      TabOrder = 1
      OnClick = panColor01Click
    end
    object panColor02: TPanel
      Tag = 2
      Left = 90
      Top = 36
      Width = 16
      Height = 20
      Color = 4376609
      ParentBackground = False
      TabOrder = 2
      OnClick = panColor01Click
    end
    object panColor04: TPanel
      Tag = 4
      Left = 126
      Top = 36
      Width = 16
      Height = 20
      Color = 15553876
      ParentBackground = False
      TabOrder = 3
      OnClick = panColor01Click
    end
    object panColor03: TPanel
      Tag = 3
      Left = 108
      Top = 36
      Width = 16
      Height = 20
      Color = 7920734
      ParentBackground = False
      TabOrder = 4
      OnClick = panColor01Click
    end
    object panColor06: TPanel
      Tag = 6
      Left = 162
      Top = 36
      Width = 16
      Height = 20
      Color = 5067476
      ParentBackground = False
      TabOrder = 5
      OnClick = panColor01Click
    end
    object panColor05: TPanel
      Tag = 5
      Left = 144
      Top = 36
      Width = 16
      Height = 20
      Color = 16545405
      ParentBackground = False
      TabOrder = 6
      OnClick = panColor01Click
    end
    object panColor08: TPanel
      Tag = 8
      Left = 198
      Top = 36
      Width = 16
      Height = 20
      Color = 5527036
      ParentBackground = False
      TabOrder = 7
      OnClick = panColor01Click
    end
    object panColor07: TPanel
      Tag = 7
      Left = 180
      Top = 36
      Width = 16
      Height = 20
      Color = 16116546
      ParentBackground = False
      TabOrder = 8
      OnClick = panColor01Click
    end
    object panColor10: TPanel
      Tag = 10
      Left = 234
      Top = 36
      Width = 16
      Height = 20
      Color = 5554644
      ParentBackground = False
      TabOrder = 9
      OnClick = panColor01Click
    end
    object panColor09: TPanel
      Tag = 9
      Left = 216
      Top = 36
      Width = 16
      Height = 20
      Color = 7895551
      ParentBackground = False
      TabOrder = 10
      OnClick = panColor01Click
    end
    object panColor12: TPanel
      Tag = 12
      Left = 270
      Top = 36
      Width = 16
      Height = 20
      Color = 3911713
      ParentBackground = False
      TabOrder = 11
      OnClick = panColor01Click
    end
    object panColor11: TPanel
      Tag = 11
      Left = 252
      Top = 36
      Width = 16
      Height = 20
      Color = 8441574
      ParentBackground = False
      TabOrder = 12
      OnClick = panColor01Click
    end
    object panColor14: TPanel
      Tag = 14
      Left = 306
      Top = 36
      Width = 16
      Height = 20
      Color = 13421772
      ParentBackground = False
      TabOrder = 13
      OnClick = panColor01Click
    end
    object panColor13: TPanel
      Tag = 13
      Left = 288
      Top = 36
      Width = 16
      Height = 20
      Color = 12213193
      ParentBackground = False
      TabOrder = 14
      OnClick = panColor01Click
    end
    object panColor15: TPanel
      Tag = 15
      Left = 324
      Top = 36
      Width = 16
      Height = 20
      BevelOuter = bvLowered
      Color = clWhite
      ParentBackground = False
      TabOrder = 15
      OnClick = panColor01Click
    end
  end
end
