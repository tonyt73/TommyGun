object frmUDGType: TfrmUDGType
  Left = 1285
  Top = 238
  ClientHeight = 737
  ClientWidth = 283
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panUDGs: TPanel
    Left = 0
    Top = 0
    Width = 283
    Height = 737
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
      737)
    object imgIcon: TImage
      Left = 30
      Top = 36
      Width = 16
      Height = 16
      AutoSize = True
      Picture.Data = {
        07544269746D617036030000424D360300000000000036000000280000001000
        000010000000010018000000000000030000130B0000130B0000000000000000
        0000FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
        FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
        FFFF00FF217DB5218AADFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
        00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF00A6FF18F7FF18D3EFFF00FF
        FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
        FF3175AD00B6FF18F7FF18FBFF18DFF7FF00FFFF00FFFF00FFFF00FFFF00FFFF
        00FFFF00FFFF00FFFF00FFFF00FFFF00FF1882CE08C7FF18EFFF18EFFF18F7FF
        18EBFF18DBF718E7F718E3F7FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
        FF009AF708D3FF10E7FF10E7FF10EBFF10EFFF18F3FF18F7FF18EBFFFF00FFFF
        00FFFF00FFFF00FFFF00FFFF00FF089EEF08C3FF10DBFF10DBFF10DFFF10E3FF
        10E3FF10E7FF10EFFF18BAE7FF00FFFF00FFFF00FFFF00FF2982B500B2FF08C7
        FF08CFFF10D3FF10D3FF10D7FF10DBFF10DBFF10DFFF10E7FFFF00FFFF00FFFF
        00FFFF00FF42799400D3FF00CBFF08C3FF08C3FF08C7FF08CBFF08CFFF10D3FF
        10D3FF10D7FF10DFFFFF00FFFF00FFFF00FFFF00FFFF00FF3986A508BEEF00CB
        FF08BEFF08BEFF08C3FF08C7FF08CBFF08CBFF08CFFF08D7FF10BEF7FF00FFFF
        00FFFF00FFFF00FFFF00FFFF00FF318EB500CFFF00BEFF08B6FF08BEFF08BEFF
        08C3FF08CBFF08CFFF08CBFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
        FF299ABD00D3FF00AEFF00B2FF00B6FF08B2FF189AD6298ABD3182ADFF00FFFF
        00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF08DBFF00AEFF00AAFF08A6FF
        FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
        FFFF00FF21BEDE00CBFF009AF7FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
        00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF21A2CEFF00FFFF00FF
        FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
        FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
        00FF}
      Transparent = True
      Visible = False
    end
    object lblUserDefinedGraphicsName: TLabel
      Left = 12
      Top = 11
      Width = 27
      Height = 13
      Caption = 'Name'
    end
    object lblPaletteWarning: TLabel
      Left = 52
      Top = 36
      Width = 216
      Height = 22
      Anchors = [akLeft, akTop, akRight]
      Caption = 
        'Warning: The monochrome palette was not found. This plugin canno' +
        't work without this palette present.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -9
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      WordWrap = True
    end
    object Label1: TLabel
      Left = 52
      Top = 388
      Width = 63
      Height = 13
      Caption = 'Magnification'
    end
    object edtUDGName: TEdit
      Left = 52
      Top = 8
      Width = 220
      Height = 21
      Hint = 'UDG Name|The name of the UDG'
      Anchors = [akLeft, akTop, akRight]
      BevelInner = bvNone
      BevelOuter = bvNone
      Color = clWhite
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnChange = edtUDGNameChange
    end
    object cmdUserDefinedGraphicsSetAdd: TBitBtn
      Left = 52
      Top = 63
      Width = 80
      Height = 24
      Hint = 'Add UDG|Add the current UDG details to the list'
      Caption = 'Add'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnClick = cmdUserDefinedGraphicsSetAddClick
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
    object cmdUserDefinedGraphicsSetRemove: TBitBtn
      Left = 192
      Top = 63
      Width = 80
      Height = 24
      Hint = 'Remove UDG|Remove the selected UDG from the list'
      Anchors = [akTop, akRight]
      Caption = 'Remove'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
      OnClick = cmdUserDefinedGraphicsSetRemoveClick
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
    object cmdUserDefinedGraphicsSetRename: TBitBtn
      Left = 192
      Top = 93
      Width = 80
      Height = 24
      Hint = 'Rename UDG|Rename the current UDG'
      Anchors = [akTop, akRight]
      Caption = 'Rename'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 3
      OnClick = cmdUserDefinedGraphicsSetRenameClick
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
    object cmdUserDefinedGraphicsSetClone: TBitBtn
      Left = 52
      Top = 93
      Width = 80
      Height = 24
      Hint = 'Clone UDG|Clone (Copy) the current screen as a new UDG item'
      Caption = 'Clone'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 4
      OnClick = cmdUserDefinedGraphicsSetCloneClick
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
    object panUserDefinedGraphics: TPanel
      Left = 52
      Top = 414
      Width = 220
      Height = 296
      Anchors = [akLeft, akTop, akRight, akBottom]
      BevelKind = bkTile
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 5
      object sbxUserDefinedGraphics: TScrollBox
        Left = 0
        Top = 0
        Width = 216
        Height = 292
        HorzScrollBar.Smooth = True
        HorzScrollBar.Style = ssFlat
        HorzScrollBar.Tracking = True
        VertScrollBar.Smooth = True
        VertScrollBar.Style = ssFlat
        VertScrollBar.Tracking = True
        Align = alClient
        BevelInner = bvNone
        BevelOuter = bvNone
        BorderStyle = bsNone
        Color = clWhite
        Ctl3D = True
        ParentColor = False
        ParentCtl3D = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        object pbxUserDefinedGraphics: TPaintBox
          Left = 0
          Top = 0
          Width = 216
          Height = 176
          Hint = 
            'UDG Character Window|Shows all the character that make up the UD' +
            'G set'
          Align = alTop
          Color = clWhite
          ParentColor = False
          OnMouseDown = pbxUserDefinedGraphicsMouseDown
          OnPaint = pbxUserDefinedGraphicsPaint
          ExplicitWidth = 171
        end
      end
    end
    object lstUDGList: TListBox
      Left = 52
      Top = 124
      Width = 220
      Height = 131
      Hint = 'List of User Defined Graphics'
      Anchors = [akLeft, akTop, akRight]
      BevelKind = bkFlat
      BorderStyle = bsNone
      Color = clWhite
      ItemHeight = 13
      TabOrder = 6
      OnClick = lstUDGListClick
    end
    object panUserDefinedGraphicsButtons: TPanel
      Left = 52
      Top = 261
      Width = 175
      Height = 118
      Anchors = [akLeft, akTop, akRight]
      AutoSize = True
      BevelKind = bkTile
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 7
      object spdUserDefinedGraphicsA: TSpeedButton
        Left = 0
        Top = 0
        Width = 57
        Height = 16
        Caption = 'A'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsU: TSpeedButton
        Tag = 20
        Left = 114
        Top = 98
        Width = 57
        Height = 16
        Caption = 'U'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsT: TSpeedButton
        Tag = 19
        Left = 57
        Top = 98
        Width = 57
        Height = 16
        Caption = 'T'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsS: TSpeedButton
        Tag = 18
        Left = 0
        Top = 98
        Width = 57
        Height = 16
        Caption = 'S'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsR: TSpeedButton
        Tag = 17
        Left = 114
        Top = 81
        Width = 57
        Height = 17
        Caption = 'R'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsQ: TSpeedButton
        Tag = 16
        Left = 57
        Top = 81
        Width = 57
        Height = 17
        Caption = 'Q'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsP: TSpeedButton
        Tag = 15
        Left = 0
        Top = 81
        Width = 57
        Height = 17
        Caption = 'P'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsO: TSpeedButton
        Tag = 14
        Left = 114
        Top = 65
        Width = 57
        Height = 16
        Caption = 'O'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsN: TSpeedButton
        Tag = 13
        Left = 57
        Top = 65
        Width = 57
        Height = 16
        Caption = 'N'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsM: TSpeedButton
        Tag = 12
        Left = 0
        Top = 65
        Width = 57
        Height = 16
        Caption = 'M'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsL: TSpeedButton
        Tag = 11
        Left = 114
        Top = 49
        Width = 57
        Height = 16
        Caption = 'L'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsK: TSpeedButton
        Tag = 10
        Left = 57
        Top = 49
        Width = 57
        Height = 16
        Caption = 'K'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsJ: TSpeedButton
        Tag = 9
        Left = 0
        Top = 49
        Width = 57
        Height = 16
        Caption = 'J'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsI: TSpeedButton
        Tag = 8
        Left = 114
        Top = 33
        Width = 57
        Height = 16
        Caption = 'I'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsH: TSpeedButton
        Tag = 7
        Left = 57
        Top = 33
        Width = 57
        Height = 16
        Caption = 'H'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsG: TSpeedButton
        Tag = 6
        Left = 0
        Top = 33
        Width = 57
        Height = 16
        Caption = 'G'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsF: TSpeedButton
        Tag = 5
        Left = 114
        Top = 16
        Width = 57
        Height = 17
        Caption = 'F'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsE: TSpeedButton
        Tag = 4
        Left = 57
        Top = 16
        Width = 57
        Height = 17
        Caption = 'E'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsD: TSpeedButton
        Tag = 3
        Left = 0
        Top = 16
        Width = 57
        Height = 17
        Caption = 'D'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsC: TSpeedButton
        Tag = 2
        Left = 114
        Top = 0
        Width = 57
        Height = 16
        Caption = 'C'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
      object spdUserDefinedGraphicsB: TSpeedButton
        Tag = 1
        Left = 57
        Top = 0
        Width = 57
        Height = 16
        Caption = 'B'
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = False
        OnClick = spdUserDefinedGraphicsAClick
      end
    end
    object spnScale: TCSpinEdit
      Left = 127
      Top = 385
      Width = 39
      Height = 22
      Color = 16777215
      MaxValue = 16
      MinValue = 2
      TabOrder = 8
      Value = 4
      OnChange = spnScaleChange
    end
  end
end
