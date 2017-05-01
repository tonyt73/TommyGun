object frmDisplayView: TfrmDisplayView
  Left = 0
  Top = 0
  AlphaBlendValue = 176
  BorderStyle = bsSizeToolWin
  Caption = 'Display View'
  ClientHeight = 196
  ClientWidth = 260
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnKeyUp = FormKeyUp
  OnMouseEnter = FormMouseEnter
  OnMouseLeave = FormMouseLeave
  OnResize = panMainDisplayWhiteResize
  PixelsPerInch = 96
  TextHeight = 13
  object imgMainDisplay: TImage
    Left = 0
    Top = 0
    Width = 260
    Height = 196
    Align = alClient
    PopupMenu = popSVOptions
    OnMouseEnter = FormMouseEnter
    OnMouseLeave = FormMouseLeave
    ExplicitLeft = 1
    ExplicitTop = 1
    ExplicitWidth = 257
    ExplicitHeight = 192
  end
  object panMainDisplayBlack: TPanel
    Left = 0
    Top = 0
    Width = 260
    Height = 196
    Align = alClient
    BevelOuter = bvNone
    Color = clBlack
    Padding.Left = 1
    Padding.Top = 1
    Padding.Right = 1
    Padding.Bottom = 1
    ParentBackground = False
    TabOrder = 0
    Visible = False
    OnMouseEnter = FormMouseEnter
    OnMouseLeave = FormMouseLeave
  end
  object panMainDisplayWhite: TPanel
    Left = 0
    Top = 0
    Width = 260
    Height = 196
    Align = alClient
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 1
    Visible = False
    OnMouseEnter = FormMouseEnter
    OnMouseLeave = FormMouseLeave
    OnResize = panMainDisplayWhiteResize
  end
  object popSVOptions: TPopupMenu
    Left = 51
    Top = 33
    object popSVNormalSize: TMenuItem
      Caption = 'Normal Size'
      Checked = True
      GroupIndex = 1
      RadioItem = True
      OnClick = popSVNormalSizeClick
    end
    object popSVDoubleSize: TMenuItem
      Caption = 'Double Size'
      GroupIndex = 1
      RadioItem = True
      OnClick = popSVDoubleSizeClick
    end
    object popSVTripleSize: TMenuItem
      Caption = 'Triple Size'
      GroupIndex = 1
      RadioItem = True
      OnClick = popSVTripleSizeClick
    end
    object popSVLine00: TMenuItem
      Caption = '-'
      GroupIndex = 1
    end
    object popTranslucent: TMenuItem
      Caption = 'Translucent'
      GroupIndex = 3
      OnClick = popTranslucentClick
    end
    object popSVShowAttributes: TMenuItem
      Caption = 'Show Attributes'
      Checked = True
      GroupIndex = 3
      OnClick = popSVShowAttributesClick
    end
    object popBlackOnWhite: TMenuItem
      Caption = 'Black on White'
      Checked = True
      Enabled = False
      GroupIndex = 4
      RadioItem = True
      OnClick = popBlackOnWhiteClick
    end
    object popWhiteOnBlack: TMenuItem
      Caption = 'White on Black'
      Enabled = False
      GroupIndex = 4
      RadioItem = True
      OnClick = popBlackOnWhiteClick
    end
  end
end
