#include "../includes/fractol.h"

/*
 * FUNZIONE JULIA - Calcola il frattale di Julia per un singolo pixel
 *
 * Il frattale di Julia è generato iterando la formula: z = z² + c
 * dove z è un numero complesso che parte da una posizione specifica
 * e c è una costante complessa che determina la forma del frattale.
 *
 * La funzione calcola quante iterazioni servono prima che il punto
 * "sfugga" (diventi maggiore di 2 in modulo) o raggiunga il limite
 * massimo di iterazioni. Questo numero determina il colore del pixel.
 *
 * PARAMETRI:
 * - fractol: puntatore alla struttura contenente tutti i dati del frattale
 *
 * VALORI DI RITORNO:
 * - int: numero di iterazioni eseguite (0 a iteration-1)
 *   Questo valore viene usato per determinare il colore del pixel
 *
 * VARIABILI LOCALI:
 * - zr: Parte reale del numero complesso z (coordinata x)
 * - zi: Parte immaginaria del numero complesso z (coordinata y)
 * - cr: Parte reale della costante c (parametro del frattale)
 * - ci: Parte immaginaria della costante c (parametro del frattale)
 * - tmp_zr: Variabile temporanea per salvare zr durante l'iterazione
 * LOGICA DELLA FUNZIONE:
 * 1. Inizializza il contatore di profondità a 0
 * 2. Converte le coordinate del pixel in coordinate del piano complesso
 *    usando lo zoom (scale) e l'offset (yi, xr)
 * 3. Imposta valori di default per la costante c (-0.8, 0.156)
 * 4. Se l'utente ha specificato parametri personalizzati (ci != 0),
 *    usa quelli invece dei valori di default
 * 5. Esegue il ciclo di iterazione principale:
 *    - Continua finché il punto non "sfugge" (modulo > 2) O raggiunge il limite
 *    - Applica la formula di Julia: z = z² + c
 *    - Salva zr in tmp_zr prima di modificarlo (necessario per calcolare zi)
 *    - Calcola nuova parte reale: zr² - zi² + cr
 *    - Calcola nuova parte immaginaria: 2 * zi * tmp_zr + ci
 *    - Incrementa il contatore di iterazioni
 * 6. Restituisce il numero di iterazioni eseguite
 *
 * CONCETTO MATEMATICO:
 * - Piano complesso: Ogni pixel corrisponde a un punto nel piano complesso
 * - Iterazione: La formula z = z² + c viene applicata ripetutamente
 * - Fuga: Se il modulo di z diventa > 2, il punto "sfugge" all'infinito
 * - Colore: Il numero di iterazioni prima della fuga determina
 *  il colore del pixel
 * - Costante c: Determina la forma specifica del frattale di Julia
 *
 * VALORI DI DEFAULT:
 * - cr = -0.8 e ci = 0.156 creano un frattale di Julia molto famoso e bello
 * - Ogni combinazione di cr e ci produce un frattale diverso
 * - L'utente può sperimentare con valori diversi per vedere forme diverse
 */
int	julia(t_fractol *fractol)
{
	double	zr;
	double	zi;
	double	cr;
	double	ci;
	double	tmp_zr;

	fractol->fractal.depth = 0;
	zi = fractol->fractal.width / fractol->fractal.scale + fractol->fractal.yi;
	zr = fractol->fractal.height / fractol->fractal.scale + fractol->fractal.xr;
	cr = -0.8;
	ci = 0.156;
	if (fractol->fractal.ci != 0)
	{
		cr = fractol->fractal.cr;
		ci = fractol->fractal.ci;
	}
	while ((zr * zr) + (zi * zi) < 4
		&& fractol->fractal.depth < fractol->fractal.iteration)
	{
		tmp_zr = zr;
		zr = (zr * zr) - (zi * zi) + cr;
		zi = (2 * zi) * tmp_zr + ci;
		fractol->fractal.depth += 1;
	}
	return (fractol->fractal.depth);
}

/*
* FUNZIONE MANDELBROT - Calcola il frattale di Mandelbrot per un singolo pixel
*
* Il frattale di Mandelbrot è generato iterando la formula: z = z² + c
* dove z inizia sempre da 0 e c è la posizione del pixel nel piano complesso.
*
* La differenza principale con Julia è che:
* - In Julia: z varia, c è costante (parametro dell'utente)
* - In Mandelbrot: z inizia da 0, c è la posizione del pixel
*
* La funzione calcola quante iterazioni servono prima che il punto
* "sfugga" (diventi maggiore di 2 in modulo) o raggiunga il limite
* massimo di iterazioni. Questo numero determina il colore del pixel.
*
* PARAMETRI:
* - fractol: puntatore alla struttura contenente tutti i dati del frattale
*
* VALORI DI RITORNO:
* - int: numero di iterazioni eseguite (0 a iteration-1)
*   Questo valore viene usato per determinare il colore del pixel
*
* VARIABILI LOCALI:
* - zr: Parte reale del numero complesso z (inizia da 0)
* - zi: Parte immaginaria del numero complesso z (inizia da 0)
* - cr: Parte reale della costante c (posizione x del pixel nel piano complesso)
* - ci: Parte immaginaria della costante c
(posizione y del pixel nel piano complesso)
* - tmp_zr: Variabile temporanea per salvare zr durante l'iterazione
*
* LOGICA DELLA FUNZIONE:
* 1. Inizializza il contatore di profondità a 0
* 2. Inizializza z a 0 (zr = 0, zi = 0) - questo è fisso per Mandelbrot
* 3. Calcola c basandosi sulla posizione del pixel:
*    - ci = posizione y del pixel nel piano complesso
*    - cr = posizione x del pixel nel piano complesso
* 4. Esegue il ciclo di iterazione principale:
*    - Continua finché il punto non "sfugge" (modulo > 2) O raggiunge il limite
*    - Applica la formula di Mandelbrot: z = z² + c
*    - Salva zr in tmp_zr prima di modificarlo (necessario per calcolare zi)
*    - Calcola nuova parte reale: zr² - zi² + cr
*    - Calcola nuova parte immaginaria: 2 * zi * tmp_zr + ci
*    - Incrementa il contatore di iterazioni
* 5. Restituisce il numero di iterazioni eseguite
*
* CONCETTO MATEMATICO:
* - Piano complesso: Ogni pixel corrisponde a un punto nel piano complesso
* - Iterazione: La formula z = z² + c viene applicata ripetutamente
* - Fuga: Se il modulo di z diventa > 2, il punto "sfugge" all'infinito
* - Colore: Il numero di iterazioni prima della fuga determina
 il colore del pixel
* - Costante c: È la posizione del pixel stesso nel piano complesso
*
* DIFFERENZE CON JULIA:
* - Mandelbrot: z inizia sempre da 0, c varia (posizione del pixel)
* - Julia: z varia (posizione del pixel), c è costante (parametro dell'utente)
* - Mandelbrot: mostra l'insieme di tutti i punti c per cui z non sfugge
* - Julia: mostra l'insieme di tutti i punti z per un dato c
*
* CARATTERISTICHE DEL FRATTALE DI MANDELBROT:
* - È l'insieme di Mandelbrot: tutti i punti c per cui la sequenza z non diverge
* - Ha una forma caratteristica a "cardioide" con bolle attaccate
* - È auto-simile: contiene copie di se stesso a scale diverse
* - I colori mostrano quanto velocemente i punti sfuggono all'infinito
*/
// Il valore 2 è scelto come soglia perché, nel piano complesso, se il
// modulo di z (|z|) supera 2, la sequenza di iterazioni diverge rapidamente
// e il punto non può far parte del frattale di Mandelbrot.
// In altre parole, se |z| > 2, le iterazioni successive fanno crescere
// indefinitamente il valore di z,quindi sappiamo che il punto esploderà
// e non appartiene al frattale. Se |z| rimane <= 2, il punto potrebbe far
// parte del frattale e la sequenza potrebbe rimanere confinata o entrare
// in cicli stabili.

// depth rappresenta il numero di iterazioni eseguite prima che
// il punto sfugga o raggiunga il limite massimo di iterazioni.
// Perché la profondità è importante?
// Nel frattale di Mandelbrot, un punto che ha una profondità maggiore indica
// che la sequenza di iterazioni non è esplosa facilmente, il che potrebbe
// significare che il punto è "vicino" alla forma del frattale. Un punto
// con una profondità bassa (che esplode velocemente) è invece lontano dal
// frattale.
// Quando generi il frattale, usi la profondità per determinare quanto
// "colorato" è un punto: i punti con una bassa profondità vengono colorati in
// modo diverso rispetto a quelli con una profondità più alta.

// Inizializza depth a 0
// Inizializzo z a zero (essendo il frattale di Mandelbrot)
// Calcolo c in base alla posizione del pixel:

// Ogni pixel sulla finestra grafica rappresenta un punto nel piano complesso.
// I calcoli di cr e ci mappano ogni pixel del piano grafico a una posizione
// nel piano complesso, tenendo conto della
// scala (zoom) e degli spostamenti orizzontale e verticale.
// es: finestra 800x600, vogliamo mappare il pixel 0,0, che è l'angolo
// in alto a sinistra, e mettiamo che scale=200 e che ci sia una traslazione
// di xr=-2 e yi=-1.5.
// La formula serve a convertire le coordinate del pixel (in pixel)
// in coordinate del piano complesso (in numeri reali).
// Quindi per il pixel (0,0):
// ci = 0 / 200 + (-1.5) = -1.5
// cr = 0 / 200 + (-2) = -2
// Quindi il pixel (0,0) mappa al punto complesso (-2, -1.5).

// Il while itera finché il modulo di z è minore di 2 (cioè
// (zr*zr + zi*zi) < 4) e la profondità è inferiore al massimo
// di iterazioni consentite per il determinato frattale.

// Mentre itera, applica la formula di Mandelbrot: z = z² + c
// Aggiorna zr e zi di conseguenza e incrementa la profondità
// Al termine, restituisce la profondità raggiunta
// che indica quante iterazioni sono state eseguite prima
// che il punto ha sfuggito o ha raggiunto il limite massimo

int	mandelbrot(t_fractol *fractol)
{
	double	zr;
	double	zi;
	double	cr;
	double	ci;
	double	tmp_zr;

	fractol->fractal.depth = 0;
	zr = 0;
	zi = 0;
	ci = fractol->fractal.width / fractol->fractal.scale + fractol->fractal.yi;
	cr = fractol->fractal.height / fractol->fractal.scale + fractol->fractal.xr;
	while ((zr * zr) + (zi * zi) < 4
		&& fractol->fractal.depth < fractol->fractal.iteration)
	{
		tmp_zr = zr;
		zr = (zr * zr) - (zi * zi) + cr;
		zi = (2 * zi) * tmp_zr + ci;
		fractol->fractal.depth += 1;
	}
	return (fractol->fractal.depth);
}

/*
 * FUNZIONE RABBIT - Calcola il frattale di Julia "Rabbit" per un singolo pixel
 *
 * Il frattale "Rabbit" è una variante specifica del frattale di Julia
 * generata iterando la formula: z = z² + c
 * dove z è un numero complesso che parte da una posizione specifica
 * e c è una costante complessa particolare che crea la forma "coniglio".
 *
 * La funzione calcola quante iterazioni servono prima che il punto
 * "sfugga" (diventi maggiore di 2 in modulo) o raggiunga il limite
 * massimo di iterazioni. Questo numero determina il colore del pixel.
 *
* PARAMETRI:
* - fractol: puntatore alla struttura contenente tutti i dati del frattale
*
* VALORI DI RITORNO:
* - int: numero di iterazioni eseguite (0 a iteration-1)
*   Questo valore viene usato per determinare il colore del pixel
*
* VARIABILI LOCALI:
* - zr: Parte reale del numero complesso z (coordinata x del pixel)
* - zi: Parte immaginaria del numero complesso z (coordinata y del pixel)
* - cr: Parte reale della costante c (parametro del frattale Rabbit)
* - ci: Parte immaginaria della costante c (parametro del frattale Rabbit)
* - tmp_zr: Variabile temporanea per salvare zr durante l'iterazione
*
* LOGICA DELLA FUNZIONE:
* 1. Inizializza il contatore di profondità a 0
* 2. Converte le coordinate del pixel in coordinate del piano complesso
*    usando lo zoom (scale) e l'offset (yi, xr)
* 3. Imposta valori di default per la costante c (-0.0123, 0.745)
*    Questi valori creano la forma caratteristica del "coniglio"
* 4. Se l'utente ha specificato parametri personalizzati (ci != 0),
*    usa quelli invece dei valori di default
* 5. Esegue il ciclo di iterazione principale:
*    - Continua finché il punto non "sfugge" (modulo > 2) O raggiunge il limite
*    - Applica la formula di Julia: z = z² + c
*    - Salva zr in tmp_zr prima di modificarlo (necessario per calcolare zi)
*    - Calcola nuova parte reale: zr² - zi² + cr
*    - Calcola nuova parte immaginaria: 2 * zi * tmp_zr + ci
*    - Incrementa il contatore di iterazioni
* 6. Restituisce il numero di iterazioni eseguite
*
* CONCETTO MATEMATICO:
* - Piano complesso: Ogni pixel corrisponde a un punto nel piano complesso
* - Iterazione: La formula z = z² + c viene applicata ripetutamente
* - Fuga: Se il modulo di z diventa > 2, il punto "sfugge" all'infinito
* - Colore: Il numero di iterazioni prima della fuga
determina il colore del pixel
* - Costante c: Determina la forma specifica del frattale Rabbit
*
* CARATTERISTICHE DEL FRATTALE RABBIT:
* - È una variante del frattale di Julia con parametri specifici
* - I valori c = -0.0123 + 0.745i creano una forma che ricorda un coniglio
* - Ha una struttura frattale complessa con molteplici "orecchie" e dettagli
* - È auto-simile: contiene copie di se stesso a scale diverse
* - I colori mostrano quanto velocemente i punti sfuggono all'infinito
*
* DIFFERENZE CON ALTRI FRATTALI:
* - Rabbit: Variante di Julia con c = -0.0123 + 0.745i (forma coniglio)
* - Julia: Variante di Julia con c = -0.8 + 0.156i (forma generica)
* - Mandelbrot: c varia (posizione del pixel), z inizia da 0, 
c è la posizione del pixel

 inizia da 0, c è la posizione del pixel
* - Tutti usano la stessa formula base: z = z² + c
*
* VALORI DI DEFAULT SPECIFICI:
* - cr = -0.0123: Parte reale che contribuisce alla forma del coniglio
* - ci = 0.745: Parte immaginaria che crea le "orecchie" caratteristiche
* - Questi valori sono stati scelti per creare la forma distintiva del Rabbit
* - L'utente può sperimentare con valori diversi per vedere forme alternative
*/
int	rabbit(t_fractol *fractol)
{
	double	zr;
	double	zi;
	double	cr;
	double	ci;
	double	tmp_zr;

	fractol->fractal.depth = 0;
	zi = fractol->fractal.width / fractol->fractal.scale + fractol->fractal.yi;
	zr = fractol->fractal.height / fractol->fractal.scale + fractol->fractal.xr;
	cr = -0.0123;
	ci = 0.745;
	if (fractol->fractal.ci != 0)
	{
		cr = fractol->fractal.cr;
		ci = fractol->fractal.ci;
	}
	while ((zr * zr) + (zi * zi) < 4
		&& fractol->fractal.depth < fractol->fractal.iteration)
	{
		tmp_zr = zr;
		zr = (zr * zr) - (zi * zi) + cr;
		zi = (2 * zi) * tmp_zr + ci;
		fractol->fractal.depth += 1;
	}
	return (fractol->fractal.depth);
}
/*
* FUNZIONE MONSTER - Calcola il frattale "Monster" per un singolo pixel
*
* Il frattale "Monster" è una variante modificata del frattale di Mandelbrot
* generata iterando la formula: z = z² + c
* dove z inizia sempre da 0 e c è la posizione del pixel nel piano complesso,
* ma con una modifica importante: c viene sempre reso positivo (valore assoluto).
*
* La funzione calcola quante iterazioni servono prima che il punto
* "sfugge" (diventi maggiore di 2 in modulo) o raggiunga il limite
* massimo di iterazioni. Questo numero determina il colore del pixel.
*
* PARAMETRI:
* - fractol: puntatore alla struttura contenente tutti i dati del frattale
*
* VALORI DI RITORNO:
* - int: numero di iterazioni eseguite (0 a iteration-1)
*   Questo valore viene usato per determinare il colore del pixel
*
* VARIABILI LOCALI:
* - zr: Parte reale del numero complesso z (inizia da 0)
* - zi: Parte immaginaria del numero complesso z (inizia da 0)
* - cr: Parte reale della costante c (posizione x del pixel, sempre positiva)
* - ci: Parte immaginaria della costante c
*       (posizione y del pixel, sempre positiva)
* - tmp_zr: Variabile temporanea per salvare zr durante l'iterazione
*
* LOGICA DELLA FUNZIONE:
* 1. Inizializza il contatore di profondità a 0
* 2. Inizializza z a 0 (zr = 0, zi = 0) - questo è fisso per Monster
* 3. Calcola c basandosi sulla posizione del pixel:
*    - ci = posizione y del pixel nel piano complesso
*    - cr = posizione x del pixel nel piano complesso
* 4. MODIFICA CARATTERISTICA: Applica il valore assoluto a c:
*    - Se ci < 0, allora ci = -ci (rende positivo)
*    - Se cr < 0, allora cr = -cr (rende positivo)
* 5. Esegue il ciclo di iterazione principale:
*    - Continua finché il punto non "sfugge" (modulo > 2) O raggiunge il limite
*    - Applica la formula di Monster: z = z² + c (con c sempre positivo)
*    - Salva zr in tmp_zr prima di modificarlo (necessario per calcolare zi)
*    - Calcola nuova parte reale: zr² - zi² + cr
*    - Calcola nuova parte immaginaria: 2 * zi * tmp_zr + ci
*    - Incrementa il contatore di iterazioni
* 6. Restituisce il numero di iterazioni eseguite
*
* CONCETTO MATEMATICO:
* - Piano complesso: Ogni pixel corrisponde a un punto nel piano complesso
* - Iterazione: La formula z = z² + c viene applicata ripetutamente
* - Fuga: Se il modulo di z diventa > 2, il punto "sfugge" all'infinito
* - Colore: Il numero di iterazioni prima della fuga determina il
colore del pixel
* - Costante c: È la posizione del pixel nel piano complesso, ma sempre positiva
*
* CARATTERISTICHE DEL FRATTALE MONSTER:
* - È una variante modificata del frattale di Mandelbrot
* - La modifica principale è che c viene sempre reso positivo (valore assoluto)
* - Questo crea una forma simmetrica e "mostruosa" rispetto al
Mandelbrot originale
* - Ha una struttura frattale complessa con simmetrie particolari
* - È auto-simile: contiene copie di se stesso a scale diverse
* - I colori mostrano quanto velocemente i punti sfuggono all'infinito
*
* DIFFERENZE CON ALTRI FRATTALI:
* - Monster: Variante di Mandelbrot con c sempre positivo (valore assoluto)
* - Mandelbrot: c può essere positivo o negativo (posizione originale del pixel)
* - Julia: z varia (posizione del pixel), c è costante (parametro dell'utente)
* - Rabbit: Variante di Julia con c = -0.0123 + 0.745i
* - Tutti usano la stessa formula base: z = z² + c
*
* MODIFICA CARATTERISTICA:
* - La trasformazione c = |c| (valore assoluto) è la chiave del frattale Monster
* - Questo crea una simmetria particolare nel piano complesso
* - Il risultato è un frattale che appare "riflesso" rispetto agli assi
* - La forma risultante è più compatta e simmetrica del Mandelbrot originale
*
* EFFETTO VISIVO:
* - Il frattale Monster appare più "pulito" e simmetrico del Mandelbrot
* - Ha bordi più definiti e una struttura più regolare
* - I colori sono distribuiti in modo più uniforme
* - La forma generale ricorda il Mandelbrot ma con una geometria modificata
*/

int	monster(t_fractol *fractol)
{
	double	zr;
	double	zi;
	double	cr;
	double	ci;
	double	tmp_zr;

	fractol->fractal.depth = 0;
	zr = 0;
	zi = 0;
	ci = fractol->fractal.width / fractol->fractal.scale + fractol->fractal.yi;
	cr = fractol->fractal.height / fractol->fractal.scale + fractol->fractal.xr;
	if (ci < 0)
		ci = -ci;
	if (cr < 0)
		cr = -cr;
	while ((zr * zr) + (zi * zi) < 4
		&& fractol->fractal.depth < fractol->fractal.iteration)
	{
		tmp_zr = zr;
		zr = (zr * zr) - (zi * zi) + cr;
		zi = (2 * zi) * tmp_zr + ci;
		fractol->fractal.depth += 1;
	}
	return (fractol->fractal.depth);
}
