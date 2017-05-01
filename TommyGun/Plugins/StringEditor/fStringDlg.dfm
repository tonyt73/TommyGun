object frmStringDlg: TfrmStringDlg
  Left = 307
  Top = 247
  ActiveControl = edtID
  Caption = 'String Properties'
  ClientHeight = 233
  ClientWidth = 397
  Color = clWhite
  Constraints.MinHeight = 250
  Constraints.MinWidth = 330
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  DesignSize = (
    397
    233)
  PixelsPerInch = 96
  TextHeight = 13
  object panButtons: TPanel
    Left = 0
    Top = 199
    Width = 397
    Height = 34
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      397
      34)
    object cmdOk: TButton
      Left = 223
      Top = 0
      Width = 80
      Height = 24
      Anchors = [akRight, akBottom]
      Caption = '&Ok'
      Enabled = False
      ModalResult = 1
      TabOrder = 0
    end
    object cmdCancel: TButton
      Left = 309
      Top = 0
      Width = 80
      Height = 24
      Anchors = [akRight, akBottom]
      Cancel = True
      Caption = '&Cancel'
      Default = True
      ModalResult = 2
      TabOrder = 1
    end
  end
  object grpStringInformaton: TGroupBox
    Left = 8
    Top = 8
    Width = 381
    Height = 185
    Anchors = [akLeft, akTop, akRight, akBottom]
    Caption = 'String Properties'
    TabOrder = 1
    DesignSize = (
      381
      185)
    object lblID: TLabel
      Left = 3
      Top = 24
      Width = 20
      Height = 13
      Caption = '* ID'
    end
    object lblValue: TLabel
      Left = 12
      Top = 52
      Width = 26
      Height = 13
      Caption = 'Value'
    end
    object lblNote: TLabel
      Left = 52
      Top = 168
      Width = 120
      Height = 11
      Anchors = [akLeft, akBottom]
      Caption = '* Note: ID can be left blank.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ExplicitTop = 204
    end
    object memoValue: TMemo
      Left = 52
      Top = 52
      Width = 317
      Height = 115
      Anchors = [akLeft, akTop, akRight, akBottom]
      Color = clWhite
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnChange = edtIDChange
      OnKeyDown = memoValueKeyDown
    end
    object edtID: TEdit
      Left = 52
      Top = 20
      Width = 317
      Height = 24
      Anchors = [akLeft, akTop, akRight]
      Color = clWhite
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnChange = edtIDChange
    end
  end
end
