object TiskDialogForm: TTiskDialogForm
  Left = 825
  Top = 720
  BorderStyle = bsDialog
  Caption = 'Tisk'
  ClientHeight = 151
  ClientWidth = 286
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 20
    Top = 10
    Width = 154
    Height = 20
    Caption = #268#237'slo tisknut'#233' faktury'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object CisloFakturyEdit: TEdit
    Left = 20
    Top = 49
    Width = 96
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    Text = '2004001'
  end
  object UpDown1: TUpDown
    Left = 135
    Top = 41
    Width = 49
    Height = 45
    Min = -999
    Max = 999
    Position = 0
    TabOrder = 1
    Wrap = False
    OnClick = UpDown1Click
  end
  object TiskBtn: TBitBtn
    Left = 200
    Top = 75
    Width = 75
    Height = 25
    Caption = '&Tisk'
    TabOrder = 2
    OnClick = TiskBtnClick
  end
  object CancelBtn: TBitBtn
    Left = 200
    Top = 110
    Width = 75
    Height = 25
    Cancel = True
    Caption = '&Storno'
    TabOrder = 3
    OnClick = CancelBtnClick
  end
  object GroupBox1: TGroupBox
    Left = 5
    Top = 90
    Width = 181
    Height = 46
    Caption = 'Odb'#283'ratel'
    TabOrder = 4
    object DBEdit1: TDBEdit
      Left = 4
      Top = 19
      Width = 172
      Height = 21
      DataField = 'OdbratelName'
      DataSource = Databaze.DataSourceFakt
      TabOrder = 0
    end
  end
  object PrintDialog1: TPrintDialog
    Options = [poWarning, poHelp, poDisablePrintToFile]
    Left = 59
    Top = 60
  end
end
