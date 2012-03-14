object DodavatelForm: TDodavatelForm
  Left = 462
  Top = 421
  Width = 359
  Height = 261
  Anchors = [akLeft, akTop, akRight, akBottom]
  Caption = 'Dodavatel'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PopupMenu = PopupMenu1
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 40
    Width = 37
    Height = 13
    Caption = 'N'#225'zev :'
  end
  object Label2: TLabel
    Left = 16
    Top = 97
    Width = 42
    Height = 13
    Caption = 'Telefon :'
  end
  object Label3: TLabel
    Left = 16
    Top = 124
    Width = 31
    Height = 13
    Caption = 'Mobil :'
  end
  object Label4: TLabel
    Left = 16
    Top = 148
    Width = 24
    Height = 13
    Caption = 'I'#268'O :'
  end
  object Label5: TLabel
    Left = 16
    Top = 175
    Width = 24
    Height = 13
    Caption = 'DI'#268' :'
  end
  object Label6: TLabel
    Left = 16
    Top = 202
    Width = 53
    Height = 13
    Caption = #268#237'slo '#250#269'tu :'
  end
  object Label7: TLabel
    Left = 16
    Top = 69
    Width = 39
    Height = 13
    Caption = 'Adresa :'
  end
  object Label8: TLabel
    Left = 96
    Top = 8
    Width = 127
    Height = 20
    Caption = #218'daje dodavatele'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object NazevEdit: TDBEdit
    Left = 74
    Top = 35
    Width = 265
    Height = 21
    DataField = 'Nazev'
    DataSource = Databaze.DataSourceDod
    TabOrder = 0
  end
  object AdresaEdit: TDBEdit
    Left = 73
    Top = 62
    Width = 265
    Height = 21
    DataField = 'Adresa'
    DataSource = Databaze.DataSourceDod
    TabOrder = 1
  end
  object TelefonEdit: TDBEdit
    Left = 73
    Top = 89
    Width = 265
    Height = 21
    DataField = 'Telefon'
    DataSource = Databaze.DataSourceDod
    TabOrder = 2
  end
  object MobilEdit: TDBEdit
    Left = 73
    Top = 116
    Width = 265
    Height = 21
    DataField = 'Mobil'
    DataSource = Databaze.DataSourceDod
    TabOrder = 3
  end
  object ICOEdit: TDBEdit
    Left = 73
    Top = 143
    Width = 137
    Height = 21
    DataField = 'ICO'
    DataSource = Databaze.DataSourceDod
    TabOrder = 4
  end
  object DICEdit: TDBEdit
    Left = 73
    Top = 170
    Width = 137
    Height = 21
    DataField = 'DIC'
    DataSource = Databaze.DataSourceDod
    TabOrder = 5
  end
  object CisloUctuEdit: TDBEdit
    Left = 73
    Top = 197
    Width = 268
    Height = 21
    DataField = 'CisloUctu'
    DataSource = Databaze.DataSourceDod
    TabOrder = 6
  end
  object PopupMenu1: TPopupMenu
    Left = 275
    Top = 150
    object Povoliteditaci1: TMenuItem
      Caption = 'Povolit editaci'
      OnClick = Povoliteditaci1Click
    end
  end
end
