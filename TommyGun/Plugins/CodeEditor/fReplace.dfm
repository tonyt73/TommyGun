object frmReplace: TfrmReplace
  Left = 973
  Top = 219
  BorderStyle = bsDialog
  Caption = 'Replace Text'
  ClientHeight = 244
  ClientWidth = 364
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  DesignSize = (
    364
    244)
  PixelsPerInch = 96
  TextHeight = 13
  object lblTextToFind: TLabel
    Left = 12
    Top = 12
    Width = 58
    Height = 13
    Caption = '&Text to Find'
  end
  object lblRepalceWith: TLabel
    Left = 12
    Top = 40
    Width = 61
    Height = 13
    Caption = '&Replace with'
  end
  object cmbFindText: TComboBox
    Left = 80
    Top = 8
    Width = 276
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    Color = clWhite
    ItemHeight = 13
    TabOrder = 0
  end
  object grpOptoins: TGroupBox
    Left = 4
    Top = 63
    Width = 174
    Height = 78
    Caption = ' Options '
    TabOrder = 2
    object chkCaseSensitive: TCheckBox
      Left = 12
      Top = 16
      Width = 154
      Height = 17
      Caption = '&Case sensitive'
      TabOrder = 0
    end
    object chkWholeWordsOnly: TCheckBox
      Left = 12
      Top = 36
      Width = 154
      Height = 17
      Caption = '&Whole words only'
      TabOrder = 1
    end
    object chkPromptOnReplace: TCheckBox
      Left = 12
      Top = 56
      Width = 154
      Height = 17
      Caption = '&Prompt on replace'
      TabOrder = 2
    end
  end
  object grpDirection: TGroupBox
    Left = 186
    Top = 63
    Width = 170
    Height = 78
    Anchors = [akLeft, akTop, akRight]
    Caption = ' Direction '
    TabOrder = 3
    object radForward: TRadioButton
      Left = 12
      Top = 16
      Width = 77
      Height = 17
      Caption = 'Forwar&d'
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object radBackwards: TRadioButton
      Left = 12
      Top = 36
      Width = 85
      Height = 17
      Caption = '&Backward'
      TabOrder = 1
    end
  end
  object grpScope: TGroupBox
    Left = 4
    Top = 143
    Width = 174
    Height = 60
    Caption = ' Scope '
    TabOrder = 4
    object radGlobal: TRadioButton
      Left = 12
      Top = 16
      Width = 154
      Height = 17
      Caption = '&Global'
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object radSelectedText: TRadioButton
      Left = 12
      Top = 36
      Width = 154
      Height = 17
      Caption = '&Selected text'
      TabOrder = 1
    end
  end
  object grpOrigin: TGroupBox
    Left = 186
    Top = 143
    Width = 170
    Height = 60
    Anchors = [akLeft, akTop, akRight]
    Caption = ' Origin '
    TabOrder = 5
    object radFromCursor: TRadioButton
      Left = 12
      Top = 16
      Width = 85
      Height = 17
      Caption = '&From cursor'
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object radEntireScope: TRadioButton
      Left = 12
      Top = 36
      Width = 85
      Height = 17
      Caption = '&Entire scope'
      TabOrder = 1
    end
  end
  object cmdOK: TButton
    Left = 104
    Top = 212
    Width = 80
    Height = 24
    Anchors = [akRight, akBottom]
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 6
  end
  object cmdCancel: TButton
    Left = 276
    Top = 212
    Width = 80
    Height = 24
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 8
  end
  object cmbReplaceText: TComboBox
    Left = 80
    Top = 36
    Width = 276
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    Color = clWhite
    ItemHeight = 13
    TabOrder = 1
  end
  object cmdReplaceAll: TButton
    Left = 190
    Top = 212
    Width = 80
    Height = 24
    Anchors = [akRight, akBottom]
    Caption = 'Replace &All'
    ModalResult = 8
    TabOrder = 7
    OnClick = cmdReplaceAllClick
  end
end
