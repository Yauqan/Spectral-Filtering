# ZÁPOČTOVÝ PROGRAM PŘEDMĚTU TEORETICKÝ ÚVOD DO FOURIEROVY SPEKTRÁLNÍ ANALÝZY
## Alexandr Dizov, Květen 2024

### Zadání

Zápočtovým úkolem bylo navzorkovat obdelníkovou funkci a užitím rychlé fourierovy transformace nalézt její spektrum. Dále provést filtraci ve spektrální oblasti a filtrovaný signál převést zpět do reálné oblasti.

### Řešení

Při řešení volíme interval od _0_ s do _2000_ s a celkový počet vzorků _2^20 = 1 048 576_ (jedná se o mocninu 2 z důvodu následného užití rychlé fourierovy transformace). Odtud obdržíme hodnotu pro časový krok cca _0,0019_ s, Nyquistovu frekvenci cca _262,144_ Hz a frekvenční krok _0,00025_ Hz.

Dále frekvenční filtr definujeme jako frekvenci oříznutí _10_ Hz a ostrostí oříznutí (odpovídající šířce přechodové oblasti mezi plně propustnou oblastí a plně nepropustnou oblastí, pro zhlazení přechodu). Volíme tři modely s rozlišnými hodnotami ostrosti oříznutí:
* SHARP _0,2_ Hz
* BLUNT _2,0_ Hz
* VERYBLUNT _10,0_ Hz
Filtraci provádíme jak Lowpass - jakožto samotnou filtraci signálu, tak i Highpass - za účelem sledování ztracené části.

### Výsledky

Pro včechny tři modely byl na vstupu využit stejný signál. Jeho graf na malém intervalu uvádíme v [grafu vstupního signálu](result/SHARP/01-timeDomain.pdf). Dále uvádíme jeho [spektrum](result/SHARP/02-SpectralDomain.pdf) a pro jednotlivé modely uvádíme v tabulce níže lowpass filtry a výsledky:

|Model|Lowpass filtr|Výsledek ve spektrální oblasti|Výsledek v časové oblasti|
|-----|-------------|------------------------------|--------------|
|SHARP|[SHARP filtr](result/SHARP/03-Lowpass.pdf)|[spektrální oblast](result/SHARP/04-SpectralDomainFiltered.pdf)|[časová oblast](result/SHARP/05-timeDomainFiltered.pdf)|
|BLUNT|[BLUNT filtr](result/BLUNT/03-Lowpass.pdf)|[spektrální oblast](result/BLUNT/04-SpectralDomainFiltered.pdf)|[časová oblast](result/BLUNT/05-timeDomainFiltered.pdf)|
|VERYBLUNT|[VERYBLUNT filtr](result/VERYBLUNT/03-Lowpass.pdf)|[spektrální oblast](result/VERYBLUNT/04-SpectralDomainFiltered.pdf)|[časová oblast](result/VERYBLUNT/05-timeDomainFiltered.pdf)|

Jak vidíme zvětšení přechodové oblasti významně potlačuje pozorovatelnost Gibbsova jevu na krajích obdelníkové funkce.

### Implementace

Hlavní [soubor programu](main.cpp) obsahuje definice volených parametrů úlohy, definici obdelníkové funkce a definice Highpass a Lowpass filtrů. Hlavní program bohatě využívá třídy [Signal](code/headers/signal.hpp). Jedná se o třídu obsahující funkce umožňující rychlou fourierovu transformaci a zjednodušení přístupu k datům, práci s nimi, filtraci a výpisu. Algoritmus rychlé fourierovy transformace [four1](code/src/four1.c) byl převzat z [numerických receptů](https://www.grad.hr/nastava/gs/prg/NumericalRecipesinC.pdf).

### Kompilace

Kompilaci je možné provést voláním příkazu _make_ v adresáři _code/_. Dále spustit program _./main_ v hlavním adresáři.
