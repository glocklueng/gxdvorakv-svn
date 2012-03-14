object Form1: TForm1
  Left = 289
  Top = 175
  Width = 738
  Height = 496
  Anchors = []
  Caption = 'Form1'
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
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBoxF: TGroupBox
    Left = 3
    Top = 0
    Width = 281
    Height = 161
    TabOrder = 0
    Visible = False
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 97
      Height = 20
      Caption = 'Èíslo Faktury'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 64
      Top = 72
      Width = 80
      Height = 13
      Caption = 'Datum vystavení'
    end
    object Label3: TLabel
      Left = 64
      Top = 104
      Width = 78
      Height = 13
      Caption = 'Datum splatnosti'
    end
    object Label4: TLabel
      Left = 8
      Top = 136
      Width = 149
      Height = 13
      Caption = 'Datum usk. zdanitelného plnìní'
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
      Top = 64
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
    end
    object DateSplatnosti: TDateTimePicker
      Left = 168
      Top = 96
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
      Top = 128
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
  end
  object GroupBoxOdb: TGroupBox
    Left = 289
    Top = 0
    Width = 437
    Height = 225
    Caption = 'Odbìratel'
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
      Top = 24
      Width = 25
      Height = 13
      Caption = 'Firma'
    end
    object Label6: TLabel
      Left = 16
      Top = 80
      Width = 33
      Height = 13
      Caption = 'Adresa'
    end
    object Label8: TLabel
      Left = 31
      Top = 112
      Width = 18
      Height = 13
      Caption = 'IÈO'
    end
    object Label7: TLabel
      Left = 31
      Top = 144
      Width = 18
      Height = 13
      Caption = 'DIÈ'
    end
    object Label9: TLabel
      Left = 13
      Top = 176
      Width = 36
      Height = 13
      Caption = 'Telefon'
    end
    object Label10: TLabel
      Left = 24
      Top = 200
      Width = 25
      Height = 13
      Caption = 'Mobil'
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
      Caption = 'ID Odbìratele'
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
      Caption = 'Pøidat'
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
      Caption = 'Uložit'
      TabOrder = 12
      OnClick = UlozitBtnClick
    end
    object PokracovatBtn: TButton
      Left = 342
      Top = 176
      Width = 75
      Height = 40
      Caption = 'Pokraèovat ...'
      TabOrder = 13
      OnClick = PokracovatBtnClick
    end
  end
  object DBGridOdb: TDBGrid
    Left = 0
    Top = 230
    Width = 730
    Height = 220
    Align = alBottom
    Anchors = [akLeft, akTop, akRight, akBottom]
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
        Width = 59
        Visible = True
      end
      item
        Alignment = taRightJustify
        Expanded = False
        FieldName = 'DIC'
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
        ReadOnly = False
        Width = 93
        Visible = True
      end>
  end
  object DBNavigatorOdb: TDBNavigator
    Left = 8
    Top = 175
    Width = 256
    Height = 49
    DataSource = Databaze.DataSourceOdb
    VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbEdit, nbPost, nbCancel, nbRefresh]
    TabOrder = 3
    Visible = False
  end
  object GroupBoxOdberatelHledani: TGroupBox
    Left = 3
    Top = 74
    Width = 281
    Height = 161
    Caption = 'Vyhledavání Odbìratelù'
    TabOrder = 4
    Visible = False
    object Firma: TLabel
      Left = 24
      Top = 56
      Width = 25
      Height = 13
      Caption = 'Firma'
    end
    object Edit2: TEdit
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
    end
  end
  object MainMenu1: TMainMenu
    OwnerDraw = True
    Left = 16
    Top = 368
    object Faktura1: TMenuItem
      Caption = '&Faktura'
      object menuNova: TMenuItem
        Caption = '  &Nová'
        OnClick = menuNovaClick
      end
      object menuEditaceUlozenych: TMenuItem
        Caption = '  &Editace uložených'
        OnClick = menuEditaceUlozenychClick
      end
      object Vyhledavanipodleodberatele1: TMenuItem
        Caption = '  &Vyhledavani podle odberatele'
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object Poznamka1: TMenuItem
        Caption = '&Poznamka'
      end
      object Tisk1: TMenuItem
        Caption = '&Tisk'
        OnClick = Tisk1Click
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object Konec1: TMenuItem
        Caption = '&Konec'
        OnClick = Konec1Click
      end
    end
    object Dodavatel1: TMenuItem
      Caption = '&Odberatele'
      object menuOdbEdit: TMenuItem
        Caption = '&Editace'
        OnClick = menuOdbEditClick
      end
      object Vyhledavani2: TMenuItem
        Caption = '&Vyhledavani'
      end
    end
    object Dodavatel2: TMenuItem
      Caption = '&Udaje Dodavatele'
      GroupIndex = 1
    end
    object Nastaveni1: TMenuItem
      Caption = '&Nastaveni Tisku'
      GroupIndex = 1
    end
  end
end
