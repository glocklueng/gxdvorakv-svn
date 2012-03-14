 #include <vcl.h>
#include "polozkyUnit.h"
#include "data.h"
#include "mainUnit.h"
#include <Printers.hpp>

#define offsetY_1  76
#define offsetY_x  26
#define distance  4.1

#define pol_1_min  35
#define pol_1_max  45

#define pol_x_min  50
#define pol_x_max  60

//namespace prn= Prntr->Canvas;
void __fastcall makeNewPage(TCanvas* canvas, double zoomx, double zoomy ,int pageNumber,int fakturaCislo);
void __fastcall printFooter(TCanvas* canvas,double zoomx, double zoomy );


//------------------------------------------------------------------------------

void __fastcall tisk(long aCisloFaktury)
{
 //  Databaze->TablePol->Edit();

   TLocateOptions Opts;
   Opts.Clear();
   Opts << loPartialKey;

   Databaze->TableDod->Active=true;
   Databaze->TableDod->First();

   Databaze->TablePol->Active=true;
   Databaze->TableFakt->Active=true;
   Databaze->TableFakt->Locate("Cislo", aCisloFaktury,Opts);

   int faktura_cislo=aCisloFaktury;
   String faktura_dat_splt=Databaze->TableFakt->FieldByName("Splatnost")->AsString;
   String faktura_dat_vyst=Databaze->TableFakt->FieldByName("Vystaveni")->AsString;
   String faktura_dat_zdan=Databaze->TableFakt->FieldByName("Zdaneni")->AsString;
   String objednavkaCislo = Databaze->TableFakt->FieldByName("CisloObjednavky")->AsString;

   String dodavatel =  Databaze->TableDod->FieldByName("Nazev")->AsString;
   String dodavatel_adresa = Databaze->TableDod->FieldByName("Adresa")->AsString;
   String dodavatel_telefon= Databaze->TableDod->FieldByName("Telefon")->AsString;
   String dodavatel_mobil= Databaze->TableDod->FieldByName("Mobil")->AsString;
   String dodavatel_ICO= Databaze->TableDod->FieldByName("ICO")->AsString;
   String dodavatel_DIC= Databaze->TableDod->FieldByName("DIC")->AsString;
   String dodavatel_ucet= Databaze->TableDod->FieldByName("CisloUctu")->AsString;

   int id_odb= Databaze->TableFakt->FieldByName("IdOdberatele")->AsInteger;
   Databaze->TableOdb->Active=true;
   Databaze->TableOdb->Locate("Id",id_odb,Opts);

   String odberatel=Databaze->TableOdb->FieldByName("Firma")->AsString;
   String odberatel_2=Databaze->TableOdb->FieldByName("Firma2")->AsString;
   String odberatel_adresa=Databaze->TableOdb->FieldByName("Adresa")->AsString;
   String odberatel_ICO=Databaze->TableOdb->FieldByName("ICO")->AsString;
   String odberatel_DIC=Databaze->TableOdb->FieldByName("DIC")->AsString;




   TPrinter* Prntr = Printer();
   TCanvas* canvas = Prntr->Canvas;

  // Prntr->Abort();
   Prntr->BeginDoc();

   double zoomx = GetDeviceCaps(canvas->Handle,LOGPIXELSX)/25.4;
   double zoomy =GetDeviceCaps(canvas->Handle,LOGPIXELSY)/25.4;



   canvas->Pen->Width=3;
   // dodavatel
   canvas->Rectangle(10*zoomx,14*zoomy,105*zoomx,63*zoomy);
   canvas->MoveTo(10*zoomx,53*zoomy);
   canvas->LineTo(105*zoomx,53*zoomy);
   // datumy
   canvas->Rectangle(105*zoomx,44*zoomy,200*zoomx,63*zoomy);
   // cara pod hlavickou
   canvas->MoveTo(10*zoomx,74*zoomy);
   canvas->LineTo(200*zoomx,74*zoomy);
   // odberatel
   canvas->Pen->Width=10;
   canvas->Rectangle(105*zoomx,14*zoomy,200*zoomx,44*zoomy);


   canvas->Font->Style=TFontStyles()<< fsBold;
   canvas->Font->Size=12;
   canvas->Font->Name=("Arial");
   canvas->TextOut(10*zoomx,7*zoomy,"FAKTURA - DAÒOVÝ DOKLAD");
   canvas->TextOut(180*zoomx,7*zoomy,IntToStr(faktura_cislo));
   canvas->TextOut(39*zoomx,20*zoomy,dodavatel);

   canvas->Font->Style =TFontStyles();
   canvas->TextOut(125*zoomx,19*zoomy,odberatel);

   canvas->Font->Size=10;
   canvas->Font->Style =TFontStyles();
   canvas->TextOut(99*zoomx,8*zoomy,"Obj. èíslo: "+objednavkaCislo);
   canvas->TextOut(157*zoomx,8*zoomy,"Faktura èíslo:");
   canvas->TextOut(25*zoomx,29*zoomy,dodavatel_adresa);
   canvas->TextOut(25*zoomx,38*zoomy,dodavatel_telefon);
   canvas->TextOut(25*zoomx,43*zoomy,dodavatel_mobil);
   canvas->TextOut(25*zoomx,48*zoomy,dodavatel_ICO);
   canvas->TextOut(65*zoomx,48*zoomy,dodavatel_DIC);
   canvas->TextOut(32*zoomx,57*zoomy,dodavatel_ucet);

   canvas->TextOut(125*zoomx,26*zoomy,odberatel_2);
   canvas->TextOut(125*zoomx,32*zoomy,odberatel_adresa);
   canvas->TextOut(118*zoomx,39*zoomy,odberatel_ICO);
   canvas->TextOut(156*zoomx,39*zoomy,odberatel_DIC);

   canvas->TextOut(175*zoomx,48*zoomy,faktura_dat_splt);
   canvas->TextOut(175*zoomx,53*zoomy,faktura_dat_vyst);
   canvas->TextOut(175*zoomx,58*zoomy,faktura_dat_zdan);

   canvas->Font->Style =TFontStyles();
   canvas->Font->Size=9;
   canvas->TextOut(12*zoomx,14.5*zoomy,"Dodavatel:");
   canvas->TextOut(108*zoomx,14.5*zoomy,"Odbìratel:");
   canvas->TextOut(12*zoomx,38.3*zoomy,"Telefon:");
   canvas->TextOut(12*zoomx,43*zoomy,"Mobil:");
   canvas->TextOut(12*zoomx,48*zoomy,"IÈO:");
   canvas->TextOut(54*zoomx,48*zoomy,"DIÈ:");
   canvas->TextOut(12*zoomx,57*zoomy,"Èíslo úètu:");
   canvas->TextOut(109*zoomx,39*zoomy,"IÈO:");
   canvas->TextOut(147*zoomx,39*zoomy,"DIÈ:");

   String tmp =  "Datum splatnosti:";
   int width = canvas->TextWidth(tmp);
   canvas->TextOut(167*zoomx-width,47*zoomy,tmp);
   tmp =  "Datum vystavení dokladu:";
   width = canvas->TextWidth(tmp);
   canvas->TextOut(167*zoomx-width,52*zoomy,tmp);
   tmp =  "Datum uskuteènìní zdanitelného plnìní:";
   width = canvas->TextWidth(tmp);
   canvas->TextOut(167*zoomx-width,57*zoomy,tmp);

   canvas->TextOut(12*zoomx,70*zoomy,"Oznaèení dodávky");
   canvas->TextOut(102*zoomx,70*zoomy,"Poèet jednotek");
   canvas->TextOut(129*zoomx,70*zoomy,"Cena za jednotku");
   canvas->TextOut(165*zoomx,70*zoomy,"Èástka");
   canvas->TextOut(192*zoomx,70*zoomy,"DPH");

   canvas->TextOut(75*zoomx,8*zoomy,"strana 1");
   int pocetStran;
   int pocetPolozek = Databaze->TablePol->RecordCount;
   int zbytekPol = pocetPolozek;


   canvas->Font->Size=10;
   canvas->Font->Style =TFontStyles();
   Databaze->TablePol->FindFirst();

   int i=0;
   int pageNumber=1;
   float posY;
   float sazbaDPH;

   double sumaCeny = 0;
   double sumaDPH = 0;

   bool eot;
   do {

      if (pageNumber==1){
         switch (i){
            case pol_1_min:
               if (zbytekPol < 10){
                  // rovnou skocit na dalsi stranu
                  i=0;
                  pageNumber++;
                  printFooter(canvas,zoomx,zoomy);
                  Prntr->NewPage();
                  makeNewPage(canvas,zoomx,zoomy,pageNumber,faktura_cislo);
               }else {
                  // pokracovat az na 45 a pak dalsi strana
               }
               break;
            case pol_1_max:
               i=0;
               pageNumber++;
               printFooter(canvas,zoomx,zoomy);
               Prntr->NewPage();
               makeNewPage(canvas,zoomx,zoomy,pageNumber,faktura_cislo);
               break;
         }
      }else {
            switch (i){
            case pol_x_min:
               if (zbytekPol < 10){
                  // rovnou skocit na dalsi stranu
                  i=0;
                  pageNumber++;
                  printFooter(canvas,zoomx,zoomy);
                  Prntr->NewPage();
                  makeNewPage(canvas,zoomx,zoomy,pageNumber,faktura_cislo);
               }else {
                // pokracovat az na 60 a pak dalsi strana
               }
               break;
            case pol_x_max:
                  i=0;
                  pageNumber++;
                  printFooter(canvas,zoomx,zoomy);
                  Prntr->NewPage();
                  makeNewPage(canvas,zoomx,zoomy,pageNumber,faktura_cislo);
               break;
         }

      }
      if (pageNumber==1){
          posY= i*distance+ offsetY_1;
      }else {
          posY= i*distance+ offsetY_x;
      }

//    int cislo =Databaze->TablePol->FieldByName("CisloPolozky")->AsInteger;
      String jmeno=  Databaze->TablePol->FieldByName("Nazev")->AsString;
      float pocet =Databaze->TablePol->FieldByName("PocetJednotek")->AsFloat;
      String typ=  Databaze->TablePol->FieldByName("TypJednotky")->AsString;
      float cenaJ =Databaze->TablePol->FieldByName("CenaJednotky")->AsFloat;
      sazbaDPH =Databaze->TablePol->FieldByName("SazbaDPH")->AsFloat;
      float cenaCelkem = cenaJ*pocet;
      float dph = cenaCelkem * sazbaDPH/(100+sazbaDPH);

      sumaCeny+=cenaCelkem;
      sumaDPH+=dph;

      canvas->TextOut(12*zoomx,posY*zoomy,jmeno);
      // pocet
      tmp= FloatToStr(pocet)+" "+typ;
      width = canvas->TextWidth(tmp);
      canvas->TextOut(120*zoomx-width,posY*zoomy,tmp);
      // cena jednotky
      tmp = FloatToStrF(cenaJ,ffCurrency,15,2);
      width = canvas->TextWidth(tmp);
      canvas->TextOut(147*zoomx-width,posY*zoomy,tmp);
      // cena celkem
      tmp = FloatToStrF(cenaCelkem,ffCurrency,15,2);
      width = canvas->TextWidth(tmp);
      canvas->TextOut(177*zoomx-width,posY*zoomy,tmp);
      // dph
      tmp = FloatToStrF(dph,ffCurrency,15,2);
      width = canvas->TextWidth(tmp);
      canvas->TextOut(200*zoomx-width,posY*zoomy,tmp);

      eot=Databaze->TablePol->FindNext();
      i++;
   } while (eot);

   // razitko
   canvas->Pen->Style=psDot;
   canvas->Pen->Width=1;
   canvas->MoveTo(122*zoomx,268*zoomy);
   canvas->LineTo(185*zoomx,268*zoomy);
  // souhrn
   canvas->Pen->Width=3;
   canvas->Rectangle(100*zoomx,225*zoomy,185*zoomx,249*zoomy);
   canvas->MoveTo(100*zoomx,233*zoomy);
   canvas->LineTo(185*zoomx,233*zoomy);
   canvas->MoveTo(100*zoomx,241*zoomy);
   canvas->LineTo(185*zoomx,241*zoomy);
   canvas->MoveTo(151*zoomx,225*zoomy);
   canvas->LineTo(151*zoomx,249*zoomy);
   canvas->Pen->Width=10;
   canvas->Rectangle(151*zoomx,241*zoomy,185*zoomx,249*zoomy);

   canvas->Pen->Width=1;
   canvas->Font->Size=12;
   canvas->Font->Style=TFontStyles();
   canvas->TextOut(104*zoomx,227*zoomy,"Cena celkem bez DPH");
   canvas->TextOut(104*zoomx,235*zoomy,"DPH 19 %");
   canvas->TextOut(104*zoomx,243*zoomy,"Celkem k úhradì");
   canvas->Font->Style=TFontStyles();
   // vyplneni souhrnu
   // cena bez dph
   float cenaBezDPH = sumaCeny*100/(100+sazbaDPH);
   tmp = FloatToStrF(cenaBezDPH,ffCurrency,15,2);
   width = canvas->TextWidth(tmp);
   canvas->TextOut(182*zoomx-width,227*zoomy,tmp);
   //dph
   tmp = FloatToStrF(sumaDPH,ffCurrency,15,2);
   width = canvas->TextWidth(tmp);
   canvas->TextOut(182*zoomx-width,235*zoomy,tmp);
   // cekem k uhrade
   tmp = FloatToStrF(sumaCeny,ffCurrency,15,2);
   width = canvas->TextWidth(tmp);
   canvas->TextOut(182*zoomx-width,243*zoomy,tmp);


   canvas->Font->Style=TFontStyles();
   canvas->Font->Size=10;
   canvas->TextOut(132*zoomx,270*zoomy,"Razítko a podpis dodavatele");
   canvas->TextOut(17*zoomx,270*zoomy,"Vystavil:  Josef ŠTOLBA");

   canvas->Font->Size=8;
   canvas->Font->Style =TFontStyles()<<fsBold;
   String poznamka=Databaze->TableDod->FieldByName("Poznamka")->AsString;
   String tmpPoznamka;
   int pos1,pos2;
   tmpPoznamka = poznamka.SubString(0,(pos1=poznamka.AnsiPos("\n"))-2);
   canvas->TextOut(17*zoomx,276*zoomy,tmpPoznamka);
   poznamka=poznamka.SubString(pos1+1,poznamka.Length()-pos1);

   tmpPoznamka = poznamka.SubString(0,(pos1=poznamka.AnsiPos("\n"))-2);
   poznamka=poznamka.SubString(pos1+1,poznamka.Length()-pos1);
   canvas->TextOut(17*zoomx,279*zoomy,tmpPoznamka);

   tmpPoznamka = poznamka.SubString(0,poznamka.Length()-pos1);
   canvas->TextOut(17*zoomx,282*zoomy,tmpPoznamka);

   Prntr->EndDoc();
}

//------------------------------------------------------------------------------

void __fastcall printFooter(TCanvas* canvas,double zoomx, double zoomy )
{
   canvas->TextOut(70*zoomx,274*zoomy,"Pokraèování na následující stranì");
}

//------------------------------------------------------------------------------

void __fastcall makeNewPage(TCanvas* canvas, double zoomx, double zoomy ,int pageNumber,int fakturaCislo )
{
   canvas->Font->Style=TFontStyles()<< fsBold;
   canvas->Font->Size=12;
   canvas->Font->Name=("Arial");
   canvas->TextOut(10*zoomx,7*zoomy,"FAKTURA - DAÒOVÝ DOKLAD");
   canvas->TextOut(180*zoomx,7*zoomy,IntToStr(fakturaCislo));
   canvas->Font->Size=10;
   canvas->Font->Style =TFontStyles();
   canvas->TextOut(157*zoomx,8*zoomy,"Faktura èíslo:");
   canvas->TextOut(75*zoomx,8*zoomy,"strana "+IntToStr(pageNumber));

   // cara pod hlavickou
   canvas->Pen->Width=3;
   canvas->MoveTo(10*zoomx,24*zoomy);
   canvas->LineTo(200*zoomx,24*zoomy);


   //
   canvas->TextOut(12*zoomx,20*zoomy,"Oznaèení dodávky");
   canvas->TextOut(102*zoomx,20*zoomy,"Poèet jednotek");
   canvas->TextOut(129*zoomx,20*zoomy,"Cena za jednotku");
   canvas->TextOut(165*zoomx,20*zoomy,"Èástka");
   canvas->TextOut(192*zoomx,20*zoomy,"DPH");



}
