object frmImageEditor: TfrmImageEditor
  Left = 684
  Top = 115
  Align = alClient
  BorderIcons = []
  BorderStyle = bsNone
  Caption = 'Image Editor'
  ClientHeight = 737
  ClientWidth = 1058
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
  object panTools: TPanel
    Left = 766
    Top = 0
    Width = 292
    Height = 737
    Align = alRight
    BevelOuter = bvNone
    Color = clWhite
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object pgcTools: TPageControl
      Left = 0
      Top = 0
      Width = 292
      Height = 737
      ActivePage = tabOptions
      Align = alClient
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      Images = imgTabImages
      MultiLine = True
      OwnerDraw = True
      ParentFont = False
      TabHeight = 32
      TabOrder = 0
      OnDrawTab = pgcToolsDrawTab
      object tabOptions: TTabSheet
        Caption = 'Settings'
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object scpOptions: TScrollBox
          Left = 0
          Top = 0
          Width = 284
          Height = 695
          VertScrollBar.Smooth = True
          VertScrollBar.Tracking = True
          Align = alClient
          BevelInner = bvNone
          BevelOuter = bvNone
          BorderStyle = bsNone
          Color = clWhite
          ParentColor = False
          TabOrder = 0
          object panOptions: TPanel
            Left = 0
            Top = 0
            Width = 284
            Height = 665
            Align = alTop
            BevelOuter = bvNone
            FullRepaint = False
            Padding.Left = 4
            Padding.Top = 4
            Padding.Right = 4
            Padding.Bottom = 4
            TabOrder = 0
            DesignSize = (
              284
              665)
            object grpEditorGridLines: TGroupBox
              Left = 8
              Top = 75
              Width = 269
              Height = 109
              Anchors = [akLeft, akTop, akRight]
              Caption = ' Grid Lines '
              Color = clWhite
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -12
              Font.Name = 'Tahoma'
              Font.Style = [fsBold]
              ParentBackground = False
              ParentColor = False
              ParentFont = False
              TabOrder = 0
              DesignSize = (
                269
                109)
              object lblChrLineColor: TLabel
                Left = 28
                Top = 60
                Width = 98
                Height = 13
                Caption = 'Character Line Color'
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblPixelLineColor: TLabel
                Left = 28
                Top = 84
                Width = 72
                Height = 13
                Caption = 'Pixel Line Color'
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object chkGridPixel: TCheckBox
                Left = 12
                Top = 36
                Width = 122
                Height = 17
                Caption = 'Show pixel grid'
                Color = clWhite
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentColor = False
                ParentFont = False
                TabOrder = 1
                OnClick = actTogglePixelGridExecute
              end
              object chkGridCharacter: TCheckBox
                Left = 12
                Top = 16
                Width = 145
                Height = 17
                Caption = 'Show character grid'
                Color = clWhite
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentColor = False
                ParentFont = False
                TabOrder = 0
                OnClick = actToggleCharGridExecute
              end
              object panChrLineColor: TPanel
                Left = 152
                Top = 52
                Width = 105
                Height = 21
                Anchors = [akLeft, akTop, akRight]
                BevelOuter = bvLowered
                Color = 4766455
                ParentBackground = False
                TabOrder = 2
                OnClick = panChrLineColorClick
              end
              object panPixelLineColor: TPanel
                Left = 152
                Top = 80
                Width = 105
                Height = 21
                Anchors = [akLeft, akTop, akRight]
                BevelOuter = bvLowered
                Color = 16512
                ParentBackground = False
                TabOrder = 3
                OnClick = panPixelLineColorClick
              end
            end
            object grpEditorMagnification: TGroupBox
              Left = 8
              Top = 190
              Width = 269
              Height = 97
              Anchors = [akLeft, akTop, akRight]
              Caption = ' Magnification '
              Color = clWhite
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -12
              Font.Name = 'Tahoma'
              Font.Style = [fsBold]
              ParentBackground = False
              ParentColor = False
              ParentFont = False
              TabOrder = 1
              DesignSize = (
                269
                97)
              object lblDisplayScreenMagnification: TLabel
                Left = 28
                Top = 56
                Width = 19
                Height = 13
                Caption = 'Size'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object slrDisplayMagnification: KSlider
                Left = 24
                Top = 75
                Width = 241
                Height = 16
                Cursor = crArrow
                ColorForeground = clBtnText
                ColorBackground = clWhite
                ColorShadow = clSilver
                ColorCursor = clBtnText
                ColorCursorShadow = clSilver
                Position = 2
                Min = 1
                Max = 32
                Flat = True
                OnChange = slrDisplayMagnificationChange
                Anchors = [akLeft, akTop, akRight]
                Enabled = False
                ExplicitWidth = 237
              end
              object lblAutoMagnification: TLabel
                Left = 28
                Top = 34
                Width = 199
                Height = 11
                Caption = 'Expands the image to fill the available workarea'
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -9
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object edtDisplayScreenMagnification: KSpinEdit
                Left = 200
                Top = 53
                Width = 60
                Height = 20
                Anchors = [akTop, akRight]
                BevelOuter = bvLowered
                Color = clWhite
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -13
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
                TabOrder = 1
                Value = 2
                Min = 1
                Max = 32
                OnChanged = edtDisplayScreenMagnificationChange
                DesignSize = (
                  60
                  20)
              end
              object chkAutoMagnification: TCheckBox
                Left = 12
                Top = 16
                Width = 169
                Height = 17
                Caption = 'Automatic Magnification'
                Checked = True
                Color = clWhite
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentColor = False
                ParentFont = False
                State = cbChecked
                TabOrder = 0
                OnClick = chkAutoMagnificationClick
              end
            end
            object grpMasking: TGroupBox
              Left = 8
              Top = 528
              Width = 269
              Height = 91
              Anchors = [akLeft, akTop, akRight]
              Caption = ' Masking '
              Color = clWhite
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -12
              Font.Name = 'Tahoma'
              Font.Style = [fsBold]
              ParentBackground = False
              ParentColor = False
              ParentFont = False
              TabOrder = 2
              DesignSize = (
                269
                91)
              object lblMaskTransparency: TLabel
                Left = 16
                Top = 20
                Width = 93
                Height = 13
                Caption = 'Mask Transparency'
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object slrMaskTransparency: KSlider
                Left = 10
                Top = 39
                Width = 255
                Height = 16
                Cursor = crArrow
                ColorForeground = clBtnText
                ColorBackground = clWhite
                ColorShadow = clSilver
                ColorCursor = clBtnText
                ColorCursorShadow = clSilver
                Position = 75
                Min = 5
                Max = 100
                Flat = True
                OnChange = slrMaskTransparencyChange
                Anchors = [akLeft, akTop, akRight]
                ExplicitWidth = 251
              end
              object lblMaskColor: TLabel
                Left = 16
                Top = 68
                Width = 121
                Height = 13
                Caption = 'Mask Transparency Color'
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object edtMaskTransparency: KSpinEdit
                Left = 200
                Top = 17
                Width = 60
                Height = 20
                Anchors = [akTop, akRight]
                BevelOuter = bvLowered
                Color = clWhite
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -13
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
                TabOrder = 1
                Value = 75
                Min = 5
                OnChanged = edtMaskTransparencyChange
                DesignSize = (
                  60
                  20)
              end
              object panMaskColor: TPanel
                Left = 152
                Top = 64
                Width = 105
                Height = 21
                Anchors = [akLeft, akTop, akRight]
                BevelOuter = bvLowered
                Color = clRed
                ParentBackground = False
                TabOrder = 0
                OnClick = panMaskColorClick
              end
            end
            object grpImageWindow: TGroupBox
              Left = 8
              Top = 4
              Width = 269
              Height = 65
              Anchors = [akLeft, akTop, akRight]
              Caption = ' Image Window '
              Color = clWhite
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -12
              Font.Name = 'Tahoma'
              Font.Style = [fsBold]
              ParentBackground = False
              ParentColor = False
              ParentFont = False
              TabOrder = 3
              DesignSize = (
                269
                65)
              object lblEditorBackgroundColor: TLabel
                Left = 28
                Top = 40
                Width = 84
                Height = 13
                Caption = 'Background Color'
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object chkCenterImage: TCheckBox
                Left = 12
                Top = 16
                Width = 205
                Height = 17
                Caption = 'Center the Image in the Editor'
                Color = clWhite
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentColor = False
                ParentFont = False
                TabOrder = 0
                OnClick = chkCenterImageClick
              end
              object panBackgroundColor: TPanel
                Left = 152
                Top = 36
                Width = 105
                Height = 21
                Anchors = [akLeft, akTop, akRight]
                BevelOuter = bvLowered
                Color = clWhite
                ParentBackground = False
                TabOrder = 1
                OnClick = panBackgroundColorClick
              end
            end
            object cmdRestoreDefaults: TButton
              Left = 149
              Top = 625
              Width = 128
              Height = 32
              Hint = 
                'Apply Map Changes|Applies the changes made to the properties of ' +
                'the map.'
              Anchors = [akTop, akRight]
              Caption = 'Restore Defaults'
              ParentShowHint = False
              ShowHint = True
              TabOrder = 4
              OnClick = cmdRestoreDefaultsClick
            end
            object grpModeScaleAdjust: TGroupBox
              Left = 8
              Top = 293
              Width = 269
              Height = 229
              Anchors = [akLeft, akTop, akRight]
              Caption = ' Mode Scale Adjust '
              Color = clWhite
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -12
              Font.Name = 'Tahoma'
              Font.Style = [fsBold]
              ParentBackground = False
              ParentColor = False
              ParentFont = False
              TabOrder = 5
              DesignSize = (
                269
                229)
              object lblCustomX25: TLabel
                Left = 30
                Top = 138
                Width = 23
                Height = 13
                Caption = '25%'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object slrCustomXScale: KSlider
                Left = 32
                Top = 155
                Width = 212
                Height = 16
                Cursor = crArrow
                ColorForeground = clBtnText
                ColorBackground = clWhite
                ColorShadow = clSilver
                ColorCursor = clBtnText
                ColorCursorShadow = clSilver
                Position = 2
                Max = 3
                Flat = True
                OnChange = radModeScaleDefaultClick
                Anchors = [akLeft, akTop, akRight]
                Enabled = False
                ExplicitWidth = 208
              end
              object lblCustomX50: TLabel
                Left = 96
                Top = 138
                Width = 23
                Height = 13
                Caption = '50%'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblCustomX100: TLabel
                Left = 157
                Top = 138
                Width = 29
                Height = 13
                Caption = '100%'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblCustomX200: TLabel
                Left = 227
                Top = 138
                Width = 29
                Height = 13
                Alignment = taRightJustify
                Anchors = [akTop, akRight]
                Caption = '200%'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
                ExplicitLeft = 223
              end
              object lblCustomXAxis: TLabel
                Left = 28
                Top = 116
                Width = 91
                Height = 13
                Caption = 'X Axis Scale Factor'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblCustomY25: TLabel
                Left = 30
                Top = 194
                Width = 23
                Height = 13
                Caption = '25%'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object slrCustomYScale: KSlider
                Left = 32
                Top = 211
                Width = 212
                Height = 16
                Cursor = crArrow
                ColorForeground = clBtnText
                ColorBackground = clWhite
                ColorShadow = clSilver
                ColorCursor = clBtnText
                ColorCursorShadow = clSilver
                Position = 2
                Max = 3
                Flat = True
                OnChange = radModeScaleDefaultClick
                Anchors = [akLeft, akTop, akRight]
                Enabled = False
                ExplicitWidth = 208
              end
              object lblCustomY50: TLabel
                Left = 96
                Top = 194
                Width = 23
                Height = 13
                Caption = '50%'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblCustomY100: TLabel
                Left = 157
                Top = 194
                Width = 29
                Height = 13
                Caption = '100%'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblCustomY200: TLabel
                Left = 227
                Top = 194
                Width = 29
                Height = 13
                Alignment = taRightJustify
                Anchors = [akTop, akRight]
                Caption = '200%'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
                ExplicitLeft = 223
              end
              object lblCustomYAxis: TLabel
                Left = 28
                Top = 172
                Width = 109
                Height = 16
                Caption = 'Y Axis Scale Factor'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -13
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblModeScaleDescription: TLabel
                Left = 12
                Top = 17
                Width = 254
                Height = 35
                Anchors = [akLeft, akTop, akRight]
                AutoSize = False
                Caption = 
                  'This setting compensates for machines that have "fat" pixels in ' +
                  'certain graphic modes.'
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
                WordWrap = True
                ExplicitWidth = 250
              end
              object radModeScaleDefault: TRadioButton
                Left = 12
                Top = 52
                Width = 213
                Height = 17
                Caption = 'Use Mode'#39's Default Scale Factor'
                Checked = True
                Color = clWhite
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentColor = False
                ParentFont = False
                TabOrder = 0
                TabStop = True
                OnClick = radModeScaleDefaultClick
              end
              object radModeScaleCustom: TRadioButton
                Left = 12
                Top = 92
                Width = 205
                Height = 17
                Caption = 'Use a Custom Scale Factor'
                Color = clWhite
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentColor = False
                ParentFont = False
                TabOrder = 1
                OnClick = radModeScaleDefaultClick
              end
              object radModeScaleRemove: TRadioButton
                Left = 12
                Top = 72
                Width = 237
                Height = 17
                Caption = 'Remove Default Scale Factor Effect'
                Color = clWhite
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentColor = False
                ParentFont = False
                TabOrder = 2
                OnClick = radModeScaleDefaultClick
              end
            end
          end
        end
      end
    end
  end
  object panContainer: TPanel
    Left = 0
    Top = 0
    Width = 766
    Height = 737
    Align = alClient
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 1
    object sbxEditor: TScrollBox
      Left = 0
      Top = 68
      Width = 766
      Height = 586
      HorzScrollBar.Smooth = True
      HorzScrollBar.Style = ssFlat
      HorzScrollBar.Tracking = True
      VertScrollBar.Smooth = True
      VertScrollBar.Style = ssFlat
      VertScrollBar.Tracking = True
      Align = alClient
      BevelInner = bvNone
      BevelOuter = bvNone
      BevelKind = bkFlat
      Color = clWhite
      ParentColor = False
      TabOrder = 0
      OnMouseMove = sbxEditorMouseMove
      OnResize = sbxEditorResize
      object imgCanvas: TImage
        Left = 0
        Top = 0
        Width = 0
        Height = 0
        OnMouseDown = imgCanvasMouseDown
        OnMouseMove = imgCanvasMouseMove
        OnMouseUp = imgCanvasMouseUp
      end
      object imgLargeIcon: TImage
        Left = 8
        Top = 16
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
          8461428461428461428461420000000000000000000000000000000000000000
          0000000084614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614200000042345A21
          247318209418209418209418208C212463312842000000846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461420000003134940828D60830E71038EF103CEF1038EF0834EF0828
          E71024C6292C6B00000084614284614284614284614284614284614284614284
          6142846142846142846142846142846142000000000000000000000000000000
          0000000000008461428461428461428461428461428461428461428461428461
          428461428461428461428461428461428461428461420000001024C62941DE6B
          7DE7737DE76B7DE76B7DE77382E75269E71028D6293094000000846142846142
          8461428461428461428461428461428461428461428461428461428461420000
          00394952105D941075BD1075BD10619C10517B293C4A00000084614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          846142846142846142000000423C8C9492CEADAEDEBDBAE7B5B2E7A5A6D66B65
          B539307B00000084614284614284614284614284614284614284614284614284
          614284614284614284614200000018557B2186CE2996DE2992DE2992DE218AD6
          1886D61079C6104D7B0000008461428461428461428461428461428461428461
          4200000000000000000000000084614284614284614284614284614200000000
          00006B51528C756373595A000000000000000000846142846142846142846142
          84614200000000000000000000000084614284614200000000000010659C319A
          DE319EE7319ADE39A2E7399EE7319ADE2992DE218ED6107DCE18456B00000084
          61428461428461428461420000000000006345297B3410732C10000000000000
          0000000000008461428461428461428461420000000000000000008461428461
          42846142846142846142846142846142000000314D5A105D9410558C21415200
          000000000029455A2182C642AAEF39A6E739A6E74AB2EF4AB2EF42AAEF39A6E7
          399EE7319ADE2992DE105D940000008461428461428461420000006349316B34
          189C2C08BD4518CE5529B54110A53008842C086B2C1000000000000000000000
          0000846142846142846142846142846142846142846142846142846142000000
          21516B1882CE2992DE218ED6187DCE0865AD105994399EDE52B6F742AEEF4AB2
          EF52BAF752B6F74AB2EF42AEEF42AAEF42A6E7319EE7218ED621598400000084
          6142846142000000734121943008B53408CE4518DE5D39EF795AEF7952E76539
          D65931C64D21B53C109C30087B2808632C100000000000000000000000008461
          4284614284614284614200000018659C2992D639A2E72996DE218ED6218ED621
          8ED6319ADE5AC3F752B6F75ABEF75AC3FF52BEF752BAF752BAF74AB6F739A2E7
          2182C621659C39596B0000008461428461420000008C4521AD3408C64118D64D
          29DE4D29DE5D39EF714AF7967BFFC3ADF79E84F78663EF7952DE6539D65931BD
          4518AD3408942C087328085A2C10000000000000000000000000086DD6188EF7
          42AEEF399EE7319ADE2992DE2996DE3196DE2992DE52B6F763CBFF63CBFF5AC3
          FF5AC3F752BEF742A6E72175B531597B00000000000000000084614284614284
          61420000009C3810CE4521DE5129DE5129D65129DE5D39EF6D4AF7A284FFFBF7
          FFF3E7FFE7D6FFCFBDFFBA9CF79A7BF78663EF7552DE6539CE5531BD4118A534
          08842C087328085234290059D6087DF742AAEF39A6E7319EE72996DE39A6E739
          A6E7319EE739A2E742AEEF52BAF763C7FF63CBFF39A2DE18496B000000000000
          8461428461428461428461428461428461420000009C3C10CE4921DE5131D651
          29D65129DE5D39E76D42F79E84FFF7EFFFF3E7FFF3E7FFF3E7FFF3E7FFEFDEFF
          DFCEFFCFB5FFB694F79673F78663E7714AE76942B54521214D840069E70079FF
          39A6EF42AAE7399EE742AAEF52BAF74AB2EF42AEEF39A6E7399EE7319EDE39A6
          E742A6E7298ED618496B00000084614284614284614284614284614284614284
          61420000009C3C10CE4921DE5531DE5531DE5531DE5D39E76942F79E84FFF7EF
          FFF3EFFFF3E7FFEFE7FFEFE7FFEFDEFFF3DEF7E7DEE7D3D6FFEFD6FFD7BDFFCB
          A5E796734A3029183852007DFF008EFF299EF74AAEEF42AAE75AC3F763C7FF5A
          C7FF5ABEF752B6F74AB2EF42AAEF39A6E7319EE7319EDE185173000000846142
          8461428461428461428461428461428461420000009C3C10CE4921DE5531DE55
          31DE5931DE6139E76942EF9E84FFFBF7FFF7EFFFF3E7FFF3E7FFF3E7FFEFE7FF
          F3DE6361B5101CAD8475BDFFF7DEDED3D6423C6B292421313039009EFF00BAFF
          109AFF4AAEEF4AB2EF52BAF752BEF75AC3FF5AC7FF63C7FF5AC3FF52BEF74AB6
          EF4AB2EF399EE7294D6300000084614284614284614284614284614284614284
          61420000009C3C10CE4D29DE5931DE5931DE5939DE6139E76542EF9E84FFFBF7
          FFF7EFFFF3EFFFF3EFFFF3E7FFF7E7E7D3D61824B51028CE101CBD7B71B53938
          AD21185A393031422C2900BEFF00E7FF00C7FF1096F72996EF42A2EF4AAEEF52
          B6EF52BAF75ABEF75AC3F763C7FF63CBFF5AC3FF1871B5000000846142846142
          8461428461428461428461428461428461420000009C3C10CE4D29DE5D39DE5D
          39DE5D39DE6542E76542EF9E84FFFBF7FFF7F7FFF7EFFFF7EFFFF3EFFFFBEFD6
          CBD6101CB5182CC6182CC6101CBD21187B4234314234394A303100D7FF00FFFF
          00FBFF00DFFF00BEFF08A2FF1896F7299AEF42AAEF4AB2EF52B6EF52BEF74AB6
          F72171AD00000084614284614284614284614284614284614284614284614284
          61420000009C3C10CE5129DE6139DE6139DE6139E76542E76139EF9E84FFFFFF
          FFFBF7FFF7EFFFF7EFFFF7EFFFFBEFD6CBDE1020B5182CC6182CC6182CCE2120
          8C4230424A3839523839089AEF00E3FF00E7FF00E3FF00DBFF00CBFF00B6FF00
          9EFF088EFF1896F731A2EF2996DE18558C000000846142846142846142846142
          8461428461428461428461428461428461420000009C3C10CE5529DE6542DE65
          42DE6942E76942E76139EF9A84FFFFFFFFFBF7FFFBF7FFF7F7FFF7EFFFFFEFDE
          CFDE1020B5182CC6182CC6182CC61828C6181CAD42305A5A414252496329558C
          0879CE08A6FF00BAFF00BAFF00B6FF00AAFF009AFF008AFF0086FF635D7B732C
          1800000084614284614284614284614284614284614284614284614284614284
          61420000009C3C10CE5531E76942DE6942DE6D4AE76942E75D39EF9A84FFFFFF
          FFFBF7FFFBF7FFFBF7FFF7F7FFFFF7B5AAD61020BD182CCE182CCE1830D61030
          DE102CDE392C7B6345425A41423124215A3C4231385229558C1079D6008EF700
          9AFF008EFF108AFFAD8EA5E769397B2808000000846142846142846142846142
          8461428461428461428461428461428461420000009C3C10D65931E76D4AE76D
          4AE7714AE76D4AE75D39EF9A84FFFFFFFFFBFFFFFBF7FFFBF7FFFBF7FFFFF79C
          96CE0820C61030DE1034E70834EF0834F7082CEF42307373514A42343963454A
          5238424A3431734942312829524D6B395D9C2179D6D6CFCEFF9E6BD665397B28
          0800000084614284614284614284614284614284614284614284614284614284
          61420000009C3C10D65D31E7714AE7714AE77552E7714AE75931EF9A84FFFFFF
          FFFFFFFFFBF7FFFBF7FFFBF7FFFFF7A59ED60824DE0838F70838FF083CFF1041
          FF103CF7312C8C633C5A7B5152734D525A41427B555A423439735152844D5252
          3C39D6BAA5FFE7C6FF9A73D665397B2808000000846142846142846142846142
          8461428461428461428461428461428461420000009C3C10D66139E77552E775
          52E77952E7714ADE5931EF9A84FFFFFFFFFFFFFFFFFFFFFBFFFFFBF7FFFFFFD6
          C7DE0020D61045FF1849FF2151FF2955FF315DFF294DF72145E77B5163945D5A
          9461637B515284595A84555A4A4142D6C3ADFFEBD6FFDFC6FF9673D661397B28
          0800000084614284614284614284614284614284614284614284614284614284
          61420000009C3C10D66942E7825AE7825AEF8663E77952DE5531EF967BFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFBFFFFFFFFB5AED62138CE4A75FF6382FF6386
          FF6B86FF6B86FF6386FF3934A5313CC62145E739289C392C9CD6C7C6FFF7DEFF
          E7D6FFE7D6FFE3CEF79673D661397B2808000000846142846142846142846142
          8461428461428461428461428461428461420000009C3C10D66942EF8663EF86
          63EF8E63E77D5ADE5529EF967BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFADAAD63945C65A71EF84A2FF8CA2FF849EFF7B96FF637DFF5279FF
          3965FF2938C6D6C7D6FFFBE7FFEBDEFFEBD6FFE7D6FFE7D6F79273D65D397B28
          0800000084614284614284614284614284614284614284614284614284614284
          61420000009C3C10D66D4AEF8E63EF8E63EF926BE7825ADE5129EF967BFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE7DBE77B7DC65A61
          CE8496EFA5BAFF9CB2FF7B9AFF6B8EFF313CCEBDAECEFFFFE7FFEFE7FFEFDEFF
          EBDEFFEBDEFFEBD6F79273D65D317B2C08000000846142846142846142846142
          8461428461428461428461428461428461420000009C3C10DE714AEF926BEF92
          6BEF9A73E7865ADE5129EF967BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFDED3E7847DC66B6DCE8492E7849AF73949CE
          948EC6FFFFEFFFF3E7FFEFE7FFEFE7FFEFDEFFEBDEFFEBDEF79273D65D317B2C
          0800000084614284614284614284614284614284614284614284614284614284
          61420000009C3810DE7952EF9A73EF9A73EF9E7BEF8663DE5531DE694AEFA694
          F7D7CEFFF7F7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBFFFFFF
          FFFFFFFFDED7E7A5A2D67B79C6B5AED6FFF7EFFFF7EFFFF3EFFFF3E7FFF3E7FF
          EFE7FFEFDEFFEFDEF7926BD65D317B2C08000000846142846142846142846142
          8461428461428461428461428461428461420000009C3810DE7D52F79E7BEF9E
          7BF7A684EF8A63DE5531DE5531DE4D29DE5531E76D4AE78A73F7B6A5FFDFD6FF
          FBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBFFFFFFFFFFFFFFFFFFF7FFFFF7
          FFF7EFFFF7EFFFF7EFFFF3EFFFF3E7FFF3E7FFEFE7FFEFE7F78E6BD659317B2C
          0800000084614284614284614284614284614284614284614284614284614284
          61420000009C3810DE825AF7A684F7A684F7AE84EF8E6BDE5131DE5531DE5531
          DE5531DE5531DE5529DE5129DE5D39E77152EF9A84F7CBBDFFE7DEFFFFFFFFFF
          FFFFFFFFFFFFFFFFFBF7FFFBF7FFFBF7FFF7F7FFF7EFFFF7EFFFF7EFFFF3EFFF
          F3EFFFF3E7FFF3E7F78E6BD659317B2C08000000846142846142846142846142
          8461428461428461428461428461428461420000009C3810DE865AF7AE84F7AE
          84F7B68CEF926BDE5129DE5531DE5531DE5531DE5931DE5931DE5931DE5931DE
          5931DE5531DE5531E76542E77D63EFA694F7D3C6FFEFE7FFFFFFFFFFFFFFFBF7
          FFFBF7FFF7F7FFF7F7FFF7EFFFF7EFFFF3EFFFF3EFFFF3E7F78E6BD659317B2C
          0800000084614284614284614284614284614284614284614284614284614284
          61420000009C3810DE8A63F7B28CF7B28CFFBA94EF9673D64D29DE5129DE5531
          DE5531DE5531DE5931DE5931DE5931DE5939DE5D39DE5D39DE5D39DE5931DE59
          31DE5D31E76D4AEF866BFFD7CEFFF3EFFFFFFFFFFFFFFFFFFFFFFBF7FFF7EFFF
          F7EFFFF7EFFFF3EFF78A6BD659317B2C08000000846142846142846142846142
          8461428461428461428461428461428461420000009C3810E7926BFFBA94FFBA
          94FFC39CF7B68CDE5129D64D29DE5129DE5131DE5531DE5531DE5531DE5931DE
          5931DE5939DE5D39DE5D39DE5D39DE6139E76139E75D39E75D39E76542E77552
          EF9E84F7C3B5FFDFD6FFF7F7FFFFFFFFFFFFFFFBF7FFF7EFF78A6BD655317B2C
          0800000084614284614284614284614284614284614284614284614284614284
          61420000009C3810E7966BFFC39CFFC39CFFC79CFFD3ADEF8E6BD64521D64D29
          DE5129DE5131DE5531DE5531DE5531DE5931DE5931DE5931DE5D39DE5D39DE5D
          39DE6139E76139E76139E76139E76139E76139E75D39E7694AEF8263F7A694F7
          C7B5FFE3D6FFFBF7EF8A6BD655297B2C08000000846142846142846142846142
          8461428461428461428461428461428461420000009C3810DE926BFFCFA5FFCB
          A5FFCFA5FFD3ADFFD3ADEF8A63D64D29D64929D64921D64D29DE5131DE5531DE
          5531DE5931DE5931DE5931DE5939DE5D39DE5D39DE5D39DE6139E76142E76542
          E76542E76542E76542E76542E76139E76539E77152EF8E73EF7D5AD655317B2C
          0800000084614284614284614284614284614284614284614284614284614284
          6142000000944518C66139FFD3ADFFD3ADFFCFADFFCFA5FFCFA5FFCFADFFBA94
          EF9A73E77952DE6542DE5129D64D29DE4D29DE5531DE5531DE5931DE5931DE59
          39DE5D39DE5D39DE5D39E76139E76139E76542E76542E76542E76942E76942E7
          6942E76942E76542EF714AD655317B2C08000000846142846142846142846142
          846142846142846142846142846142846142846142000000A53008DE8E63FFDB
          B5FFD7ADFFD3ADFFCBA5FFCBA5FFCFA5FFCFA5FFCFA5FFC39CF7AA84EF8E6BE7
          7552DE6139DE5531DE5129DE5531DE5931DE5931DE5D39DE5D39DE6139E76139
          E76139E76142E76542E76542E76542E76942E76942E7694AEF714ACE55317B2C
          0800000084614284614284614284614284614284614284614284614284614284
          6142846142846142000000A53408CE6942E79A73F7B68CFFCBA5FFCFADFFCFA5
          FFC7A5FFC39CFFC39CFFC39CFFC39CFFBE94FFB28CF79A73EF825AE76D4ADE5D
          39DE5531DE5531DE5931DE5D39DE5D39E76139E76139E76142E76542E76542E7
          6542E76942E76942EF6D4ACE55317B2C08000000846142846142846142846142
          8461428461428461428461428461428461428461428461428461420000009445
          21943810AD3810BD4D21D67952E79A73F7B68CFFC39CFFC79CFFC39CFFBA94FF
          B694FFB68CFFB68CFFB68CFFAE84FF9E7BF78A63EF7552E76542DE5931DE5931
          DE5D39DE5D39E76139E76139E76542E76542E76542E76542EF6D4ACE55297B2C
          0800000084614284614284614284614284614284614284614284614284614284
          61428461428461428461428461420000000000000000008C51299441189C3410
          AD3810BD5529DE7D52EF966BFFAE8CFFB694FFB694FFAE8CFFAA84FFA684FFA6
          84FFA67BFFA27BFF9A73EF7952E76D4AE76139DE5D39DE5D39DE6139E76139E7
          6542E76542E76542EF694ACE4D297B3010000000846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          428461428461420000000000000000000000008C4929943C18A53408B54110CE
          5D31DE7952EF926BFFA27BFFA684FFA27BFF9E7BFF9673FF9673F78E6BF78A63
          EF7D5AEF7552E76942E76542E76139E76139E76542E76542DE5D39B53810733C
          2100000084614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461420000000000000000008455318C4521943C10A53408BD4518CE6139DE75
          4AEF8663FF926BFF926BF7825AEF7D5AEF7952EF7152E76D4AE76942E76139E7
          6139DE5D39CE4D21AD3408843C18000000846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614200000000
          00000000000000008451318C45189C3810AD3408BD4918CE5931E77552EF7552
          EF714AE7694AE76542E76139DE5939CE4921B534089434087B49290000008461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461420000000000000000
          000000008C4D29944118AD3808BD4518CE4D29D65531DE5931D65129BD3C109C
          3008844521000000000000846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          61428461428461428461428461428461428461420000000000000000008C4D29
          943C18A53408AD3408A534088C41180000000000007B61428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614200000000000000000000000000000000000084
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142846142846142846142846142846142846142846142846142846142846142
          8461428461428461428461428461428461428461428461428461428461428461
          4284614284614284614284614284614284614284614284614284614284614284
          6142}
        Visible = False
      end
      object imgSmallIcon: TImage
        Left = 4
        Top = 76
        Width = 16
        Height = 16
        AutoSize = True
        Picture.Data = {
          07544269746D617036030000424D360300000000000036000000280000001000
          000010000000010018000000000000030000130B0000130B0000000000000000
          0000FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
          FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
          FFFF00FF5A4129523C29523C29523C29FF00FFFF00FFFF00FFFF00FFFF00FFFF
          00FFFF00FFFF00FFFF00FFFF00FFFF00FF312CAD2920C62920C62924B531248C
          31285A423021FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF4238
          73422CC65234C62920EF2920EF2920F72920EF2924B54A3439FF00FFFF00FFFF
          00FFFF00FFFF00FFFF00FFFF00FF3930317B5963A575949C5D845A41A52920E7
          2920EF2920EF42309CFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF84B2
          BD5AD7EF18D7F7738E9C7B494A5238523128945A4539FF00FFFF00FFFF00FFFF
          00FFFF00FFFF00FFFF00FF4A717B84DFFF4ABEEF10C3F75AEBFF7B8A9C4A3031
          423039FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF39759C319E
          E72992DE218ED65AC7EFB5FBFF3971844A3821FF00FFFF00FFFF00FFFF00FFFF
          00FFFF00FFFF00FFFF00FF4AA2D652BAF739A6E7218AD6298AD663C7F7319AB5
          5A4529FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF526D7B52B6
          EF4AB6F739A2E7218AD6218ED6315973634D31FF00FFFF00FFFF00FFFF00FFFF
          00FFFF00FFFF00FFFF00FFFF00FF2975AD298ED639A2E739A6E7218AD642494A
          FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF2992
          D61886CE218AD64AB2EF316D94FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
          00FFFF00FFFF00FFFF00FF42718C399EE7218AD62171AD425152FF00FFFF00FF
          FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF4A96C639A2
          E72992D6296184FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
          00FFFF00FFFF00FFFF00FF4A82A552B6F739A2E7426173FF00FFFF00FFFF00FF
          FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF5286
          A54286ADFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
          00FF}
        Visible = False
      end
      object panImageKeysPanel: TPanel
        Left = 8
        Top = 96
        Width = 336
        Height = 145
        BevelOuter = bvNone
        TabOrder = 0
        Visible = False
        object lblKeysImage: TLabel
          Left = 4
          Top = 4
          Width = 73
          Height = 13
          Caption = 'Image Editor'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Image1: TImage
          Left = 16
          Top = 116
          Width = 16
          Height = 16
          AutoSize = True
          Picture.Data = {
            07544269746D617036040000424D360400000000000036000000280000001000
            0000100000000100200000000000000400000000000000000000000000000000
            0000FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
            FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
            FF00848484008484840000000000848484008484840084848400848484008484
            840084848400848484008484840084848400000000008484840084848400FF00
            FF0084848400FF00FF0000000000FF00FF0084848400FF00FF0084848400FF00
            FF0084848400FF00FF0084848400FF00FF0000000000FF00FF0084848400FF00
            FF00000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000000000000000FF00
            FF0084848400FF00FF0000000000FF00FF0084848400FF00FF0084848400FF00
            FF0084848400FF00FF0084848400FF00FF0000000000FF00FF0084848400FF00
            FF00848484008484840000000000848484008484840084848400848484008484
            840084848400848484008484840084848400000000008484840084848400FF00
            FF0084848400FF00FF0000000000FF00FF0084848400FF00FF0084848400FF00
            FF0084848400FF00FF0084848400FF00FF0000000000FF00FF0084848400FF00
            FF00848484008484840000000000848484008484840084848400848484008484
            840084848400848484008484840084848400000000008484840084848400FF00
            FF0084848400FF00FF0000000000FF00FF0084848400FF00FF0084848400FF00
            FF0084848400FF00FF0084848400FF00FF0000000000FF00FF0084848400FF00
            FF00848484008484840000000000848484008484840084848400848484008484
            840084848400848484008484840084848400000000008484840084848400FF00
            FF0084848400FF00FF0000000000FF00FF0084848400FF00FF0084848400FF00
            FF0084848400FF00FF0084848400FF00FF0000000000FF00FF0084848400FF00
            FF00848484008484840000000000848484008484840084848400848484008484
            840084848400848484008484840084848400000000008484840084848400FF00
            FF0084848400FF00FF0000000000FF00FF0084848400FF00FF0084848400FF00
            FF0084848400FF00FF0084848400FF00FF0000000000FF00FF0084848400FF00
            FF00000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000000000000000FF00
            FF0084848400FF00FF0000000000FF00FF0084848400FF00FF0084848400FF00
            FF0084848400FF00FF0084848400FF00FF0000000000FF00FF0084848400FF00
            FF00848484008484840000000000848484008484840084848400848484008484
            840084848400848484008484840084848400000000008484840084848400FF00
            FF00}
          Transparent = True
        end
        object Label2: TLabel
          Left = 40
          Top = 24
          Width = 59
          Height = 13
          Caption = 'Ctrl+Shift+I'
        end
        object Label3: TLabel
          Left = 120
          Top = 24
          Width = 85
          Height = 13
          Caption = 'Zoom IN-to image'
        end
        object Image2: TImage
          Left = 16
          Top = 96
          Width = 16
          Height = 16
          AutoSize = True
          Picture.Data = {
            07544269746D617036040000424D360400000000000036000000280000001000
            0000100000000100200000000000000400000000000000000000000000000000
            0000FF00FF00FF00FF0000000000FF00FF00FF00FF00FF00FF00FF00FF00FF00
            FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF0000000000FF00FF00FF00
            FF00FF00FF00FF00FF0000000000FF00FF00FF00FF00FF00FF00FF00FF00FF00
            FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF0000000000FF00FF00FF00
            FF00000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000FF00FF00FF00FF0000000000FF00FF00FF00FF00FF00FF00FF00FF00FF00
            FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF0000000000FF00FF00FF00
            FF00FF00FF00FF00FF0000000000FF00FF00FF00FF00FF00FF00FF00FF00FF00
            FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF0000000000FF00FF00FF00
            FF00FF00FF00FF00FF0000000000FF00FF00FF00FF00FF00FF00FF00FF00FF00
            FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF0000000000FF00FF00FF00
            FF00FF00FF00FF00FF0000000000FF00FF00FF00FF00FF00FF00FF00FF00FF00
            FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF0000000000FF00FF00FF00
            FF00FF00FF00FF00FF0000000000FF00FF00FF00FF00FF00FF00FF00FF00FF00
            FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF0000000000FF00FF00FF00
            FF00FF00FF00FF00FF0000000000FF00FF00FF00FF00FF00FF00FF00FF00FF00
            FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF0000000000FF00FF00FF00
            FF00FF00FF00FF00FF0000000000FF00FF00FF00FF00FF00FF00FF00FF00FF00
            FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF0000000000FF00FF00FF00
            FF00FF00FF00FF00FF0000000000FF00FF00FF00FF00FF00FF00FF00FF00FF00
            FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF0000000000FF00FF00FF00
            FF00FF00FF00FF00FF0000000000FF00FF00FF00FF00FF00FF00FF00FF00FF00
            FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF0000000000FF00FF00FF00
            FF00FF00FF00FF00FF0000000000FF00FF00FF00FF00FF00FF00FF00FF00FF00
            FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF0000000000FF00FF00FF00
            FF00000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000FF00FF00FF00FF0000000000FF00FF00FF00FF00FF00FF00FF00FF00FF00
            FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF0000000000FF00FF00FF00
            FF00FF00FF00FF00FF0000000000FF00FF00FF00FF00FF00FF00FF00FF00FF00
            FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF0000000000FF00FF00FF00
            FF00}
          Transparent = True
        end
        object Label5: TLabel
          Left = 120
          Top = 60
          Width = 114
          Height = 13
          Caption = 'Zoom OUT-of the image'
        end
        object Label4: TLabel
          Left = 40
          Top = 60
          Width = 63
          Height = 13
          Caption = 'Ctrl+Shift+O'
        end
        object Label1: TLabel
          Left = 40
          Top = 96
          Width = 32
          Height = 13
          Caption = 'Ctrl+G'
        end
        object Label6: TLabel
          Left = 120
          Top = 96
          Width = 123
          Height = 13
          Caption = 'Toogle the Character grid'
        end
        object Label7: TLabel
          Left = 40
          Top = 116
          Width = 62
          Height = 13
          Caption = 'Ctrl+Shift+G'
        end
        object Label8: TLabel
          Left = 120
          Top = 116
          Width = 97
          Height = 13
          Caption = 'Toggle the Pixel grid'
        end
        object Label9: TLabel
          Left = 24
          Top = 76
          Width = 80
          Height = 13
          Caption = 'Mouse Wheel Up'
        end
        object Label10: TLabel
          Left = 8
          Top = 40
          Width = 94
          Height = 13
          Caption = 'Mouse Wheel Down'
        end
        object panImageKeysBar: TPanel
          Left = 0
          Top = 143
          Width = 336
          Height = 2
          Align = alBottom
          BevelOuter = bvNone
          Color = clBtnShadow
          TabOrder = 0
        end
      end
    end
    object panMapTiles: TPanel
      Left = 0
      Top = 0
      Width = 766
      Height = 32
      Align = alTop
      Caption = 'Image Editor'
      Color = 8675650
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clCream
      Font.Height = -17
      Font.Name = 'Octin Stencil Rg'
      Font.Style = [fsBold]
      ParentBackground = False
      ParentFont = False
      TabOrder = 1
      OnDblClick = cbrImageEditorDblClick
      object panTilesButtons: TPanel
        Left = 718
        Top = 1
        Width = 47
        Height = 30
        Align = alRight
        BevelOuter = bvNone
        Color = 8675650
        TabOrder = 0
        object cmdZoomOut: TBitBtn
          Tag = 1
          Left = 22
          Top = 5
          Width = 21
          Height = 21
          Hint = 
            'Zoom In|Zooms the image in so you can work on a smaller area in ' +
            'more detail.'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
          TabStop = False
          OnClick = actZoomInExecute
          Glyph.Data = {
            C6000000424DC6000000000000007600000028000000090000000A0000000100
            0400000000005000000000000000000000001000000010000000000000000000
            80000080000000808000800000008000800080800000C0C0C000808080000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDD000
            0000DDDDDDDDD0000000DDDD00DDD0000000DDDD00DDD0000000DD000000D000
            0000DD000000D0000000DDDD00DDD0000000DDDD00DDD0000000DDDDDDDDD000
            0000DDDDDDDDD0000000}
        end
        object cmdZoomIn: TBitBtn
          Tag = -1
          Left = 3
          Top = 5
          Width = 21
          Height = 21
          Hint = 
            'Zoom Out|Zooms the image out so you can work on a larger area of' +
            ' the image.'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
          TabStop = False
          OnClick = actZoomOutExecute
          Glyph.Data = {
            C6000000424DC6000000000000007600000028000000090000000A0000000100
            0400000000005000000000000000000000001000000010000000000000000000
            80000080000000808000800000008000800080800000C0C0C000808080000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDD000
            0000DDDDDDDDD0000000DDDDDDDDD0000000DDDDDDDDD0000000DD000000D000
            0000DD000000D0000000DDDDDDDDD0000000DDDDDDDDD0000000DDDDDDDDD000
            0000DDDDDDDDD0000000}
        end
      end
    end
    object panPaletteContainer: TPanel
      Left = 0
      Top = 654
      Width = 766
      Height = 83
      Align = alBottom
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 2
      object bvlBevel00: TBevel
        Left = 765
        Top = 0
        Width = 1
        Height = 83
        Align = alRight
        ExplicitLeft = 535
      end
    end
    object cbrImageEditor: TControlBar
      Left = 0
      Top = 32
      Width = 766
      Height = 36
      Align = alTop
      AutoSize = True
      BevelEdges = []
      Color = clWhite
      ParentBackground = False
      ParentColor = False
      RowSize = 36
      RowSnap = False
      TabOrder = 3
      OnDblClick = cbrImageEditorDblClick
      object tbrImageGridTools: TToolBar
        Left = 201
        Top = 2
        Width = 64
        Height = 29
        AutoSize = True
        ButtonHeight = 32
        ButtonWidth = 32
        Caption = 'Grid Tools'
        Constraints.MaxHeight = 32
        Constraints.MaxWidth = 64
        Constraints.MinHeight = 32
        Constraints.MinWidth = 64
        EdgeInner = esNone
        HotImages = imgIcons
        Images = imgIcons
        TabOrder = 0
        Wrapable = False
        object tbnGridCharacter: TToolButton
          Left = 0
          Top = 0
          Action = actToggleCharGrid
          AllowAllUp = True
          ParentShowHint = False
          ShowHint = True
          Style = tbsCheck
        end
        object tbnGridPixel: TToolButton
          Left = 32
          Top = 0
          Action = actTogglePixelGrid
          AllowAllUp = True
          ParentShowHint = False
          ShowHint = True
          Style = tbsCheck
        end
      end
      object tbrImagePaintTools: TToolBar
        Left = 11
        Top = 2
        Width = 32
        Height = 29
        AutoSize = True
        ButtonHeight = 32
        ButtonWidth = 32
        Caption = 'Paint Tools'
        Images = imgPaintToolBar
        TabOrder = 1
        Wrapable = False
        object tbnToolSelect: TToolButton
          Tag = 1
          Left = 0
          Top = 0
          Hint = 
            'Selection Mode (Shift - Character Block Select)|Select regions o' +
            'f the image to operate on. (Hold Shift to snap selection to Char' +
            'acter Block)'
          Grouped = True
          ImageIndex = 0
          ParentShowHint = False
          ShowHint = True
          Style = tbsCheck
          OnClick = tbnToolSelectClick
        end
      end
      object tbrPaletteAttributes: TToolBar
        Left = 355
        Top = 2
        Width = 64
        Height = 29
        AutoSize = True
        ButtonHeight = 32
        ButtonWidth = 32
        Caption = 'Attributes'
        Constraints.MaxHeight = 32
        Constraints.MaxWidth = 64
        Constraints.MinHeight = 32
        Constraints.MinWidth = 64
        Images = imgSpectrumIcons
        TabOrder = 2
        Wrapable = False
        object tbnPaletteShowAttributes: TToolButton
          Left = 0
          Top = 0
          Hint = 'Show Attributes|Show the image with color enabled.'
          Down = True
          Grouped = True
          ImageIndex = 0
          ParentShowHint = False
          ShowHint = True
          Style = tbsCheck
          OnClick = tbnPaletteShowAttributesClick
        end
        object tbnPaletteHideAttributes: TToolButton
          Left = 32
          Top = 0
          Hint = 'Hide Attributes|Show the image in monochrome. ie. Pixels only.'
          Caption = 'tbnPaletteHideAttributes'
          Enabled = False
          Grouped = True
          ImageIndex = 1
          ParentShowHint = False
          ShowHint = True
          Style = tbsCheck
          OnClick = tbnPaletteShowAttributesClick
        end
      end
      object tbrMaskTools: TToolBar
        Left = 434
        Top = 2
        Width = 144
        Height = 29
        AutoSize = True
        ButtonHeight = 32
        ButtonWidth = 32
        Caption = 'Mask Tools'
        Constraints.MaxHeight = 32
        Constraints.MaxWidth = 144
        Constraints.MinHeight = 32
        Constraints.MinWidth = 144
        Images = imgIcons
        TabOrder = 3
        object tbnMaskModeOff: TToolButton
          Left = 0
          Top = 0
          Action = actMaskModeOff
          Grouped = True
          ParentShowHint = False
          ShowHint = True
          Style = tbsCheck
        end
        object tbnMaskModeOn: TToolButton
          Left = 32
          Top = 0
          Action = actMaskModeOn
          Grouped = True
          ParentShowHint = False
          ShowHint = True
          Style = tbsCheck
        end
        object tbnSeparator01: TToolButton
          Left = 64
          Top = 0
          Width = 8
          Caption = 'tbnSeparator01'
          ImageIndex = 6
          Style = tbsSeparator
        end
        object tbnMaskGenerate: TToolButton
          Left = 72
          Top = 0
          Action = actMaskGenerate
          ParentShowHint = False
          ShowHint = True
        end
        object ToolButton1: TToolButton
          Left = 104
          Top = 0
          Width = 8
          Caption = 'ToolButton1'
          ImageIndex = 10
          Style = tbsSeparator
        end
        object tbnMaskInvert: TToolButton
          Left = 112
          Top = 0
          Action = actMaskInvert
          ParentShowHint = False
          ShowHint = True
        end
      end
      object tbnImageTools: TToolBar
        Left = 278
        Top = 2
        Width = 64
        Height = 29
        AutoSize = True
        ButtonHeight = 32
        ButtonWidth = 32
        Caption = 'Image Tools'
        Constraints.MaxHeight = 32
        Constraints.MaxWidth = 64
        Constraints.MinHeight = 32
        Constraints.MinWidth = 64
        Images = imgIcons
        TabOrder = 4
        object tbnImageResize: TToolButton
          Left = 0
          Top = 0
          Hint = 
            'Resize Image|Allow you to increase or decrease the size of an im' +
            'age'
          Caption = 'tbnImageResize'
          Enabled = False
          ImageIndex = 7
          ParentShowHint = False
          ShowHint = True
          OnClick = tbnImageResizeClick
        end
        object tbnImageChangePalette: TToolButton
          Left = 32
          Top = 0
          Hint = 'Change Palette|Allows you to change the palette of an image'
          Caption = 'tbnImageChangePalette'
          Enabled = False
          ImageIndex = 8
          ParentShowHint = False
          Wrap = True
          ShowHint = True
          OnClick = tbnImageChangePaletteClick
        end
      end
      object tbrAnimationTools: TToolBar
        Left = 595
        Top = 2
        Width = 64
        Height = 29
        AutoSize = True
        ButtonHeight = 32
        ButtonWidth = 32
        Caption = 'tbrAnimationTools'
        Constraints.MaxHeight = 32
        Constraints.MaxWidth = 64
        Constraints.MinHeight = 32
        Constraints.MinWidth = 64
        Images = imgIcons
        TabOrder = 5
        object tbnAnimationUnderlay: TToolButton
          Left = 0
          Top = 0
          Action = actToggleAnimationUnderlay
          AllowAllUp = True
          Caption = 'Toggle Previous Frame'
          Grouped = True
          ParentShowHint = False
          ShowHint = True
          Style = tbsCheck
        end
        object tbnShowHotSpot: TToolButton
          Left = 32
          Top = 0
          Action = actToggleHotSpot
          AllowAllUp = True
          Caption = 'Toggle Hot Spot'
          ParentShowHint = False
          ShowHint = True
          Style = tbsCheck
        end
      end
    end
  end
  object imgTabImages: TImageList
    Left = 180
    Top = 204
    Bitmap = {
      494C0101030004008C0010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000001000000001002000000000000010
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
      3000000000000000000000000000000000004A5A5A002963840029637B002942
      5200000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C0A89000FFF8F000FFF0E000F0E8
      E000F0E0D000F0D0C000F0C8B000E0C0A000E0B8A000E0B09000E0A890006048
      3000000000000000000000000000000000002984BD006BA5CE009CA5BD007B9C
      BD00428CBD0029739C0021526300000000000000000000000000000000000000
      00000000000000000000000000000000000084848400FFFFFF00C6C6C600FFFF
      FF00C6C6C600FFFFFF00C6C6C600FFFFFF00C6C6C600FFFFFF00C6C6C600FFFF
      FF00C6C6C600FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C0A8A000FFFFF000C0A8A000B0A0
      A000F0E8E000B0A09000B0989000B0989000B0989000B0989000E0B090006048
      300000000000000000000000000000000000298CCE0084A5C600EFDEDE00FFE7
      D600EFD6C600BDBDBD007B8C9C004A738C00316B8C0021526300000000000000
      00000000000000000000000000000000000084848400C6C6C600FFFFFF00C6C6
      C60000000000C6C6C600FFFFFF00C6C6C600FFFFFF00C6C6C600FFFFFF00C6C6
      C600FFFFFF00C6C6C60000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C0A8A000FFFFF000FFFFF000FFF8
      F000FFF0E000F0E8E000F0E0D000F0D0C000F0C8B000E0C0A000E0B8A0006048
      3000000000000000000000000000000000002984CE008CADC600EFDEE7008C8C
      E700ADADDE00F7D6CE00D6B59C00B59C8C00AD9C9400738CA50029526B000000
      00000000000000000000000000000000000084848400FFFFFF00C6C6C6000000
      00000000000000000000C6C6C600FFFFFF00C6C6C600FFFFFF00C6C6C600FFFF
      FF00C6C6C600FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C0A8A000FFFFF000B0A8A000B0A0
      A000FFF8F000B0A09000B0989000B0989000B0989000B0989000E0C0A0006048
      300000000000000000000000000000000000298CCE0084ADC600EFE7E7007B84
      EF009494EF00D6B5AD009C9C94009C9CA500E7AD9400B5A5A500296384000000
      00000000000000000000000000000000000084848400C6C6C600FFFFFF000000
      0000FFFFFF000000000000000000C6C6C600FFFFFF00C6C6C600FFFFFF00C6C6
      C600FFFFFF00C6C6C60000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C0B0A000FFFFF000FFFFF000FFFF
      F000FFFFF000FFF8F000FFF0E000F0E8E000F0E0D000F0D0C000F0C8B0006048
      300000000000000000000000000000000000298CCE0084A5CE00F7EFEF0094C6
      AD00BDCECE00E7D6DE009CADC600AD8C9400F7734A00BD6B5200395A6B000000
      00000000000000000000000000000000000084848400FFFFFF00C6C6C600FFFF
      FF00C6C6C600FFFFFF000000000000000000C6C6C600FFFFFF00C6C6C600FFFF
      FF00C6C6C600FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C0B0A000FFFFF000FFFFF000FFFF
      F000FFFFF000FFFFF000FFF8F000C0C8C00040607000F0E0D000F0D0C0006048
      300000000000000000000000000000000000298CCE0084A5CE00FFF7EF00ADEF
      A500ADE7A500E7DED600E7BDBD00EF9C7B00FF734A00D65A39008C4231000000
      00000000000000000000000000000000000084848400C6C6C600FFFFFF00C6C6
      C60000000000C6C6C600FFFFFF00C6C6C600FFFFFF00C6C6C600FFFFFF00C6C6
      C600FFFFFF00C6C6C60000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C0B0A000FFFFFF00E0E8F0006078
      8000E0E0E000FFFFF000C0C8D0005060700030A8D00020384000B0A0A0006048
      30000000000000000000A0A0750040805000298CCE007BA5C600F7F7F700D6F7
      D600B5E7BD00E7E7CE00FFDEC600FFBD9C00FFA57B00F77B5A00EF522100AD39
      10000000000000000000000000000000000084848400FFFFFF00C6C6C6000000
      00000000000000000000C6C6C600FFFFFF00C6C6C600FFFFFF00C6C6C600FFFF
      FF00C6C6C600FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000D0B0A000FFFFFF0090A8B00080D0
      E00050607000B0B8C0005060700060C0E0005060700030B8F000102830001030
      400010283000716763004078400050A86000298CCE007BA5CE00F7F7F700ADE7
      AD00B5E7BD00F7F7E700FFEFE700FFDEC600FFBD9C00FFA57B00F7845A00C673
      5A0063526B0000000000000000000000000084848400C6C6C600FFFFFF000000
      0000FFFFFF000000000000000000C6C6C600FFFFFF00C6C6C600FFFFFF00C6C6
      C600FFFFFF00C6C6C60000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000D0B8A000FFFFFF00E0E8F00090A8
      B00080E0F0005060700080D0E0005060700060D0F0004060700030B0E0002098
      D0002088B000205070005088600050B06000298CCE0084A5CE00FFF7F700A5E7
      AD009CE7AD00EFE7D600FFE7DE00FFDECE00FFD6B500FFC69400E7AD9C00848C
      D6002952F7002131A500000000000000000084848400FFFFFF00C6C6C600FFFF
      FF00C6C6C600FFFFFF000000000000000000C6C6C600FFFFFF00C6C6C600FFFF
      FF00C6C6C600FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000D0B8A000D0B8A000D0B8A000C0B0
      A00090A8B00080E0F0005060700080E0F0004058700060D0F00050C8F00040C0
      F00020B0E00020A0D0006098700050B87000298CD600739CCE00E7DEDE00FFEF
      F700C6DECE00DEE7D600FFEFE700FFE7DE00FFE7D600EFCEBD00ADADCE005A84
      FF002152FF000839FF002131A5000000000084848400C6C6C600FFFFFF00C6C6
      C600FFFFFF00C6C6C600FFFFFF00C6C6C600FFFFFF00C6C6C600FFFFFF00C6C6
      C600FFFFFF00C6C6C60000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000090A8B00080E0F0004058700080E0F00070D8F00060D0F00050C8
      F00040C0F00030B8F00070A8800060C080003984AD004A94D60094ADBD00CEC6
      C600DECED600D6D6D600DEE7E700F7F7F700FFF7EF00C6BDC6006384BD007384
      E7005273FF003952D60052527B00000000008484840000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000090A8B00080E0F00080E0F00080E0F00070D8F00060D0
      F00060B0D00080889000B0C0A00090D0A00000000000396B840039739C009CAD
      B500CEC6C600C6C6C600CECECE00D6D6D600DECEC6009CADB50031638C005A52
      7300737BBD006B526300000000000000000084848400FFFFFF00000000008400
      000084000000840000008400000084000000840000008400000084000000FFFF
      FF0084000000FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000090A8B00090A0B00090A0A0008098A0008090
      A00080889000B7A59A00A0B8A000B0C0A0000000000000000000000000000000
      00009C9C9400BDB5B500BDBDBD00C6C6C6009CADBD00528CB500395A73000000
      0000000000000000000000000000000000008484840084848400848484008484
      8400848484008484840084848400848484008484840084848400848484008484
      8400848484008484840084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009C8C7B00A594840073736B004A636B004A636B00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFFFFFF0000000F0FFF00010000
      000F01FF00010000000F003F00010000000F001F00010000000F001F00010000
      000F001F00010000000F001F00010000000C000F000100000000000700010000
      00000003000100000000000100010000F800000100010000FC00800300010000
      FE00F01F00010000FFFFF83FFFFF000000000000000000000000000000000000
      000000000000}
  end
  object imgIcons: TImageList
    Left = 148
    Top = 204
    Bitmap = {
      494C01010C000E008C0010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000004000000001002000000000000040
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
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000800000008000000080000000
      8000C0C0C000C0C0C000C0C0C000C0C0C000FF000000FF000000FF000000FF00
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080008080
      8000808080000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000800000008000000080000000
      8000C0C0C000C0C0C000C0C0C000C0C0C000FF000000FF000000FF000000FF00
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080008080
      8000808080000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000800000008000000080000000
      8000C0C0C000C0C0C000C0C0C000C0C0C000FF000000FF000000FF000000FF00
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080008080
      8000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF00000000000000
      0000000000000000000000000000000000000000800000008000000080000000
      8000C0C0C000C0C0C000C0C0C000C0C0C000FF000000FF000000FF000000FF00
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080008080
      8000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080008080
      8000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080008080
      8000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080008080
      8000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080008080
      8000808080000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080008080
      8000808080008080800000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080008080
      8000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080008080
      8000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000FF00000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000000FF
      000000FF000000FF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF000000FF000000
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FF000000FF000000FF000000FF
      0000FFFF0000FFFF0000FFFF0000FFFF00000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080008080
      8000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000FF000000FF
      00000000000000FF000000FF0000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF000000FF000000
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FF000000FF000000FF000000FF
      0000FFFF0000FFFF0000FFFF0000FFFF00000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000080808000808080008080
      8000808080000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000FF00000000
      0000000000000000000000FF000000FF00000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF000000FF000000
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FF000000FF000000FF000000FF
      0000FFFF0000FFFF0000FFFF0000FFFF00000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000080808000808080008080
      8000808080000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000FF000000FF000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF000000FF000000
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FF000000FF000000FF000000FF
      0000FFFF0000FFFF0000FFFF0000FFFF00000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080008080
      8000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF0000000000FFFFFF00FFFF
      FF00FFFFFF00000000000000000000000000000000000000000000000000FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00000000000000000000000000000000000000
      0000FFFFFF00000000000000000000000000FFFFFF00FFFFFF00000000000000
      0000008484000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00000000000000
      0000000000000084840000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF000000000000FFFF0000000000000000000000
      00000000000000000000FFFFFF0000000000FFFFFF0000000000FFFFFF000000
      0000000000000000000000848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00000000000000000000FFFF00000000000000
      00000000000000000000FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF000000
      000000000000000000000000000000FFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000000000FFFF0000FF
      FF00000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000FFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00000000000000000000848400000000000000
      000000FFFF0000FFFF0000000000000000000000000000000000000000000000
      00000000000000FFFF0000FFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C0C000C0C0C000C0C0
      C00000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF000000000000000000008484000000000000FF
      FF00000000000000000000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C0C000C0C0C000C0C0
      C00000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF000000000000000000008484000000000000FF
      FF0000FFFF0000FFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C0C000C0C0C000C0C0
      C000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008484000000
      000000FFFF0000FFFF0000FFFF000000000000FFFF0000FFFF0000FFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000084
      84000000000000FFFF000000000000FFFF0000FFFF0000FFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000008484000000000000FFFF0000FFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000000000000000000000000000000000000000
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
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840084848400000000008484
      8400848484008484840084848400848484008484840084848400848484008484
      8400000000008484840084848400000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840000000000000000000000
      0000848484000000000084848400000000008484840000000000848484000000
      0000000000000000000084848400000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00000000000000
      0000000000000000000000000000000000000000000084848400848484000000
      0000848484008484840000000000848484008484840000000000848484008484
      8400000000008484840084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840000000000000000000000
      0000848484000000000084848400000000008484840000000000848484000000
      0000000000000000000084848400000000000000000000000000000000000000
      0000FFFFFF000000000000000000FFFFFF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840084848400000000008484
      8400848484008484840084848400848484008484840084848400848484008484
      8400000000008484840084848400000000000000000000000000000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000084848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840000000000000000000000
      0000848484000000000084848400000000008484840000000000848484000000
      0000000000000000000084848400000000000000000000000000000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000084848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840084848400000000008484
      8400848484008484840084848400848484008484840084848400848484008484
      8400000000008484840084848400000000000000000000000000000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840000000000000000000000
      0000848484000000000084848400000000008484840000000000848484000000
      0000000000000000000084848400000000000000000000000000000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00000000000000
      0000000000000000000000000000000000000000000084848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840084848400000000008484
      8400848484008484840084848400848484008484840084848400848484008484
      8400000000008484840084848400000000000000000000000000000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000084848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840000000000000000000000
      0000848484000000000084848400000000008484840000000000848484000000
      0000000000000000000084848400000000000000000000000000000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840084848400000000008484
      8400848484008484840084848400848484008484840084848400848484008484
      8400000000008484840084848400000000000000000000000000000000000000
      0000FFFFFF00FFFFFF00FFFFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084848400848484000000
      0000848484008484840000000000848484008484840000000000848484008484
      8400000000008484840084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840000000000000000000000
      0000848484000000000084848400000000008484840000000000848484000000
      0000000000000000000084848400000000000000000000000000000000000000
      0000FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840000000000000000000000
      0000848484000000000084848400000000008484840000000000848484000000
      0000000000000000000084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840084848400000000008484
      8400848484008484840084848400848484008484840084848400848484008484
      840000000000848484008484840000000000424D3E000000000000003E000000
      2800000040000000400000000100010000000000000200000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007FFFC071FFFF0000FFFEC0E0FE1F
      0000FFFCCC44FE1F0000FFF8CE0FFE1FFE7FFFFCCF1FF003FC3FFFFECE3FF003
      F81FFFFFCC3FF003F00FFFFFC10FF003E007FFFFC007FE1FF81FFFFFCE2FF61F
      F81FFFFECF3FE21FF81FFFF8FFFFC1FF00007FF0CF3F80FF00003FE0861F887F
      00001FC0861F9C3F00000F00CF3FFE7F800080009FFCF000000100013FF9F000
      000300033FF3E000000700073FE7F000000300033FF3D000000100013FF9F000
      000000003FFCB000000000003FFCF000000000003FFC0000000000003FF80000
      000100013FF10000000700073FE70000800F800F9FCF00FBC01FC01FCF1F00EF
      E03FE03FE03F00BFF0FFF0FFF0FF00FFFF9FFFFFDFFBFFFFFF0FFFFFDFFB0001
      FF0FFFFF00005555EE1FFFFFDFFB0001E61F9249DFFB5555E03F2493DFFB0001
      E03FBFFDDFFB5555E0073FF9DFFB0001E00F7FFBDFFB5555E01FBFFDDFFB0001
      E03F3FF9DFFB5555E07F7FFBDFFB0001E0FF9249DFFB5555E1FF249300000001
      E3FFFFFFDFFB5555E7FFFFFFDFFB000100000000000000000000000000000000
      000000000000}
  end
  object actMain: TActionList
    Images = imgIcons
    Left = 84
    Top = 172
    object actZoomIn: TAction
      Caption = 'Zoom In'
      Hint = 
        'Zoom In|Zooms the image in so you can work on a smaller area in ' +
        'more detail.'
      ImageIndex = 3
      ShortCut = 24649
      OnExecute = actZoomInExecute
    end
    object actZoomOut: TAction
      Caption = 'Zoom Out'
      Hint = 
        'Zoom Out|Zooms the image out so you can work on a larger area of' +
        ' the image.'
      ImageIndex = 2
      ShortCut = 24655
      OnExecute = actZoomOutExecute
    end
    object actMaskModeOff: TAction
      Caption = 'Mask Mode Off'
      Checked = True
      GroupIndex = 7
      Hint = 'Mask Mode Off|Turns mask editing Off'
      ImageIndex = 4
      OnExecute = actMaskModeOffExecute
    end
    object actMaskModeOn: TAction
      Caption = 'Mask Mode On'
      Enabled = False
      GroupIndex = 7
      Hint = 'Mask Mode On|Turns mask editing On'
      ImageIndex = 5
      OnExecute = actMaskModeOnExecute
    end
    object actMaskGenerate: TAction
      Caption = 'Generate Mask'
      Enabled = False
      Hint = 'Generate Mask|Automatically generate a mask for the image'
      ImageIndex = 6
      OnExecute = actMaskGenerateExecute
    end
    object actMaskInvert: TAction
      Caption = 'actMaskInvert'
      Enabled = False
      Hint = 'Invert Mask|Toggles the mask bits'
      ImageIndex = 9
      OnExecute = actMaskInvertExecute
    end
    object actToggleCharGrid: TAction
      Caption = 'Toggle Character Grid'
      Hint = 'Toggle the Character Grid'
      ImageIndex = 2
      ShortCut = 16454
      OnExecute = actToggleCharGridExecute
    end
    object actTogglePixelGrid: TAction
      Caption = 'Toggle the Pixel Grid'
      Hint = 'Toggle ths Pixel Grid'
      ImageIndex = 3
      ShortCut = 24647
      OnExecute = actTogglePixelGridExecute
    end
    object actToggleAnimationUnderlay: TAction
      Caption = 'Toggle Animation Underlay'
      Hint = 
        'Toggle Animation Helper|Toggles the previous frame of a multi-fr' +
        'ame image to use as an animation helper'
      ImageIndex = 10
      OnExecute = actToggleAnimationUnderlayExecute
    end
    object actToggleHotSpot: TAction
      Caption = 'actToggleHotSpot'
      Hint = 'Toggle Hot Spot|Toggle the visibility of the Hot Spot of images'
      ImageIndex = 11
      OnExecute = actToggleHotSpotExecute
    end
  end
  object imgPaintToolBar: TImageList
    Left = 116
    Top = 204
    Bitmap = {
      494C0101010004008C0010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
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
      0000000000000000000000000000000000000000000084848400848484000000
      0000848484008484840000000000848484008484840000000000848484008484
      8400000000008484840084848400000000000000000000000000000000000000
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
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000084848400000000000000000000000000000000000000
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
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000084848400000000000000000000000000000000000000
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
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084848400848484000000
      0000848484008484840000000000848484008484840000000000848484008484
      8400000000008484840084848400000000000000000000000000000000000000
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
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF00FFFF000000000000FFFF000000000000
      FFFF000000000000FFFF00000000000092490000000000002493000000000000
      BFFD0000000000003FF90000000000007FFB000000000000BFFD000000000000
      3FF90000000000007FFB00000000000092490000000000002493000000000000
      FFFF000000000000FFFF00000000000000000000000000000000000000000000
      000000000000}
  end
  object imgSpectrumIcons: TImageList
    Left = 84
    Top = 204
    Bitmap = {
      494C0101020004008C0010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
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
      0000000000008484840000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000008484840000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000000FF
      FF00000000000000000000000000000000008484840000000000000000000000
      00000000000000000000000000000000000000000000000000000000000000FF
      FF00000000000000000000000000000000008484840000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000FFFF000084840000000000000000000000000084848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000FFFF000084840000000000000000000000000084848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000FFFF0000848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000FFFF0000848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000FFFF0000FFFF00008484000084840000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000FFFF0000FFFF00008484000084840000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000FFFF0000FFFF000084840000848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000FFFF0000FFFF000084840000848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000FFFF0000848400000000008484
      8400000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000FFFF0000848400000000008484
      8400000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00C6C6C6000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00C6C6C6000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000848400008484000084
      840084000000840000008400000000000000000000000000000000000000FFFF
      FF000000000000000000000000000000000000000000C6C6C600C6C6C600C6C6
      C60084848400848484008484840000000000000000000000000000000000FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000FFFF0000FFFF0000FFFF00FF00
      0000FF000000FF00000084000000000000000000000000000000000000000000
      0000000000000000FF000000840000000000FFFFFF00FFFFFF00FFFFFF000000
      0000000000000000000084848400000000000000000000000000000000000000
      0000000000000000FF0000008400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000FFFF0000FFFF0000FFFF00FF00
      0000FF000000FF00000084000000000000000000000000000000000000000000
      000000000000000084000000840000008400FFFFFF00FFFFFF00FFFFFF000000
      0000000000000000000084848400000000000000000000000000000000000000
      0000000000000000840000008400000084000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000FFFF0000FFFF0000FFFF00FF00
      0000FF000000FF00000000840000000000000000000000000000000000000000
      00000000000000000000000084000000FF00FFFFFF00FFFFFF00FFFFFF000000
      00000000000000000000C6C6C600000000000000000000000000000000000000
      00000000000000000000000084000000FF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF000000FF0000FF
      000000FF000000FF000000840000000000000000000000000000000000000000
      000000000000000000000000000000008400000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF00C6C6C600000000000000000000000000000000000000
      0000000000000000000000000000000084000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF000000FF0000FF
      000000FF000000FF000000840000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF00C6C6C600000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF000000FF0000FF
      000000FF000000FF000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFF0000000003FF03FF00000000
      C07FC07F00000000E03FE03F00000000F01FF01F00000000F01FF01F00000000
      F80FF80F00000000FC07FC0700000000FF01FF010000000081C081C000000000
      01E001E00000000001F001F00000000001F801F80000000001FC01FC00000000
      01FE01FE0000000003FF03FF0000000000000000000000000000000000000000
      000000000000}
  end
  object dlgColor: TColorDialog
    Color = clRed
    Options = [cdFullOpen, cdAnyColor]
    Left = 148
    Top = 172
  end
  object regScorpio: KRegistry
    Section = 'TommyGun'
    RootKey = rkHKEY_CURRENT_USER
    SoftwareKey = '\Software\Scorpio\'
    Left = 180
    Top = 172
  end
  object popImage: TPopupMenu
    Left = 116
    Top = 172
    object popToggleGridChar: TMenuItem
      Action = actToggleCharGrid
      ShortCut = 16455
      Visible = False
    end
    object popToggleGridPixel: TMenuItem
      Action = actTogglePixelGrid
      Visible = False
    end
    object popZoomIn: TMenuItem
      Action = actZoomIn
      Visible = False
    end
    object popZoomOut: TMenuItem
      Action = actZoomOut
      Visible = False
    end
  end
  object appEvents: TApplicationEvents
    OnMessage = appEventsMessage
    Left = 212
    Top = 172
  end
end
