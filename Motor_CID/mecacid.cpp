#include "mecacid.h"
#include "mecacid_model.h"
#include "calibracion_teclado.h"
#include "mapa_teclas_cid.h"
#include "teclado_cid.h"
#include "superposicion_cid.h"
#include <windowsx.h>
#include <shlobj.h>
#include <algorithm>
#include <array>
#include <fstream>
#include <filesystem>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#pragma comment(lib, "Shell32.lib")

namespace {
constexpr int VW = 1280, VH = 840;
constexpr UINT TimerAcorde = 41, TimerReloj = 42;
constexpr int NavAprender=100, NavTraductor=101, NavProgreso=102;
constexpr int NivelBase=110, Iniciar=120, Siguiente=121, Pista=122, AnteriorPaso=123, ProximoPaso=124, Traducir=125, Entrada=126;
constexpr COLORREF Fondo=RGB(244,247,246), Tinta=RGB(26,46,46), Suave=RGB(102,120,117), Verde=RGB(15,116,91), Menta=RGB(220,244,233), Borde=RGB(224,232,227), Blanco=RGB(255,255,255), Rojo=RGB(175,55,55);
struct TeclaVisual { const wchar_t* nombre; int x, y; };
const TeclaVisual Teclas[] = {
 {L"I1",292,477},{L"I2",357,477},{L"I3",422,477},{L"C1",487,477},{L"C2",552,477},{L"D1",617,477},{L"D2",682,477},{L"D3",747,477},
 {L"I4",310,529},{L"I5",375,529},{L"I6",440,529},{L"C3",505,529},{L"D4",570,529},{L"D5",635,529},{L"D6",700,529},
 {L"I7",326,581},{L"I8",391,581},{L"C4",456,581},{L"C5",521,581},{L"D7",586,581},{L"D8",651,581},
 {L"I9",343,633},{L"I10",408,633},{L"C6",473,633},{L"D9",538,633},{L"D10",603,633}
};
struct EstadoMeca {
 HINSTANCE instancia=nullptr; HWND ventana=nullptr, entrada=nullptr;
 std::unique_ptr<MecaModelo> modelo;
 std::map<int,HWND> controles;
 HFONT fuenteControles=nullptr;
 int vista=0, nivel=0; size_t turno=0, paso=0, paginaProgreso=0;
 MecaPlan plan;
 bool activo=false, pista=true, ventanaAcorde=false, esperandoSoltar=false, espacioAbajo=false, demo=false, explorando=false;
 std::set<std::wstring> abajo, acorde;
 std::wstring feedback=L"Empieza sin prisa. Aquí puedes equivocarte: no se escribe en otras aplicaciones.";
 std::wstring escrito, literal, rutaProgreso;
 bool error=false, guardadoCorrecto=true;
 unsigned aciertos=0, errores=0, racha=0, mejorRacha=0, ejercicios=0, acordesCorrectos=0;
 ULONGLONG inicio=0, tiempo=0;
 std::map<std::wstring,MecaMarca> marcas;
};
EstadoMeca g;
RECT R(int x,int y,int w,int h){ return RECT{x,y,x+w,y+h}; }
HFONT Fuente(int alto,int peso=FW_NORMAL){ return CreateFontW(-alto,0,0,0,peso,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,DEFAULT_PITCH,L"Segoe UI"); }
void Caja(HDC dc,RECT r,COLORREF color,int radio=16,COLORREF linea=CLR_INVALID)
{
 HBRUSH b=CreateSolidBrush(color); HPEN p=CreatePen(PS_SOLID,1,linea==CLR_INVALID?color:linea);
 auto ob=SelectObject(dc,b); auto op=SelectObject(dc,p);
 RoundRect(dc,r.left,r.top,r.right,r.bottom,radio,radio);
 SelectObject(dc,ob); SelectObject(dc,op); DeleteObject(b); DeleteObject(p);
}
void Texto(HDC dc,const std::wstring& t,RECT r,int tam=16,COLORREF color=Tinta,int peso=FW_NORMAL,UINT flags=DT_LEFT|DT_TOP|DT_WORDBREAK)
{
 auto f=Fuente(tam,peso);auto old=SelectObject(dc,f);SetBkMode(dc,TRANSPARENT);SetTextColor(dc,color);
 DrawTextW(dc,t.c_str(),static_cast<int>(t.size()),&r,flags|DT_NOPREFIX);
 SelectObject(dc,old);DeleteObject(f);
}
void Invalidar(){ if(g.ventana) InvalidateRect(g.ventana,nullptr,FALSE); }
const MecaPaso* Actual(){ return g.paso<g.plan.pasos.size()?&g.plan.pasos[g.paso]:nullptr; }
std::wstring Numero(size_t n){return std::to_wstring(n);}
void LimpiarCaptura()
{
 if(g.ventana)KillTimer(g.ventana,TimerAcorde);
 g.ventanaAcorde=false;g.esperandoSoltar=false;g.espacioAbajo=false;g.abajo.clear();g.acorde.clear();
}
void Pausar()
{
 if(g.activo && g.inicio)g.tiempo+=GetTickCount64()-g.inicio;
 g.inicio=0;g.activo=false;LimpiarCaptura();
 if(g.controles.count(Iniciar))SetWindowTextW(g.controles[Iniciar],L"Empezar / continuar");
 Invalidar();
}
std::wstring EtiquetaFisica(const std::wstring& nombre)
{
 if(nombre==L"ESPACIO")return L"Espacio";
 DWORD sc=0;if(!ObtenerScanCodeDeNombreCID(nombre.c_str(),sc))return L"Sin asignar";
 wchar_t etiqueta[64]{};
 if(GetKeyNameTextW(static_cast<LONG>(sc<<16),etiqueta,64)>0)return etiqueta;
 return L"SC "+Numero(sc);
}
std::wstring CombinacionFisica(const std::wstring& acorde)
{
 if(acorde==L"ESPACIO")return L"Espacio";
 if(acorde==L"QWERTY")return L"Escritura convencional";
 std::wistringstream in(acorde);std::wstring token,out;
 while(std::getline(in,token,L'+')){if(!out.empty())out+=L" + ";out+=EtiquetaFisica(token);}return out;
}
std::set<std::wstring> Nombres(const std::wstring& s)
{
 std::set<std::wstring> out;std::wistringstream in(s);std::wstring p;
 while(std::getline(in,p,L'+'))out.insert(p);return out;
}
std::wstring Canonico(const std::set<std::wstring>& teclas)
{
 std::vector<std::wstring> v(teclas.begin(),teclas.end());
 std::sort(v.begin(),v.end(),[](const auto&a,const auto&b){return OrdenTeclaCID_PorNombre(a.c_str())<OrdenTeclaCID_PorNombre(b.c_str());});
 std::wstring out;for(auto& t:v){if(!out.empty())out+=L"+";out+=t;}return out;
}
void LeerProgreso()
{
 if(g.demo)return;
 wchar_t base[MAX_PATH]{};
 if(FAILED(SHGetFolderPathW(nullptr,CSIDL_LOCAL_APPDATA,nullptr,SHGFP_TYPE_CURRENT,base)))return;
 std::wstring carpeta=std::wstring(base)+L"\\MECACID";
 SHCreateDirectoryExW(nullptr,carpeta.c_str(),nullptr);g.rutaProgreso=carpeta+L"\\progreso-v1.txt";
 std::ifstream f{std::filesystem::path(g.rutaProgreso)};std::string key;unsigned a=0,e=0;
 while(f>>key>>a>>e)
 {
  if(a>1000000||e>1000000)continue;
  if(key=="EJERCICIOS"){g.ejercicios=a;continue;}
  if(key.size()>40||key.find_first_not_of("ICD0123456789+ESPACOQWRTY")!=std::string::npos)continue;
  g.marcas[std::wstring(key.begin(),key.end())]={a,e};
 }
}
void GuardarProgreso()
{
 if(g.demo)return;
 if(g.rutaProgreso.empty()){g.guardadoCorrecto=false;return;}
 const auto tmp=g.rutaProgreso+L".tmp";
 std::ofstream f(std::filesystem::path(tmp),std::ios::trunc);
 f<<"EJERCICIOS "<<g.ejercicios<<" 0\n";
 for(const auto& [k,v]:g.marcas){std::string key;for(wchar_t c:k)key.push_back(static_cast<char>(c));f<<key<<' '<<v.aciertos<<' '<<v.errores<<'\n';}
 f.close();g.guardadoCorrecto=static_cast<bool>(f)&&MoveFileExW(tmp.c_str(),g.rutaProgreso.c_str(),MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH);
 if(!g.guardadoCorrecto)DeleteFileW(tmp.c_str());
}
void CargarPlan(const std::wstring& texto)
{
 Pausar();g.plan=g.modelo->Traducir(texto);g.paso=0;g.explorando=false;g.escrito.clear();g.literal.clear();g.error=false;
 g.feedback=g.plan.pasos.empty()?(texto.size()>512?g.plan.aviso:L"Escribe una palabra o una frase para empezar."):L"Listo. Pulsa Empezar y forma el acorde que aparece en verde.";
 Invalidar();
}
void NuevoEjercicio(){ CargarPlan(g.modelo->Siguiente(g.nivel,g.marcas,g.turno++)); }
void Evaluar(const std::wstring& recibido)
{
 const auto* p=Actual();if(!g.activo||!p)return;
 if(recibido!=p->acorde)
 {
  ++g.errores;g.racha=0;++g.marcas[p->acorde].errores;g.error=true;
  g.feedback=L"Has pulsado "+recibido+L". Inténtalo otra vez: "+p->acorde+L" ("+CombinacionFisica(p->acorde)+L").";
  Invalidar();return;
 }
 ++g.aciertos;++g.racha;g.mejorRacha=(std::max)(g.mejorRacha,g.racha);++g.marcas[p->acorde].aciertos;
 if(p->tipo==MecaTipo::Acorde||p->tipo==MecaTipo::Modificador)++g.acordesCorrectos;
 if(p->tipo==MecaTipo::Asentar)g.escrito+=p->fragmento+L" ";
 if(p->tipo==MecaTipo::Qwerty)g.escrito+=p->fragmento;
 ++g.paso;g.literal.clear();g.error=false;
 if(!Actual())
 {
  ++g.ejercicios;Pausar();GuardarProgreso();
  g.feedback=L"Ejercicio completado. "+Numero(g.plan.pasos.size())+L" pasos: ya has construido «"+g.plan.normalizado+L"».";
 }
 else g.feedback=std::wstring(L"Bien. ")+(Actual()->tipo==MecaTipo::Asentar?L"Ahora pulsa y suelta Espacio para cerrar la palabra.":L"Suelta las teclas y continúa con el siguiente paso.");
 Invalidar();
}
void FinalizarAcorde()
{
 if(!g.ventanaAcorde)return;
 KillTimer(g.ventana,TimerAcorde);g.ventanaAcorde=false;
 const auto acorde=Canonico(g.acorde);g.acorde.clear();g.esperandoSoltar=!g.abajo.empty();
 if(!acorde.empty())Evaluar(acorde);
}
void CambiarVista(int vista);
void Distribuir();
void Dibujar(HDC dc)
{
 RECT client{};GetClientRect(g.ventana,&client);
 int save=SaveDC(dc);SetMapMode(dc,MM_ANISOTROPIC);SetWindowExtEx(dc,VW,VH,nullptr);SetViewportExtEx(dc,client.right,client.bottom,nullptr);
 Caja(dc,R(0,0,VW,VH),Fondo,0);Caja(dc,R(0,0,214,VH),RGB(23,47,44),0);
 Caja(dc,R(27,32,42,42),RGB(174,232,191),12);Texto(dc,L"M",R(27,37,42,34),27,RGB(23,47,44),FW_BOLD,DT_CENTER|DT_SINGLELINE);
 Texto(dc,L"MECACID",R(81,34,120,25),22,Blanco,FW_BOLD);Texto(dc,L"Tu taller de acordes",R(28,90,164,30),14,RGB(167,190,181));
 Texto(dc,L"ESCRIBIR SE APRENDE",R(28,139,168,20),10,RGB(148,174,164),FW_BOLD);
 Caja(dc,R(23,564,168,145),RGB(35,62,55),14);
 Texto(dc,L"De tecla a palabra",R(39,581,138,52),18,RGB(208,242,214),FW_SEMIBOLD);
 Texto(dc,L"Primero precisión.\nDespués ritmo.\nA tu velocidad.",R(39,640,133,60),14,RGB(181,208,196));
 Texto(dc,L"PRÁCTICA LOCAL",R(28,751,168,22),11,RGB(183,222,192),FW_BOLD);
 Texto(dc,L"CID externo en pausa.\nNada sale de esta ventana.",R(28,777,168,46),12,RGB(158,184,172));
 std::wstring ceja=g.vista==0?L"ENTRENAMIENTO / PASO A PASO":g.vista==1?L"TRADUCTOR / QWERTY → CID":L"TU PROGRESO / EN ESTE EQUIPO";
 Texto(dc,ceja,R(252,34,680,24),11,Verde,FW_BOLD);
 Texto(dc,g.vista==0?L"Aprende a escribir en CID.":g.vista==1?L"Tu texto, acorde a acorde.":L"Mira lo que ya sabes.",R(250,67,930,51),34,Tinta,FW_BOLD);
 Texto(dc,g.vista==0?L"Teclas, bloques, palabras y frases. Practica con tu diccionario y tu teclado.":g.vista==1?L"Descompón una frase y recórrela. Luego escríbela con las teclas reales.":L"Los errores sirven para elegir qué practicar después. No para castigarte.",R(252,120,946,32),15,Suave);
 Caja(dc,R(1023,30,215,28),Menta,14);Texto(dc,Numero(g.modelo->NumeroEntradas())+L" entradas · diccionario activo",R(1033,36,195,18),11,Verde,FW_SEMIBOLD,DT_CENTER|DT_SINGLELINE);
 if(g.vista==2)
 {
  unsigned totalA=0,totalE=0;size_t dominados=0;
  for(const auto&[k,v]:g.marcas){totalA+=v.aciertos;totalE+=v.errores;if(k!=L"ESPACIO"&&k!=L"QWERTY"&&v.aciertos>=5&&v.aciertos>=4*v.errores)++dominados;}
  const std::wstring valores[]={Numero(g.ejercicios),Numero(totalA),Numero(dominados)};
  const wchar_t* nombres[]={L"EJERCICIOS COMPLETADOS",L"PASOS CORRECTOS",L"ACORDES AFIANZADOS"};
  for(int i=0;i<3;++i){int x=252+i*332;Caja(dc,R(x,175,314,103),Blanco);Texto(dc,nombres[i],R(x+20,193,280,23),11,Suave,FW_BOLD);Texto(dc,valores[i],R(x+20,220,280,40),30,Tinta,FW_BOLD);}
  Caja(dc,R(252,300,978,436),Blanco);Texto(dc,L"Tu mapa de práctica",R(276,323,860,36),24,Tinta,FW_SEMIBOLD);
  Texto(dc,L"Un acorde se afianza con 5 aciertos y al menos un 80 % de precisión.",R(276,363,900,25),13,Suave);
  if(g.marcas.empty())
  {
   Texto(dc,L"Tu primera sesión empieza aquí.",R(320,461,835,46),29,Tinta,FW_SEMIBOLD,DT_CENTER|DT_SINGLELINE);
   Texto(dc,L"Completa un ejercicio. Tus acordes y errores aparecerán en este panel.",R(345,521,780,58),17,Suave,FW_NORMAL,DT_CENTER|DT_WORDBREAK);
  }
  else
  {
   std::vector<std::pair<std::wstring,MecaMarca>> rows(g.marcas.begin(),g.marcas.end());
   std::stable_sort(rows.begin(),rows.end(),[](const auto&a,const auto&b){return a.second.errores>b.second.errores;});
   const size_t desde=g.paginaProgreso*7;
   Texto(dc,Numero(desde+1)+L"–"+Numero((std::min)(desde+7,rows.size()))+L" de "+Numero(rows.size()),R(1000,327,194,24),12,Suave,FW_NORMAL,DT_RIGHT|DT_SINGLELINE);
   for(size_t i=desde;i<(std::min)(rows.size(),desde+7);++i)
   {
    auto&[key,v]=rows[i];int y=408+static_cast<int>(i-desde)*41;const unsigned t=v.aciertos+v.errores;int pct=t?static_cast<int>(100*v.aciertos/t):0;
    Texto(dc,key,R(279,y,228,26),15,Tinta,FW_SEMIBOLD);
    Caja(dc,R(528,y+7,320,8),Borde,8);if(pct)Caja(dc,R(528,y+7,320*pct/100,8),Verde,8);
    Texto(dc,Numero(pct)+L" %",R(876,y,78,25),14,Verde,FW_BOLD);
    Texto(dc,Numero(v.errores)+L" errores",R(1010,y,165,25),14,Suave);
   }
  }
  Texto(dc,g.guardadoCorrecto?L"Guardado automáticamente al completar y al cerrar. El repaso prioriza los acordes que más cuestan.":L"No se pudo guardar el progreso. Comprueba el espacio disponible y los permisos de tu cuenta.",R(257,758,953,44),14,g.guardadoCorrecto?Suave:Rojo);
  RestoreDC(dc,save);return;
 }
 if(g.vista==0)
 {
  unsigned total=g.aciertos+g.errores;auto dur=g.tiempo+(g.activo?GetTickCount64()-g.inicio:0);
  std::wstring vals[]={total?Numero(100*g.aciertos/total)+L" %":L"—",Numero(g.racha),dur>=1000?Numero(g.acordesCorrectos*60000/dur):L"—"};
  const wchar_t* labs[]={L"PRECISIÓN DE LA SESIÓN",L"RACHA ACTUAL",L"ACORDES / MINUTO"};
  for(int i=0;i<3;++i){int x=252+i*332;Caja(dc,R(x,221,314,70),Blanco,15);Texto(dc,labs[i],R(x+18,236,224,18),10,Suave,FW_BOLD);Texto(dc,vals[i],R(x+18,253,255,35),25,Tinta,FW_SEMIBOLD);}
 }
 else
 {
  Caja(dc,R(252,165,978,89),Blanco,15,Borde);
  Texto(dc,L"Hasta 512 caracteres. La guía normaliza mayúsculas y espacios;\nCID aplica su mayúscula inicial y deja un espacio al asentar.",R(255,262,742,40),12,Suave);
 }
 Caja(dc,R(252,310,623,408),Blanco,18);
 Caja(dc,R(897,310,333,408),Blanco,18);
 const auto* actual=Actual();
 std::wstring objetivo=actual?actual->tipo==MecaTipo::Asentar?actual->fragmento:actual->tipo==MecaTipo::Qwerty?actual->fragmento:actual->acumulado:L"¡Completado!";
 std::wstring meta;
 for(size_t i=g.paso;i<g.plan.pasos.size();++i){if(g.plan.pasos[i].tipo==MecaTipo::Asentar||g.plan.pasos[i].tipo==MecaTipo::Qwerty){meta=g.plan.pasos[i].fragmento;break;}}
 Texto(dc,meta.empty()?L"PRÁCTICA COMPLETADA":L"Objetivo: «"+meta+L"»",R(277,328,550,20),12,Suave,FW_SEMIBOLD,DT_SINGLELINE|DT_END_ELLIPSIS);
 Texto(dc,objetivo,R(277,354,573,51),objetivo.size()>25?25:36,Tinta,FW_SEMIBOLD,DT_SINGLELINE|DT_END_ELLIPSIS);
 std::wstring instruccion=actual?(g.pista?actual->acorde+L"   /   "+CombinacionFisica(actual->acorde):L"Recuerda el acorde. La pista está oculta."):L"Pulsa Siguiente ejercicio para continuar.";
 Texto(dc,instruccion,R(277,411,567,42),17,Verde,FW_SEMIBOLD);
 Texto(dc,L"TU TECLADO · POSICIONES CID",R(277,454,550,18),10,Suave,FW_BOLD);
 auto esperadas=actual&&g.pista?Nombres(actual->acorde):std::set<std::wstring>{};
 for(const auto& k:Teclas)
 {
  bool indicada=esperadas.count(k.nombre)!=0;bool pulsada=g.abajo.count(k.nombre)!=0;
  Caja(dc,R(k.x,k.y,58,44),pulsada?Verde:indicada?Menta:RGB(246,248,247),9,indicada?RGB(94,173,137):Borde);
  Texto(dc,k.nombre,R(k.x+4,k.y+4,50,20),14,pulsada?Blanco:indicada?Verde:Tinta,FW_BOLD,DT_CENTER|DT_SINGLELINE);
  Texto(dc,EtiquetaFisica(k.nombre),R(k.x+3,k.y+24,52,17),10,pulsada?Menta:Suave,FW_NORMAL,DT_CENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
 }
 Caja(dc,R(674,633,154,44),g.espacioAbajo?Verde:esperadas.count(L"ESPACIO")?Menta:RGB(246,248,247),9,Borde);
 Texto(dc,L"Espacio",R(679,639,144,20),13,g.espacioAbajo?Blanco:Tinta,FW_SEMIBOLD,DT_CENTER|DT_SINGLELINE);
 Texto(dc,L"asentar",R(679,658,144,16),10,g.espacioAbajo?Menta:Suave,FW_NORMAL,DT_CENTER|DT_SINGLELINE);
 Texto(dc,g.activo?L"Escuchando tus acordes · Esc para pausar":L"Pulsa Empezar. Forma cada acorde y suelta las teclas.",R(279,691,570,18),11,Suave,FW_NORMAL,DT_CENTER|DT_SINGLELINE);
 Texto(dc,L"El camino",R(921,330,283,30),22,Tinta,FW_SEMIBOLD);
 Texto(dc,L"Paso "+Numero((std::min)(g.paso+1,g.plan.pasos.size()))+L" de "+Numero(g.plan.pasos.size())+L" · "+Numero(g.plan.palabras)+L" palabras",R(922,365,280,24),12,Suave);
 Caja(dc,R(922,397,282,5),Borde,4);
 if(!g.plan.pasos.empty()&&g.paso)Caja(dc,R(922,397,static_cast<int>(282*g.paso/g.plan.pasos.size()),5),Verde,4);
 const size_t begin=g.paso>1?g.paso-1:0;
 for(size_t i=begin;i<(std::min)(g.plan.pasos.size(),begin+4);++i)
 {
  const auto& p=g.plan.pasos[i];int y=421+static_cast<int>(i-begin)*56;
  bool activo=i==g.paso;Caja(dc,R(916,y,296,48),activo?Menta:Blanco,10);
  Texto(dc,Numero(i+1),R(926,y+12,29,25),13,activo?Verde:Suave,FW_BOLD,DT_CENTER|DT_SINGLELINE);
  Texto(dc,p.tipo==MecaTipo::Asentar?L"Asentar «"+p.fragmento+L"»":L"«"+p.fragmento+L"»",R(967,y+5,233,21),14,Tinta,FW_SEMIBOLD,DT_SINGLELINE|DT_END_ELLIPSIS);
  Texto(dc,g.pista||p.tipo==MecaTipo::Asentar?p.acorde:L"Pista oculta",R(967,y+26,233,18),11,activo?Verde:Suave,FW_NORMAL,DT_SINGLELINE|DT_END_ELLIPSIS);
 }
 Texto(dc,actual?actual->explicacion:L"Ya sabes cómo se construye. Repite sin pistas o prueba otra palabra.",R(921,653,287,53),12,Suave);
 Caja(dc,R(252,734,978,40),g.error?RGB(253,234,231):Menta,12);
 Texto(dc,g.feedback,R(266,744,947,26),12,g.error?Rojo:Verde,FW_SEMIBOLD,DT_SINGLELINE|DT_END_ELLIPSIS);
 RestoreDC(dc,save);
}
void Boton(HDC dc,const DRAWITEMSTRUCT& item)
{
 RECT client{};GetClientRect(g.ventana,&client);const double escala=client.bottom/static_cast<double>(VH);
 int id=static_cast<int>(item.CtlID);bool nav=id>=NavAprender&&id<=NavProgreso;bool elegido=nav?g.vista==id-NavAprender:id>=NivelBase&&id<NivelBase+5&&g.nivel==id-NivelBase;
 bool primario=id==Iniciar||id==Traducir;
 COLORREF bg=nav?(elegido?RGB(174,232,191):RGB(23,47,44)):primario?Verde:elegido?Menta:Blanco;
 if(item.itemState&ODS_SELECTED)bg=RGB(139,210,173);
 HBRUSH fondoBoton=CreateSolidBrush(nav?RGB(23,47,44):Fondo);FillRect(dc,&item.rcItem,fondoBoton);DeleteObject(fondoBoton);
 Caja(dc,item.rcItem,bg,static_cast<int>(12*escala),nav||primario?bg:Borde);
 wchar_t texto[180]{};GetWindowTextW(item.hwndItem,texto,180);
 auto rect=item.rcItem;InflateRect(&rect,-8,-2);
 Texto(dc,texto,rect,static_cast<int>(14*escala),nav?(elegido?Tinta:RGB(195,214,203)):primario?Blanco:Tinta,FW_SEMIBOLD,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
 if(item.itemState&ODS_FOCUS){auto focus=item.rcItem;InflateRect(&focus,-5,-5);DrawFocusRect(dc,&focus);}
}
void Mover(int id,int x,int y,int w,int h,bool visible)
{
 auto it=g.controles.find(id);if(it==g.controles.end())return;
 RECT r{};GetClientRect(g.ventana,&r);
 MoveWindow(it->second,x*r.right/VW,y*r.bottom/VH,w*r.right/VW,h*r.bottom/VH,TRUE);
 ShowWindow(it->second,visible?SW_SHOW:SW_HIDE);
}
void Distribuir()
{
 for(int i=0;i<3;++i)Mover(NavAprender+i,23,178+i*59,168,46,true);
 for(int i=0;i<5;++i)Mover(NivelBase+i,252+i*198,166,184,37,g.vista==0);
 Mover(Entrada,271,181,937,57,g.vista==1);Mover(Traducir,1032,262,197,35,g.vista==1);
 Mover(Iniciar,252,791,202,36,g.vista!=2);Mover(Siguiente,465,791,220,36,g.vista!=1);
 Mover(Pista,696,791,186,36,g.vista!=2);Mover(AnteriorPaso,907,791,145,36,g.vista!=0);Mover(ProximoPaso,1064,791,166,36,g.vista!=0);
 SetWindowTextW(g.controles[Siguiente],g.vista==2?L"Practicar mis errores":L"Siguiente ejercicio");
 RECT r{};GetClientRect(g.ventana,&r);auto nueva=Fuente((std::max)(12L,17*r.bottom/VH));
 SendMessageW(g.entrada,WM_SETFONT,reinterpret_cast<WPARAM>(nueva),TRUE);
 if(g.fuenteControles)DeleteObject(g.fuenteControles);g.fuenteControles=nueva;
 Invalidar();
}
void CambiarVista(int vista)
{
 Pausar();GuardarProgreso();g.vista=vista;g.paginaProgreso=0;
 if(vista==0)NuevoEjercicio();
 if(vista==1){std::array<wchar_t,514> texto{};GetWindowTextW(g.entrada,texto.data(),static_cast<int>(texto.size()));CargarPlan(texto.data());}
 Distribuir();
}
void Comando(int id)
{
 if(id>=NavAprender&&id<=NavProgreso){CambiarVista(id-NavAprender);return;}
 if(id>=NivelBase&&id<NivelBase+5){g.nivel=id-NivelBase;g.turno=0;NuevoEjercicio();Distribuir();return;}
 if(id==Iniciar)
 {
  if(g.activo){Pausar();return;}
  if(!Actual()||g.explorando){g.paso=0;g.explorando=false;g.escrito.clear();g.literal.clear();}
  if(!Actual())return;
  LimpiarCaptura();g.activo=true;g.inicio=GetTickCount64();SetFocus(g.ventana);
  SetWindowTextW(g.controles[Iniciar],L"Pausar (Esc)");g.feedback=L"Ya puedes escribir. Forma el acorde marcado y suelta las teclas.";g.error=false;Invalidar();return;
 }
 if(id==Siguiente){if(g.vista==2){g.nivel=4;CambiarVista(0);}else NuevoEjercicio();return;}
 if(id==Pista){g.pista=!g.pista;SetWindowTextW(g.controles[Pista],g.pista?L"Ocultar pistas":L"Mostrar pistas");Invalidar();return;}
 if(id==Traducir){std::array<wchar_t,514> texto{};GetWindowTextW(g.entrada,texto.data(),static_cast<int>(texto.size()));CargarPlan(texto.data());return;}
 if(id==AnteriorPaso||id==ProximoPaso)
 {
  if(g.vista==2){if(id==AnteriorPaso&&g.paginaProgreso)--g.paginaProgreso;if(id==ProximoPaso&&(g.paginaProgreso+1)*7<g.marcas.size())++g.paginaProgreso;Invalidar();return;}
  Pausar();g.explorando=true;if(id==AnteriorPaso&&g.paso)--g.paso;
  if(id==ProximoPaso&&g.paso+1<g.plan.pasos.size())++g.paso;
  g.feedback=L"Explora cada paso. Empezar practica el texto completo desde el principio.";Invalidar();
 }
}
LRESULT CALLBACK Procedimiento(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{
 switch(msg)
 {
 case WM_CREATE:return 0;
 case WM_ERASEBKGND:return 1;
 case WM_PAINT:{PAINTSTRUCT ps{};auto dc=BeginPaint(hwnd,&ps);RECT r{};GetClientRect(hwnd,&r);auto mem=CreateCompatibleDC(dc);auto bmp=CreateCompatibleBitmap(dc,(std::max)(1L,r.right),(std::max)(1L,r.bottom));auto old=SelectObject(mem,bmp);Dibujar(mem);BitBlt(dc,0,0,r.right,r.bottom,mem,0,0,SRCCOPY);SelectObject(mem,old);DeleteObject(bmp);DeleteDC(mem);EndPaint(hwnd,&ps);return 0;}
 case WM_PRINTCLIENT:Dibujar(reinterpret_cast<HDC>(wp));return 0;
 case WM_DRAWITEM:Boton(reinterpret_cast<DRAWITEMSTRUCT*>(lp)->hDC,*reinterpret_cast<DRAWITEMSTRUCT*>(lp));return TRUE;
 case WM_CTLCOLOREDIT:SetTextColor(reinterpret_cast<HDC>(wp),Tinta);SetBkColor(reinterpret_cast<HDC>(wp),Blanco);return reinterpret_cast<LRESULT>(GetStockObject(WHITE_BRUSH));
 case WM_SIZE:if(!g.controles.empty())Distribuir();return 0;
 case WM_GETMINMAXINFO:{auto mm=reinterpret_cast<MINMAXINFO*>(lp);mm->ptMinTrackSize={1024,740};return 0;}
 case WM_COMMAND:if(HIWORD(wp)==BN_CLICKED)Comando(LOWORD(wp));return 0;
 case WM_TIMER:if(wp==TimerAcorde)FinalizarAcorde();else if(wp==TimerReloj&&g.activo)Invalidar();return 0;
 case WM_ACTIVATE:if(LOWORD(wp)==WA_INACTIVE){Pausar();g.feedback=L"Práctica pausada. Vuelve y pulsa Empezar para continuar.";}return 0;
 case WM_KILLFOCUS:if(g.activo){Pausar();g.feedback=L"Práctica pausada al cambiar de control.";}return 0;
 case WM_CHAR:
 {
  const auto* p=Actual();if(!g.activo||!p||p->tipo!=MecaTipo::Qwerty)return 0;
  wchar_t c=static_cast<wchar_t>(wp);if(c<32&&c!=L'\r')return 0;
  if(c==L'\r')c=L' ';
  if(g.literal.size()<p->fragmento.size()&&c==p->fragmento[g.literal.size()])
  {g.literal+=c;g.feedback=L"QWERTY: "+g.literal;if(g.literal==p->fragmento)Evaluar(L"QWERTY");}
  else{++g.errores;++g.marcas[L"QWERTY"].errores;g.racha=0;g.error=true;g.feedback=L"Ese carácter no coincide. Continúa con el siguiente carácter de la palabra.";}
  Invalidar();return 0;
 }
 case WM_CLOSE:Pausar();GuardarProgreso();DestroyWindow(hwnd);return 0;
 case WM_DESTROY:KillTimer(hwnd,TimerReloj);g.ventana=nullptr;g.entrada=nullptr;g.controles.clear();if(g.fuenteControles){DeleteObject(g.fuenteControles);g.fuenteControles=nullptr;}return 0;
 }
 return DefWindowProcW(hwnd,msg,wp,lp);
}
void CrearBoton(int id,const wchar_t* texto)
{
 g.controles[id]=CreateWindowExW(0,L"BUTTON",texto,WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_OWNERDRAW,0,0,10,10,g.ventana,reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)),g.instancia,nullptr);
}
bool GuardarVista(const std::wstring& ruta)
{
 RECT r{};GetClientRect(g.ventana,&r);auto dc=GetDC(g.ventana);auto mem=CreateCompatibleDC(dc);
 BITMAPINFO info{};info.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);info.bmiHeader.biWidth=r.right;info.bmiHeader.biHeight=-r.bottom;info.bmiHeader.biPlanes=1;info.bmiHeader.biBitCount=32;info.bmiHeader.biCompression=BI_RGB;
 void* pixels=nullptr;auto bmp=CreateDIBSection(dc,&info,DIB_RGB_COLORS,&pixels,nullptr,0);if(!bmp){DeleteDC(mem);ReleaseDC(g.ventana,dc);return false;}
 auto old=SelectObject(mem,bmp);SendMessageW(g.ventana,WM_PRINTCLIENT,reinterpret_cast<WPARAM>(mem),PRF_CLIENT);
 for(auto [id,child]:g.controles)
 {
  if(!IsWindowVisible(child))continue;RECT cr{};GetWindowRect(child,&cr);MapWindowPoints(nullptr,g.ventana,reinterpret_cast<POINT*>(&cr),2);
  int save=SaveDC(mem);SetViewportOrgEx(mem,cr.left,cr.top,nullptr);SendMessageW(child,WM_PRINT,reinterpret_cast<WPARAM>(mem),PRF_CLIENT|PRF_ERASEBKGND);RestoreDC(mem,save);
 }
 GdiFlush();BITMAPFILEHEADER file{};file.bfType=0x4d42;file.bfOffBits=sizeof(file)+sizeof(BITMAPINFOHEADER);file.bfSize=file.bfOffBits+r.right*r.bottom*4;
 std::ofstream out(std::filesystem::path(ruta),std::ios::binary);out.write(reinterpret_cast<char*>(&file),sizeof(file));out.write(reinterpret_cast<char*>(&info.bmiHeader),sizeof(BITMAPINFOHEADER));out.write(static_cast<char*>(pixels),static_cast<std::streamsize>(r.right)*r.bottom*4);out.close();bool ok=static_cast<bool>(out);
 SelectObject(mem,old);DeleteObject(bmp);DeleteDC(mem);ReleaseDC(g.ventana,dc);return ok;
}
}
void MECACID_Inicializar(HINSTANCE instancia,const DiccionarioCID& diccionario)
{
 g.instancia=instancia;g.modelo=std::make_unique<MecaModelo>(diccionario);LeerProgreso();
}
void MECACID_Abrir()
{
 if(!g.modelo)return;
 EstablecerModoCID(false);Superposicion_SetModoQwerty(true);Superposicion_SetUltimoAsentado(L"MECACID · práctica local");
 if(g.ventana){ShowWindow(g.ventana,SW_RESTORE);SetForegroundWindow(g.ventana);return;}
 WNDCLASSW wc{};wc.hInstance=g.instancia;wc.lpfnWndProc=Procedimiento;wc.lpszClassName=L"MECACID_03";wc.hCursor=LoadCursorW(nullptr,IDC_ARROW);
 if(!RegisterClassW(&wc)&&GetLastError()!=ERROR_CLASS_ALREADY_EXISTS)return;
 RECT frame{0,0,VW,VH};AdjustWindowRectEx(&frame,WS_OVERLAPPEDWINDOW,FALSE,WS_EX_CONTROLPARENT);
 RECT work{};SystemParametersInfoW(SPI_GETWORKAREA,0,&work,0);
 int w=(std::min)(frame.right-frame.left,work.right-work.left-30),h=(std::min)(frame.bottom-frame.top,work.bottom-work.top-30);
 g.ventana=CreateWindowExW(WS_EX_CONTROLPARENT,wc.lpszClassName,L"MECACID — Aprende a escribir en CID",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,w,h,nullptr,nullptr,g.instancia,nullptr);
 if(!g.ventana){MessageBoxW(nullptr,L"No se pudo abrir MECACID.",L"CID",MB_OK|MB_ICONERROR);return;}
 CrearBoton(NavAprender,L"01   Aprender");CrearBoton(NavTraductor,L"02   Traductor");CrearBoton(NavProgreso,L"03   Tu progreso");
 const wchar_t* levels[]={L"1  Teclas",L"2  Acordes",L"3  Palabras",L"4  Frases",L"5  Repaso"};
 for(int i=0;i<5;++i)CrearBoton(NivelBase+i,levels[i]);
 CrearBoton(Iniciar,L"Empezar / continuar");CrearBoton(Siguiente,L"Siguiente ejercicio");CrearBoton(Pista,L"Ocultar pistas");CrearBoton(AnteriorPaso,L"← Anterior");CrearBoton(ProximoPaso,L"Siguiente →");CrearBoton(Traducir,L"Descomponer →");
 g.entrada=CreateWindowExW(0,L"EDIT",L"hola mundo, mañana tomo café",WS_CHILD|WS_TABSTOP|ES_MULTILINE|ES_AUTOVSCROLL|WS_VSCROLL,0,0,10,10,g.ventana,reinterpret_cast<HMENU>(static_cast<INT_PTR>(Entrada)),g.instancia,nullptr);g.controles[Entrada]=g.entrada;SendMessageW(g.entrada,EM_SETLIMITTEXT,512,0);
 g.vista=0;NuevoEjercicio();Distribuir();SetTimer(g.ventana,TimerReloj,1000,nullptr);ShowWindow(g.ventana,SW_SHOW);UpdateWindow(g.ventana);SetForegroundWindow(g.ventana);
}
void MECACID_Cerrar(){if(g.ventana)SendMessageW(g.ventana,WM_CLOSE,0,0);}
bool MECACID_TieneFoco(){return g.ventana&&GetForegroundWindow()==g.ventana;}
bool MECACID_ProcesarMensaje(MSG* msg)
{
 if(!g.ventana)return false;
 if(g.activo&&msg->hwnd==g.ventana)return false;
 return IsDialogMessageW(g.ventana,msg)!=FALSE;
}
bool MECACID_ProcesarTecla(DWORD vk,DWORD scanCode,bool presionada,DWORD flags)
{
 if(!g.activo)return false;
 if(vk==VK_ESCAPE){if(presionada)Pausar();return true;}
 if(vk==VK_CONTROL||vk==VK_LCONTROL||vk==VK_RCONTROL||vk==VK_MENU||vk==VK_LMENU||vk==VK_RMENU||vk==VK_LWIN||vk==VK_RWIN||vk==VK_TAB)
 {if(presionada)Pausar();return false;}
 const auto* p=Actual();if(!p)return false;
 if(p->tipo==MecaTipo::Qwerty)return false;
 if(flags&LLKHF_INJECTED)return true;
 if(vk==VK_SPACE)
 {
  bool era=g.espacioAbajo;g.espacioAbajo=presionada;
  if(!presionada&&era&&p->tipo==MecaTipo::Asentar)Evaluar(L"ESPACIO");
  Invalidar();return true;
 }
 const auto* nombre=(flags&LLKHF_EXTENDED)?nullptr:NombreTeclaCID_PorScanCode(scanCode);
 if(!nombre){if(presionada&&vk!=VK_SHIFT&&vk!=VK_LSHIFT&&vk!=VK_RSHIFT){g.feedback=L"Esa tecla no pertenece al mapa CID. Sigue las posiciones del teclado visual.";g.error=true;Invalidar();}return true;}
 if(presionada)
 {
  if(g.abajo.count(nombre))return true;g.abajo.insert(nombre);
  if(!g.esperandoSoltar)
  {
   g.acorde.insert(nombre);
   if(!g.ventanaAcorde){g.ventanaAcorde=true;if(!SetTimer(g.ventana,TimerAcorde,60,nullptr)){Pausar();g.feedback=L"No se pudo iniciar la captura. Pulsa Empezar para reintentar.";}}
  }
 }
 else{g.abajo.erase(nombre);if(g.abajo.empty())g.esperandoSoltar=false;}
 Invalidar();return true;
}
int MECACID_PruebaVisual(HINSTANCE instancia,const DiccionarioCID& diccionario,const std::wstring& directorio)
{
 g.demo=true;MECACID_Inicializar(instancia,diccionario);
 const DWORD vks[]={'3','4','5','6','7','8','9','0','E','R','T','Y','U','I','O','D','F','G','H','J','K','C','V','B','N','M'};
 for(size_t i=0;i<std::size(Teclas);++i)EstablecerAsignacionTeclaCID(Teclas[i].nombre,MapVirtualKeyW(vks[i],MAPVK_VK_TO_VSC));
 MECACID_Abrir();if(!g.ventana)return 2;
 SetWindowPos(g.ventana,nullptr,0,0,1296,879,SWP_NOZORDER); // Cliente de referencia cercano a 1280×840.
 g.nivel=2;g.turno=0;NuevoEjercicio();Distribuir();
 if(!GuardarVista(directorio+L"\\mecacid-aprender.bmp"))return 3;
 Comando(Iniciar);size_t limite=0;
 while(Actual()&&++limite<100)
 {
  const auto step=*Actual();if(step.tipo==MecaTipo::Asentar){MECACID_ProcesarTecla(VK_SPACE,57,true,0);MECACID_ProcesarTecla(VK_SPACE,57,false,0);}
  else
  {
   for(const auto& key:Nombres(step.acorde)){DWORD sc=0;if(!ObtenerScanCodeDeNombreCID(key.c_str(),sc))return 4;MECACID_ProcesarTecla(0,sc,true,0);}
   FinalizarAcorde();
   for(const auto& key:Nombres(step.acorde)){DWORD sc=0;ObtenerScanCodeDeNombreCID(key.c_str(),sc);MECACID_ProcesarTecla(0,sc,false,0);}
  }
 }
 if(Actual()||g.errores||g.escrito!=g.plan.normalizado)return 5;
 // Un fallo no avanza; Esc elimina acordes pendientes y el siguiente inicio es limpio.
 CargarPlan(L"café");Comando(Iniciar);const size_t previo=g.paso;
 Evaluar(L"INCORRECTO");if(g.paso!=previo||g.errores!=1)return 8;
 DWORD pendiente=0;ObtenerScanCodeDeNombreCID(Nombres(Actual()->acorde).begin()->c_str(),pendiente);
 MECACID_ProcesarTecla(0,pendiente,true,0);if(!g.ventanaAcorde)return 14;
 MECACID_ProcesarTecla(VK_ESCAPE,1,true,0);if(g.activo||g.ventanaAcorde||!g.abajo.empty())return 9;
 Comando(Iniciar);SendMessageW(g.ventana,WM_ACTIVATE,WA_INACTIVE,0);if(g.activo)return 15;
 // La navegación didáctica no permite contabilizar un ejercicio parcialmente saltado.
 CambiarVista(1);Comando(ProximoPaso);Comando(Iniciar);if(g.paso!=0||!g.escrito.empty())return 11;Pausar();
 // QWERTY sin cobertura se valida por carácter y no se asienta una palabra parcial.
 CargarPlan(L"☃");Comando(Iniciar);SendMessageW(g.ventana,WM_CHAR,L'☃',0);
 if(!Actual())return 12;SendMessageW(g.ventana,WM_CHAR,L' ',0);
 if(Actual()||g.escrito!=g.plan.normalizado)return 13;
 CambiarVista(1);g.paso=2;g.explorando=true;Invalidar();
 if(!GuardarVista(directorio+L"\\mecacid-traductor.bmp"))return 6;
 CambiarVista(2);if(!GuardarVista(directorio+L"\\mecacid-progreso.bmp"))return 7;
 MECACID_Cerrar();return 0;
}
