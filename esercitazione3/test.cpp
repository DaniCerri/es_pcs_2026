#include <iostream>
#include <sstream>
#include <string>
#include "rational.hpp"

using namespace std;

// Converte un Rational in stringa usando operator<<
template <typename I>
string str(const Rational<I>& r) {
    ostringstream oss;
    oss << r;
    return oss.str();
}

int passed = 0, failed = 0;

template <typename I>
void check(const string& expr, const Rational<I>& result, const string& expected) {
    string got = str(result);
    bool ok = (got == expected);
    cout << (ok ? "PASS" : "FAIL") << " | " << expr << " = " << got;
    if (!ok) {
        cout << "  (atteso: " << expected << ")";
        failed++;
    } else {
        passed++;
    }
    cout << endl;
}

int main() {
    Rational<int> inf(1, 0);           // Inf
    Rational<int> ninf(-1, 0);         // -Inf
    Rational<int> nan(0, 0);           // NaN
    Rational<int> zero(0, 1);          // 0
    Rational<int> half(1, 2);          // 1/2
    Rational<int> nhalf(-1, 2);        // -1/2
    Rational<int> third(1, 3);         // 1/3
    Rational<int> twothirds(2, 3);     // 2/3
    Rational<int> threequarters(3, 4); // 3/4

    // ===================== STAMPA =====================
    cout << "=== STAMPA ===" << endl;
    check("Rational(1,0)",  inf,  "Inf");
    check("Rational(-1,0)", ninf, "-Inf");
    check("Rational(0,0)",  nan,  "NaN");
    check("Rational(0,1)",  zero, "0");
    check("Rational(1,2)",  half, "1/2");
    check("Rational(-1,2)", nhalf, "-1/2");
    check("Rational(2,3)",  twothirds, "2/3");
    check("Rational(4,8)",  Rational<int>(4, 8), "1/2");   // semplificazione
    check("Rational(2,-4)", Rational<int>(2, -4), "-1/2");  // segno nel denominatore

    // ===================== SOMMA =====================
    cout << "\n=== SOMMA ===" << endl;
    // Normali
    check("1/2 + 1/3",    half + third,  "5/6");
    check("1/2 + (-1/2)", half + nhalf,  "0");
    check("1/2 + 0",      half + zero,   "1/2");
    check("0 + 0",        zero + zero,   "0");
    check("2/3 + 1/3",    twothirds + third, "1/1");
    // Inf
    check("Inf + 1/2",    inf + half,    "Inf");
    check("-Inf + 1/2",   ninf + half,   "-Inf");
    check("1/2 + Inf",    half + inf,    "Inf");
    check("Inf + Inf",    inf + inf,     "Inf");
    check("-Inf + -Inf",  ninf + ninf,   "-Inf");
    check("Inf + -Inf",   inf + ninf,    "NaN");
    check("-Inf + Inf",   ninf + inf,    "NaN");
    // NaN
    check("NaN + 1/2",    nan + half,    "NaN");
    check("1/2 + NaN",    half + nan,    "NaN");
    check("NaN + Inf",    nan + inf,     "NaN");
    check("NaN + NaN",    nan + nan,     "NaN");

    // ===================== SOTTRAZIONE =====================
    cout << "\n=== SOTTRAZIONE ===" << endl;
    // Normali
    check("1/2 - 1/3",    half - third,  "1/6");
    check("2/3 - 3/4",    twothirds - threequarters, "-1/12");
    check("3/4 - 3/4",    threequarters - threequarters, "0");
    check("1/2 - 0",      half - zero,   "1/2");
    check("0 - 1/2",      zero - half,   "-1/2");
    // Inf
    check("Inf - Inf",    inf - inf,     "NaN");
    check("-Inf - -Inf",  ninf - ninf,   "NaN");
    check("Inf - -Inf",   inf - ninf,    "Inf");
    check("-Inf - Inf",   ninf - inf,    "-Inf");
    check("Inf - 1/2",    inf - half,    "Inf");
    check("1/2 - Inf",    half - inf,    "-Inf");
    // NaN
    check("NaN - 1/2",    nan - half,    "NaN");
    check("1/2 - NaN",    half - nan,    "NaN");

    // ===================== MOLTIPLICAZIONE =====================
    cout << "\n=== MOLTIPLICAZIONE ===" << endl;
    // Normali
    check("1/2 * 2/3",    half * twothirds, "1/3");
    check("1/2 * (-1/2)", half * nhalf,     "-1/4");
    check("(-1/2) * (-1/2)", nhalf * nhalf, "1/4");
    check("3/4 * 2/3",    threequarters * twothirds, "1/2");
    check("1/2 * 0",      half * zero,      "0");
    check("0 * 0",        zero * zero,      "0");
    // Inf
    check("Inf * 1/2",    inf * half,       "Inf");
    check("Inf * (-1/2)", inf * nhalf,      "-Inf");
    check("-Inf * (-1/2)", ninf * nhalf,    "Inf");
    check("Inf * Inf",    inf * inf,        "Inf");
    check("Inf * -Inf",   inf * ninf,       "-Inf");
    check("-Inf * -Inf",  ninf * ninf,      "Inf");
    check("Inf * 0",      inf * zero,       "NaN");
    check("0 * Inf",      zero * inf,       "NaN");
    check("0 * -Inf",     zero * ninf,      "NaN");
    // NaN
    check("NaN * 1/2",    nan * half,       "NaN");
    check("NaN * 0",      nan * zero,       "NaN");
    check("NaN * Inf",    nan * inf,        "NaN");

    // ===================== DIVISIONE =====================
    cout << "\n=== DIVISIONE ===" << endl;
    // Normali
    check("1/2 / 1/3",    half / third,         "3/2");
    check("1/2 / (-1/2)", half / nhalf,         "-1/1");
    check("2/3 / 2/3",    twothirds / twothirds, "1/1");
    check("3/4 / 1/2",    threequarters / half,  "3/2");
    check("0 / 1/2",      zero / half,          "0");
    // Divisione per zero -> Inf
    check("1/2 / 0",      half / zero,          "Inf");
    check("(-1/2) / 0",   nhalf / zero,         "-Inf");
    // Inf / numero
    check("Inf / 1/2",    inf / half,           "Inf");
    check("Inf / (-1/2)", inf / nhalf,          "-Inf");
    check("-Inf / (-1/2)", ninf / nhalf,        "Inf");
    // numero / Inf
    check("1/2 / Inf",    half / inf,           "0");
    check("(-1/2) / Inf", nhalf / inf,          "0");
    // Inf / Inf
    check("Inf / Inf",    inf / inf,            "NaN");
    check("Inf / -Inf",   inf / ninf,           "NaN");
    check("-Inf / -Inf",  ninf / ninf,          "NaN");
    // 0 / 0
    check("0 / 0",        zero / zero,          "NaN");
    // NaN
    check("NaN / 1/2",    nan / half,           "NaN");
    check("1/2 / NaN",    half / nan,           "NaN");

    // ===================== TRE TERMINI =====================
    cout << "\n=== TRE TERMINI ===" << endl;
    // Aritmetica normale
    check("1/2 + 1/3 + 3/4",         half + third + threequarters,           "19/12");
    check("1/2 * 2/3 * 3/4",         half * twothirds * threequarters,       "1/4");
    check("(-1/2) * (-1/2) * (-1/2)", nhalf * nhalf * nhalf,                 "-1/8");
    check("1/2 + 1/3 - 3/4",         half + third - threequarters,           "1/12");
    check("1/3 * 3/4 - 1/2",         third * threequarters - half,           "-1/4");
    // Precedenza: * prima di +
    check("1/2 + 1/3 * 3/4",         half + third * threequarters,           "3/4");
    // Identita'
    check("1/2 / 1/3 * 1/3",         half / third * third,                   "1/2");
    check("(1/2 + 1/2) * 1/3",       (half + half) * third,                  "1/3");
    // Inf che si propaga
    check("Inf + 1/2 - Inf",         inf + half - inf,                       "NaN");
    check("Inf * 1/2 * 0",           inf * half * zero,                      "NaN");
    check("1/2 * 0 + Inf",           half * zero + inf,                      "Inf");
    check("Inf * 2/3 / Inf",         inf * twothirds / inf,                  "NaN");
    // NaN contagioso
    check("NaN + 1/2 + 1/3",         nan + half + third,                     "NaN");
    check("0 * Inf + 1/2",           zero * inf + half,                      "NaN");

    // ===================== RIEPILOGO =====================
    cout << "\n=== RIEPILOGO ===" << endl;
    cout << "Passati: " << passed << "/" << (passed + failed) << endl;
    if (failed == 0) cout << "Tutti i test passati!" << endl;
    else cout << "Test falliti: " << failed << endl;

    return 0;
}
