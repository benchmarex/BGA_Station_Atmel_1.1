# BGA_Station_Atmel_1.1
Program and schematic controller

PL

Program napisany przezmnie w Atmel studio 6 w języku C

Stcja lutownicza do wymiany i lutowania układów BGA w płytach głównych. 

Projekt składa się z podgrzewacza dolnego o mocy 1600W (4 promienniki podczerwieni każdy po 400W) który podgrzewa naprawianą płytę. Zapewnia początkowe grzanie płyty, i poźniej grzanie po profilu lutowniczym. W odpowiednim według  momencie lutowania jest dołączana górna grzałka. Lutowanie i przebieg temperatury odbywa się według zaprogramowanego profilu grzewczego dla grząłki podgrzewacza dolnego i górnego. Jako grzałka górna wykorzystywana jest lampa halogonewa 100W 12V platerowana złotem. Nie jest stosowana żadna dodatkowa optyka. Kontrola temperatury odbywa się za pomocą termopar 'thermocouple' są to 2 termopary typu K produkcji Omega o średnicy kulki 80um. Jedna termopara jest przyklajana w pobliże lutowanego układu bga około 1cm po tej samej stronie co układ BGA za pomocą taśmy kaptonowej. Druga termopara jest bezpośrednio przyklejona na lutowanym układzie BGA. Program jest automatyczny tzn wystrczy uruchomić lutowanie i cały proces lutowanie przebiegnie automatycznie, poza poózeniem i zdjeciem układu :).  Podczas wykonia programu lutowania istnieje możliwość wstrzymania, cofnięcia lub przyspieszenia programu. Czasem jest to wymagane ze względu na czynniki losowe np. odklejenie sie termopary. Dodatkowo jest wbudowany mechanizm zabezpieczający przed nadmierną róznicą temperatur pomiedzy płytą i lutowanym układem. Brak takiego zabezpeiczenia grozi zniszczeniem układu lub płyty (wygięcia, rozwarstwienia PCB). 
Komunikaty wyświtlane są na wyswietlaczu LCD, sterowanie odbywa się przciskami. 


EN

Program written by me in Atmel studio 6 in C language

Soldering station for replacing and soldering the BGA system in motherboards.

The design consists of a bottom heater with a power of 1600W (4 radiators of 400W each), which heats the repaired board. Provide pre-heating of the board, and subsequent heating after the soldering profile. In any case, according to soldering, the upper heater is attached. The soldering and temperature course behaves according to the heating level standard for the lower and upper heater heaters. As the top heater, a 100W 12V gold-plated halogen lamp is used. It is not an optical group. Temperature control is carried out using thermocouples "thermocouple" are 2 type K thermocouples manufactured by Omega with a diameter of 80um. One thermocouple is glued near the soldered BGA chip about 1cm on the same side as the BGA chip with Kapton. The second thermocouple is directly glued on the soldered BGA chip. The program is automatic, i.e. it is enough to call soldering and the whole soldering process will run real, apart from positioning and removing the system :). While the soldering program is running, it is possible to run, undo or accelerate the program. Sometimes it is required due to random composition, e.g. thermocouple detachment. In addition, it is a mechanism against excessive temperature difference between the board and the soldered system. Lack of such protection may damage the system or the board (bends, delamination of the PCB).
Messages are displayed on the LCD display, operation is carried out with buttons.
