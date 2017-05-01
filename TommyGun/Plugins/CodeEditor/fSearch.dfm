object frmSearch: TfrmSearch
  Left = 1279
  Top = 555
  BorderStyle = bsDialog
  Caption = 'Find Text'
  ClientHeight = 198
  ClientWidth = 364
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCloseQuery = FormCloseQuery
  OnShow = FormShow
  DesignSize = (
    364
    198)
  PixelsPerInch = 96
  TextHeight = 13
  object lblTextToFind: TLabel
    Left = 12
    Top = 12
    Width = 58
    Height = 13
    Caption = '&Text to Find'
  end
  object cmdOK: TButton
    Left = 190
    Top = 170
    Width = 80
    Height = 24
    Anchors = [akRight, akBottom]
    Caption = 'OK'
    Default = True
    TabOrder = 0
    OnClick = cmdOKClick
  end
  object cmdCancel: TButton
    Left = 276
    Top = 170
    Width = 80
    Height = 24
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object cmbFindText: TComboBox
    Left = 76
    Top = 8
    Width = 280
    Height = 21
    Color = clWhite
    ItemHeight = 13
    TabOrder = 2
  end
  object grpOptoins: TGroupBox
    Left = 4
    Top = 36
    Width = 174
    Height = 60
    Caption = ' Options '
    TabOrder = 3
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
  end
  object grpDirection: TGroupBox
    Left = 182
    Top = 36
    Width = 174
    Height = 60
    Caption = ' Direction '
    TabOrder = 4
    object radForward: TRadioButton
      Left = 12
      Top = 16
      Width = 154
      Height = 17
      Caption = 'Forwar&d'
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object radBackwards: TRadioButton
      Left = 12
      Top = 36
      Width = 154
      Height = 17
      Caption = '&Backward'
      TabOrder = 1
    end
  end
  object grpScope: TGroupBox
    Left = 4
    Top = 100
    Width = 174
    Height = 60
    Caption = ' Scope '
    TabOrder = 5
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
    object radAllFiles: TRadioButton
      Left = 12
      Top = 36
      Width = 154
      Height = 17
      Caption = '&All Files in the Project'
      TabOrder = 1
    end
    object radProjectFiles: TRadioButton
      Left = 12
      Top = 36
      Width = 154
      Height = 17
      Caption = 'Project Files'
      TabOrder = 2
    end
  end
  object grpOrigin: TGroupBox
    Left = 182
    Top = 100
    Width = 174
    Height = 60
    Caption = ' Origin '
    TabOrder = 6
    object radFromCursor: TRadioButton
      Left = 12
      Top = 16
      Width = 154
      Height = 17
      Caption = '&From cursor'
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object radEntireScope: TRadioButton
      Left = 12
      Top = 36
      Width = 154
      Height = 17
      Caption = '&Entire scope'
      TabOrder = 1
    end
  end
end
