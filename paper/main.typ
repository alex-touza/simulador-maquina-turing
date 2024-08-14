#import "template.typ": *
#import "@preview/codelst:2.0.0": sourcecode
#import "@preview/treet:0.1.0": *

#set text(lang: "cat")

#show link: underline

#show: project.with(
  title: "Simulador de màquina de Turing",
  authors: (
    (name: "Gisele Jaccottet Lopes Pires Ferreira", year: "1r Batxillerat A", email: "06gjaccottet@insernestlluch.cat"),
    (name: "Àlex Xavier Touza Luque", year: "1r Batxillerat B", email: "07atouz@insernestlluch.cat"),
  ),
  date: "30 de maig de 2024",
  organisation: "Institut Ernest Lluch\nCurs 2023-2024",
  logo: "Connexions.JPG"

)

#show "C++": t => [#set text(weight: "bold", hyphenate: false);#box("C++")]

#text(weight: "medium", size: 15pt)[#smallcaps()[Abstract]]

Aquesta memòria explica el desenvolupament del projecte final de Robòtica. El nostre projecte ha consistit en el disseny, la programació i el muntatge d'un simulador d'una màquina de Turing.

Es presentarà el concepte de màquina de Turing, ressaltant la seva gran importància tant a la informàtica teòrica com en el món d'avui dia. Posteriorment, es presentaran els objectius del projecte, seguit d'una explicació de la seva estructura. Es presentarà el disseny 3D de la màquina des de diversos angles, així com les diverses impressions que s'han pogut fer al llarg del projecte. Després, s'explicarà la part electrònica del projecte, exposant la placa, els components i les connexions utilitzats. Més endavant, es detallarà la programació del projecte, explicant la seva estructura i fragments del codi, així com el diagrama de classes.


#pagebreak()
= Fonament teòric

== La màquina de Turing

Una màquina de Turing és una màquina abstracta que permet resoldre qualsevol problema computacional ideada per Alan Turing (1912--1954). La seva constitució és molt simple, però es pot utilitzar per aplicar qualsevol algoritme.

A continuació oferim una definició informal d'una màquina de Turing. Es compon per una cinta infinita dividida en cel·les amb símbols (sovint zeros, uns i cel·les en blanc) i un capçal que es desplaça per aquesta cinta i pot reescriure els símbols de les cel·les. El capçal segueix unes instruccions anomenades _estats_. Cada _estat_ conté ordres diferents depenent del símbol en el qual es trobi el capçal. Les ordres són, en aquest ordre, escriure un símbol, moure's a l'esquerra o a la dreta i executar un altre estat o aturar-se.

#figure(caption: "La cinta i el capçal d'una màquina de Turing")[
#image("turingMachineTape.png", height: 80pt)
]

Com que diferents _estats_ estan enllaçats entre si, els programes de les màquines de Turing  es solen representar en diagrames de transicions (i.e. un graf on els vèrtexs són els _estats_).

#figure(caption: "Exemple d'un programa d'una màquina de Turing representat en un diagrama de transicions.")[#image("turingMachineDiagrama.png", height: 200pt)]

Els ordinadors com els entenem avui dia són hereus d'aquest model matemàtic d'Alan Turing. La cinta és el que avui anomenaríem memòria; el capçal és el processador, i les instruccions són el codi del nostre programa.

== La nostra màquina

Quant als aspectes formals, definim la nostra màquina de Turing de la següent forma:

$
M = lr(angle.l Q, Gamma, b, Sigma, delta, q_0, F angle.r) \
Gamma = {"B", 0, 1} \
b = "B" \
Sigma = {0, 1} \
Q = {q_0, q_1, ..., q_9, "halt"} \
F = "halt" \
delta = "definit a cada programa"
$

$M$ és una 7-tupla (i.e. una tupla de 7 objectes) que simbolitza formalment tota la màquina de Turing.

Tant $b$ com $Sigma$ han de pertànyer a $Gamma$, que és el conjunt de tots els símbols possibles de la cinta. $Sigma$ indica els símbols d'entrada, aquells que es permet que estiguin als continguts inicials de la cinta; $b$ indica el símbol blanc, l'únic símbol que es permet que es repeteixi infinitament.

El terme _estats_ és sovint motiu de confusió, ja que formalment només es refereix a una variable que pertany a $Q$ que indica l'estat de la màquina pròpiament dit, sense referir-se a les pròpies instruccions, que estan definides per $delta$, l'anomenada _funció de transició_ per a cada estat. $F$ indica quin és l'_estat final_, és a dir, l'estat que atura el programa.

Aquesta definició és molt semblant a la del tipus de màquina de Turing més conegut, _busy beaver_, amb la diferència que la nostra accepta $0$ com a símbol d'entrada i els estats i les funcions de transició estan indefinides.

= Objectius

La màquina de Turing no està pensada per ser representada al món físic; és un model matemàtic sobre el qual es formalitzen els algoritmes. Això no obstant, crear un model de la màquina de Turing ajuda a materialitzar aquest element clau de la informàtica teòrica, encara que sigui només de forma visual.

Si bé hom podria considerar la utilitat pràctica d'aquest projecte nul·la, creiem que la màquina de Turing és un concepte molt interessant, tant per la seva gran importància actual com la seva potència computacional. Això últim és especialment important, perquè significa que només aplicant el concepte bàsic de màquina de Turing, el nostre projecte és capaç, en sentit literal, de resoldre ---gairebé--- qualsevol problema computacional.

Som conscients que és molt difícil crear-ne una semblant a les representacions comunes. Per això, hem simplificat la representació perquè el projecte sigui viable.


= Estructura del projecte // = disseny del projecte, per no confondre amb el disseny 3D
== Parts del projecte
El nostre projecte es pot dividir en dues parts: la màquina de Turing pròpiament dita i el mòdul de lectura-escriptura. Tota la màquina en si és una caixa.

- *Màquina de Turing.* Ubicada a la part superior de la caixa.
  - *Cinta.* És representada per 30 LEDs, 15 blancs i 15 blaus. Aquesta cinta és més llarga, però un intel·ligent sistema de desplaçament permet moure's per tota la cinta fictícia, de forma que les posicions de les cel·les es mantenen.

  - *Pantalla.* Per mostrar a l'usuari les opcions per controlar la màquina.

  - *Botons.* 8 botons per controlar la màquina.

- *Mòdul lectura-escriptura.* Situat a la part frontal de la caixa. Permet la inserció d'un paper per imprimir-hi un programa codificat en ratlles negres o llegir-ne un programa escrit. El paper es desplaça per una superfície gràcies als motors.

  - *Motors amb roda.* Comencen a girar quan s'espera l'arribada d'un paper. N'hi ha un a cada extrem de la superfície.
  
  - *Retoladors.* Accionats per un servomotor, s'aixequen i baixen per pintar sobre el paper en el moment adequat.

  - *Sensor de color.* Llegeix el paper i envia la informació a la placa. No té gaire precisió, motiu pel qual vam escollir el negre per pintar els papers.

El conjunt de la pantalla i els botons permetran interactuar amb la màquina. Es podrà executar un programa predefinit i veure en acció com la cinta es va actualitzant, i també es podrà "jugar" amb la màquina, utilitzant els botons per controlar-la directament.
  
_Algunes de les parts d'aquesta estructura encara no s'han realitzat._

#pagebreak()
== Diagrama de flux
#figure(caption: [Diagrama de flux.],
[#image("DiagramaDeFlux.jpg")])

= Disseny
Per poder aconseguir que la màquina funcioni de la manera que volíem, vam decidir fer tota l'estructura en disseny 3D. D'aquesta manera, podem controlar amb bastanta precisió on serà cada element.

L'estructura serà com una caixa que, a més de la base i de la tapa, té un pis al mig:
#figure(caption: [Esborrany inicial.],
[#image("Esborrany.JPG", height: 150pt)])

A la primera meitat de la base, passarà el paper per a lectura o dibuix. L'ordre dels elements és: roda 1, sensor de color, retoladors, i roda 2. A la segona meitat, posarem la placa controladora d'aquests elements i de la pantalla LCD (placa 2).
#figure(caption: [Visió lateral base.],
[#image("VisióLateralBase.jpg", height: 150pt)])

Abans de fer el disseny de la base, vam haver de dividir-la en quatre parts, d'acord amb els límits de la impressora. Després, vam haver de tenir en compte com connectaríem cada part amb les altres i amb les parets.

Per a fer-ho, vam decidir fer servir un mecanisme semblant a peces Lego per a connectar la base amb les parets, i un altre basat en jocs de taula per a connectar les quatre parts entre elles. A més, abans d'implementar aquests mecanismes, vam fer petites proves per a assegurar-nos que feien el que volíem.

#figure(caption: [Disseny base. La superfície llisa de la part superior],
[#image("DissenyBase.jpg", height: 150pt)]
)
#figure(caption: [Disseny base en perspectiva.],
[#image("DissenyBasePerspectiva.jpg", height: 150pt)]
)

En la primera prova, no vam tenir èxit. Vam analitzar-la i vam arribar a la conclusió que havíem de disminuir una mica la mida de la part que entraria al forat.
#figure(caption: [Prova encaix 1, separats.],
[#image("1aProvaEncaix1.JPG", height: 150pt)],
)
#figure(caption: [Prova encaix 1, junts.],
[#image("1aProvaEncaix2.JPG", height: 150pt)]
)

En la segona prova, sí que vam tenir èxit. Per tant, ja sabíem la proporció de les mides del forat i del connector i podíem finalment aplicar-la al disseny de la base.

#figure(caption: [Prova encaix 2, separats.])[#image("2aProvaEncaix1.JPG", height: 150pt)]

#figure(caption: [Prova encaix 2, junts.],
[#image("2aProvaEncaix2.JPG", height: 150pt)])

#figure(caption: [Prova encaix 2, perspectiva.],
[#image("2aProvaEncaix3.JPG", height: 150pt)]
)


A més a més, vam fer tres altres proves: una per a comprovar l'encaix dels botons, una altra pel de la pantalla LCD, i una per a la politja que controlarà el retolador.
#columns(2, gutter: 11pt)[#figure(caption: [Prova botons,estructura.],
[#image("ProvaBotons1.JPG", height: 150pt)]
)
#figure(caption: [Prova botons, amb botó.],
[#image("ProvaBotons2.JPG", height: 150pt)]
)
#figure(caption: [Prova pantalla, estructura.],
[#image("ProvaLCD.JPG", height: 150pt)]
)
#figure(caption: [Prova pantalla, amb LCD.],
[#image("ProvaLCD2.JPG", height: 150pt)]
)
#figure(caption: [Disseny politja.],
[#image("DissenyPolitja.jpg", height: 150pt, width: 320pt)]
)
#figure(caption: [Politja, separades.],
[#image("Politja.JPG", height: 150pt)]
)
#figure(caption: [Politja, connexió amb servo.],
[#image("PolitjaiServo.JPG", height: 150pt)]
)
#figure(caption: [Encaix politja amb servo.],
[´#image("EncaixPolitja.JPG", height: 150pt)]
)]

Ara, la meitat de la base on posarem la placa no té molt de misteri, només s'ha d'aplicar els mecanismes proposats. En canvi, a la part on passa el paper, vam dissenyar el camí que seguirà el paper en una alçada més alta que la resta per a delimitar-lo.
#figure(caption: [Mitja base.],
[#image("MItjaBase.JPG", height: 150pt)]
)

Cal mencionar també que, per a encaixar tots els elements de la base on els volem, vam haver de dissenyar una paret entre les dues meitats de la placa. En ella, s'encaixaran els motors que mouen les rodes i el sensor de color.
#columns(2, gutter: 11pt)[#figure(caption: [Disseny parets.],
[#image("DissenyParetsPerspectiva.jpg", height: 150pt)])
#figure(caption: [Disseny parets, separades],
[#image("DissenyParetsSeparades.jpg", height: 150pt)]
)]

En el pis de dalt, posarem la politja i el servomotor que controlaran el retolador, les _protoboards_ dels LEDs i dels botons, la pantalla LCD, i la placa controladora dels LEDs i dels botons.

Finalment, la tapa tindrà forats per a encaixar els LEDs, els botons i la placa LCD.
#columns(2, gutter: 11pt)[
#figure(caption: [Disseny tapa.],
[#image("DissenyTapa.jpg", height: 150pt)])
#figure(caption: [Impressió botons.],
[#image("Impressió.JPG", height: 150pt)])
#figure(caption: [Un quart de la tapa, botons, visió de dalt.],
[#image("MigBotonsTapa.JPG", height: 150pt)])
#figure(caption: [Un quart de la tapa, botons, visió de baix.],
[#image("MigBotonsTapaAbaix.JPG", height: 150pt)])
#figure(caption: [Comprovació botons tapa.],
[#image("BotonsTapaComprovació.JPG", height: 150pt)])
]

= Electrònica
== Plaques
La placa que hem escollit al nostre projecte és l'Arduino Mega. En un primer moment, teníem pensat usar l'ESP32 Steamakers, però no té suficient pins perquè es puguin connectar tots els LEDs. L'Arduino Mega, amb 54 pins digitals, ens era molt més còmode, no només pels pins, sinó també per l'ús de l'Arduino IDE---ja no feia falta portar un pen drive amb l'Arduino IDE preinstal·lat ni esperar tres minuts a que compili.

Un inconvenient de l'Arduino Mega, no obstant, és que té menys memòria i un processador menys potent que l'ESP32. Durant les proves codi, però, això no ha causat cap problema.

Tot i això, ens hem vist obligats a utilitzar dues plaques per distribuir l'ús de l'energia i per no haver de fer-se camí entre els cables dels LEDs. Aquesta és la distribució que hem escollit:

#table(columns: 2, rows: 2,
[*Placa 1* _tape_], [*Placa 2* _master_],
[
  LEDs

  Botons
],
[
  Motors

  Pantalla
  
]
)

La placa 2 és el controlador principal ---d'aquí el nom _master_--- i controla la pantalla i el mòdul de lectura-escriptura de programes. La placa 1 controla els LEDs seguint les instruccions de _master_ i també l'avisa quan es prem algun botó.


== Components
#table(
  columns: (auto, auto, 1fr),
  align: horizon,
  stroke: 0pt,
  [*Component*], [*Descripció*], [*Imatge*],
  "Cable USB","Connexió entre la placa i l'ordinador", image("cableUSB.jpg"),
  "Cable dupont", "Connexió entre components", image("cable2.jpg"),
  "Sensor de color TCS3200", "Sensor de color RGB", image("SensorDeColor.jpg"),
  "Pantalla LCD I2C", "Pantalla de cristall líquid", image("PantallaLCD.jpg"),
  "Botons", "Aparells de commanament que 
permeten el pas del corrent quan
accionats", image("Botó.jpg"),
  "Motor DC amb rodes", "Motor que transforma l'energia
elèctrica en energia mecànica 
per a les rodes", image("MotorDC.jpg"),
  "Controladora L298N", "Controladora del motor DC", image("Controladora.jpg"),
  "LEDs", "Díodes emissors de llum", image("LED.jpg"),
  "Servomotor", "Actuador que permet controlar
  amb preció la posició i el moviment
  de l'eix", image("Servo.jpg"),
  
)
== Connexions
#table(
  columns: (auto, auto, auto),
  stroke: 0pt,
  [*Pin*], [*Component*], [*Placa*],
  "38-52", "LEDs blaus", "1",
  "22-37", "LEDs blancs", "1",
  "22", "Sensor de color - S0", "2",
  "23", "Sensor de color - S1", "2",
  "24", "Sensor de color - S2", "2",
  "25", "Sensor de color - S3", "2",
  "26", "Sensor de color - OUT", "2",
  "-", "Botons", "1",
  "-", "Pantalla LCD", "2",
  "-", "Servomotor", "2",
  "-", "Controladora L298N", "2",
  "RX1 (19) i TX1 (18)", "Connexió entre plaques", "1 i 2",
  
)
#columns(2, gutter: 11pt)[#figure(caption: [Connexions a la placa.],
[#image("PlaquesiConnexions.JPG", height: 250pt)])
#figure(
  image("Connexions.JPG", height: 150pt)
)]

== Esquema electrònic
#figure(
  image("fritzing.jpg"),
)

= Programació
== Entorn

L'entorn que hem escollit per a la programació del projecte, igual que a l'anterior, és PlatformIO amb C++. Aquesta plataforma ens ha permès, a més, poder compilar el codi de cada placa per separat. Això es pot observar al fitxer `plaformio.ini`, que configura l'entorn:

#sourcecode[
  ```yaml
[env:master]
build_src_filter = 
	+<master/**/*.cpp>
	+<master/**/*.h>
	+<common/**/*.cpp>
	+<common/**/*.h>

[env:tape]
build_src_filter = 
	+<tape/**/*.cpp>
	+<tape/**/*.h>
	+<common/**/*.cpp>
	+<common/**/*.h>

  ```
]

Desgraciadament, Arduino IDE no accepta subcarpetes al projecte. Per tant, hem hagut d'ampliar el nostre script de còpia de fitxers perquè també "aplani" les rutes, de forma que tots els fitxers estiguin a l'arrel.

== Estructura
A continuació, s'exposa l'estructura del codi. S'obvien els fitxers `main.cpp` (i.e. `sketch.ino`).

- `common`: Codi que s'utilitza a les dues plaques.

  - `Communication.h` / `Communication.cpp`: Conté la classe `Communication` que administra l'intercanvi de les instruccions entre les plaques, definides per l'_enum_ `Codes`.

  - `Head.h`: Conté els _enums_ `Direction` i `Cell`, dins el _namespace_ `Computer`.

  - `pins`: Carpeta amb totes les classes per controlar els pins. Mateixa estructura que al projecte Casa Domòtica.

- `master`

  - `Computer.h` / `Computer.cpp`: Conté la classe `Program` dins el _namespace_ `Computer`, que està compost pels _structs_ `State` i `Instruction`. El fitxer _source_ és el més extens de tot el projecte, ja que conté les llargues funcions `decode()` i `encode()` de la classe `Program` que converteixen programes a binari i viceversa.

- `tape`

  - `Tape.h` / `Tape.cpp`: Conté la classe `Tape` dins el _namespace_ `Computer`.
  - `LEDArray.h` / `LEDArray.cpp`: Conté la classe `LEDArray`, que serveix per controlar un rang de pins a la vegada de forma que es puguin indexar.
  
== Diagrama de classes

El diagrama de classes d'aquest projecte és més simple, però amaga darrere un codi ben complex (vegeu apartat següent).

S'ha intentat respectar la notació dels diagrames UML, en què diferents tipus de relacions són representades per fletxes diferents:

- Una línia contínua indica una relació genèrica, quan dues classes es comuniquen d'alguna forma.

- Una fletxa amb l'extrem buit indica inherència.

- Una fletxa amb l'extrem en forma de rombe indica composició, quan una classe té com a membre una altra classe.

- Una fletxa normal indica associació, quan una classe té accés a una altra perquè la té com a argument d'algun mètode.

#figure(caption: "Diagrama de classes.")[
  #image("classDiagram.png")
]








== Explicació del codi

=== `Computer.h` / `Computer.cpp`

Aquest parell _header-source_ declara i defineix l'estructura de dades per a la computació dels algoritmes. En aquest segment de codi, es fa un ús considerable dels punters.

==== Classes bàsiques
Els _estats_ estan representats per la classe `State` i les instruccions que formen cada _estat_ per la classe `Instruction`.

#sourcecode[
```cpp

struct Instruction {
    bool write;
    Direction dir;
    State* nextState; // pot ser nullptr
};

struct State {
    int id = -1;
    Instruction ifZero = {ZERO, RIGHT, nullptr};
    Instruction ifOne = {ZERO, RIGHT, nullptr};
    Instruction ifBlank = {ZERO, RIGHT, nullptr};

    State* operator()(Communication& communication);

    virtual Instruction* operator[](int);

    State(const Instruction& ifZero, const Instruction& ifOne, const Instruction& ifBlank);

    State() = default;
};
```
]

Aquestes classes, de fet, formen un graf: `State` és el vèrtex i cada instància de la classe `Instruction` pot formar una aresta amb un altre `State`.

Que el membre `nextState` de `Instruction` sigui `nullptr` causa que el programa s'aturi si s'arriba a executar la instrucció.

El membre `id` de `State` només s'utilitza durant la codificació, i serveix per identificar els _estats_ enlloc de l'adreça de memòria. No fa falta que sigui especificada quan es crea una instància de la classe manualment.

L'_overload_ de l'operador `()` rep un objecte de comunicació com a argument i executa l'estat, amb les instruccions de comunicació adequades. Si la instrucció té un estat següent a executar, no es fa recursivament i es retorna un punter a l'altre estat.

#sourcecode[
```cpp
State* State::operator()(Communication& communication) {
    communication.sendCode(Codes::QUERY);

    while (!communication.received());

    Codes cell = communication.readCode();

    Instruction* instruction;

    switch (cell) {
        case Codes::BLANK:
            instruction = &ifBlank;
            break;
        case Codes::ZERO:
            instruction = &ifZero;
            break;
        case Codes::ONE:
            instruction = &ifOne;
            break;
        default:
            Serial.println("Wrong code received.");
            return nullptr;
    }

    
    communication.sendCode(
      static_cast<Codes>(static_cast<int>(instruction->write))
    );
    delay(200);

    communication.sendCode(
      static_cast<Codes>(static_cast<int>(instruction->dir))
    );
    delay(200);

    return instruction->nextState;
}
```
]

L'_overload_ de l'operador `[]` rep un enter entre 0 i 2 retorna un punter a la instrucció `ifZero`, `ifOne` o `ifBlank` segons el nombre.

==== Classe `Program`
La classe està definida de la següent manera:

#sourcecode[
```cpp
class Program {
protected:
    State** states;
    int n;

public:
    explicit Program(State**, int);

    void compute(Communication&);

    int encode(bool*, int);

    static Program decode(bool*, int);

};
```
]

El membre `states` és un _array_ de punters de mida `n`. No conté cada _estat_ directament perquè els llocs buits puguin ser assignats `nullptr`. El punter i la mida són rebuts al constructor.

La funció `compute()` rep un objecte de comunicació com a argument i executa el programa. Ho fa sense recursió per evitar els clàssics errors _stack overflow_.

#sourcecode[
```cpp
void Program::compute(Communication& communication) {
    State* currentState = *this->states;
    while ((currentState = (*currentState)(communication)));
}
```
]

Primer, obté el punter al primer _estat_ a executar i el desa a la variable `currentState`. Després, l'executa i desa el punter rebut a `currentState`. Si el punter és `nullptr`, vol dir que el programa ja ha acabat, i com que `nullptr` es considera fals en un context de booleà, el bucle acaba. Si el punter està definit, aleshores continua el cicle.

#figure(caption: [Diagrama de flux que representa el funcionament de la funció `compute()`])[
#image("compute.png", height: 200pt)]

La funció `encode()` rep un _buffer_ i la seva mida (i.e. un punter que serveix d'_array_), on desarà el programa codificat en booleans (o el que és el mateix, en zeros i uns). El codi d'aquesta funció és una mica més complicat---té gairebé 70 línies. A continuació es simplifica el seu funcionament amb alguna mostra del codi:

- Restablir els IDs de tots els estats i crear un comptador nou
- Per a cada _estat_:
  - Assignar l'ID de l'_estat_ al comptador
  - Per a cada instrucció:
    - Afegir un 0 al _buffer_ si s'escriu un 0, un 1 si s'escriu un 1
    - Afegir un 0 al _buffer_ si es mou a l'esquerra, un 1 si es mou a la dreta
    - Afegir al _buffer_ l'ID de l'estat següent en binari, o tres zeros si el programa s'ha d'aturar


La funció estàtica `decode()` rep una _array_ de booleans que representa un programa i el converteix a un objecte `Program`. Igual que a la funció anterior, a continuació s'explica el seu funcionament:

- Crear una _array_ d'_estats_ parcials (i.e. amb instruccions parcials, que enlloc de tenir un punter a l'estat següent tenen un ID) d'una mida preestablerta 
- Per cada 15 bits:
  - Per cada 5 bits:
    - Assignar el primer bit al membre `write`
    - Assignar el segon bit al membre `dir`
    - Convertir els tres bits restants a un nombre decimal i assignar-lo al membre `nextStateId`
  - Crear l'_estat_ parcial amb les instruccions descodificades i afegir-lo a l'_array_
- Assignar els punters restants de l'_array_ a `nullptr`.
- Copiar els ítem de l'_array_ d'_estats_ parcials a un nou _array_ d'_estats_.
- Per cada _estat_ parcial:
  - Per cada instrucció:
    - Cercar l'adreça de memòria de l'_estat_ següent utilitzant l'ID a l'_array_ d'_estats_ i desar-la a l'_estat_ corresponent no parcial
- Crear l'objecte `Program` a partir de l'_array_ d'_estats_ i retornar-lo.

Aquestes són les declaracions de les classes parcials, que s'utilitzen durant la descodificació.

#sourcecode[
```cpp
struct PartialInstruction : Instruction {
    int nextStateId;
};

struct PartialState : State {
    PartialInstruction ifZeroPartial;
    PartialInstruction ifOnePartial;
    PartialInstruction ifBlankPartial;

    PartialState(
            const PartialInstruction& ifZeroPartial, const PartialInstruction& ifOnePartial,
            const PartialInstruction& ifBlankPartial);

    PartialInstruction* operator[](int) override;

};
```
]

L'única diferència entre `PartialInstruction` i un `Instruction` és que el primer té un membre anomenat `stateNextId`, que indica l'ID del següent _estat_ enlloc de la seva adreça de memòria (ja que aquesta no es coneix quan es codifica). Aleshores, `PartialState` afegeix les instruccions de tipus `PartialInstruction`. El constructor i l'_overload_ de l'operador `[]` de `PartialState` es reimplementen perquè utilitzin aquests nous membres.



=== `Tape.h` / `Tape.cpp`
La classe `Tape` està definida així:

#sourcecode[
```cpp
#define TAPE_LENGTH 128
#define VIEW_LENGTH 15

class Tape {
public:
    Tape();

    void begin();


    void write(Cell);

    void update();

    void update(int, int);

    bool move(Direction);

    Cell& read();

    int head = 7;

private:
    LEDArray blanks{22, 37};
    LEDArray ones{38, 52};

    Cell buffer[TAPE_LENGTH]{};
};
```
]

Com es pot observar al principi del codi, es defineixen dues _macros_ `TAPE_LENGTH` i `VIEW_LENGTH`. Es veu clara, doncs, la diferència entre el que es veu als LEDs i la cinta total, que es troba a `buffer`.

La implementació de la majoria de funcions de la classe `Tape` és trivial. Fixem-nos, però, en la funció `move()`

#sourcecode[
```cpp
bool Tape::move(Direction d) {
    if (d == LEFT) {
        if (head == VIEW_LENGTH / 2) return false;

        --head;
    } else {
        if (head == TAPE_LENGTH - VIEW_LENGTH / 2 - 1) return false;

        ++head;
    }

    Serial.println("Head pos " + String(head));

    update();
    return true;
}
```
]

La funció retorna `false` si el moviment no és possible, cosa que passa quan es causaria que els primers o últims LEDs no tinguessin una cel·la corresponent. Si el moviment és possible, aleshores simplement suma o resta una unitat a la variable `head`, que indica la posició del capçal.

Per actualitzar tots els LEDs, es crida la funció `update()` sense arguments.

#sourcecode[
```cpp
void Tape::update() {
    int j = 0;
    for (int i = head - VIEW_LENGTH / 2; i < head + VIEW_LENGTH / 2 + 1; ++i) {
        update(i, j);
        ++j;
    }
}

void Tape::update(int bufferInd, int ledInd) {
    Cell& c = this->buffer[bufferInd];
    
    this->ones.set(ledInd, c == ONE);
    this->blanks.set(ledInd, c == BLANK);
}
```
]

La funció `update()` amb arguments actualitza els dos LEDs d'una cel·la per a una posició concreta. Aquest _overload_ és cridat per l'anterior per a cada cel·la visible.

=== `Communication.h` / `Communication.cpp`

L'_enum_ `Codes` defineix les instruccions que poden transmetre les plaques. En el cas d'aquest _enum_, li afegim la paraula `class` per evitar que els seus membres siguin convertits implícitament a `int`.

#sourcecode[
```cpp
enum class Codes : int {
    NONE = -1,

    ZERO = 0, ONE = 1, BLANK = 2,

    LEFT = 3, RIGHT = 4, QUERY = 5, WRITE = 6, RESET = 7,

    BUTTONPRESSED = 8,

    ERROR_OUT_OF_RANGE = 9, ERROR_INVALID_CHARACTER = 10
};
```
]

La classe `Communication` és un _wrapper_ per sobre la interfície de `Serial` nativa d'Arduino. El constructor rep un punter a un objecte de tipus `HardwareSerial` i la velocitat de transmissió.

#sourcecode[
```cpp
class Communication {
public:
    Communication(HardwareSerial*, long);

    void begin();


    void sendChar(char);

    void sendCode(Codes);


    char readChar();

    Codes readCode();

    String readString();

    int received();


    HardwareSerial* serial;
protected:
    long speed;
};
```
]

Les funcions que ens interessen són `sendCode()` i `readCode()`. Estan implementades de la següent forma:

#sourcecode[
```cpp
void Communication::sendCode(Codes code) {
    this->serial->write(static_cast<int>(code));
}

Codes Communication::readCode() {
    return static_cast<Codes>(this->serial->read());
}
```
]

Ja que `Codes` és un `enum class`, s'ha de fer un `static_cast` per convertir-lo a un `int`. La conversió inversa requereix aquest constructe tant en `enum class` com _enums_ normals. És evident que fallarà si cap instrucció està associada al nombre llegit.

Com es pot observar, les funcions de `Communication` només ofereixen una forma més còmoda de tractar la comunicació entre les plaques, aplicant els _casts_ necessaris.

== Repositori

El repositori de GitHub amb tot el codi del projecte, incloent els diagrames, es troba #link("https://github.com/alex-touza/simulador-maquina-turing", "aquí").

= Conclusions
Com vist anteriorment, l'objectiu d'aquest projecte era dissenyar una màquina de Turing simplificada fent servir una placa Arduino MEGA 2560.

Si bé encara no hem arribat a complir del tot aquest objectiu, esperem avançar més el projecte durant els propers dies.

== Avaluació
Aquest projecte ha sigut bastant desafiant, especialment per la qüestió de la gestió del temps. Desafortunadament, no vam aconseguir acabar de muntar tot el nostre projecte. Ens falten algunes peces finals de l'estructura per a imprimir i part del codi. 

Això és degut especialment al fet de no tenir temps suficient disponible, cosa que va passar perquè el projecte del segon trimestre es va allargar molt, traient temps del tercer trimestre, i perquè vam tenir alguns contratemps durant aquestes setmanes.

Cal mencionar que va haver-hi entorn de dues o tres sessions en les quals el nostre ordinador no funcionava, o havia desaparegut, cosa que ens va treure bastant temps fins que hem pogut trobar una solució.

Esperem poder enllestir el projecte durant la setmana següent.

== Propostes de millora

En aquest moment, la nostra prioritat és acabar el projecte com estava planejat. Sabem que era un projecte considerablement ambiciós, i creiem que estarem prou satisfets si aconseguim fer tot el que ens havíem proposat.

Si haguéssim d'afegir-hi alguna cosa més, consideraríem implementar un sistema de programació al propi programa de la placa, de forma que l'usuari pugui crear els seus programes amb la pantalla i els botons.

