object frmMemoryEditor: TfrmMemoryEditor
  Left = 351
  Top = 233
  Align = alClient
  BorderIcons = []
  BorderStyle = bsNone
  Caption = 'Memory Editor'
  ClientHeight = 702
  ClientWidth = 1006
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  WindowState = wsMaximized
  OnCreate = FormCreate
  ExplicitWidth = 320
  ExplicitHeight = 240
  PixelsPerInch = 96
  TextHeight = 13
  object pgcMemoryMap: TPageControl
    Left = 714
    Top = 0
    Width = 292
    Height = 702
    ActivePage = tabMemoryObjects
    Align = alRight
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Images = imgTabImages
    OwnerDraw = True
    ParentFont = False
    TabHeight = 32
    TabOrder = 0
    TabWidth = 100
    OnDrawTab = pgcMemoryMapDrawTab
    object tabMemoryObjects: TTabSheet
      Caption = 'Objects'
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object scpMemoryObjects: TScrollBox
        Left = 0
        Top = 0
        Width = 284
        Height = 660
        Align = alClient
        BevelInner = bvNone
        BevelOuter = bvNone
        BorderStyle = bsNone
        TabOrder = 0
        ExplicitLeft = 2
        object Panel3: TPanel
          Left = 0
          Top = 0
          Width = 284
          Height = 573
          Align = alTop
          BevelOuter = bvNone
          Color = clWhite
          ParentBackground = False
          TabOrder = 0
          object GroupBox3: TGroupBox
            Left = 8
            Top = 83
            Width = 272
            Height = 481
            Caption = ' Game Objects '
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            object lblMemoryMapName: TLabel
              Left = 12
              Top = 28
              Width = 27
              Height = 13
              Caption = 'Name'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
            end
            object lblMemoryMapCustomObjects: TLabel
              Left = 12
              Top = 104
              Width = 76
              Height = 13
              Caption = 'Custom Objects'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
            end
            object lblMemoryMapSystemObjects: TLabel
              Left = 16
              Top = 212
              Width = 75
              Height = 13
              Caption = 'System Objects'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
            end
            object lblMemoryMapAddress: TLabel
              Left = 12
              Top = 52
              Width = 27
              Height = 13
              Caption = 'Addr.'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              WordWrap = True
            end
            object lblMemoryMapSize: TLabel
              Left = 156
              Top = 52
              Width = 19
              Height = 13
              Caption = 'Size'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
            end
            object edtMemoryMapName: TEdit
              Left = 52
              Top = 24
              Width = 209
              Height = 21
              Hint = 'UDG Name|The name of the UDG'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentColor = True
              ParentFont = False
              ParentShowHint = False
              ShowHint = True
              TabOrder = 0
            end
            object panMemoryMapCustomObjects: TPanel
              Left = 52
              Top = 123
              Width = 209
              Height = 80
              BevelOuter = bvNone
              Caption = 'FlatPanel3'
              ParentColor = True
              TabOrder = 1
              object lstMemoryMapCustom: TCheckListBox
                Left = 0
                Top = 0
                Width = 209
                Height = 80
                OnClickCheck = lstMemoryMapCustomClickCheck
                Align = alClient
                BevelInner = bvNone
                BevelOuter = bvNone
                Color = clWhite
                ItemHeight = 13
                TabOrder = 0
              end
            end
            object panMemoryMapSystemObjects: TPanel
              Left = 52
              Top = 232
              Width = 209
              Height = 232
              BevelOuter = bvNone
              Caption = 'FlatPanel3'
              ParentColor = True
              TabOrder = 2
              object lstMemoryMapSystem: TCheckListBox
                Left = 0
                Top = 0
                Width = 209
                Height = 232
                OnClickCheck = lstMemoryMapSystemClickCheck
                Align = alClient
                BevelInner = bvNone
                BevelOuter = bvNone
                Color = clWhite
                ItemHeight = 13
                TabOrder = 0
              end
            end
            object cmdMemoryMapAdd: TBitBtn
              Left = 52
              Top = 72
              Width = 80
              Height = 24
              Hint = 'Add File|Adds a new file object to the project.'
              Caption = 'Add'
              Enabled = False
              ParentShowHint = False
              ShowHint = True
              TabOrder = 3
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
            object cmdMemoryMapRemove: TBitBtn
              Left = 182
              Top = 72
              Width = 80
              Height = 24
              Hint = 'Remove File|Removes the selected file from the list.'
              Caption = 'Remove'
              Enabled = False
              ParentShowHint = False
              ShowHint = True
              TabOrder = 4
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
            object edtMemoryMapAddress: KSpinEdit
              Left = 52
              Top = 48
              Width = 80
              Height = 20
              BevelOuter = bvLowered
              Color = clWhite
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              TabOrder = 5
              Value = 16384
              Min = 100
              Max = 65536
              Step = 256
              DesignSize = (
                80
                20)
            end
            object edtMemoryMapSize: KSpinEdit
              Left = 182
              Top = 48
              Width = 80
              Height = 20
              BevelOuter = bvLowered
              Color = clWhite
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              TabOrder = 6
              Value = 1
              Min = 1
              Max = 49152
              DesignSize = (
                80
                20)
            end
          end
          object GroupBox1: TGroupBox
            Left = 8
            Top = 4
            Width = 272
            Height = 73
            Caption = ' Stack '
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 1
            object lblMemoryMapStackAddress: TLabel
              Left = 16
              Top = 19
              Width = 110
              Height = 13
              Caption = 'Machine Stack Address'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
            end
            object lblMemoryMapStackSize: TLabel
              Left = 16
              Top = 45
              Width = 90
              Height = 13
              Caption = 'Machine Stack Size'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
            end
            object edtMemoryMapStackAddress: KSpinEdit
              Left = 181
              Top = 16
              Width = 80
              Height = 20
              BevelOuter = bvLowered
              Color = clWhite
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              TabOrder = 0
              Value = 65535
              Min = 100
              Max = 65535
              Step = 256
              DesignSize = (
                80
                20)
            end
            object edtMemoryMapStackSize: KSpinEdit
              Left = 181
              Top = 42
              Width = 80
              Height = 20
              BevelOuter = bvLowered
              Color = clWhite
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              TabOrder = 1
              Value = 2048
              Min = 1
              Max = 8192
              Step = 256
              DesignSize = (
                80
                20)
            end
          end
        end
      end
    end
    object tabMemorySettings: TTabSheet
      Caption = 'Settings'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object scpMemorySettings: TScrollBox
        Left = 0
        Top = 0
        Width = 284
        Height = 660
        Align = alClient
        BevelInner = bvNone
        BevelOuter = bvNone
        BorderStyle = bsNone
        Color = clWhite
        ParentColor = False
        TabOrder = 0
        object Panel2: TPanel
          Left = 0
          Top = 0
          Width = 284
          Height = 189
          Align = alTop
          BevelOuter = bvNone
          Color = clWhite
          ParentBackground = False
          TabOrder = 0
          object GroupBox2: TGroupBox
            Left = 8
            Top = 4
            Width = 272
            Height = 96
            Caption = ' Number Format '
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            object FlatRadioButton1: TRadioButton
              Left = 16
              Top = 24
              Width = 121
              Height = 17
              Caption = 'Decimal'
              Checked = True
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              TabOrder = 0
              TabStop = True
            end
            object FlatRadioButton2: TRadioButton
              Left = 16
              Top = 47
              Width = 121
              Height = 17
              Caption = 'Hexidecimal'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              TabOrder = 1
            end
            object FlatRadioButton3: TRadioButton
              Left = 16
              Top = 70
              Width = 121
              Height = 17
              Caption = 'Octal'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              TabOrder = 2
            end
          end
        end
      end
    end
  end
  object panMemoryEditorMap: TPanel
    Left = 0
    Top = 0
    Width = 714
    Height = 702
    Align = alClient
    BevelOuter = bvNone
    Color = clWhite
    TabOrder = 1
    object panMemoryMapLegend: TPanel
      Left = 0
      Top = 632
      Width = 714
      Height = 70
      Align = alBottom
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object Label7: TLabel
        Left = 4
        Top = 4
        Width = 118
        Height = 13
        Caption = 'Memory Map Legend'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Panel1: TPanel
        Left = 176
        Top = 24
        Width = 78
        Height = 18
        BevelOuter = bvLowered
        Caption = 'Tiles Table'
        Color = clNavy
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
      end
      object Panel5: TPanel
        Left = 176
        Top = 46
        Width = 78
        Height = 18
        BevelOuter = bvLowered
        Caption = 'Tiles'
        Color = clBlue
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
      end
      object Panel6: TPanel
        Left = 256
        Top = 24
        Width = 78
        Height = 18
        BevelOuter = bvLowered
        Caption = 'Sprite Table'
        Color = clOlive
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
      end
      object Panel7: TPanel
        Left = 256
        Top = 46
        Width = 78
        Height = 18
        BevelOuter = bvLowered
        Caption = 'Sprites'
        Color = clYellow
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
      end
      object Panel8: TPanel
        Left = 336
        Top = 24
        Width = 78
        Height = 18
        BevelOuter = bvLowered
        Caption = 'Map Table'
        Color = clGreen
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 4
      end
      object Panel9: TPanel
        Left = 336
        Top = 46
        Width = 78
        Height = 18
        BevelOuter = bvLowered
        Caption = 'Map Screens'
        Color = clLime
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 5
      end
      object Panel10: TPanel
        Left = 96
        Top = 24
        Width = 78
        Height = 18
        BevelOuter = bvLowered
        Caption = 'Screen$'
        Color = 14811135
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 6
      end
      object Panel11: TPanel
        Left = 416
        Top = 24
        Width = 78
        Height = 18
        BevelOuter = bvLowered
        Caption = 'Custom'
        Color = clFuchsia
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 7
      end
      object Panel12: TPanel
        Left = 16
        Top = 24
        Width = 78
        Height = 18
        BevelOuter = bvLowered
        Caption = 'ROM'
        Color = clGray
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 8
      end
      object Panel13: TPanel
        Left = 16
        Top = 46
        Width = 78
        Height = 18
        BevelOuter = bvLowered
        Caption = 'System'
        Color = clSilver
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 9
      end
      object Panel15: TPanel
        Left = 416
        Top = 46
        Width = 78
        Height = 18
        BevelOuter = bvLowered
        Caption = 'Chr Set'
        Color = clAqua
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 10
      end
      object Panel16: TPanel
        Left = 96
        Top = 45
        Width = 78
        Height = 18
        BevelOuter = bvLowered
        Caption = 'Free Mem'
        Color = clWhite
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 11
      end
      object Panel17: TPanel
        Left = 496
        Top = 45
        Width = 78
        Height = 18
        BevelOuter = bvLowered
        Caption = 'Overlap'
        Color = clRed
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 12
      end
      object Panel18: TPanel
        Left = 496
        Top = 24
        Width = 78
        Height = 18
        BevelOuter = bvLowered
        Caption = 'Stack'
        Color = clMaroon
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 13
      end
    end
    object sbxMemoryMap: TScrollBox
      Left = 0
      Top = 20
      Width = 714
      Height = 612
      VertScrollBar.Smooth = True
      VertScrollBar.Style = ssFlat
      VertScrollBar.Tracking = True
      Align = alClient
      BorderStyle = bsNone
      TabOrder = 1
      OnResize = sbxMemoryMapResize
      object imgMemoryMap: TImage
        Left = 0
        Top = 0
        Width = 714
        Height = 400
        Align = alTop
        ParentShowHint = False
        ShowHint = True
        OnMouseMove = imgMemoryMapMouseMove
      end
      object imgLargeIcon: TImage
        Left = 46
        Top = 179
        Width = 48
        Height = 48
        Picture.Data = {
          07544269746D6170361B0000424D361B00000000000036000000280000003000
          0000300000000100180000000000001B0000130B0000130B0000000000000000
          0000846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          0000000000000000000000000000008461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          428461428461428461420000000000005241294A38214A38215241295A452900
          0000000000000000846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          61428461428461428461428461428461428461420000000000004A4D4A296594
          1892CE1886C621658C294D63393C394234214A38215241290000000000000000
          0084614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          42000000525552296994188ED608BAEF00D7FF00D7FF08C7F708B6EF109EDE21
          7DB5295D8431495A393831423421523C29000000000000000000846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          61428461428461428461428461420000005A6563188ACE10A2DE10AEE700CBF7
          00CFF700CFF700D3FF00D7FF00D7FF00D3FF10AEE71896DE1896D62171A52955
          7331454A4234294A342100000000000000000084614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461420000
          003179A510A6E710AEEF10AEE708BEEF08C7F700CBF700CBF700CBF700CFF700
          D7FF08B6EF10B2E700DBFF00CFF708BEEF10AAE7188EC6216994314142423421
          4A38210000000000000000000000008461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142000000297DBD089ECE089ACE109ADE10A2EF
          10AAEF08B2EF08BEEF08C3F708C7F700CFF708B2E710AAE700D3FF00D3FF00D7
          FF00D7FF00D3FF00CBF71896D62179B529618C314D633938394234214A382100
          0000000000000000000000846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461420000000000004249
          21106D4A18923918923908794A08827B0886A51092D6109EE710A6EF10AEEF08
          BAEF10AAE710A6E700CBF700CBF700CBF700CFF700CFF700D3FF10AEE708BAEF
          00CBF710B2E71096D62175AD29597B3145523938294A3421523C290000000000
          0000000000000084614284614284614284614284614284614284614284614284
          614284614200000052512921551000690031BA425AF78C5AF78C52E37339C34A
          21A639108E3908825A088684108AB5109ADE1896E7189AE710B2EF08BAEF08C3
          EF08C7F700CBF700CBF710A6E708BAEF00D7FF00D7FF00D7FF00CFF708C3EF10
          AEE71892CE216DA529557331454A4234294A3821523C29000000000000000000
          8461428461428461428461428461428461420000005A5D290869080875081086
          184ADF7352F78C52F3845AFB8C63FF945AF78439CF5A31BE4A29AE39219A3910
          8642087D63087D8C108EC6109ADE10A2EF10AAEF10B2EF08BAEF10A2E708B2EF
          00CFF700CBF700CFF700D3F700D7FF00DBFF00D3FF10A2DE08B2EF10AAE7188A
          C6216594295163393C394A34215A452900000084614284614284614284614284
          6142000000296510088210188E21189A3142DB6B4AEF7B4AEF7B52F38442DF6B
          21923921793121963121AE4231BE4A39C75231BA4229AA391896390882420882
          7308869C1092CE109AE71896E710A6E708BEEF08C3F708C7F700CBF700CBF700
          CBF700CFF710A2DE00CBF700DBFF00D3FF00CBF708B6EF109AD6295D84423421
          5A452900000084614284614284614284614200000021691018962921A23929AE
          4242DB634AE7734AEB734AE7732971394A3C3984555A6B5552525D4231713921
          8231189E3139C75A5AF78C52E77331BA4221A239188E390882521082A5188ED6
          109EE710A6EF10AEEF08B6EF08BEEF08C7F708C7F7109EDE08C3F700CFF700CF
          F700D3FF00D7FF00D7FF10AAE729516B523C2900000084614284614284614284
          614200000021691029AA4231BA5239C35A42DB6342E36342EB6B39BE5A292429
          63414A945D63A5656BB56973AD6573A5656B735D52217D3139DB6329BA4A21AA
          4229BA4A31C34A39C34A219E39108A39087D5A08828C108AB51096DE10A2E710
          AAEF10B2EF189ADE08BAEF08C7F700CBF700CBF700CBF700CFF700CBF72179B5
          4A382100000084614284614284614284614200000021691039BE5A42D36B4ADB
          7339DB6339DB5A39E36331B25231303163414A84555A945D639C656BB56D73C6
          757BDE7D8C6B6152186D2942513952514239653921793121923129BA4A42D763
          4ADB6B31B642189A3910864208826B08869C108EC6188EDE109EE710AAEF08B6
          EF08BEEF08C3F708C7F700CBF7188ECE42382900000084614284614284614284
          6142000000216D184AD7735AEB845AF7944AE77331D75231DF5A31B252423839
          63414A7B515284555A945D63A5656BAD6D73C6798484555A211C217B4D5A9C61
          6BA55D6B9C5D6B845D5A316D3129AE4252F38442D76331C34A39C34A31B64221
          A639189239107D4A087D730886A51092CE109EE710A6EF10AEEF08B6EF188AC6
          423829000000846142846142846142846142000000216D1052E37B63FF9C5AF3
          8C52E38439D35A31DB5229AE4A4A3C3963414A6B49527B51528C595A946163A5
          656BBD717B7B515A312C31734D528C59639C6163AD6973BD717BBD697B397539
          189231316531316D31218631219E3929B64231C34A39C75239C34A29A639188E
          39088252088684108AAD1096DE1882C642302100000000000084614284614284
          61420000004A61291886214AD36B4AD76B39C35A31BA4A29D34A29AA42524142
          63414A63454A734D527B515A8C59639C616BAD6D737351523930316B49527B55
          5A8C59639C616BAD6973D67D8C524542292C2984515A9455638C595A6B59524A
          6542297531188E3142DB6B63FF9442DB6B31C34A29AE39219A39108A4208714A
          213C103134184A3821000000846142846142846142000000526129188A2131B6
          5229A63918962921CB3921AA3963494A63414A5A414263454A734D5284555A8C
          5D63A5656B734D524A383963494A734D5284555A8C5D639C656BC6797B523842
          39303184595A945D63A5656BB56D73BD6D7BBD697B735952219E3929B24A2186
          3121923121AE4231BE4A31C34A31BE4A29AE4218822118450842342100000084
          6142846142846142000000186910189229108218108E1821CB3921A6396B4D4A
          63414A4A38395A41426B494A73515284555A9461636B4D52523C4263454A6B49
          4A73515284555A945D63B5717B523C424234397B515284595A945D63A5656BB5
          6D73CE7D84BD717B2951293149317B5152735552525D42396D39218231189A31
          29BE4A52EB84219E31213C10523C290000008461420000000000001061080875
          08109E2118BA3118CB3121A23173515263414A423439523C4263454A6B49527B
          51528C59636B494A63454A5A414263454A6B49527B515284595AAD6973523C42
          4A38396B4D527B51528C595A946163A5696BB5717BB56D733128314A3439945D
          639C616BAD6573AD65739C616B7B615A31693139D76352EB7B105D084A382100
          0000000000216510087508087D10108A1810B22110BE2910C329189E298C5D63
          63454A312C314234394A38395A414263454A734D5263454A7B5152523C424A38
          395A414263454A734D52945D63523C4263454A5A414263494A734D5284555A8C
          5D639C656B9C616B423439523C42734D5284555A8C5D639C656BAD6973C6757B
          AD656B39AA524AEF731071184A3821000000000000216510108618189229189A
          3110B22910BA2110BE21109A2194616363454A292829393031423439523C425A
          41426B494A63454A84555A4A3839423439523C425A41426B494A84555A523C42
          6B494A523C425A41426B494A734D5284555A945D638C5D634A38395A41426B49
          4A73515284555A945D63A5656BB56D739C616331A64A42E76B1071104A382100
          000000000021691018962921A23929AA4210B62908B61808BE21109A219C696B
          63454A212429312C313930314A3439523C425A41425A414A8C5D634A38393930
          314A3439523C425A414A7B5152523C42734D524A3439523C4263414A6B494A7B
          51528C595A84555A523C4263454A63454A6B49527B51528C595A945D63AD6973
          945D6331A24A39E7631071104A382100000000000021691029AA4231B65239BE
          5210B62908B61808BA18109621AD6D73734D52181C21292829312C314230314A
          3839523C425A41429C616B423439312C294230314A3839523C426B4952523C42
          7B515A3930314A3839523C4263454A6B4D527B555A7B5152523C4263494A523C
          4263454A6B4D527B515A8C595A9C616B8C555A29A24231DB521071105A412900
          000000000021691031BA5242CB634AD77321C33900B21008B61800A6187B615A
          BD657B4A3039312829292829312C314234394A38395A4142A5696B4234392928
          29392C314234394A383963454A5A414284595A312C314234394A38395A414263
          454A734D52734D525A41426B49524A38395A414263454A734D5284555A945D63
          84555A21862908861018611000000084614200000029691842CB6352E37B5AEB
          8C52EB7B10BA2100AE0800B21010921842693963594A63414A523442422C3939
          2C314228314A3439B5717B393031212429312C293930314234395A41425A4142
          945D633128293930314234395238425A41426B494A63454A63454A734D524234
          39523C425A41426B494A734D5284555A7B555A08590829491000000084614284
          614200000042612131B24A63FF9C63FF9C6BFFA55AF78C31D75A18C33108BA21
          00B21000A610089218217521295129293C29186521187121C66D7B84515A2120
          21212429312C293930314A38395A41429C616B292429312C313930314A343952
          3C4263454A5A41426B494A7B51523930314A3839523C425A454A6B494A7B515A
          734D52105908423021000000846142846142846142000000216D1039C35A5AEF
          8C63FF9C6BFFA56BFFA563FF9C52F78C42E76B29D34A10C72908BA1800B21000
          AA1000B61000AE10426939845D5A6B45525A3842422C39392C314230395A3C42
          A5696B212021292829312C314230314A3839523C42523C42734D5284555A312C
          314230314A3839523C4263454A734D526B494A0859103134184A382100000084
          6142846142846142000000426121217118218E2931B64A4AD7735AF38C63FF9C
          6BFFA563FF9C63FB944AEF7B39DF5A21CB4210BA2908B61800AE100096101886
          213169313949313934312149214A5539CE7584393031182021292829392C3142
          34394A38394A38397B515284595A292829392C314234394A38395A41426B454A
          63454A1079181061083134185241290000008461428461428461420000000000
          00000000526129316518217518219A3131BE524ADF735AF38C63FF9C63FF9C5A
          FB9452F38442E36B31D75218C73108BE2100B61000AA1008921800B618188E21
          9C5D6B945563523442392C31312C313930314234394230397B515A8C59632124
          29312C31393031423439523C425A414A5A3C4218922910AE210861084A382100
          0000846142846142846142846142846142846142000000000000000000000000
          4A6121296918187D1821A23939C35A4AE37352F3845AFB945AFB8C52F3844AEB
          7339DB5A21CF4210C32900B21000B210088E182979294A5D395249424A343942
          283939283129302984595A9C656B182021292429312C313930314A3439523C42
          523839188E2110C729086D084A38210000008461428461428461428461428461
          4284614284614284614284614284614200000000000000000000000042612121
          6910188A2121AA3939CB5A4AE37352EF7B52F78452F37B4AEB7329D34A21C739
          10BE2100BA1800AE1000A210108618216521186921009E184A6939CE6D845A3C
          4A312829292829312C314230314A38394A343918922110BE21086D084A382100
          0000846142846142846142846142846142846142846142846142846142846142
          846142846142846142846142000000000000000000526129396518217110188E
          2129AE3939CF5A42DF6B4AEB7342E76B39E36331D75221CB4210C32908BE1800
          B61800B61000BA10089E18396D316B594A63494A5A3442422C39392C31422839
          39303110A22108BA210869084A38210000008461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          614284614200000000000000000000000052612931651818751821B23931CB52
          39DB5A39E36339E36339DB5A31D75221CF4218C33110BA2108B61800B21000AA
          1010921821792129552931382921492910862108BA1808B618086D084A382100
          0000846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          420000000000000000004A6121296918187D18189A2121B23929CB4A31D35231
          DB5231D75229CF4A21CB4218C33110BE2908BA1800BA1800B21008AA1808B218
          08BA1808B61808B218086D085A41290000008461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142000000000000
          000000000000426121216910108218109E2118B23121C33921CB4221CF4221CB
          3918C33110BE2910BA2108BA1808B61808B61808B618009A10215D1000000084
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614200000000000000000000
          0000396518187110108610109E1810AE2918BA2910BE2910BE2910BE2108BA21
          08A210007D082161100000008461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461420000000000000000004A61213165
          18107510088A10089E10089E1000820821611000000000000084614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142000000000000000000000000426121396518000000
          0000008461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614200000000000084614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142}
        Stretch = True
        Visible = False
      end
      object imgSmallIcon: TImage
        Left = 132
        Top = 224
        Width = 16
        Height = 16
        AutoSize = True
        Picture.Data = {
          07544269746D617036030000424D360300000000000036000000280000001000
          000010000000010018000000000000030000130B0000130B0000000000000000
          0000FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
          FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
          FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
          00FFFF00FFFF00FF39657B29718C315163393831FF00FFFF00FFFF00FFFF00FF
          FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF39655A10A6CE08BEEF08BA
          F710AAE7188AB521617B31454A423829FF00FFFF00FFFF00FFFF00FFFF00FFFF
          00FF525D29299E3942CF7318965A10968408A6B508BAE708B2EF08BEF710A2D6
          217194295163423829FF00FFFF00FFFF00FF31752942DF6B42AE5A735D527375
          4A398E4229864A189A6B10AAA508AAC608B2E708C3F7295D7BFF00FFFF00FFFF
          00FF42793142DF6B399242734552A5616B6B494A94616373755242793942864A
          219A5A109E84187173393021FF00FFFF00FF5A5D29109E213992395238427B51
          5263414A84515A7B4952734952A5656B63614A6B6D4A4A8642216118FF00FFFF
          00FF39652108AA213992394228315A414A523C425A414263454A5A414284555A
          6B454A8C515A9C7173298229FF00FFFF00FF397D3131D752299A293938314234
          315238423928315A38424A383963454A5A414263454A7B5D5A215918FF00FFFF
          00FF52693142B65231CF5231BE4A29A639398239294529424531422C394A2C39
          5238424A30395A4942294110FF00FFFF00FFFF00FFFF00FF6365314A7531399A
          3931BA4229C34221BA39318E312165294A5D39392831423C39187118FF00FFFF
          00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF5A6D31427D31299E3118B629
          18B229218E29108E21187518FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
          FFFF00FFFF00FFFF00FFFF00FF636531426D29298618217D18FF00FFFF00FFFF
          00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
          FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
          FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
          00FF}
        Transparent = True
        Visible = False
      end
    end
    object panMemoryMap: TPanel
      Left = 0
      Top = 0
      Width = 714
      Height = 20
      Align = alTop
      Caption = 'Memory Map'
      Color = 8675650
      Font.Charset = ANSI_CHARSET
      Font.Color = clCream
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      object Panel14: TPanel
        Left = 678
        Top = 1
        Width = 35
        Height = 18
        Align = alRight
        BevelOuter = bvNone
        Color = 8675650
        TabOrder = 0
        object cmdMemoryMapDecrease: TBitBtn
          Tag = -1
          Left = 1
          Top = 2
          Width = 14
          Height = 14
          Hint = 
            'Decrease Map Detail|Decreases the size of the display used to sh' +
            'ow the Memory Map'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
          OnClick = cmdMemoryMapDecreaseClick
          Glyph.Data = {
            C6000000424DC6000000000000007600000028000000090000000A0000000100
            0400000000005000000000000000000000001000000010000000000000000000
            80000080000000808000800000008000800080800000C0C0C000808080000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDD000
            0000DDDDDDDDD0000000DDDDDDDDD0000000DDDDDDDDD0000000DD000000D000
            0000DD000000D0000000DDDDDDDDD0000000DDDDDDDDD0000000DDDDDDDDD000
            0000DDDDDDDDD0000000}
        end
        object cmdMemoryMapIncrease: TBitBtn
          Tag = 1
          Left = 17
          Top = 2
          Width = 14
          Height = 14
          Hint = 
            'Increase Map Detail|Increases the size of the display used to sh' +
            'ow the Memory Map'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
          OnClick = cmdMemoryMapIncreaseClick
          Glyph.Data = {
            C6000000424DC6000000000000007600000028000000090000000A0000000100
            0400000000005000000000000000000000001000000010000000000000000000
            80000080000000808000800000008000800080800000C0C0C000808080000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDD000
            0000DDDDDDDDD0000000DDDD00DDD0000000DDDD00DDD0000000DD000000D000
            0000DD000000D0000000DDDD00DDD0000000DDDD00DDD0000000DDDDDDDDD000
            0000DDDDDDDDD0000000}
        end
      end
    end
  end
  object imgTabImages: TImageList
    Left = 20
    Top = 272
    Bitmap = {
      494C0101020004001C0010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000001000000001002000000000000010
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C0A0900060483000604830006048
      3000604830006048300060483000604830006048300060483000604830006048
      3000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000039637B002973
      8C00315263003939310000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C0A89000FFF8F000FFF0E000F0E8
      E000F0E0D000F0D0C000F0C8B000E0C0A000E0B8A000E0B09000E0A890006048
      3000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000039635A0010A5CE0008BD
      EF0008BDF70010ADE700188CB50021637B0031424A0042392900000000000000
      000000000000000000000000000000000000C0A8A000FFFFF000C0A8A000B0A0
      A000F0E8E000B0A09000B0989000B0989000B0989000B0989000E0B090006048
      3000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000525A2900299C390042CE73001894
      5A001094840008A5B50008BDE70008B5EF0008BDF70010A5D600217394002952
      630042392900000000000000000000000000C0A8A000FFFFF000FFFFF000FFF8
      F000FFF0E000F0E8E000F0E0D000F0D0C000F0C8B000E0C0A000E0B8A0006048
      3000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000003173290042DE6B0042AD5A00735A
      520073734A00398C420029844A00189C6B0010ADA50008ADC60008B5E70008C6
      F700295A7B00000000000000000000000000C0A8A000FFFFF000B0A8A000B0A0
      A000FFF8F000B0A09000B0989000B0989000B0989000B0989000E0C0A0006048
      3000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000427B310042DE6B00399442007342
      5200A5636B006B4A4A009463630073735200427B390042844A00219C5A00109C
      840018737300393121000000000000000000C0B0A000FFFFF000FFFFF000FFFF
      F000FFFFF000FFF8F000FFF0E000F0E8E000F0E0D000F0D0C000F0C8B0006048
      3000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000005A5A2900109C2100399439005239
      42007B52520063424A0084525A007B4A5200734A5200A5636B0063634A006B6B
      4A004A844200216318000000000000000000C0B0A000FFFFF000FFFFF000FFFF
      F000FFFFF000FFFFF000FFF8F000C0C8C00040607000F0E0D000F0D0C0006048
      3000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000003963210008AD2100399439004229
      31005A424A00523942005A42420063424A005A42420084525A006B424A008C52
      5A009C737300298429000000000000000000C0B0A000FFFFFF00E0E8F0006078
      8000E0E0E000FFFFF000C0C8D0005060700030A8D00020384000B0A0A0006048
      30000000000000000000A0A07500408050000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000397B310031D65200299C29003939
      31004231310052394200392931005A3942004A39390063424A005A4242006342
      4A007B5A5A00215A18000000000000000000D0B0A000FFFFFF0090A8B00080D0
      E00050607000B0B8C0005060700060C0E0005060700030B8F000102830001030
      400010283000716763004078400050A860000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000526B310042B5520031CE520031BD
      4A0029A53900398439002942290042423100422939004A293900523942004A31
      39005A4A4200294210000000000000000000D0B8A000FFFFFF00E0E8F00090A8
      B00080E0F0005060700080D0E0005060700060D0F0004060700030B0E0002098
      D0002088B000205070005088600050B060000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000636331004A73
      3100399C390031BD420029C6420021BD3900318C3100216329004A5A39003929
      310042393900187318000000000000000000D0B8A000D0B8A000D0B8A000C0B0
      A00090A8B00080E0F0005060700080E0F0004058700060D0F00050C8F00040C0
      F00020B0E00020A0D0006098700050B870000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000005A6B3100427B3100299C310018B5290018B52900218C
      2900108C21001873180000000000000000000000000000000000000000000000
      00000000000090A8B00080E0F0004058700080E0F00070D8F00060D0F00050C8
      F00040C0F00030B8F00070A8800060C080000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000063633100426B29002984
      1800217B18000000000000000000000000000000000000000000000000000000
      0000000000000000000090A8B00080E0F00080E0F00080E0F00070D8F00060D0
      F00060B0D00080889000B0C0A00090D0A0000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000090A8B00090A0B00090A0A0008098A0008090
      A00080889000B7A59A00A0B8A000B0C0A0000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFF00000000FFFF000F00000000
      C3FF000F00000000803F000F000000000007000F000000000007000F00000000
      0003000F000000000003000F000000000003000C000000000003000000000000
      0003000000000000C003000000000000FC03F80000000000FF87FC0000000000
      FFFFFE0000000000FFFFFFFF0000000000000000000000000000000000000000
      000000000000}
  end
end
