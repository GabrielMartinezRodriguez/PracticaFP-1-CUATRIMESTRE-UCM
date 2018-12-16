//Gabriel Martinez Rodriguez Y Oscar Molano Buitrago
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std;

/*TIPOS DEFINIDOS*/
typedef int tCartasPorAparecer[8];
typedef float tConjuntoCartas[40];

/*CONSTANTES*/
const char tab = 9;/*EN CODIGO ASCII EL 9 ES UNA TABULACION*/



/*FUNCIONES PRINCIPALES LLAMADAS DESDE EL MAIN*/
int menu();//Imprime menu en pantalla y pide un valor a usuario, se repite hasta que este entre 1 y 4. Devuelve el valor
void FuncionModoA(ifstream &baraja);//En ella se lleva a cabo todo lo referente al modo A(Declaracion de variables unicas del modo correspondiente y llamadas a otras funciones)
void FuncionModoB(ifstream &baraja);//En ella se lleva a cabo todo lo referente al modo B(Declaracion de variables unicas del modo correspondiente y llamadas a otras funciones)
void FuncionModoC(ifstream &baraja);//En ella se lleva a cabo todo lo referente al modo C(Declaracion de variables unicas del modo correspondiente y llamadas a otras funciones)
void FuncionModoD(int NPartida);//En ella se lleva a cabo todo lo referente al modo D(Declaracion de variables unicas del modo correspondiente y llamadas a otras funciones)

/*FUNCIONES VERSION 1*/
float ModoA(int max_cartas, ifstream &baraja);//Se lleva a cabo el turno de la maquina o el humano del ModoA, devuelve los puntos obtenidos.
float modoBhumano(int max_cartas, ifstream &baraja);//Se lleva a cabo el  del humano del ModoB, devuelve los puntos obtenidos.
float modoBmaquina(int max_cartas, ifstream &baraja, float puntos_humano);//Se lleva a cabo el turno de la maquina del ModoB, devuelve los puntos obtenidos.
int determinaGanador(float puntos_humano, float puntos_maquina);//Recibe los puntos de la maquina y el humano y devuelve 1 si maquia gana o 2 si humano gana

/*FUNCIONE VERSION 2*/
void ModoCHumano(ifstream &baraja, tCartasPorAparecer cartas, float &puntos_humano);//Se lleva a cabo el turno de humano en el modo c y recibe el fichero de texto, las cartasporaparecer inicializadas y los puntos humano a 0
void modoCmaquina(ifstream &baraja, tCartasPorAparecer cartas, float puntos_humano);//Se lleva a cabo el turno de la maquina en el modo c. Recibe el fichero de texto, las cartas por aparecer y los puntos del humano

/*FUNCIONES VERSIONES 3*/
void inicializa(tConjuntoCartas &mazo);//Rellena un array de tipo tconjuntocartas con el siguiente patron 4 veces 1,2,3,4,5,6,7,0.5,0.5,0.5
void crearMazo(tConjuntoCartas &mazo);//Barajea el mazo ya inicializado
void rellenar(tConjuntoCartas &cartas);//Rellena un array de tipo tconjuntoscartas todo a 0
void ModoDHumano(tConjuntoCartas &mazo, tCartasPorAparecer cartas, tConjuntoCartas & cartasHumano, float & puntos);//Se lleva a cabo el turno del humano en el modo D.Recibe el mazo, las cartas por aparecer, las cartas humano (inicializado con todo 0), y una variable puntos(inicializada a 0)
void modoDmaquina(tConjuntoCartas & mazo, tCartasPorAparecer cartas, float puntosHumano, tConjuntoCartas & cartasMaquina, float & puntos);//Se lleva a cabo el turno del humano en el modo D.Recibe el mazo, las cartas por aparecer, las cartas de la maquina (inicializado con todo 0), los puntos del humano y una variable puntos(inicializada a 0)
void ImprimirCartas(tConjuntoCartas Cartas, float Puntos_Totales);//Muestra por pantalla todas las cartas en el el tconjuntocartas hasta llegar a una posicion con indice cero y luego muestra los puntos totales
void SacarCarta(tConjuntoCartas mazo, float &cartas);//Saca una carta de la variable del array tipo tConjuntoCartas, la introduce en la variable cartas y desplaza una posicion a la izquierda todo el array;
void desplazar(tConjuntoCartas mazo);//Desplaza todo el array una posicion a la izquierda. (el extremo izquierdo se pierde es sustituido por el valor de la posicion 1 y el extremo derecho se iguala a NULL)
void AnnadirCarta(tConjuntoCartas mazo, float carta);//Recibe una carta y la introduce en la primera posicion que no sea igual a 0 
int CuentaCartasSacadas(tConjuntoCartas Cartas);//Recibe una varible tipo tConjuntoCartas, y cuenta hasta encontrar un 0 en el array y devuelve el numero de cartas
int ComparadorNCartas(tConjuntoCartas CartasHumano, tConjuntoCartas  CartasMaquina);//Devuelve 1 si humano ha sacado menos cartas y 2 si es la maquina quienaha sacado menos carats. En caso de empate devuelve 1 o 2 aleatoriamente
void RegistrarPartidaTxt(int Comparador, int Npartida, tConjuntoCartas CartasHumano, tConjuntoCartas CartasMaquina, float PuntosMaquina, float PuntosHumano);//Recibe todos los datos necesarios para escribir el registro de la partida en un archivo txt con nombre el numero cardinal de la partida

/*FUNCIONES COMUNES A VERSION 2 Y 3*/
void IniciarCartasPorAparecer(tCartasPorAparecer cartas);//Inicia el array de tipo tcartasporaparecer de la siguiente forma: 12,4,4,4,4,4,4,4. 
bool esProbablePasarse(float puntos_maquina, const tCartasPorAparecer cartas);// Recibe los puntos de la maquina y la variable cartas de tipo tCartasPorAparecer, devuelve true si la prop de pasarse supera el 0.5 y false de lo contrario
int CuentaCartas(const tCartasPorAparecer CartasPorAparecer, int contador);//Cuenta las cartas desde el indice contador. Recibe el contador(indice) y las cartas por aparecer 

/*FUNCION COMUN A LA VERSION 1 Y 3*/
void MostrarGanador(int resultado);//Recibe una varible y en funcion de esta muestra por pantalla el ganador




int main() {
	//Variables
	int selector, NPartida = 0;
	bool SeguirJugando = true;
	string NombreFichero;
	ifstream baraja;//fichero para modos A B y C

	//LOOP DE JUEGO, PARA PODER JUGAR TANTAS PARTIDAS COMO QUIERAS
	while (SeguirJugando){

		selector = menu();
		 /*PARA LOS MODOS A,B Y C, SE PIDE QUE SE INTRODUZCA EL NOMBRE DE ARCHIVO DE TEXTO DONDE ESTA 
		  LA BARAJA SIN EL .txt, Y COMPRUEBA SI EL ARCHIVO HA SIDO ABIERTO SI NO LO VUELVE A PEDIR*/
		if (selector >= 0 && selector <= 3) {
			do {
				cout << "Introduzca el nombre del fichero de texto donde esta ubicada la baraja" << endl;
				cin >> NombreFichero;
				NombreFichero.append(".txt");
				baraja.open(NombreFichero);
				if (!baraja.is_open()) {
					cout << "No se ha podido abrir el fichero" << endl;
				}
			} while (!baraja.is_open());
		}
		switch (selector) {
			
			case 1:
				FuncionModoA(baraja);		
				baraja.close();
				break;
			case 2:
				FuncionModoB(baraja);
				baraja.close();
				break;
			case 3:
				FuncionModoC(baraja);
				baraja.close();
				break;
			case 4:
				NPartida++;//AUMENTA EL NUMERO DE LA PARTIDA, PARA QUE EL REGISTRO EN UN FICHERO DE TEXTO TENGA DE NOMBRE EL NUMERO DE PARTIDA
				FuncionModoD(NPartida);
				break;
			default:
				SeguirJugando = false;
		}
		if (SeguirJugando) {
			system("pause");
		}
	}
	return 0;

}

/*FUNCIONES LLAMADAS DESDE EL MAIN*/


int menu() {
	int selector = 0;
	while (selector < 1 || selector>5) {
		system("cls");
		cout << setw(35) << "SIETE Y MEDIA" << endl << "-----------------------------------------------------------" << endl;
		cout << "Selecciones el modo de juego que desea jugar: " << endl;
		cout << "1-Modo A" << endl;
		cout << "2-Modo B" << endl;
		cout << "3-Modo C" << endl;
		cout << "4-Modo D" << endl;
		cout << "5-Salir" << endl;
		cin >> selector;
	}
	return selector;
}
void FuncionModoA(ifstream &baraja) {

	//Declaracion de Variables
	float puntos_humano = 0, puntos_maquina = 0;
	int max_cartas, resultado;
	bool HumanoSePasa = false;

	//Genera un numero aleatorio entre 3 y 5
	srand(time(NULL));
	max_cartas = rand() % 3 + 3;

	//Bloque Visual
	system("cls");
	cout << "MAXIMAS CARTAS: " << max_cartas << endl << endl;;
	cout << "TURNO HUMANO: " << endl;

	//Bloque Humano
	puntos_humano = ModoA(max_cartas, baraja);

	//Bloque Maquina
	if (puntos_humano <= 7.5) {
		cout << "TURNO MAQUINA: " << endl;
		puntos_maquina = ModoA(max_cartas, baraja);
	}
	//Bloque Final	
	resultado = determinaGanador(puntos_humano, puntos_maquina);
	MostrarGanador(resultado);
}

void FuncionModoB(ifstream &baraja) {
	//VARIABLES
	int max_cartas, comprobar, resultado;
	float puntos_humano, puntos_maquina;

	//GENERA UN NUMERO ALEATORIO ENTRE 3 Y 5
	srand(time(NULL));
	max_cartas = rand() % 3 + 3;

	//TURNO HUMANO-VISUAL
	system("cls");
	cout << "TURNO HUMANO:" << endl;
	cout << "MAXIMO DE CARTAS POR JUGADOR: " << max_cartas << endl;

	//PARTIDA HUMANO
	puntos_humano = modoBhumano(max_cartas, baraja);


	if (puntos_humano <= 7.5) {
		//TURNO MAQUINA-VISUAL
		cout << "TURNO MAQUINA:" << endl;
		//PARTIDA MAQUINA
		puntos_maquina = modoBmaquina(max_cartas, baraja, puntos_humano);
	}
	//DETERMINA EL GANADOR Y LO MUESTRA POR PANTALLA
	resultado = determinaGanador(puntos_humano, puntos_maquina);
	MostrarGanador(resultado);

}
void FuncionModoC(ifstream &baraja) {
	//VARIABLES
	float puntos_humano = 0, puntos_maquina = 0;
	tCartasPorAparecer cartas;

	IniciarCartasPorAparecer(cartas);
	//BLOQUE VISUAL
	system("cls");
	cout << "MODO C- TURNO HUMANO:" << endl;
	//TURNO HUMANO

	ModoCHumano(baraja, cartas, puntos_humano);
	//BLOQUE MAQUINA
	if (puntos_humano <= 7.5) {
		cout << "MODO C-TURNO MAQUINA" << endl;
		modoCmaquina(baraja, cartas, puntos_humano);
	}
}
void FuncionModoD(int NPartida) {
	//VARIABLES
	float puntos_humano = 0, puntos_maquina = 0;
	int Comparador = NULL;
	tConjuntoCartas Mazo, CartasHumano, CartasMaquina;
	tCartasPorAparecer CartasPorAparecer;
	
	//SE INICIALIZAN LAS VARIABLES DE TIPO tCartasPorAparecer y tConjuntoCartas
	IniciarCartasPorAparecer(CartasPorAparecer);
	rellenar(CartasHumano);
	rellenar(CartasMaquina);
	inicializa(Mazo);
	crearMazo(Mazo);

	//BLOQUE VISUAL
	system("cls");
	cout << "MODO D- TURNO HUMANO" << endl << "-------------------------------------" << endl;
	//TURNO HUMANO
	ModoDHumano(Mazo, CartasPorAparecer, CartasHumano, puntos_humano);
	//SI HUMANO NO SE HA PASADO SE REALIZA EL TURNO DE LA MAQUINA
	if (puntos_humano <= 7.5) {
		cout << "MODO D- MAQUINA" << endl << "-------------------------------------" << endl;
		//TURNO MAQUINA
		modoDmaquina(Mazo, CartasPorAparecer, puntos_humano, CartasMaquina, puntos_maquina);
		//EN CASO DE IGUALDAD DE PUNTOS, EL GANADOR ES EL QUE HA LOGRADO LA PUNTUACUIN CON MENOR NUMERO DE CARTAS(EN CASO DE IGUAL NUMERO DE CARTAS, ALEATORIAMENTE)
		if (puntos_humano == puntos_maquina) {
			Comparador = ComparadorNCartas(CartasHumano, CartasMaquina);
			MostrarGanador(Comparador);
		}
	}
	//REGISTRA EN UN FICHERO DE TEXTO, EL NUMERO DE PARTIDA, GANADOR, LAS CARTAS QUE HAN SACADO AMBOS JUGADORES (MAQUINA Y HUMANO), Y LA PUNTACION
	RegistrarPartidaTxt(Comparador, NPartida, CartasHumano, CartasMaquina, puntos_maquina, puntos_humano);
}

/*FUNCIONES EXCLUSIVAS DE LA VERSION 1*/
float ModoA(int max_cartas, ifstream &baraja) {
	//VARIABLES
	int contador = 0;
	float turno, puntos = 0;
	bool SeHaPasado = false;
	
	//SE SACAN CARTAS HASTA QUE SE SACAN EL MAXIMO DE CARTAS O SE PASA LA PUNTUACIONDE 7.5
	while (contador < max_cartas && !SeHaPasado) {
		baraja >> turno;
		puntos = puntos + turno;
		//MUESTRA POR PANTALLA LA CARTA SACADA Y LA PUNTUACION ACUMULADA
		cout << contador + 1 << "-Carta: " << turno <<tab<< "Puntuacion: " << puntos << endl;
		contador++;
		if (puntos > 7.5) {
			SeHaPasado = true;
		}
	}
	//DEVUELVE LOS PUNTOS OBTENIDOS
	return puntos;
}
float modoBhumano(int max_cartas, ifstream &baraja) {
	//VARIABLES
	int contador = 1;
	float turno, puntos = 0;
	bool NoPlantarse = true, pasarse = false;

	//BUCLE QUE SE REPITE MIENTRAS NO HAYA SACADO EL MAXIMO DE CARTAS, NO SE PLANTE Y NO SE PASE
	while (contador <= max_cartas && NoPlantarse && !pasarse) {
		baraja >> turno;
		puntos = puntos + turno;
		cout << contador << "-Carta: " << turno << tab << "Puntos: " << puntos << endl;

		if (puntos > 7.5) {
			pasarse = true;
		}
		else if (contador < max_cartas) {
			cout << "Introduzca 1 para pedir otra cartas o 0 para plantarse: ";
			cin >> NoPlantarse;//AL SER UNA VARIABLE BOOLEANA EL 0 ES FALSE Y EL 1 ES TRUE
		}
		contador++;
	}

	if (!NoPlantarse) {
		cout << "Te has plantado, tu puntuacion es: " << puntos << endl;
	}
	return puntos;
}
float modoBmaquina(int max_cartas, ifstream &baraja, float puntos_humano) {
	//VARIABLES
	int contador = 1;
	float turno, puntos = 0;
	bool NoPlantarse = true, pasarse = false;

	//BUCLE QUE SE REPITE MIENTRAS NO HAYA SACADO EL MAXIMO DE CARTAS, NO SE PLANTE(TENGA MENOS PUNTUACION QUE EL HUMANO) Y NO SE PASE
	while (contador <= max_cartas && NoPlantarse && !pasarse) {
		baraja >> turno;
		puntos = puntos + turno;
		cout << contador << "-Carta: " << turno << tab << "Puntos: " << puntos << endl;

		if (puntos > 7.5) {
			pasarse = true;
		}
		if (puntos > puntos_humano) {
			NoPlantarse = false;
		}
		contador++;
	}
	return puntos;
}
int determinaGanador(float puntos_humano, float puntos_maquina) {
	int devolver; // 1 gana humano , 2 gana maquina
	srand(time(NULL));
	//COMPROBACIONES NECESARIAS PARA DETERMINAR EL GANADOR
	if (puntos_humano > 7.5) {
		devolver = 2;
	}
	else if (puntos_maquina > 7.5) {
		devolver = 1;
	}
	else if (puntos_maquina < puntos_humano) {
		devolver = 1;
	}
	else if (puntos_humano == puntos_maquina) {
		devolver = rand() % 2 + 1;
	}
	else {
		devolver = 2;
	}
	return devolver;
}

/*FUNCIONES EXCLUSIVAS DE LA VERSION 2*/

void ModoCHumano(ifstream &baraja, tCartasPorAparecer cartas, float &puntos_humano) {
	//VARIABLES
	bool SeguirSacando = true, SeHaPasado = false;
	float carta;
	int contador = 1, selector, carta_entera;
	
	//SACA CARTAS HASTA QUE EL HUMANO DECIDA NO SEGUIR O SE PASE
	while (SeguirSacando && !SeHaPasado) {
		baraja >> carta;
		puntos_humano = puntos_humano + carta;
		cout << contador << "---> " << carta <<tab<<"Puntos totales--->" << puntos_humano << endl;

		if (puntos_humano > 7.5) {
			SeHaPasado = true;
		}

		//RESTA LA CARTA SACADA A LA VARIABLE CARTAS DE TIPO CARTASPORAPARECER PARA POSTERIORMENTE CALCULAR LA PROP EN MODO MAQUINA
		if (carta != 0.5) {
			carta_entera = int(carta);
			cartas[carta_entera]--;
		}
		else {
			cartas[0]--;
		}

		//SI NO SE HA PASADO PREGUNTA SI QUIERE SACAR OTRA CARTA
		if (!SeHaPasado) {

			cout << "Quieres sacar otra carta?  0-No 1-Si" << endl;
			cin >> selector;

			//PREGUNTA SI QUIERE SACAR UNA CARTA HASTA QUE NO INTRODUZCA UN VALOR VALIDO
			while (selector != 0 && selector != 1) {
				cout << "Introduzca un caracter valido" << endl;
				cout << "Quieres sacar otra carta?  0-No 1-Si" << endl;
				cin >> selector;

			}
			if (selector == 0) {
				SeguirSacando = false;
			}

		}
		else {
			cout << "TU PIERDES, TE HAS PASADO" << endl;
		}
		contador++;
	}

}
void modoCmaquina(ifstream &baraja, tCartasPorAparecer cartas, float puntos_humano) {
	//VARIABLES
	bool Arriesgar = false, SeHaPasado = false, Plantarse = false;
	float carta, puntos_maquina = 0;
	int contador = 1, carta_entera;
	//SEMILLA
	srand(time(NULL));

	//SACA CARTAS HASTA QUE SE PASE O SE PLANTE TENIENDO COMO CONDICION PARA ESTO QUE LA PROB DE PASARSE SEA MAYOR DE 0.5 Y QUE LA PUNTUACION DEL HUMANO SEA LA MISMA
	while (!SeHaPasado && !Plantarse) {
		baraja >> carta;
		puntos_maquina = puntos_maquina + carta;
		cout << contador << "---> " << carta <<tab<<"Puntos Acomulados--->" << puntos_maquina << endl;
		contador++;

		//RESTA LA CARTA SELECIONADA DE LA VARIABLE TIPO CARTAS POR APARECER
		if (carta != 0.5) {
			carta_entera = int(carta);
			cartas[carta_entera]--;
		}
		else {
			cartas[0]--;
		}

		/*HACE LAS COMPROBACIONES SIGUIENTE: SI SE HA PASADO, SI NO SE HA PASADO PERO LA PUNTUACION ES MAYOR QUE LA DEL HUMANO
		Y SI LAS PUNTUCIONES SON IGUALES, Y MUESTRA EL MENSAJE CORRESPONDIENTE */
		if (puntos_maquina > 7.5) {
			SeHaPasado = true;
			cout << "MAQUINA SE HA PASADO, TU GANAS" << endl;
		}
		else {
			if (puntos_maquina >= puntos_humano) {
				if (puntos_maquina == puntos_humano) {
					Arriesgar = esProbablePasarse(puntos_maquina, cartas);//DEVUELVE TRUE SI LA PROP DE PASARSE ES MENOR O IGUAL  QUE 0.5
					if (!Arriesgar) {
						Plantarse = true;
						
						if (rand() % 2 == 0) {
							cout << "EMPATE. EL AZAR DECIDE QUE GANA MAQUINA" << endl;
						}
						else {
							cout << "EMPATE. EL AZAR DECIDE QUE GANA HUMANO" << endl;
						}
					}
				}
				else {
					Plantarse = true;
					cout << "MAQUINA GANA" << endl;
				}
			}
		}

	}

}
/*FUNCIONES EXCLUSIVAS DE LA VERSION 3*/
void inicializa(tConjuntoCartas &mazo) {
	//INTRODUCE EN LA VARIABLE CARTAS DE TIPO tConjuntoCartas TODAS LAS CARTAS DE UNA BARAJA CON EL SIGUIENTE PATRON 1,2,3,4,5,6,7,0.5,0.5,0.5 CUATRO VECES
	for (int contador = 0; contador < 4; contador++) {
		for (int contador2 = 0; contador2 < 7; contador2++) {
			mazo[contador2 + (contador * 10)] = contador2 + 1;
		}
		for (int contador3 = 0; contador3 < 3; contador3++) {
			mazo[contador3 + (contador * 10) + 7] = 0.5;
		}
	}
}
void crearMazo(tConjuntoCartas &mazo) {
	//VARIABLES
	int contador = 0, rand1, rand2;
	float aux;

	//SEMILLA PARA GENERAR NUMEROS ALEATORIOS
	srand(time(NULL));
	//MEDIANTE EL ALGORITMO DE LA BURBUJA INTERCAMBIA 600 VECES UNA CARTA ALEATORIA POR OTRA ES DECIR INTERCAMBIA DOS POSICIONES DEL VECTOR ENTRE SI 600 VECES
	while (contador < 600) {
		rand1 = rand() % 40;
		rand2 = rand() % 40;
		aux = mazo[rand1];
		mazo[rand1] = mazo[rand2];
		mazo[rand2] = aux;
		contador++;
	}
}
void rellenar(tConjuntoCartas &cartas) {
	//RELLENA UNA VARIABLE DE TIPO tConjuntoCartas CON 0
	int contador = 0;
	while (contador < 40) {
		cartas[contador] = 0.0;
		contador++;
	}
}
void ModoDHumano(tConjuntoCartas &mazo, tCartasPorAparecer CartasPorAparecer, tConjuntoCartas &	CartasHumano, float &puntos_humano) {

	bool SeguirSacando = true, SeHaPasado = false;
	float carta;
	int	NCartas = 1, selector;//NCartas es una variable que indica el numero ordinal referente a las cartas
	int carta_entero;

	//La maquina saca carta hasta que se pase de 7 y media o decida plantarse
	while (SeguirSacando && !SeHaPasado) {

		//Saca carta de mazo, y la introduze en CartasHumano
		SacarCarta(mazo, carta);
		AnnadirCarta(CartasHumano, carta);
		puntos_humano += carta;
		NCartas++;

		//Algoritmo que baja una unidad a la variable CartasPorAparecer
		if (carta != 0.5) {
			carta_entero = carta;
			CartasPorAparecer[carta_entero]--;
		}
		else {
			CartasPorAparecer[0]--;
		}
		//Muestra por pantalla todos las cartas en el haber del humano y los puntos acumulados
		ImprimirCartas(CartasHumano, puntos_humano);

		if (puntos_humano <= 7.5) {

			//Consulta si quiere sacar otra carta hasta que meta un caracter valido
			cout << "Quieres sacar otra carta?  0-No 1-Si" << endl;
			cin >> selector;
			while (selector != 0 && selector != 1) {
				cout << "Introduzca un caracter valido" << endl;
				cout << "Quieres sacar otra carta?  0-No 1-Si" << endl;
				cin >> selector;

			}
			if (selector == 0) {
				SeguirSacando = false;
			}
		}
		else {
			SeHaPasado = true;
			cout << "TU PIERDES, TE HAS PASADO" << endl;
		}
	}
}
void modoDmaquina(tConjuntoCartas &Mazo, tCartasPorAparecer CartasPorAparecer, float puntos_humano, tConjuntoCartas &CartasMaquina, float &puntos_maquina) {

	bool Arriesgar = false, MasDeSieteyMedio = false, Plantarse = false;
	float carta;
	int  carta_entero;//SE UTILIZA PARA CAMBIAR UNA VARIABLE DE TIPO FLOAT COMO ES LA CARTA SACADA A UNA VARIABLE DE TIPO INT QUE SERA UTILIZADA COMO INDICE DEL ARRAY TIPO tCartasPorAparecer

	//La maquina saca carta hasta que se pase de 7 y media o decida plantarse
	while (!MasDeSieteyMedio && !Plantarse) {
		//Saca carta de mazo, y la introduze en CartasMaquina
		SacarCarta(Mazo, carta);
		AnnadirCarta(CartasMaquina, carta);

		//Algoritmo que baja una unidad a la variable CartasPorAparecer 
		if (carta != 0.5) {
			carta_entero = int(carta);
			CartasPorAparecer[carta_entero]--;
		}
		else {
			CartasPorAparecer[0]--;
		}

		//Suma la carta a los puntos maquina
		puntos_maquina = puntos_maquina + carta;

		//MUESTRA LAS CARTAS EN EL HABER DE LA MAQUINA Y LOS PUNTOS ACUMULADOS
		ImprimirCartas(CartasMaquina, puntos_maquina);


		//Hace las comporaciones para determinar si seguir sacando cartas y imprime el mensaje correspondiente 
		if (puntos_maquina > 7.5) {
			MasDeSieteyMedio = true;
			cout << "MAQUINA SE HA PASADO, TU GANAS" << endl;
		}
		else {
			if (puntos_maquina >= puntos_humano) {
				if (puntos_maquina == puntos_humano) {

					Arriesgar = esProbablePasarse(puntos_maquina, CartasPorAparecer);
					if (!Arriesgar) {
						Plantarse = true;
					}
				}
				else {
					Plantarse = true;
					cout << "MAQUINA GANA" << endl;
				}
			}
		}
	}
}
void ImprimirCartas(tConjuntoCartas Cartas, float Puntos_Totales) {
	int iterador = 0;
	cout << "Cartas en haber ";
	while (Cartas[iterador] != 0) {
		cout << Cartas[iterador];
		if (Cartas[iterador + 1] != 0) {
			cout << ", ";
		}
		iterador++;
	}
	cout << tab << "Puntos_Totales: " << Puntos_Totales << endl;
}
void SacarCarta(tConjuntoCartas mazo, float &carta) {
	carta = mazo[0];
	desplazar(mazo);
}
void desplazar(tConjuntoCartas mazo) {
	int contador = 1;
	while (contador < 40) {
		mazo[contador - 1] = mazo[contador];
		contador++;
	}
}
void AnnadirCarta(tConjuntoCartas mazo, float carta) {
	int contador = 0;
	while (mazo[contador] != 0) {
		contador++;
	}
	mazo[contador] = carta;
}
int CuentaCartasSacadas(tConjuntoCartas Cartas) {
	//CUENTA LAS CARTAS DEL ARRAY CARTAS HASTA ENCONTRAR UN 0
	int contador = 0;
	while (Cartas[contador] != 0) {
		contador++;
	}
	return contador;
}
int ComparadorNCartas(tConjuntoCartas CartasHumano, tConjuntoCartas  CartasMaquina) {
	//VARIABLES
	int NCartasHumano, NCartasMaquina, ganador;
	//SEMILLA
	srand(time(NULL));
	//GUARDA EL NUMERO DE CARTAS SACADAS DEL HUMANO Y DE LA MAQUINA EN SU CORRESPONDIENTE VARIABLE
	NCartasHumano = CuentaCartasSacadas(CartasHumano);
	NCartasMaquina = CuentaCartasSacadas(CartasMaquina);

	//HACE LAS COMPROBACIONES NECESARIAS PARA DETERMINAR EL GANADOR 
	if (NCartasHumano <= NCartasMaquina) {
		if (NCartasHumano < NCartasMaquina) {
			ganador = 1;
		}
		else {
			ganador = rand() % 2 + 1;
		}
	}
	else {
		ganador = 2;
	}
	//DEVUELVE 1 SI GANA HUMANO Y 2 SI GANA MAQUINA
	return ganador;
}
void RegistrarPartidaTxt(int Comparador, int NPartida, tConjuntoCartas CartasHumano, tConjuntoCartas CartasMaquina, float PuntosMaquina, float PuntosHumano) {
	//VARIABLES
	int iterador = 0;
	string NombreFichero;
	ofstream txt;
	//TRANSFORMA UN ENTERO A TIPO STRING
	NombreFichero = to_string(NPartida);
	//SE AÑADE AL FINAL DEL STRING LOS CARACTERES .txt
	NombreFichero.append(".txt");
	//SE CREA UN FICHERO DE TEXTO CON NOMBRE -> NombreFichero el cual indica el numero de partida
	txt.open(NombreFichero);
	
	//TODO ESTE BLOQUE ESCRIBE EN EL FICHERO DE TEXTO EL GANADOR,EL NUMERO DE PARTIDA, LAS CARTAS DEL HUMANO, LAS DE LA MAQUINA, LOS PUNTOS DE LA MAQUINA Y EL HUMANO
	txt << "Partida: " << NPartida << endl;
	txt << tab << "Humano:" << endl;
	txt << tab << tab << "Cartas: ";
	while (CartasHumano[iterador] != 0) {
		txt << CartasHumano[iterador] << " ";
		iterador++;
	}
	txt << endl;
	txt << tab << tab << "Puntuacion: " << PuntosHumano << endl;
	txt << tab << "Maquina:" << endl;
	txt << tab << tab << "Cartas: ";
	iterador = 0;
	while (CartasMaquina[iterador] != 0) {
		txt << CartasMaquina[iterador] << " ";

		iterador++;
	}
	txt << endl;
	txt << tab << tab << "Puntuacion: " << PuntosMaquina << endl;
	txt << "Ganador: ";
	if (PuntosHumano <= 7.5) {
		if (PuntosMaquina <= 7.5) {
			if (PuntosMaquina <= PuntosHumano) {
				if (PuntosHumano == PuntosMaquina) {
					if (Comparador == 1) {
						txt << "Humano";
					}
					else {
						txt << "Maquina";
					}
				}
				else {
					txt << "Humano";
				}
			}
			else {
				txt << "Maquina";
			}
		}
		else {
			txt << "Humano";
		}
	}
	else {
		txt << "Maquina";
	}
	txt.close();
}



/*FUNCIONES COMUNES A VERSION 2 Y 3*/
void IniciarCartasPorAparecer(tCartasPorAparecer cartas) {
	cartas[0] = 12;
	for (int contador = 1; contador < 8; contador++) {
		cartas[contador] = 4;
	}
}
bool esProbablePasarse(float puntos_maquina, const tCartasPorAparecer cartas) {
	//VARIABLES
	int contador = 0;
	float Numero_Cartas_Baraja, Numero_Cartas_Pasan;
	float Prob;
	//CON ESTE ALGORIMO SE ENCUENTRA EL VALOR A PARTID DE QUE CARTA SE PASA, Y ESTE VALOR ES UTILIZADO COMO INDICE PARA CALCULAR LA PROP POSTERIORMENTE
	if (puntos_maquina + 0.5 > 7.5) {
	}
	else {
		contador = 1;
		while (puntos_maquina + contador <= 7.5) {
			contador++;
		}

	}
	//CUENTA TODAS LAS CARTAS DE LA BARAJA
	Numero_Cartas_Baraja = CuentaCartas(cartas, 0);
	//CUENTA LAS CARTAS QUE HACEN QUE SE PASE
	Numero_Cartas_Pasan = CuentaCartas(cartas, contador);
	//SE DIVIDEN LAS DOS VARIABLES ANTERIORES Y CON ELLO SE CALCULA LA PROP
	Prob = Numero_Cartas_Pasan / Numero_Cartas_Baraja;

	if (Prob > 0.5) {
		return false;
	}
	else {
		return true;
	}
}
int  CuentaCartas(const tCartasPorAparecer CartasPorAparecer, int contador) {
	float suma = 0;
	while (contador < 8) {
		suma = suma + CartasPorAparecer[contador];
		contador++;
	}
	return suma;
}

/*FUNCION COMUN A LA VERSION Y 3*/

void MostrarGanador(int resultado) {
	if (resultado == 1) {
		cout << "TU GANAS" << endl;
	}
	else {
		cout << "MAQUINA GANA" << endl;
	}
}












