object frmImageRotate: TfrmImageRotate
  Left = 407
  Top = 331
  ActiveControl = edtAngle
  Caption = 'Rotate Image'
  ClientHeight = 422
  ClientWidth = 556
  Color = clWhite
  Constraints.MinHeight = 455
  Constraints.MinWidth = 564
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnResize = FormResize
  DesignSize = (
    556
    422)
  PixelsPerInch = 96
  TextHeight = 13
  object grpAngleOfRotation: TGroupBox
    Left = 8
    Top = 8
    Width = 209
    Height = 97
    Caption = 'Angle of Rotation'
    TabOrder = 0
    object lblAngle: TLabel
      Left = 12
      Top = 20
      Width = 27
      Height = 13
      Caption = 'Angle'
    end
    object slrAngle: KSlider
      Left = 3
      Top = 39
      Width = 196
      Height = 16
      ColorBackground = clWhite
      ColorShadow = clSilver
      ColorCursorShadow = clSilver
      Max = 359
      EditBox = edtAngle
    end
    object lblSnapModulo: TLabel
      Left = 12
      Top = 56
      Width = 93
      Height = 13
      Caption = 'Angle Snap Modulo'
    end
    object lblSnappedAngle: TLabel
      Left = 12
      Top = 80
      Width = 73
      Height = 13
      Caption = 'Snapped Angle'
    end
    object lblSnappedAngleValue: TLabel
      Left = 132
      Top = 80
      Width = 6
      Height = 13
      Caption = '0'
    end
    object edtAngle: KSpinEdit
      Left = 132
      Top = 16
      Width = 64
      Height = 20
      BevelOuter = bvLowered
      Caption = '0'
      ParentColor = True
      TabOrder = 0
      Max = 359
      OnChanged = edtAngleChange
      DesignSize = (
        64
        20)
    end
    object edtAngleSnap: KSpinEdit
      Left = 132
      Top = 52
      Width = 64
      Height = 20
      BevelOuter = bvLowered
      Color = clWhite
      TabOrder = 1
      Value = 1
      Min = 1
      Max = 90
      DesignSize = (
        64
        20)
    end
  end
  object grpCentreOfRotation: TGroupBox
    Left = 8
    Top = 108
    Width = 209
    Height = 65
    Caption = 'Centre of Rotation'
    TabOrder = 1
    object lblXCoord: TLabel
      Left = 12
      Top = 20
      Width = 64
      Height = 13
      Caption = 'X Co-ordinate'
    end
    object lblYCoord: TLabel
      Left = 12
      Top = 48
      Width = 64
      Height = 13
      Caption = 'Y Co-ordinate'
    end
    object edtXCoord: KSpinEdit
      Left = 132
      Top = 16
      Width = 64
      Height = 20
      BevelOuter = bvLowered
      Color = clWhite
      TabOrder = 0
      DesignSize = (
        64
        20)
    end
    object edtYCoord: KSpinEdit
      Left = 132
      Top = 40
      Width = 64
      Height = 20
      BevelOuter = bvLowered
      Color = clWhite
      TabOrder = 1
      DesignSize = (
        64
        20)
    end
  end
  object grpPreviewOfRotation: TGroupBox
    Left = 240
    Top = 8
    Width = 308
    Height = 376
    Anchors = [akLeft, akTop, akRight, akBottom]
    Caption = 'Preview of Rotation'
    TabOrder = 2
    DesignSize = (
      308
      376)
    object lblPreviewNote: TLabel
      Left = 14
      Top = 316
      Width = 291
      Height = 17
      Anchors = [akLeft, akRight, akBottom]
      AutoSize = False
      Caption = 'Note: Left click and drag to rotate image.'
      Layout = tlBottom
      WordWrap = True
      ExplicitTop = 311
      ExplicitWidth = 328
    end
    object lblRightClick: TLabel
      Left = 14
      Top = 336
      Width = 221
      Height = 13
      Anchors = [akLeft, akBottom]
      Caption = 'Right click to move the centre of rotation point.'
      ExplicitTop = 331
    end
    object lblHoldShift: TLabel
      Left = 14
      Top = 352
      Width = 277
      Height = 13
      Anchors = [akLeft, akBottom]
      Caption = 'Hold SHIFT to reset the rotation to the centre of the image.'
      ExplicitTop = 347
    end
    object panPreview: TPanel
      Left = 8
      Top = 16
      Width = 292
      Height = 294
      Anchors = [akLeft, akTop, akRight, akBottom]
      BevelKind = bkTile
      BevelOuter = bvNone
      Color = clWhite
      TabOrder = 0
      object imgPreview: TImage
        Left = 1
        Top = 1
        Width = 280
        Height = 280
        Stretch = True
        OnMouseDown = imgPreviewMouseDown
        OnMouseMove = imgPreviewMouseMove
      end
      object imgCursorCenter: TImage
        Left = 60
        Top = 80
        Width = 32
        Height = 32
        AutoSize = True
        Picture.Data = {
          07544269746D617076020000424D760200000000000076000000280000002000
          000020000000010004000000000000020000120B0000120B0000100000001000
          000000000000000080000080000000808000800000008000800080800000C0C0
          C000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
          FF00DDDDDDDDDDDDD0000000DDDDDDDDDDDDDDDDDDDDDDDDD0FFFFF0DDDDDDDD
          DDDDDDDDDDDDDDDDD0F000F0DDDDDDDDDDDDDDDDDDDDDDDDD0F0D0F0DDDDDDDD
          DDDDDDDDDDDDDDDDD0F0D0F0DDDDDDDDDDDDDDDDDDDDDDDDD0F0D0F0DDDDDDDD
          DDDDDDDDDDDDDDDDD0F0D0F0DDDDDDDDDDDDDDDDDDDDDDDDD0F0D0F0DDDDDDDD
          DDDDDDDDDDDDDDDDD0F0D0F0DDDDDDDDDDDDDDDDDDDDDDDDD0F0D0F0DDDDDDDD
          DDDDDDDDDDDDDDDDD0F0D0F0DDDDDDDDDDDDDDDDDDDDDDDDD0F0D0F0DDDDDDDD
          DDDDD0000000000000F0D0F0000000000000D0FFFFFFFFFFFFF0D0FFFFFFFFFF
          FFF0D0F0000000000000D0000000000000F0D0F0DDDDDDDDDDDDDDDDDDDDDDDD
          D0F0D0F0000000000000D0000000000000F0D0FFFFFFFFFFFFF0D0FFFFFFFFFF
          FFF0D0000000000000F0D0F0000000000000DDDDDDDDDDDDD0F0D0F0DDDDDDDD
          DDDDDDDDDDDDDDDDD0F0D0F0DDDDDDDDDDDDDDDDDDDDDDDDD0F0D0F0DDDDDDDD
          DDDDDDDDDDDDDDDDD0F0D0F0DDDDDDDDDDDDDDDDDDDDDDDDD0F0D0F0DDDDDDDD
          DDDDDDDDDDDDDDDDD0F0D0F0DDDDDDDDDDDDDDDDDDDDDDDDD0F0D0F0DDDDDDDD
          DDDDDDDDDDDDDDDDD0F0D0F0DDDDDDDDDDDDDDDDDDDDDDDDD0F0D0F0DDDDDDDD
          DDDDDDDDDDDDDDDDD0F000F0DDDDDDDDDDDDDDDDDDDDDDDDD0FFFFF0DDDDDDDD
          DDDDDDDDDDDDDDDDD0000000DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
          DDDD}
        Transparent = True
        OnMouseDown = imgCursorCenterMouseDown
        OnMouseMove = imgCursorCenterMouseMove
      end
      object imgCursorTo: TImage
        Left = 132
        Top = 144
        Width = 11
        Height = 11
        AutoSize = True
        Picture.Data = {
          07544269746D6170CE000000424DCE0000000000000076000000280000000B00
          00000B000000010004000000000058000000120B0000120B0000100000001000
          000000000000000080000080000000808000800000008000800080800000C0C0
          C000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
          FF00DDDDD0DDDDD00000DDDD0F0DDDD00000DDD0F0F0DDD00000DD0F0D0F0DD0
          0000D0F0DDD0F0D000000F0DDDDD0F000000D0F0DDD0F0D00000DD0F0D0F0DD0
          0000DDD0F0F0DDD00000DDDD0F0DDDD00000DDDDD0DDDDD00000}
        Transparent = True
        OnMouseDown = imgCursorCenterMouseDown
        OnMouseMove = imgCursorCenterMouseMove
      end
    end
  end
  object panView: TPanel
    Left = 8
    Top = 179
    Width = 209
    Height = 204
    BevelOuter = bvLowered
    TabOrder = 3
    object imgView: TImage
      Left = 1
      Top = 1
      Width = 183
      Height = 115
      Stretch = True
    end
  end
  object cmdOk: TButton
    Left = 382
    Top = 390
    Width = 80
    Height = 24
    Anchors = [akRight, akBottom]
    Caption = '&Ok'
    ModalResult = 1
    TabOrder = 4
  end
  object cmdCancel: TButton
    Left = 468
    Top = 390
    Width = 80
    Height = 24
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = '&Cancel'
    Default = True
    ModalResult = 2
    TabOrder = 5
  end
end
