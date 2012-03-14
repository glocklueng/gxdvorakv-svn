object MainForm: TMainForm
  Left = 311
  Top = 216
  Width = 738
  Height = 488
  Anchors = []
  Caption = 'Faktura 2010 (rev.2.0.3)'
  Color = clBtnFace
  Constraints.MinHeight = 400
  Constraints.MinWidth = 730
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Visible = True
  OnActivate = FormActivate
  OnCreate = FormCreate
  DesignSize = (
    730
    434)
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBoxOdberatelHledani: TGroupBox
    Left = 3
    Top = 4
    Width = 281
    Height = 162
    Caption = 'Vyhledav'#225'n'#237' Odb'#283'ratel'#367
    TabOrder = 4
    Visible = False
    object Firma: TLabel
      Left = 24
      Top = 51
      Width = 25
      Height = 13
      Caption = 'Firma'
    end
    object FirmEdit: TEdit
      Left = 72
      Top = 48
      Width = 193
      Height = 21
      TabOrder = 0
    end
    object NajdiBtn: TButton
      Left = 96
      Top = 104
      Width = 75
      Height = 25
      Caption = 'Najdi'
      TabOrder = 1
      OnClick = NajdiBtnClick
    end
  end
  object GroupBoxF: TGroupBox
    Left = 3
    Top = 0
    Width = 281
    Height = 169
    TabOrder = 0
    Visible = False
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 97
      Height = 20
      Caption = #268#237'slo Faktury'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 78
      Top = 92
      Width = 80
      Height = 13
      Caption = 'Datum vystaven'#237
    end
    object Label3: TLabel
      Left = 80
      Top = 116
      Width = 78
      Height = 13
      Caption = 'Datum splatnosti'
    end
    object Label4: TLabel
      Left = 9
      Top = 140
      Width = 149
      Height = 13
      Caption = 'Datum usk. zdaniteln'#233'ho pln'#283'n'#237
    end
    object Label11: TLabel
      Left = 8
      Top = 68
      Width = 81
      Height = 13
      Caption = #268#237'slo objedn'#225'vky'
    end
    object CisloFakturyEdit: TEdit
      Left = 120
      Top = 24
      Width = 81
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
      Left = 216
      Top = 16
      Width = 49
      Height = 41
      Min = -999
      Max = 999
      Position = 0
      TabOrder = 1
      Wrap = False
      OnClick = UpDown1Click
    end
    object DateVystaveni: TDateTimePicker
      Left = 168
      Top = 88
      Width = 97
      Height = 21
      CalAlignment = dtaLeft
      Date = 38153.9830466898
      Time = 38153.9830466898
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 2
      OnChange = DateVystaveniChange
    end
    object DateSplatnosti: TDateTimePicker
      Left = 168
      Top = 112
      Width = 97
      Height = 21
      CalAlignment = dtaLeft
      Date = 38153.983153206
      Time = 38153.983153206
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 3
    end
    object DateZdaneni: TDateTimePicker
      Left = 168
      Top = 136
      Width = 97
      Height = 21
      CalAlignment = dtaLeft
      Date = 38153.9834919329
      Time = 38153.9834919329
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 4
    end
    object CisloObjednavkyEdit: TEdit
      Left = 104
      Top = 64
      Width = 161
      Height = 21
      TabOrder = 5
    end
  end
  object GroupBoxOdb: TGroupBox
    Left = 289
    Top = 0
    Width = 437
    Height = 225
    Caption = 'Odb'#283'ratel'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    Visible = False
    object Label5: TLabel
      Left = 24
      Top = 20
      Width = 25
      Height = 13
      Caption = 'Firma'
    end
    object Label6: TLabel
      Left = 16
      Top = 76
      Width = 33
      Height = 13
      Caption = 'Adresa'
    end
    object Label8: TLabel
      Left = 31
      Top = 108
      Width = 18
      Height = 13
      Caption = 'I'#268'O'
    end
    object Label7: TLabel
      Left = 31
      Top = 140
      Width = 18
      Height = 13
      Caption = 'DI'#268
    end
    object Label9: TLabel
      Left = 13
      Top = 172
      Width = 36
      Height = 13
      Caption = 'Telefon'
    end
    object Label10: TLabel
      Left = 24
      Top = 196
      Width = 25
      Height = 13
      Caption = 'Mobil'
    end
    object KonecBtn: TButton
      Left = 340
      Top = 175
      Width = 76
      Height = 41
      Caption = 'Konec'
      TabOrder = 14
      OnClick = KonecBtnClick
    end
    object DBEdit1: TDBEdit
      Left = 56
      Top = 40
      Width = 265
      Height = 21
      DataField = 'Firma2'
      DataSource = Databaze.DataSourceOdb
      TabOrder = 0
    end
    object DBEdit2: TDBEdit
      Left = 56
      Top = 16
      Width = 265
      Height = 21
      DataField = 'Firma'
      DataSource = Databaze.DataSourceOdb
      TabOrder = 1
    end
    object DBEdit3: TDBEdit
      Left = 56
      Top = 72
      Width = 265
      Height = 21
      DataField = 'Adresa'
      DataSource = Databaze.DataSourceOdb
      TabOrder = 2
    end
    object DBEdit4: TDBEdit
      Left = 56
      Top = 104
      Width = 121
      Height = 21
      DataField = 'ICO'
      DataSource = Databaze.DataSourceOdb
      TabOrder = 3
    end
    object DBEdit5: TDBEdit
      Left = 56
      Top = 136
      Width = 121
      Height = 21
      DataField = 'DIC'
      DataSource = Databaze.DataSourceOdb
      TabOrder = 4
    end
    object DBEdit6: TDBEdit
      Left = 56
      Top = 168
      Width = 241
      Height = 21
      DataField = 'Telefon'
      DataSource = Databaze.DataSourceOdb
      TabOrder = 5
    end
    object DBEdit7: TDBEdit
      Left = 56
      Top = 192
      Width = 241
      Height = 21
      DataField = 'Mobil'
      DataSource = Databaze.DataSourceOdb
      TabOrder = 6
    end
    object GroupBox3: TGroupBox
      Left = 200
      Top = 104
      Width = 81
      Height = 49
      Caption = 'ID Odb'#283'ratele'
      TabOrder = 7
      object DBText1: TDBText
        Left = 2
        Top = 24
        Width = 77
        Height = 23
        Align = alBottom
        Alignment = taCenter
        DataField = 'Id'
        DataSource = Databaze.DataSourceOdb
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object UpravitBtn: TButton
      Left = 342
      Top = 15
      Width = 75
      Height = 25
      Caption = 'Upravit'
      TabOrder = 8
      OnClick = UpravitBtnClick
    end
    object PridatBtn: TButton
      Left = 342
      Top = 47
      Width = 75
      Height = 25
      Caption = 'P'#345'idat'
      TabOrder = 9
      OnClick = PridatBtnClick
    end
    object SmazatBtn: TButton
      Left = 342
      Top = 79
      Width = 75
      Height = 25
      Caption = 'Smazat'
      TabOrder = 10
      OnClick = SmazatBtnClick
    end
    object StornoBtn: TButton
      Left = 342
      Top = 111
      Width = 75
      Height = 25
      Caption = 'Storno'
      TabOrder = 11
      OnClick = StornoBtnClick
    end
    object UlozitBtn: TButton
      Left = 342
      Top = 143
      Width = 75
      Height = 25
      Caption = 'Ulo'#382'it'
      TabOrder = 12
      OnClick = UlozitBtnClick
    end
    object PokracovatBtn: TButton
      Left = 342
      Top = 176
      Width = 75
      Height = 40
      Caption = 'Pokra'#269'ovat ...'
      TabOrder = 13
      OnClick = PokracovatBtnClick
    end
  end
  object DBGridOdb: TDBGrid
    Left = 0
    Top = 232
    Width = 730
    Height = 202
    Anchors = [akLeft]
    DataSource = Databaze.DataSourceOdb
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
    ReadOnly = True
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    Visible = False
    Columns = <
      item
        Expanded = False
        FieldName = 'Id'
        Width = 29
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Firma'
        Width = 156
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Firma2'
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'Adresa'
        Width = 177
        Visible = True
      end
      item
        Alignment = taRightJustify
        Expanded = False
        FieldName = 'ICO'
        Title.Caption = 'I'#268'O'
        Width = 59
        Visible = True
      end
      item
        Alignment = taRightJustify
        Expanded = False
        FieldName = 'DIC'
        Title.Caption = 'DI'#268
        Width = 77
        Visible = True
      end
      item
        Alignment = taRightJustify
        Expanded = False
        FieldName = 'Telefon'
        Width = 100
        Visible = True
      end
      item
        Alignment = taRightJustify
        Expanded = False
        FieldName = 'Mobil'
        Width = 93
        Visible = True
      end>
  end
  object DBNavigatorOdb: TDBNavigator
    Left = 8
    Top = 175
    Width = 265
    Height = 49
    DataSource = Databaze.DataSourceOdb
    VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbRefresh]
    TabOrder = 3
    Visible = False
  end
  object MainMenu1: TMainMenu
    OwnerDraw = True
    Left = 11
    Top = 373
    object Faktura1: TMenuItem
      Caption = '&Faktura'
      object menuNova: TMenuItem
        Caption = '&Nov'#225
        OnClick = menuNovaClick
      end
      object menuEditaceUlozenych: TMenuItem
        Caption = '&Editace ulo'#382'en'#253'ch'
        OnClick = menuEditaceUlozenychClick
      end
      object menuVyhleOdb: TMenuItem
        Caption = '&Vyhled'#225'van'#237' podle odb'#283'ratele'
        OnClick = menuVyhleOdbClick
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object Poznamka1: TMenuItem
        Caption = '&Pozn'#225'mka'
        OnClick = Poznamka1Click
      end
      object menuTisk: TMenuItem
        Caption = '&Tisk'
        OnClick = menuTiskClick
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object menuKonec: TMenuItem
        Caption = '&Konec'
        GroupIndex = 1
        OnClick = menuKonecClick
      end
    end
    object menuOdbEdit: TMenuItem
      Caption = '&Editace'
      object menuDodavatel: TMenuItem
        Caption = '&'#218'daje dodavatele'
        GroupIndex = 1
        OnClick = menuDodavatelClick
      end
      object Odberetele: TMenuItem
        Caption = '&Odb'#283'ratel'#233
        GroupIndex = 1
        OnClick = OdbereteleClick
      end
    end
    object menuNastTisk: TMenuItem
      Caption = '&Nastaven'#237' Tisku'
      GroupIndex = 1
      OnClick = menuNastTiskClick
    end
  end
  object PrinterSetupDialog1: TPrinterSetupDialog
    Left = 585
    Top = 115
  end
end
