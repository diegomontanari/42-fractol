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
		clean_exit(fractol, 0);
	else if (key == SPACE_KEY)
		random_colors(fractol);
	else if (key == W_KEY || key == UP_ARROW)
		fractol->fractal.offset_y += 10 / fractol->fractal.scale;  // Move up
	else if (key == A_KEY || key == LEFT_ARROW)
		fractol->fractal.offset_x -= 10 / fractol->fractal.scale;  // Move left
	else if (key == S_KEY || key == DOWN_ARROW)
		fractol->fractal.offset_y -= 10 / fractol->fractal.scale;  // Move down
	else if (key == D_KEY || key == RIGHT_ARROW)
		fractol->fractal.offset_x += 10 / fractol->fractal.scale;  // Move right
	
	// Reset rendering coordinates and redraw
	fractol->fractal.pixel_x = 0;
	fractol->fractal.pixel_y = 0;
	ft_draw(fractol);
	return (0);
}

/* Function that zooms in by increasing the scale and keeping the mouse position fixed */
// 1. (double mouse_x) Save current mouse position in complex plane
// 2. Update the scale
// 3. Calculate new offsets to keep the mouse position fixed
// 4. Increase iterations for more detail
void	zoom_in(int x, int y, t_fractol *f)
{
    if (f->fractal.scale >= SCALE_LIMIT)
        return;

    double mouse_x = (double)x / f->fractal.scale + f->fractal.offset_x;
    double mouse_y = (double)y / f->fractal.scale + f->fractal.offset_y;

    f->fractal.scale *= SCALE_PRS;
    
    f->fractal.offset_x = mouse_x - ((double)x / f->fractal.scale);
    f->fractal.offset_y = mouse_y - ((double)y / f->fractal.scale);
    
    f->fractal.iteration += SCALE_ITER;
}

/* Zoom out from the current mouse position */
// 1. Save current mouse position in complex plane
// 2. Update the scale (decrease it)
// 3. Calculate new offsets to keep the mouse position fixed
// 4. Decrease iterations for better performance
void zoom_out(int x, int y, t_fractol *f)
{
    if (f->fractal.scale <= 1.0)  // Prevent zooming out too much
        return;

    // 1. Save current mouse position in complex plane
    double mouse_x = (double)x / f->fractal.scale + f->fractal.offset_x;
    double mouse_y = (double)y / f->fractal.scale + f->fractal.offset_y;

    // 2. Update the scale (decrease it)
    f->fractal.scale /= SCALE_PRS;
    
    // 3. Calculate new offsets to keep the mouse position fixed
    f->fractal.offset_x = mouse_x - ((double)x / f->fractal.scale);
    f->fractal.offset_y = mouse_y - ((double)y / f->fractal.scale);
    
    // 4. Decrease iterations for better performance
    if (f->fractal.iteration > 50) {  // Keep a minimum iteration count
        f->fractal.iteration -= SCALE_ITER;
    }
}

/* Function which takes the inputs of the mouse */
int	mouse(int mouse, int x, int y, t_fractol *fractol)
{
	struct timeval	tv;
	long			current_time;
	int				throttle_ms;
	
	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	
	/* Dynamic throttling based on zoom level */
	throttle_ms = 50;  /* Default throttle */
	if (fractol->fractal.scale > 10000)
		throttle_ms = 100;  /* Slower throttle for high zoom */
	
	if (current_time - fractol->last_zoom_time < throttle_ms)
		return (0);
	
	if (mouse == DOWN_SCROLL)
		zoom_in(x, y, fractol);
	if (mouse == UP_SCROLL)
		zoom_out(x, y, fractol);
	
	fractol->last_zoom_time = current_time;
	fractol->fractal.pixel_y = 0;
	fractol->fractal.pixel_x = 0;
	ft_draw(fractol);
	return (0);
}

/**
 * @brief Clean up MLX resources and exit the program
 * 
 * @param f Pointer to the fractol structure (can be NULL)
 * @param exit_code The exit code to return
 */
void	clean_exit(t_fractol *f, int exit_code)
{
	if (f)
	{
		if (f->mlx.img && f->mlx.mlx)
			mlx_destroy_image(f->mlx.mlx, f->mlx.img);
		if (f->mlx.win && f->mlx.mlx)
			mlx_destroy_window(f->mlx.mlx, f->mlx.win);
		if (f->mlx.mlx)
		{
			mlx_destroy_display(f->mlx.mlx);
			free(f->mlx.mlx);
		}
	}
	exit(exit_code);
}

/**
 * @brief Handle signals (like Ctrl+C) to ensure clean exit
 * 
 * @param sig Signal number
 */
void	handle_signal(int sig)
{
	(void)sig;
	ft_putstr_fd("\n\033[33mProgram terminated by user\e[0m\n", 2);
	exit(0);
}

/**
 * @brief Handle window close event (X button)
 */
int	close_window(t_fractol *fractol)
{
	clean_exit(fractol, 0);
	return (0);
}
