object frmImageImport: TfrmImageImport
  Left = 981
  Top = 26
  ClientHeight = 548
  ClientWidth = 738
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object mnuImportImage: TPopupMenu
    Left = 8
    Top = 4
    object mnuImportImages: TMenuItem
      Caption = 'Images...'
      OnClick = mnuImportImagesClick
    end
    object mnuImportImageSheet: TMenuItem
      Caption = 'Image Sheet...'
      OnClick = mnuImportImageSheetClick
    end
  end
  object dlgImport: TOpenPictureDialog
    DefaultExt = '*.bmp'
    Filter = 
      'Screen Memory Snapshot|*.scr|Spectrum 48K Snapshot|*.sna|Spectru' +
      'm Graphics File|*.zxg|SevenuP File|*.sev|Windows Bitmap|*.bmp|Al' +
      'l Import Files|*.scr;*.sna;*.zxg;*.sev;*.bmp;*.tgp|All Files|*.*'
    FilterIndex = 6
    Options = [ofHideReadOnly, ofAllowMultiSelect, ofPathMustExist, ofFileMustExist, ofEnableSizing, ofDontAddToRecent]
    Title = 'Select Images to Import'
    Left = 40
    Top = 4
  end
  object dlgImportSheet: TOpenPictureDialog
    DefaultExt = '*.bmp'
    Filter = 'Windows Bitmap|*.bmp|All Files|*.*'
    FilterIndex = 0
    Options = [ofHideReadOnly, ofAllowMultiSelect, ofPathMustExist, ofFileMustExist, ofEnableSizing, ofDontAddToRecent]
    Title = 'Select Image Sheet to Import'
    Left = 72
    Top = 4
  end
end
