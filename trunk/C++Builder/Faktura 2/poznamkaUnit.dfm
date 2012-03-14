object PoznamkaForm: TPoznamkaForm
  Left = 269
  Top = 512
  Width = 379
  Height = 155
  ActiveControl = OKBtn
  Anchors = [akLeft, akTop, akRight, akBottom]
  BorderIcons = [biMinimize]
  Caption = 'PoznamkaForm'
  Color = clBtnFace
  Constraints.MaxHeight = 155
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnDeactivate = FormDeactivate
  DesignSize = (
    371
    121)
  PixelsPerInch = 96
  TextHeight = 13
  object Label9: TLabel
    Left = 6
    Top = 4
    Width = 164
    Height = 20
    Caption = 'Pozn'#225'mka na fakturu :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object DBMemo1: TDBMemo
    Left = 8
    Top = 25
    Width = 354
    Height = 48
    Anchors = [akLeft, akTop, akRight]
    DataField = 'Poznamka'
    DataSource = Databaze.DataSourceDod
    TabOrder = 0
  end
  object OKBtn: TButton
    Left = 251
    Top = 83
    Width = 111
    Height = 31
    Anchors = [akTop, akRight]
    Caption = '&OK'
    TabOrder = 1
    OnClick = OKBtnClick
  end
end
