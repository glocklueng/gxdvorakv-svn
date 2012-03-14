object VyhledavaniForm: TVyhledavaniForm
  Left = 232
  Top = 265
  Width = 721
  Height = 450
  Caption = 'VyhledavaniForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object DBGridOdb: TDBGrid
    Left = 0
    Top = 0
    Width = 713
    Height = 206
    Align = alTop
    DataSource = Databaze.DataSourceOdb
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
    ReadOnly = True
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
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
        Width = 194
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Firma2'
        Title.Caption = 'Firma - rozšíøení'
        Width = 143
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Adresa'
        Width = 162
        Visible = True
      end
      item
        Alignment = taRightJustify
        Expanded = False
        FieldName = 'ICO'
        Title.Caption = 'IÈO'
        Width = 59
        Visible = True
      end
      item
        Alignment = taRightJustify
        Expanded = False
        FieldName = 'DIC'
        Title.Caption = 'DIÈ'
        Width = 77
        Visible = True
      end
      item
        Alignment = taRightJustify
        Expanded = False
        FieldName = 'Telefon'
        Visible = False
      end
      item
        Alignment = taRightJustify
        Expanded = False
        FieldName = 'Mobil'
        Visible = False
      end>
  end
  object DBGridFaktury: TDBGrid
    Left = -5
    Top = 210
    Width = 436
    Height = 201
    DataSource = Databaze.DataSourceFakt
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'Cislo'
        ReadOnly = True
        Title.Caption = 'Èíslo Faktury'
        Width = 66
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'IdOdberatele'
        ReadOnly = True
        Title.Caption = 'È. Odbìratele'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'OdbratelName'
        ReadOnly = True
        Title.Caption = 'Odbìratel'
        Visible = False
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'Splatnost'
        ReadOnly = True
        Title.Caption = 'Datum Splatnosti'
        Width = 89
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'Vystaveni'
        ReadOnly = True
        Title.Caption = 'Datum Vystavení'
        Width = 88
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'Zdaneni'
        ReadOnly = True
        Title.Caption = 'Daum Zdanìní'
        Width = 82
        Visible = True
      end>
  end
  object GroupBoxFakt: TGroupBox
    Left = 445
    Top = 300
    Width = 251
    Height = 111
    Caption = 'Faktury'
    TabOrder = 2
    object StornoBtn: TButton
      Left = 30
      Top = 75
      Width = 86
      Height = 25
      Caption = 'Zpìt'
      TabOrder = 0
      OnClick = StornoBtnClick
    end
    object ZobrazitBtn: TButton
      Left = 130
      Top = 75
      Width = 90
      Height = 25
      Caption = 'Zobrazit položky'
      TabOrder = 1
      OnClick = ZobrazitBtnClick
    end
    object DBNavigator2: TDBNavigator
      Left = 31
      Top = 20
      Width = 192
      Height = 36
      DataSource = Databaze.DataSourceFakt
      VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast]
      TabOrder = 2
    end
  end
  object GroupBoxOdb: TGroupBox
    Left = 445
    Top = 220
    Width = 251
    Height = 71
    Caption = 'Odbìratel'
    TabOrder = 3
    object DBNavigator1: TDBNavigator
      Left = 31
      Top = 20
      Width = 192
      Height = 41
      DataSource = Databaze.DataSourceOdb
      VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast]
      TabOrder = 0
    end
  end
end
