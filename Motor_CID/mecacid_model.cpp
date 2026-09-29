#include "mecacid_model.h"
#include "bitacora_cid.h"
#include <algorithm>
#include <limits>
#include <sstream>
#include <set>

std::wstring MecaMinusculas(std::wstring texto)
{
    // Conversión española explícita: independiente de la locale C del proceso.
    const std::wstring may = L"ABCDEFGHIJKLMNOPQRSTUVWXYZÁÉÍÓÚÜÑ";
    const std::wstring min = L"abcdefghijklmnopqrstuvwxyzáéíóúüñ";
    for (auto& c : texto) { auto i = may.find(c); if (i != std::wstring::npos) c = min[i]; }
    return texto;
}
MecaModelo::MecaModelo(const DiccionarioCID& diccionario) : entradas(diccionario.EnumerarEntradas())
{
    for (const auto& [acorde, entrada] : entradas)
    {
        const int teclas = 1 + static_cast<int>(std::count(acorde.begin(), acorde.end(), L'+'));
        if (acorde == L"D10" || teclas > 3 || entrada.resultado_crudo.empty() ||
            entrada.resultado_crudo.find_first_of(L" \r\n\t") != std::wstring::npos) continue;
        const auto base = MecaMinusculas(entrada.resultado_crudo);
        formas.push_back({base, base, acorde, false, teclas});
        // Derivar del mismo modificador que utiliza CID evita un segundo juego de reglas.
        BitacoraCID bitacora;
        bitacora.Anotar(entrada.resultado_crudo, entrada.numero_tildal);
        if (bitacora.AplicarModificadorD10())
        {
            auto variante = MecaMinusculas(bitacora.ObtenerCopia().back());
            if (variante != base) formas.push_back({variante, base, acorde, true, teclas});
        }
    }
    std::sort(formas.begin(), formas.end(), [](const Forma& a, const Forma& b) {
        if (a.texto != b.texto) return a.texto < b.texto;
        if (a.modificar != b.modificar) return a.modificar < b.modificar;
        if (a.teclas != b.teclas) return a.teclas < b.teclas;
        return a.acorde < b.acorde;
    });
}
MecaPlan MecaModelo::Traducir(const std::wstring& texto) const
{
    MecaPlan plan;
    plan.original = texto;
    plan.aviso = L"Guía en minúsculas y espacios simples. CID aplica la mayúscula inicial y añade un espacio al asentar.";
    if (texto.size() > 512)
    {
        plan.aviso = L"Usa un máximo de 512 caracteres por práctica.";
        return plan;
    }
    std::wistringstream palabras(MecaMinusculas(texto));
    std::wstring palabra;
    while (palabras >> palabra)
    {
        ++plan.palabras;
        plan.normalizado += palabra + L" ";
        const size_t n = palabra.size();
        const int infinito = (std::numeric_limits<int>::max)() / 4;
        std::vector<int> coste(n + 1, infinito), pulsaciones(n + 1, infinito), elegido(n, -1);
        coste[n] = pulsaciones[n] = 0;
        for (size_t pos = n; pos-- > 0;)
        {
            for (size_t i = 0; i < formas.size(); ++i)
            {
                const auto& f = formas[i];
                if (pos + f.texto.size() > n || palabra.compare(pos, f.texto.size(), f.texto) != 0) continue;
                const auto fin = pos + f.texto.size();
                if (coste[fin] == infinito) continue;
                int c = coste[fin] + (f.modificar ? 2 : 1);
                int p = pulsaciones[fin] + f.teclas + (f.modificar ? 1 : 0);
                if (c < coste[pos] || (c == coste[pos] && p < pulsaciones[pos]))
                { coste[pos] = c; pulsaciones[pos] = p; elegido[pos] = static_cast<int>(i); }
            }
        }
        if (elegido[0] == -1)
        {
            ++plan.alternativasQwerty;
            plan.pasos.push_back({MecaTipo::Qwerty, L"QWERTY", palabra + L" ", palabra,
                L"No hay una composición completa en el diccionario. En CID: cambia con Ctrl+Shift+F11 y escribe esta palabra."});
            continue;
        }
        std::wstring acumulado;
        for (size_t pos = 0; pos < n;)
        {
            const auto& f = formas[static_cast<size_t>(elegido[pos])];
            auto antes = acumulado;
            acumulado += f.base;
            plan.pasos.push_back({MecaTipo::Acorde, f.acorde, f.base, acumulado,
                L"Pulsa las teclas juntas. Este acorde añade «" + f.base + L"» a la palabra."});
            if (f.modificar)
            {
                acumulado = antes + f.texto;
                plan.pasos.push_back({MecaTipo::Modificador, L"D10", f.texto, acumulado,
                    L"Suelta el acorde anterior y pulsa D10: «" + f.base + L"» se convierte en «" + f.texto + L"»."});
            }
            pos += f.texto.size();
        }
        plan.pasos.push_back({MecaTipo::Asentar, L"ESPACIO", palabra, palabra,
            L"Pulsa y suelta Espacio para asentar la palabra. En CID puedes mantenerlo mientras compones."});
    }
    return plan;
}
std::vector<std::wstring> MecaModelo::Ejercicios(int nivel) const
{
    std::vector<std::wstring> resultado;
    std::set<std::wstring> vistos;
    auto anadir = [&](const std::wstring& palabra) {
        auto p = Traducir(palabra);
        if (!p.pasos.empty() && p.alternativasQwerty == 0 && vistos.insert(palabra).second) resultado.push_back(palabra);
    };
    if (nivel == 0)
    {
        for (const wchar_t* p : {L"a",L"e",L"i",L"o",L"u",L"s",L"n",L"m",L"b",L"c",L"d",L"h"}) anadir(p);
        return resultado;
    }
    if (nivel == 2)
        for (const wchar_t* p : {L"casa",L"hola",L"amigo",L"mañana",L"café",L"tiempo",L"escribir",L"teclado",L"palabra",L"música",L"trabajo",L"aprender"}) anadir(p);
    if (nivel == 3)
    {
        for (const wchar_t* p : {L"hola mundo",L"mi casa es tu casa",L"quiero aprender a escribir",L"mañana tomo café",L"poco a poco sale mejor",L"¿cómo estás?",L"hoy escribo con acordes"}) anadir(p);
        return resultado;
    }
    for (const auto& [acorde, entrada] : entradas)
    {
        auto texto = MecaMinusculas(entrada.resultado_crudo);
        if (texto.find_first_not_of(L"abcdefghijklmnopqrstuvwxyzáéíóúüñ") != std::wstring::npos) continue;
        if ((nivel == 1 && texto.size() >= 2 && texto.size() <= 3) ||
            (nivel >= 2 && texto.size() >= 4 && texto.size() <= 10)) anadir(texto);
    }
    return resultado;
}
std::wstring MecaModelo::Siguiente(int nivel, const std::map<std::wstring, MecaMarca>& marcas, size_t turno) const
{
    auto candidatos = Ejercicios(nivel == 4 ? 2 : nivel);
    if (candidatos.empty()) return L"";
    if (nivel != 4) return candidatos[turno % candidatos.size()];
    // Puntuar los pasos realmente elegidos por el traductor, incluidos D10.
    // Una entrada puede tener acordes equivalentes: no prometer repasar uno que
    // luego no aparece en la práctica, ni generar ejercicios QWERTY accidentales.
    const auto iniciales = candidatos.size();
    for (const auto& [acorde, entrada] : entradas) {
        const auto texto = MecaMinusculas(entrada.resultado_crudo);
        if (std::find(candidatos.begin(), candidatos.end(), texto) == candidatos.end()) candidatos.push_back(texto);
    }
    std::wstring peor;
    double necesidad = 0;
    for (const auto& texto : candidatos) {
        auto plan = Traducir(texto);
        if (plan.alternativasQwerty || plan.pasos.empty()) continue;
        double score = 0;
        for (const auto& paso : plan.pasos) {
            if (paso.tipo == MecaTipo::Asentar) continue;
            auto it = marcas.find(paso.acorde);
            if (it != marcas.end()) score = (std::max)(score, static_cast<double>(it->second.errores) / (1.0 + it->second.aciertos));
        }
        if (score > necesidad) { necesidad = score; peor = texto; }
    }
    return peor.empty() ? candidatos[turno % iniciales] : peor;
}
