object PoznamkaForm: TPoznamkaForm
  Left = 307
  Top = 79
  Width = 516
  Height = 177
  ActiveControl = OKBtn
  Caption = 'Pozn'#225'mka'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnDeactivate = FormDeactivate
  DesignSize = (
    508
    143)
  PixelsPerInch = 96
  TextHeight = 13
  object Label9: TLabel
    Left = 6
    Top = 9
    Width = 225
    Height = 20
    Caption = 'Pozn'#225'mka na fakturu  (z'#225'pat'#237'):'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object DBMemo1: TDBMemo
    Left = 8
    Top = 35
    Width = 493
    Height = 48
    Anchors = [akLeft, akTop, akRight]
    DataField = 'Poznamka'
    DataSource = Databaze.DataSourceDod
    TabOrder = 0
  end
  object OKBtn: TButton
    Left = 371
    Top = 98
    Width = 111
    Height = 31
    Anchors = [akTop, akRight]
    Caption = '&OK'
    TabOrder = 1
    OnClick = OKBtnClick
  end
end
