object frmZXImageTableParserOptions: TfrmZXImageTableParserOptions
  Left = 1233
  Top = 443
  ClientHeight = 676
  ClientWidth = 340
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panZXImageTableParser: TPanel
    Left = 0
    Top = 0
    Width = 340
    Height = 676
    Align = alClient
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 0
    object scpZXImageTableParser: TScrollBox
      Left = 0
      Top = 45
      Width = 340
      Height = 631
      VertScrollBar.Smooth = True
      VertScrollBar.Tracking = True
      Align = alClient
      Color = clWhite
      ParentColor = False
      TabOrder = 0
      object panOptions: TPanel
        Left = 0
        Top = 0
        Width = 336
        Height = 322
        Align = alTop
        BevelOuter = bvNone
        Color = clWhite
        ParentBackground = False
        TabOrder = 0
        DesignSize = (
          336
          322)
        object FlatGroupBox1: TGroupBox
          Left = 6
          Top = 6
          Width = 324
          Height = 73
          Anchors = [akLeft, akTop, akRight]
          Caption = ' Table Name '
          TabOrder = 0
          DesignSize = (
            324
            73)
          object Label1: TLabel
            Left = 8
            Top = 40
            Width = 307
            Height = 29
            Anchors = [akLeft, akTop, akRight]
            AutoSize = False
            Caption = 
              'A blank name will generate a table name constructed of the image' +
              ' type. eg. Sprite type table name is SpriteTable:'
            WordWrap = True
            ExplicitWidth = 325
          end
          object edtTableName: TEdit
            Left = 8
            Top = 16
            Width = 310
            Height = 21
            Anchors = [akLeft, akTop, akRight]
            ParentColor = True
            TabOrder = 0
            OnChange = chkTableAddNumberClick
          end
        end
        object grpZXImageTableParserPixelOrder: TGroupBox
          Left = 5
          Top = 85
          Width = 325
          Height = 40
          Anchors = [akLeft, akTop, akRight]
          Caption = ' Table Options '
          TabOrder = 1
          object chkTableAddNumber: TCheckBox
            Left = 8
            Top = 16
            Width = 230
            Height = 17
            Caption = 'Add number of images to the Table entries'
            TabOrder = 0
            OnClick = chkTableAddNumberClick
          end
        end
        object grpPreview: TGroupBox
          Left = 6
          Top = 131
          Width = 324
          Height = 183
          Anchors = [akLeft, akTop, akRight]
          Caption = ' Preview '
          TabOrder = 2
          DesignSize = (
            324
            183)
          object rdtZXImageTableParserPreview: TRichEdit
            Left = 8
            Top = 16
            Width = 308
            Height = 157
            Anchors = [akLeft, akTop, akRight]
            Color = clBlack
            Font.Charset = OEM_CHARSET
            Font.Color = clWhite
            Font.Height = -8
            Font.Name = 'Terminal'
            Font.Style = []
            Lines.Strings = (
              ';'
              '; Sprites table'
              ';'
              'SpriteTable:'
              'defb {n}           ; number of sprite images'
              'defw image1'
              'defw image2'
              'defw image3'
              'defw ...')
            ParentFont = False
            ReadOnly = True
            ScrollBars = ssBoth
            TabOrder = 0
          end
        end
      end
    end
    object panTitle: TPanel
      Left = 0
      Top = 0
      Width = 340
      Height = 45
      Align = alTop
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 1
      DesignSize = (
        340
        45)
      object lblZXImagesParser: TLabel
        Left = 4
        Top = 4
        Width = 169
        Height = 13
        Caption = 'Images Table Builder (Parser)'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lblZXImageTableParserDescription: TLabel
        Left = 8
        Top = 24
        Width = 333
        Height = 17
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 'Parses a list of images into an asm Image Table.'
        WordWrap = True
        ExplicitWidth = 343
      end
    end
  end
end
