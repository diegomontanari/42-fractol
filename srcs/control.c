#include "../includes/fractol.h"
/*
* FUNZIONE KEY - Gestisce gli input da tastiera per controllare il frattale
* 
* Questa funzione è il callback principale per la gestione degli eventi da tastiera
* nel programma Fractol. Viene chiamata automaticamente dalla libreria MiniLibX
* ogni volta che l'utente preme un tasto.
* 
* La funzione implementa diversi controlli per navigare e modificare il frattale:
* - Uscita dal programma
* - Cambio dei colori
* - Movimento nel piano complesso (pan)
* 
* PARAMETRI:
* - key: codice del tasto premuto (definito nelle macro in fractol.h)
* - fractol: puntatore alla struttura contenente tutti i dati del frattale
* 
* VALORI DI RITORNO:
* - int: sempre 0 (richiesto dal protocollo MiniLibX)
* 
* TASTI SUPPORTATI E LORO FUNZIONI:
* 
* ESC (53): 
* - Termina immediatamente il programma
* - Equivale a chiudere la finestra
* 
* SPACE_KEY (49):
* - Cambia i colori del frattale chiamando random_colors()
* - Genera una nuova palette di colori per il rendering
* 
* W_KEY (13) o UP_ARROW (126):
* - Muove la vista verso l'alto nel piano complesso
* - Decrementa yi (coordinata immaginaria superiore)
* - Formula: yi -= 10 / scale (movimento proporzionale allo zoom)
* 
* A_KEY (0) o LEFT_ARROW (123):
* - Muove la vista verso sinistra nel piano complesso
* - Decrementa xr (coordinata reale sinistra)
* - Formula: xr -= 10 / scale (movimento proporzionale allo zoom)
* 
* S_KEY (1) o DOWN_ARROW (125):
* - Muove la vista verso il basso nel piano complesso
* - Incrementa yi (coordinata immaginaria superiore)
* - Formula: yi += 10 / scale (movimento proporzionale allo zoom)
* 
* D_KEY (2) o RIGHT_ARROW (124):
* - Muove la vista verso destra nel piano complesso
* - Incrementa xr (coordinata reale sinistra)
* - Formula: xr += 10 / scale (movimento proporzionale allo zoom)
* 
* LOGICA DELLA FUNZIONE:
* 1. Controlla il codice del tasto premuto
* 2. Esegue l'azione corrispondente:
*    - ESC: termina il programma
*    - SPACE: cambia i colori
*    - Tasti direzionali: sposta la vista nel piano complesso
* 3. Resetta le coordinate di rendering (height = 0, width = 0)
* 4. Ridisegna il frattale con le nuove impostazioni
* 5. Restituisce 0 (richiesto da MiniLibX)
* 
* CONCETTO DI MOVIMENTO NEL PIANO COMPLESSO:
* - Il frattale è visualizzato in una finestra di dimensioni fisse
* - La vista può essere spostata nel piano complesso modificando xr e yi
* - Il movimento è proporzionale allo zoom (scale):
*   - Zoom alto (scale grande) = movimento piccolo
*   - Zoom basso (scale piccolo) = movimento grande
* - Questo crea un movimento fluido e intuitivo
* 
* FORMULA DEL MOVIMENTO:
* - Movimento = 10 / scale
* - 10 è una costante che determina la velocità di movimento
* - La divisione per scale rende il movimento proporzionale allo zoom
* - Risultato: movimento più preciso quando si è zoomati
* 
* RESET DELLE COORDINATE:
* - height = 0 e width = 0: riparte il rendering dall'angolo in alto a sinistra
* - Necessario per ridisegnare correttamente il frattale dopo le modifiche
* - ft_draw() userà questi valori come punto di partenza
* 
* INTEGRAZIONE CON MINILIBX:
* - Questa funzione è registrata come callback con mlx_key_hook()
* - MiniLibX chiama automaticamente questa funzione quando viene premuto un tasto
* - Il protocollo richiede che la funzione restituisca sempre 0
* - La funzione deve gestire tutti i tasti di interesse del programma
*/
int	key(int key, t_fractol *fractol)
{
	if (key == ESC)
		exit(0);
	else if (key == SPACE_KEY)
		random_colors(fractol);
	else if (key == W_KEY || key == UP_ARROW)
		fractol->fractal.yi -= 10 / fractol->fractal.scale;
	else if (key == A_KEY || key == LEFT_ARROW)
		fractol->fractal.xr -= 10 / fractol->fractal.scale;
	else if (key == S_KEY || key == DOWN_ARROW)
		fractol->fractal.yi += 10 / fractol->fractal.scale;
	else if (key == D_KEY || key == RIGHT_ARROW)
		fractol->fractal.xr += 10 / fractol->fractal.scale;
	fractol->fractal.height = 0;
	fractol->fractal.width = 0;
	ft_draw(fractol);
	return (0);
}

/* Function that zooms in by increasing the scale, the iteration and adding
 to the x and y the values of scale_multi */
void	zoom_in(int x, int y, t_fractol *f)
{
	double	scale_multi;

	if (f->fractal.scale >= SCALE_LIMIT)
		return ;
	else
	{
		scale_multi = f->fractal.scale * SCALE_PRS;
		f->fractal.xr = ((double)x / f->fractal.scale + f->fractal.xr) \
		 - (scale_multi / 2);
		f->fractal.xr += (scale_multi / 2) - ((double)x / scale_multi);
		f->fractal.yi = ((double)y / f->fractal.scale + f->fractal.yi) \
		 - (scale_multi / 2);
		f->fractal.yi += (scale_multi / 2) - ((double)y / scale_multi);
		f->fractal.scale *= SCALE_PRS;
		f->fractal.iteration += SCALE_ITER;
	}
}

/* Same but in the other way */
void	zoom_out(int x, int y, t_fractol *f)
{
	double	scale_multi;

	scale_multi = f->fractal.scale / SCALE_PRS;
	f->fractal.xr = ((double)x / f->fractal.scale + f->fractal.xr) \
	 - (scale_multi / 2);
	f->fractal.xr += (scale_multi / 2) - ((double)x / scale_multi);
	f->fractal.yi = ((double)y / f->fractal.scale + f->fractal.yi) \
	 - (scale_multi / 2);
	f->fractal.yi += (scale_multi / 2) - ((double)y / scale_multi);
	f->fractal.scale /= SCALE_PRS;
	f->fractal.iteration -= SCALE_ITER;
}

/* Function which takes the inputs of the mouse */
int	mouse(int mouse, int x, int y, t_fractol *fractol)
{
	if (mouse == DOWN_SCROLL)
		zoom_in(x, y, fractol);
	if (mouse == UP_SCROLL)
		zoom_out(x, y, fractol);
	fractol->fractal.height = 0;
	fractol->fractal.width = 0;
	ft_draw(fractol);
	return (0);
}
