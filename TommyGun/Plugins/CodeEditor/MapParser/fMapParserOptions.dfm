object frmMapParserOptions: TfrmMapParserOptions
  Left = 1230
  Top = -2
  ClientHeight = 977
  ClientWidth = 600
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panMapParser: TPanel
    Left = 0
    Top = 0
    Width = 600
    Height = 981
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
    object scpMapParser: TScrollBox
      Left = 0
      Top = 41
      Width = 600
      Height = 940
      VertScrollBar.Smooth = True
      VertScrollBar.Tracking = True
      Align = alClient
      TabOrder = 0
      object panOptions: TPanel
        Left = 0
        Top = 0
        Width = 579
        Height = 1465
        Align = alTop
        TabOrder = 0
        DesignSize = (
          579
          1465)
        object grpScreenPrefix: TGroupBox
          Left = 6
          Top = 6
          Width = 564
          Height = 81
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Screen Name Prefix'
          Color = clWhite
          ParentBackground = False
          ParentColor = False
          TabOrder = 0
          DesignSize = (
            564
            81)
          object Label2: TLabel
            Left = 8
            Top = 40
            Width = 548
            Height = 41
            Anchors = [akLeft, akTop, akRight]
            AutoSize = False
            Caption = 
              'This is the name prefixed to all screen tables. All screens are ' +
              'numbered in col/row format. eg. Screen002x001 is Screen column 2' +
              ', row 1.'
            WordWrap = True
            ExplicitWidth = 389
          end
          object edtPrefix: TEdit
            Left = 8
            Top = 16
            Width = 548
            Height = 21
            Anchors = [akLeft, akTop, akRight]
            Color = clWhite
            TabOrder = 0
          end
        end
        object grpMapOutputInformation: TGroupBox
          Left = 6
          Top = 93
          Width = 564
          Height = 294
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Map Screens'
          Color = clWhite
          ParentBackground = False
          ParentColor = False
          TabOrder = 1
          object lblTileWidth: TLabel
            Left = 40
            Top = 171
            Width = 47
            Height = 13
            Caption = 'Tile Width'
            Enabled = False
          end
          object lblTileHeight: TLabel
            Left = 40
            Top = 197
            Width = 50
            Height = 13
            Caption = 'Tile Height'
            Enabled = False
          end
          object lblDefaultTileIndex: TLabel
            Left = 24
            Top = 224
            Width = 54
            Height = 13
            Caption = 'Default Tile'
            Enabled = False
          end
          object lblDefaultMessage: TLabel
            Left = 40
            Top = 244
            Width = 171
            Height = 11
            Caption = 'If a tile is missing then this index is used  '
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -9
            Font.Name = 'Tahoma'
            Font.Style = [fsItalic]
            ParentFont = False
          end
          object lblIndexOnlyMessage: TLabel
            Left = 24
            Top = 277
            Width = 103
            Height = 11
            Caption = 'Default is a Byte (defb)  '
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -9
            Font.Name = 'Tahoma'
            Font.Style = [fsItalic]
            ParentFont = False
          end
          object lblCoordIndexMessage: TLabel
            Left = 41
            Top = 104
            Width = 100
            Height = 11
            Caption = 'Default is a Byte (defb) '
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -9
            Font.Name = 'Tahoma'
            Font.Style = [fsItalic]
            ParentFont = False
          end
          object radUseCoordIndex: TRadioButton
            Left = 8
            Top = 19
            Width = 193
            Height = 17
            Caption = 'Co-ordinate/Index pair based map'
            Checked = True
            TabOrder = 0
            TabStop = True
            OnClick = radUseCoordIndexClick
          end
          object radUseIndexOnly: TRadioButton
            Left = 8
            Top = 121
            Width = 149
            Height = 17
            Caption = 'Index only tile based map'
            TabOrder = 1
            OnClick = radUseCoordIndexClick
          end
          object edtTileWidth: KSpinEdit
            Left = 96
            Top = 167
            Width = 64
            Height = 20
            BevelOuter = bvLowered
            Color = clWhite
            Enabled = False
            TabOrder = 2
            Value = 8
            Max = 256
            Step = 8
            DesignSize = (
              64
              20)
          end
          object edtTileHeight: KSpinEdit
            Left = 96
            Top = 193
            Width = 64
            Height = 21
            BevelOuter = bvLowered
            Color = clWhite
            Enabled = False
            TabOrder = 3
            Value = 8
            Max = 256
            Step = 8
            DesignSize = (
              64
              21)
          end
          object chkOverrideTileSize: TCheckBox
            Left = 24
            Top = 144
            Width = 172
            Height = 17
            Caption = 'Override the maps tile size'
            Enabled = False
            TabOrder = 4
            OnClick = radUseCoordIndexClick
          end
          object edtDefaultTileIndex: KSpinEdit
            Left = 96
            Top = 220
            Width = 64
            Height = 20
            BevelOuter = bvLowered
            Color = clWhite
            Enabled = False
            ParentBackground = False
            TabOrder = 5
            DesignSize = (
              64
              20)
          end
          object chkIndexUseDefw: TCheckBox
            Left = 8
            Top = 261
            Width = 211
            Height = 17
            Caption = 'Use Word (defw) to store indexes'
            Enabled = False
            TabOrder = 6
          end
          object chkConvertX: TCheckBox
            Left = 24
            Top = 42
            Width = 239
            Height = 17
            Caption = 'Convert X co-ordinate to Character position'
            TabOrder = 7
          end
          object chkConvertY: TCheckBox
            Left = 24
            Top = 65
            Width = 247
            Height = 17
            Caption = 'Convert Y co-ordinate to Character position'
            TabOrder = 8
          end
          object chkCoordUseDefw: TCheckBox
            Left = 24
            Top = 88
            Width = 225
            Height = 17
            Caption = 'Use Word (defw) to store co-ordinates'
            Enabled = False
            TabOrder = 9
          end
        end
        object FlatGroupBox2: TGroupBox
          Left = 7
          Top = 393
          Width = 563
          Height = 274
          Anchors = [akLeft, akTop, akRight]
          TabOrder = 2
          DesignSize = (
            563
            274)
          object lblApplication: TLabel
            Left = 8
            Top = 86
            Width = 52
            Height = 13
            Caption = 'Application'
            Enabled = False
          end
          object lblParameters: TLabel
            Left = 8
            Top = 114
            Width = 55
            Height = 13
            Caption = 'Parameters'
            Enabled = False
          end
          object lblConvertToSourceCode: TLabel
            Left = 24
            Top = 159
            Width = 531
            Height = 29
            Anchors = [akLeft, akTop, akRight]
            AutoSize = False
            Caption = 'Converts the binary output file (out.bin) into Source Code.'
            Enabled = False
            WordWrap = True
            ExplicitWidth = 395
          end
          object lblUseOutputBinary: TLabel
            Left = 24
            Top = 217
            Width = 531
            Height = 53
            Anchors = [akLeft, akTop, akRight]
            AutoSize = False
            Caption = 
              'Copies the '#39'out.bin'#39' file generated to a new file in sequential ' +
              'order of the data being generated. The Source Code generated wil' +
              'l then '#39'incbin'#39' the file.'
            Enabled = False
            WordWrap = True
            ExplicitWidth = 395
          end
          object Label3: TLabel
            Left = 8
            Top = 18
            Width = 549
            Height = 58
            Anchors = [akLeft, akTop, akRight]
            AutoSize = False
            Caption = 
              'This step will call an external application to allow you to post' +
              ' process the map data. It will save the map data to an input fil' +
              'e called '#39'in.bin'#39' and then run the application; finally expectin' +
              'g an output file called '#39'out.bin'#39' as a result.'
            WordWrap = True
            ExplicitWidth = 413
          end
          object edtApplication: TEdit
            Left = 72
            Top = 82
            Width = 455
            Height = 21
            Anchors = [akLeft, akTop, akRight]
            Color = clWhite
            Enabled = False
            TabOrder = 0
            OnChange = edtApplicationChange
          end
          object edtParameters: TEdit
            Left = 72
            Top = 109
            Width = 483
            Height = 21
            Anchors = [akLeft, akTop, akRight]
            Color = clWhite
            Enabled = False
            TabOrder = 1
            OnChange = edtApplicationChange
          end
          object radConvertToSourceCode: TRadioButton
            Left = 8
            Top = 136
            Width = 229
            Height = 17
            Caption = 'Convert output file back into Source Code'
            Checked = True
            Color = clWhite
            Enabled = False
            ParentColor = False
            TabOrder = 2
            TabStop = True
            OnClick = radUseCoordIndexClick
          end
          object radUseOutputBinary: TRadioButton
            Left = 8
            Top = 194
            Width = 153
            Height = 17
            Caption = 'Use the Output Binary file'
            Color = clWhite
            Enabled = False
            ParentColor = False
            TabOrder = 3
            OnClick = radUseCoordIndexClick
          end
          object cmdApplication: TButton
            Left = 533
            Top = 81
            Width = 22
            Height = 19
            Hint = 'Locate an application to call during the post-process phase'
            Anchors = [akTop, akRight]
            Caption = '...'
            Enabled = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 4
            OnClick = cmdApplicationClick
          end
        end
        object chkUsePostProcessor: TCheckBox
          Left = 14
          Top = 393
          Width = 255
          Height = 17
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Use Post Processing'
          Color = clWhite
          ParentColor = False
          TabOrder = 3
          OnClick = chkUsePostProcessorClick
        end
        object grpMapName: TGroupBox
          Left = 7
          Top = 673
          Width = 563
          Height = 76
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Map Table'
          Color = clWhite
          ParentBackground = False
          ParentColor = False
          TabOrder = 4
          DesignSize = (
            563
            76)
          object lblDefaultTableName: TLabel
            Left = 72
            Top = 36
            Width = 137
            Height = 11
            Caption = 'Default Table Name: MapTable  '
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -9
            Font.Name = 'Tahoma'
            Font.Style = [fsItalic]
            ParentFont = False
          end
          object lblMapSortOrder: TLabel
            Left = 8
            Top = 53
            Width = 51
            Height = 13
            Caption = 'Sort Order'
          end
          object Label5: TLabel
            Left = 8
            Top = 24
            Width = 56
            Height = 13
            Caption = 'Table Name'
          end
          object edtTableName: TEdit
            Left = 72
            Top = 16
            Width = 483
            Height = 21
            Anchors = [akLeft, akTop, akRight]
            ParentColor = True
            TabOrder = 0
          end
          object radMapColRow: TRadioButton
            Left = 72
            Top = 53
            Width = 123
            Height = 17
            Caption = 'Column / Row (X / Y)'
            Checked = True
            Color = clWhite
            ParentColor = False
            TabOrder = 1
            TabStop = True
            OnClick = radUseCoordIndexClick
          end
          object radMapRowCol: TRadioButton
            Left = 206
            Top = 53
            Width = 119
            Height = 17
            Caption = 'Row / Column (Y / X)'
            Color = clWhite
            ParentColor = False
            TabOrder = 2
            OnClick = radUseCoordIndexClick
          end
        end
        object grpTilesTable: TGroupBox
          Left = 6
          Top = 755
          Width = 564
          Height = 515
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Tiles Table'
          Color = clWhite
          ParentBackground = False
          ParentColor = False
          TabOrder = 5
          DesignSize = (
            564
            515)
          object lblBuildTheTilesTable: TLabel
            Left = 24
            Top = 32
            Width = 539
            Height = 49
            Anchors = [akLeft, akTop, akRight]
            AutoSize = False
            Caption = 
              'Using this option inserts the Tile Table resources into the code' +
              '.'
            WordWrap = True
            ExplicitWidth = 380
          end
          object chkBuildTilesTable: TCheckBox
            Left = 8
            Top = 16
            Width = 113
            Height = 17
            Caption = 'Build the Tiles Table'
            Checked = True
            Color = clWhite
            ParentColor = False
            State = cbChecked
            TabOrder = 0
          end
          object FlatGroupBox4: TGroupBox
            Left = 20
            Top = 78
            Width = 536
            Height = 75
            Anchors = [akLeft, akTop, akRight]
            Caption = 'Sprite Index Management'
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            TabOrder = 1
            object Label1: TLabel
              Left = 26
              Top = 32
              Width = 235
              Height = 11
              Caption = 'Requires a Image Type indicator field in the Tiles Table  '
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -9
              Font.Name = 'Tahoma'
              Font.Style = [fsItalic]
              ParentFont = False
            end
            object Label4: TLabel
              Left = 26
              Top = 60
              Width = 240
              Height = 11
              Caption = 'Requires a No. of frames indicator field in the Tiles Table  '
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -9
              Font.Name = 'Tahoma'
              Font.Style = [fsItalic]
              ParentFont = False
            end
            object FlatRadioButton1: TRadioButton
              Left = 10
              Top = 16
              Width = 199
              Height = 17
              Caption = 'Use separate Tile and Sprite Tables'
              Checked = True
              TabOrder = 0
              TabStop = True
              OnClick = radUseCoordIndexClick
            end
            object FlatRadioButton2: TRadioButton
              Left = 10
              Top = 44
              Width = 207
              Height = 17
              Caption = 'Merge the Sprites into the Tiles Table'
              TabOrder = 1
              OnClick = radUseCoordIndexClick
            end
          end
          object grpTilesTableFormat: TGroupBox
            Left = 20
            Top = 155
            Width = 536
            Height = 353
            Anchors = [akLeft, akTop, akRight]
            Caption = 'Tiles Table Format'
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            TabOrder = 2
            DesignSize = (
              536
              353)
            object cmdTilesTableFormatUp: TBitBtn
              Left = 502
              Top = 14
              Width = 24
              Height = 24
              Hint = 'Move the selected item up in priority in the list'
              Anchors = [akTop, akRight]
              Enabled = False
              ParentShowHint = False
              ShowHint = True
              TabOrder = 0
              OnClick = cmdTilesTableFormatUpClick
              Glyph.Data = {
                AE000000424DAE00000000000000760000002800000009000000070000000100
                0400000000003800000000000000000000001000000010000000000000000000
                80000080000000808000800000008000800080800000C0C0C000808080000000
                FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDD000
                00000000000000000000D0000000D0000000DD00000DD0000000DDD000DDD000
                0000DDDD0DDDD0000000DDDDDDDDD0000000}
            end
            object cmdTilesTableFormatDown: TBitBtn
              Left = 502
              Top = 44
              Width = 24
              Height = 24
              Hint = 'Move the selected item down in priority in the list'
              Anchors = [akTop, akRight]
              Enabled = False
              ParentShowHint = False
              ShowHint = True
              TabOrder = 1
              OnClick = cmdTilesTableFormatDownClick
              Glyph.Data = {
                AE000000424DAE00000000000000760000002800000009000000070000000100
                0400000000003800000000000000000000001000000010000000000000000000
                80000080000000808000800000008000800080800000C0C0C000808080000000
                FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDD000
                0000DDDD0DDDD0000000DDD000DDD0000000DD00000DD0000000D0000000D000
                00000000000000000000DDDDDDDDD0000000}
            end
            object cmdTilesTableFormatAdd: TBitBtn
              Left = 502
              Top = 184
              Width = 24
              Height = 24
              Hint = 
                'Add the selected item from the available items list to the table' +
                ' format list'
              Anchors = [akTop, akRight]
              Enabled = False
              ParentShowHint = False
              ShowHint = True
              TabOrder = 2
              OnClick = cmdTilesTableFormatAddClick
              Glyph.Data = {
                36040000424D3604000000000000360000002800000010000000100000000100
                2000000000000004000000000000000000000000000000000000FF00FF00FF00
                FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
                FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
                FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
                FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
                FF00FF00FF00FF00FF00FF00FF00FF00FF008484840084848400848484008484
                840084848400FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
                FF00FF00FF00FF00FF00FF00FF00000000000000000000000000000000000000
                000084848400FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
                FF00FF00FF00FF00FF00FF00FF000000000000FF000000FF000000FF00000000
                000084848400FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
                FF00FF00FF0084848400848484000000000000FF000000FF000000FF00000000
                000084848400848484008484840084848400FF00FF00FF00FF00FF00FF00FF00
                FF000000000000000000000000000000000000FF000000FF000000FF00000000
                000000000000000000000000000084848400FF00FF00FF00FF00FF00FF00FF00
                FF000000000000FF000000FF000000FF000000FF000000FF000000FF000000FF
                000000FF000000FF00000000000084848400FF00FF00FF00FF00FF00FF00FF00
                FF000000000000FF000000FF000000FF000000FF000000FF000000FF000000FF
                000000FF000000FF00000000000084848400FF00FF00FF00FF00FF00FF00FF00
                FF000000000000FF000000FF000000FF000000FF000000FF000000FF000000FF
                000000FF000000FF00000000000084848400FF00FF00FF00FF00FF00FF00FF00
                FF000000000000000000000000000000000000FF000000FF000000FF00000000
                0000000000000000000000000000FF00FF00FF00FF00FF00FF00FF00FF00FF00
                FF00FF00FF00FF00FF00FF00FF000000000000FF000000FF000000FF00000000
                000084848400FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
                FF00FF00FF00FF00FF00FF00FF000000000000FF000000FF000000FF00000000
                000084848400FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
                FF00FF00FF00FF00FF00FF00FF00000000000000000000000000000000000000
                0000FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
                FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
                FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
                FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
                FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00}
            end
            object cmdTilesTableFormatRemove: TBitBtn
              Left = 502
              Top = 74
              Width = 24
              Height = 24
              Hint = 
                'Remove the item from this format list back into the available it' +
                'ems list'
              Anchors = [akTop, akRight]
              Enabled = False
              ParentShowHint = False
              ShowHint = True
              TabOrder = 3
              OnClick = cmdTilesTableFormatRemoveClick
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
            object panTilesTableFormat: TPanel
              Left = 8
              Top = 16
              Width = 488
              Height = 160
              Anchors = [akLeft, akTop, akRight]
              ParentColor = True
              TabOrder = 4
              object lstTileTableFormat: TListView
                Left = 1
                Top = 1
                Width = 486
                Height = 158
                Align = alClient
                BorderStyle = bsNone
                Color = clWhite
                Columns = <
                  item
                    Caption = 'Item'
                    MaxWidth = 120
                    MinWidth = 120
                    Width = 120
                  end
                  item
                    Alignment = taCenter
                    Caption = 'Bytes'
                    MaxWidth = 40
                    MinWidth = 40
                    Width = 40
                  end
                  item
                    Caption = 'Description'
                    MinWidth = 120
                    Width = 500
                  end>
                ColumnClick = False
                FlatScrollBars = True
                GridLines = True
                HideSelection = False
                ReadOnly = True
                RowSelect = True
                TabOrder = 0
                ViewStyle = vsReport
                OnChange = lstTileTableFormatChange
                OnDblClick = cmdTilesTableFormatRemoveClick
              end
            end
            object panItemsAvailable: TPanel
              Left = 8
              Top = 184
              Width = 488
              Height = 160
              Anchors = [akLeft, akTop, akRight]
              ParentColor = True
              TabOrder = 5
              object lstItemsAvailable: TListView
                Left = 1
                Top = 1
                Width = 486
                Height = 158
                Align = alClient
                BorderStyle = bsNone
                Color = clWhite
                Columns = <
                  item
                    Caption = 'Item'
                    MaxWidth = 120
                    MinWidth = 120
                    Width = 120
                  end
                  item
                    Alignment = taCenter
                    Caption = 'Bytes'
                    MaxWidth = 40
                    MinWidth = 40
                    Width = 40
                  end
                  item
                    Caption = 'Description'
                    MinWidth = 120
                    Width = 500
                  end>
                ColumnClick = False
                FlatScrollBars = True
                GridLines = True
                HideSelection = False
                ReadOnly = True
                RowSelect = True
                TabOrder = 0
                ViewStyle = vsReport
                OnChange = lstItemsAvailableChange
                OnDblClick = cmdTilesTableFormatAddClick
              end
            end
          end
        end
        object grpNumberBase: TGroupBox
          Left = 8
          Top = 1276
          Width = 562
          Height = 112
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Number Base'
          Color = clWhite
          ParentBackground = False
          ParentColor = False
          TabOrder = 6
          object lblNumberBasePrefix: TLabel
            Left = 8
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
            Left = 8
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
        object grpEndianess: TGroupBox
          Left = 6
          Top = 1394
          Width = 563
          Height = 62
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Endianess'
          Color = clWhite
          ParentBackground = False
          ParentColor = False
          TabOrder = 7
          object radLittleEndian: TRadioButton
            Left = 8
            Top = 16
            Width = 181
            Height = 17
            Caption = 'Little Endian (Z80, 6502, x86 etc)'
            Checked = True
            Enabled = False
            TabOrder = 0
            TabStop = True
            OnClick = radUseCoordIndexClick
          end
          object radBigEndian: TRadioButton
            Left = 8
            Top = 39
            Width = 161
            Height = 17
            Caption = 'Big Endian (6800, 68000 etc)'
            Enabled = False
            TabOrder = 1
            OnClick = radUseCoordIndexClick
          end
        end
      end
    end
    object panTitle: TPanel
      Left = 0
      Top = 0
      Width = 600
      Height = 41
      Align = alTop
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 1
      object lblMapParserDescription: TLabel
        Left = 8
        Top = 20
        Width = 226
        Height = 13
        AutoSize = False
        Caption = 'Parses maps into co-ordinate based tiled data.'
      end
      object lblMapParser: TLabel
        Left = 4
        Top = 4
        Width = 70
        Height = 13
        Caption = 'Maps Parser'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
  end
  object dlgBrowse: TOpenDialog
    DefaultExt = '*.exe'
    Filter = 'Application Files|*.exe|Batch Files|*.bat|All Files|*.*'
    InitialDir = 'C:\Program Files'
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing, ofDontAddToRecent]
    Title = 'Locate Application'
    Left = 232
    Top = 8
  end
  object regScorpio: KRegistry
    Section = 'TommyGun'
    RootKey = rkHKEY_CURRENT_USER
    SoftwareKey = '\Software\Scorpio\'
    Left = 264
    Top = 8
  end
end
