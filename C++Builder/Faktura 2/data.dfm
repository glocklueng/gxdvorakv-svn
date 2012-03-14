object Databaze: TDatabaze
  OldCreateOrder = False
  Left = 144
  Top = 788
  Height = 187
  Width = 453
  object TableDod: TTable
    TableName = 'dodavatel.DB'
    Left = 28
    Top = 12
    object TableDodId: TSmallintField
      FieldName = 'Id'
      Required = True
    end
    object TableDodNazev: TStringField
      DisplayWidth = 30
      FieldName = 'Nazev'
      Size = 30
    end
    object TableDodAdresa: TStringField
      FieldName = 'Adresa'
      Size = 30
    end
    object TableDodTelefon: TStringField
      FieldName = 'Telefon'
      Size = 15
    end
    object TableDodMobil: TStringField
      FieldName = 'Mobil'
      Size = 32
    end
    object TableDodICO: TStringField
      FieldName = 'ICO'
      Size = 9
    end
    object TableDodDIC: TStringField
      FieldName = 'DIC'
      Size = 11
    end
    object TableDodCisloUctu: TStringField
      FieldName = 'CisloUctu'
      Size = 30
    end
    object TableDodPoznamka: TStringField
      FieldName = 'Poznamka'
      Size = 255
    end
  end
  object TableOdb: TTable
    FieldDefs = <
      item
        Name = 'Id'
        Attributes = [faReadonly]
        DataType = ftAutoInc
      end
      item
        Name = 'Firma'
        DataType = ftString
        Size = 30
      end
      item
        Name = 'Firma2'
        DataType = ftString
        Size = 30
      end
      item
        Name = 'Adresa'
        DataType = ftString
        Size = 30
      end
      item
        Name = 'ICO'
        DataType = ftString
        Size = 9
      end
      item
        Name = 'DIC'
        DataType = ftString
        Size = 11
      end
      item
        Name = 'Telefon'
        DataType = ftString
        Size = 30
      end
      item
        Name = 'Mobil'
        DataType = ftString
        Size = 17
      end>
    IndexDefs = <
      item
        Name = 'TableOdbIndex1'
        Fields = 'Id'
        Options = [ixPrimary, ixUnique]
      end
      item
        Name = 'firmName'
        Fields = 'Firma'
        Options = [ixCaseInsensitive]
      end>
    StoreDefs = True
    TableName = 'odberatel.DB'
    Left = 144
    Top = 8
    object TableOdbId: TSmallintField
      FieldName = 'Id'
      Required = True
    end
    object TableOdbFirma: TStringField
      FieldName = 'Firma'
      Size = 30
    end
    object TableOdbFirma2: TStringField
      FieldName = 'Firma2'
      Size = 30
    end
    object TableOdbAdresa: TStringField
      FieldName = 'Adresa'
      Size = 60
    end
    object TableOdbICO: TStringField
      FieldName = 'ICO'
      Size = 9
    end
    object TableOdbDIC: TStringField
      FieldName = 'DIC'
      Size = 11
    end
    object TableOdbTelefon: TStringField
      FieldName = 'Telefon'
      Size = 30
    end
    object TableOdbMobil: TStringField
      FieldName = 'Mobil'
      Size = 17
    end
  end
  object TableFakt: TTable
    AfterScroll = TableFaktAfterScroll
    FieldDefs = <
      item
        Name = 'Cislo'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'IdOdberatele'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'CisloObjednavky'
        DataType = ftString
        Size = 20
      end
      item
        Name = 'Splatnost'
        DataType = ftDate
      end
      item
        Name = 'Vystaveni'
        DataType = ftDate
      end
      item
        Name = 'Zdaneni'
        DataType = ftDate
      end>
    IndexDefs = <
      item
        Name = 'TableFaktIndex1'
        Fields = 'Cislo'
        Options = [ixPrimary, ixUnique]
      end>
    StoreDefs = True
    TableName = 'faktury.DB'
    Left = 272
    Top = 12
    object TableFaktCislo: TIntegerField
      FieldName = 'Cislo'
      Required = True
    end
    object TableFaktIdOdberatele: TSmallintField
      FieldName = 'IdOdberatele'
      Required = True
    end
    object TableFaktCisloObjednavky: TStringField
      DisplayWidth = 20
      FieldName = 'CisloObjednavky'
    end
    object TableFaktSplatnost: TDateField
      FieldName = 'Splatnost'
    end
    object TableFaktVystaveni: TDateField
      FieldName = 'Vystaveni'
    end
    object TableFaktZdaneni: TDateField
      FieldName = 'Zdaneni'
    end
    object TableFaktOdbratelName: TStringField
      FieldKind = fkLookup
      FieldName = 'OdbratelName'
      LookupDataSet = TableOdb
      LookupKeyFields = 'Id'
      LookupResultField = 'Firma'
      KeyFields = 'IdOdberatele'
      Lookup = True
    end
  end
  object TablePol: TTable
    BeforeInsert = TablePolBeforeInsert
    AfterEdit = TablePolAfterEdit
    AfterCancel = TablePolAfterCancel
    OnCalcFields = TablePolCalcFields
    OnNewRecord = TablePolNewRecord
    AutoRefresh = True
    Constraints = <
      item
        FromDictionary = True
      end>
    FieldDefs = <
      item
        Name = 'IdPolozky'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'CisloFaktury'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'CisloPolozky'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'Nazev'
        DataType = ftString
        Size = 45
      end
      item
        Name = 'PocetJednotek'
        Attributes = [faRequired]
        DataType = ftFloat
      end
      item
        Name = 'TypJednotky'
        DataType = ftString
        Size = 2
      end
      item
        Name = 'CenaJednotky'
        Attributes = [faRequired]
        DataType = ftFloat
      end
      item
        Name = 'SazbaDPH'
        Attributes = [faRequired]
        DataType = ftFloat
      end>
    IndexDefs = <
      item
        Name = 'TablePolIndex1'
        Fields = 'IdPolozky'
        Options = [ixPrimary, ixUnique]
      end
      item
        Name = 'FakturaCislo'
        Fields = 'CisloFaktury'
        Options = [ixCaseInsensitive]
      end>
    IndexName = 'FakturaCislo'
    MasterFields = 'Cislo'
    MasterSource = DataSourceFakt
    StoreDefs = True
    TableName = 'polozky.DB'
    Left = 368
    Top = 8
    object TablePolIdPolozky: TSmallintField
      FieldName = 'IdPolozky'
    end
    object TablePolCisloFaktury: TIntegerField
      FieldName = 'CisloFaktury'
      Required = True
    end
    object TablePolCisloPolozky: TSmallintField
      FieldName = 'CisloPolozky'
      Required = True
    end
    object TablePolNazev: TStringField
      DisplayWidth = 45
      FieldName = 'Nazev'
      Size = 45
    end
    object TablePolPocetJednotek: TFloatField
      FieldName = 'PocetJednotek'
      Required = True
    end
    object TablePolTypJednotky: TStringField
      FieldName = 'TypJednotky'
      OnChange = TablePolTypJednotkyChange
      Size = 2
    end
    object TablePolCenaJednotky: TFloatField
      DisplayWidth = 10
      FieldName = 'CenaJednotky'
      Required = True
      currency = True
      Precision = 8
    end
    object TablePolSazbaDPH: TFloatField
      FieldName = 'SazbaDPH'
      ProviderFlags = [pfInWhere]
      Required = True
      Precision = 4
    end
    object TablePolCenaCelkem: TCurrencyField
      FieldKind = fkCalculated
      FieldName = 'CenaCelkem'
      ReadOnly = True
      Calculated = True
    end
    object TablePolDPHCelkem: TFloatField
      FieldKind = fkCalculated
      FieldName = 'DPHCelkem'
      ReadOnly = True
      currency = True
      Calculated = True
    end
  end
  object DataSourceDod: TDataSource
    DataSet = TableDod
    Left = 32
    Top = 84
  end
  object DataSourceOdb: TDataSource
    AutoEdit = False
    DataSet = TableOdb
    Left = 144
    Top = 88
  end
  object DataSourceFakt: TDataSource
    DataSet = TableFakt
    Left = 272
    Top = 88
  end
  object DataSourcePol: TDataSource
    DataSet = TablePol
    Left = 376
    Top = 88
  end
end
