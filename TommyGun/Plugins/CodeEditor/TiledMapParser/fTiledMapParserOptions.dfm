object frmTiledMapParserOptions: TfrmTiledMapParserOptions
  Left = 841
  Top = 402
  Width = 279
  Height = 582
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panTiledMapParser: TPanel
    Left = 0
    Top = 0
    Width = 263
    Height = 546
    Align = alClient
    BevelOuter = bvNone
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object scpTiledMapParser: TScrollBox
      Left = 0
      Top = 41
      Width = 263
      Height = 505
      ColorBar = clBtnShadow
      ColorBorder = clBtnShadow
      ColorBarHighlight = clBtnHighlight
      Align = alClient
      TabOrder = 0
      object shpMapOptions: KShadePanel
        Left = 0
        Top = 0
        Width = 254
        Height = 377
        Cursor = 25
        Speed = 15
        AutoWidth = True
        Caption = 'Options'
        LineColor = clBtnShadow
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -13
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = [fsBold]
        ShowSeperator = True
        PanelHeight = 377
        ParentName = 'TfrmTiledMapParserOptions'
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        DesignSize = (
          254
          377)
        object FlatGroupBox1: TGroupBox
          Left = 4
          Top = 280
          Width = 256
          Height = 93
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Tiles Table'
          TabOrder = 1
          ColorBorder = clBtnShadow
          Border = brOnlyTopLine
          DesignSize = (
            256
            93)
          object Label4: TLabel
            Left = 24
            Top = 36
            Width = 224
            Height = 53
            Anchors = [akLeft, akTop, akRight]
            AutoSize = False
            Caption = 
              'Using this option requires you to Insert the Tile resources into' +
              ' the code. You should not Insert the Tile Images Table though, a' +
              's this would be unnecessary.'
            WordWrap = True
          end
          object chkBuildTilesTable: TCheckBox
            Left = 8
            Top = 16
            Width = 240
            Height = 17
            Caption = 'Build the Tiles Table'
            ColorBorder = clBtnShadow
            ColorInnerShadow = clWhite
            Anchors = [akLeft, akTop, akRight]
            TabOrder = 0
            TabStop = True
          end
        end
        object grpCoordinates: TGroupBox
          Left = 4
          Top = 184
          Width = 256
          Height = 93
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Tiling Options'
          TabOrder = 2
          ColorBorder = clBtnShadow
          Border = brOnlyTopLine
          DesignSize = (
            256
            93)
          object Label3: TLabel
            Left = 24
            Top = 76
            Width = 112
            Height = 13
            Caption = 'Default is a Byte (defb)'
          end
          object lblDefaultTileIndex: TLabel
            Left = 8
            Top = 20
            Width = 85
            Height = 13
            Caption = 'Default Tile Index'
          end
          object lblDefaultMessage: TLabel
            Left = 24
            Top = 40
            Width = 195
            Height = 13
            Caption = 'If a tile is missing then this index is used.'
          end
          object chkUseDefw: TCheckBox
            Left = 8
            Top = 60
            Width = 240
            Height = 17
            Caption = 'Use Word (defw) to store tile indexes'
            ColorBorder = clBtnShadow
            ColorInnerShadow = clWhite
            Anchors = [akLeft, akTop, akRight]
            TabOrder = 0
            TabStop = True
          end
          object edtDefaultTileIndex: KSpinEdit
            Left = 100
            Top = 16
            Width = 57
            Height = 20
            ColorFlat = clWhite
            ColorInnerShadow = 14805739
            AutoSize = False
            Max = 0
            Min = 0
            ParentColor = True
            TabOrder = 1
            Value = 0
          end
        end
        object grpScreenPrefix: TGroupBox
          Left = 4
          Top = 96
          Width = 256
          Height = 81
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Screen Name Prefix'
          TabOrder = 3
          ColorBorder = clBtnShadow
          Border = brOnlyTopLine
          DesignSize = (
            256
            81)
          object Label2: TLabel
            Left = 8
            Top = 40
            Width = 240
            Height = 41
            Anchors = [akLeft, akTop, akRight]
            AutoSize = False
            Caption = 
              'This is the name prefixed to all screen tables. All screens are ' +
              'numbered in col/row format. eg. Screen002x001 is Screen column 2' +
              ', row 1.'
            WordWrap = True
          end
          object edtPrefix: TEdit
            Left = 8
            Top = 16
            Width = 242
            Height = 19
            ColorFlat = clWhite
            ColorInnerShadow = 14805739
            ParentColor = True
            Anchors = [akLeft, akTop, akRight]
            TabOrder = 0
          end
        end
        object grpMapName: TGroupBox
          Left = 4
          Top = 24
          Width = 256
          Height = 73
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Map Table Name'
          TabOrder = 4
          ColorBorder = clBtnShadow
          Border = brOnlyTopLine
          DesignSize = (
            256
            73)
          object Label1: TLabel
            Left = 8
            Top = 40
            Width = 240
            Height = 29
            Anchors = [akLeft, akTop, akRight]
            AutoSize = False
            Caption = 'A blank name will use the default Map table name: MapTable'
            WordWrap = True
          end
          object edtTableName: TEdit
            Left = 8
            Top = 16
            Width = 242
            Height = 19
            ColorFlat = clWhite
            ColorInnerShadow = 14805739
            ParentColor = True
            Anchors = [akLeft, akTop, akRight]
            TabOrder = 0
          end
        end
      end
    end
    object panTitle: TPanel
      Left = 0
      Top = 0
      Width = 263
      Height = 41
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      object lblTiledMapParserDescription: TLabel
        Left = 8
        Top = 20
        Width = 197
        Height = 13
        Caption = 'Parses maps into indexed tiled map data.'
      end
      object lblTiledMapParser: TLabel
        Left = 4
        Top = 4
        Width = 143
        Height = 13
        Caption = 'Indexed Tiles Map Parser'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
  end
end
