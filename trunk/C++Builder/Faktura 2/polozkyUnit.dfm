object PolozkyForm: TPolozkyForm
  Left = 240
  Top = 109
  Width = 706
  Height = 636
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  Caption = 'Polo'#382'ky faktury'
  Color = clBtnFace
  Constraints.MinHeight = 300
  Constraints.MinWidth = 703
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnResize = FormResize
  OnShow = FormShow
  DesignSize = (
    698
    602)
  PixelsPerInch = 96
  TextHeight = 13
  object DBGridPolozky: TDBGrid
    Left = 0
    Top = 204
    Width = 697
    Height = 397
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = Databaze.DataSourcePol
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'IdPolozky'
        ReadOnly = True
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'CisloFaktury'
        ReadOnly = True
        Title.Caption = #268#237's.Fakt.'
        Width = 48
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'CisloPolozky'
        ReadOnly = True
        Title.Caption = #268#237'slo'
        Width = 29
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'SazbaDPH'
        ReadOnly = True
        Title.Caption = 'Sazba DPH'
        Width = 61
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Nazev'
        Title.Caption = 'N'#225'zev'
        Width = 234
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'PocetJednotek'
        Title.Caption = 'Mno'#382'stv'#237
        Width = 48
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'TypJednotky'
        PopupMenu = PopupMenu1
        Title.Caption = 'Typ'
        Width = 23
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'CenaJednotky'
        Title.Caption = 'Cena Jednotky'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'CenaCelkem'
        Title.Caption = 'Cena Celkem'
        Width = 64
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'DPHCelkem'
        Title.Caption = 'DPH Celkem'
        Width = 68
        Visible = True
      end>
  end
  object GroupBoxFaktury: TGroupBox
    Left = 0
    Top = 76
    Width = 698
    Height = 128
    Anchors = [akLeft, akTop, akRight]
    Caption = 'Faktury'
    TabOrder = 2
    object DBGridFaktury: TDBGrid
      Left = 2
      Top = 15
      Width = 694
      Height = 111
      Align = alClient
      DataSource = Databaze.DataSourceFakt
      TabOrder = 0
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
          Title.Caption = #268#237'slo Faktury'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'CisloObjednavky'
          Title.Caption = #268'. Objedn'#225'vky'
          Width = 77
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'IdOdberatele'
          ReadOnly = True
          Title.Caption = #268'. Odb.'
          Width = 42
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'OdbratelName'
          Title.Caption = 'Odb'#283'ratel'
          Width = 270
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'Splatnost'
          Title.Caption = 'D. Splatnosti'
          Width = 68
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'Vystaveni'
          Title.Caption = 'D. Vystaven'#237
          Width = 72
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'Zdaneni'
          Title.Caption = 'D. Zdan'#283'n'#237
          Width = 61
          Visible = True
        end>
    end
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 698
    Height = 76
    Align = alTop
    TabOrder = 1
    object CisloFakturyLabel: TLabel
      Left = 120
      Top = 14
      Width = 70
      Height = 24
      Caption = '2004001'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label1: TLabel
      Left = 5
      Top = 16
      Width = 101
      Height = 20
      Caption = #268#237'slo faktury :'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 32
      Top = 40
      Width = 74
      Height = 13
      Caption = 'Po'#269'et polo'#382'ek :'
    end
    object pocetPolozek: TLabel
      Left = 120
      Top = 40
      Width = 65
      Height = 13
      Caption = 'pocetPolozek'
    end
    object Label4: TLabel
      Left = 38
      Top = 56
      Width = 68
      Height = 13
      Caption = 'Cena celkem :'
    end
    object cenaCelkem: TLabel
      Left = 120
      Top = 56
      Width = 59
      Height = 13
      Caption = 'cenaCelkem'
    end
    object KonecBtn: TButton
      Left = 610
      Top = 11
      Width = 81
      Height = 60
      Caption = 'Konec'
      TabOrder = 0
      OnClick = KonecBtnClick
    end
    object DBNavigator1: TDBNavigator
      Left = 240
      Top = 11
      Width = 276
      Height = 60
      DataSource = Databaze.DataSourcePol
      VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast]
      TabOrder = 1
    end
    object EditBtn: TButton
      Left = 525
      Top = 11
      Width = 75
      Height = 60
      Caption = 'Edit'
      TabOrder = 2
      OnClick = EditBtnClick
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 200
    Top = 24
    object kg1: TMenuItem
      Caption = 'kg'
      OnClick = kg1Click
    end
    object ks1: TMenuItem
      Caption = 'ks'
      OnClick = ks1Click
    end
    object m: TMenuItem
      Caption = 'm'
      OnClick = mClick
    end
  end
end
