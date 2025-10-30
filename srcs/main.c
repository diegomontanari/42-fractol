#include <signal.h>
#include "../includes/fractol.h"

/*
 * Inizializza i valori della struttura t_fractol per preparare il disegno del frattale.
 *
 * - Imposta il bordo sinistro del piano complesso (xr) a -2.0 per default.
 * - Imposta il bordo superiore del piano complesso (yi) a -1.30 per default.
 * - Se il tipo di frattale è Mandelbrot (type == 2), imposta xr a -2.5 e yi a -1.30.
 * - Imposta il numero di iterazioni di default a 50.
 * - Se viene passato un terzo argomento da linea di comando, lo usa per impostare il numero di iterazioni.
 * - Imposta le costanti cr e ci (usate solo per Julia) a 0 di default.
 * - Se vengono passati quarto e quinto argomento da linea di comando, li usa per impostare cr e ci.
 *   Lì usa atof (ASCII to float) per convertire i numeri in virgola mobile.
 *   Esempi di cosa fa atof:
 *   atof("3.14") → restituisce 3.14
 *   atof("-0.5") → restituisce -0.5
 *   atof("123.456") → restituisce 123.456
 *   atof("42") → restituisce 42.0
 * - Imposta lo zoom (scale) iniziale a 300.00.
 * - Imposta il colore iniziale (r, g, b) rispettivamente a 0x42, 0x32, 0x22.
 * - Imposta le coordinate height e width a 0 per iniziare il disegno dall'angolo in alto a sinistra.
 */
void	ft_init(t_fractol *fractol, char **av)
{
	fractol->fractal.offset_x = -2.0;
	fractol->fractal.offset_y = -1.30;
	if (fractol->fractal.type == 2)
	{
		fractol->fractal.offset_x = -2.5;
		fractol->fractal.offset_y = -1.30;
	}
	fractol->fractal.iteration = 50;
	if (av[2])
		fractol->fractal.iteration = ft_atoi(av[2]);
	fractol->fractal.cr = 0;
	fractol->fractal.ci = 0;
	if (av[3] && av[4])
	{
		fractol->fractal.cr = ft_atof(av[3]);
		fractol->fractal.ci = ft_atof(av[4]);
	}
	fractol->fractal.scale = 300.00;
	fractol->color.r = 0x42;
	fractol->color.g = 0x32;
	fractol->color.b = 0x22;
	fractol->fractal.pixel_y = 0;
	fractol->fractal.pixel_x = 0;
	fractol->last_zoom_time = 0;
}

/* Menu */
void	menu(void)
{
	printf("Arg 1 : Choose a fractal # :\n");
	printf("    Julia................1\n");
	printf("    Mandelbrot...........2\n");
	printf("    Rabbit...............3\n");
	printf("    Monster..............4\n");
	printf("(Optional) :\n");
	printf("Arg 2 : Iteration from 20 to 1000\n");
	printf("(For Julia Only) :\n");
	printf("Arg 3 : Real complex number\n");
	printf("Arg 4 : Imaginary complex number\n\n");
	printf("Commands :\n");
	printf("    ESC..................Quit\n");
	printf("    Space................Change Color\n");
	printf("    Scroll up............Zoom in\n");
	printf("    Scroll down..........Zoom out\n\n");
}

/* Function that changes the type of fractal according to the chosen argument */
/*
 * Analizza il primo argomento passato da linea di comando (av[1]) e imposta il tipo di frattale da generare.
 *
 * @param fractol Puntatore alla struttura t_fractol
 * @param av Argomenti della riga di comando
 * @return 0 in caso di successo, 1 in caso di errore
 */
int	fractal_choice(t_fractol *fractol, char **av)
{
	if (av[1][0] == '1' && av[1][1] == '\0')
		fractol->fractal.type = 1;
	else if (av[1][0] == '2' && av[1][1] == '\0')
		fractol->fractal.type = 2;
	else if (av[1][0] == '3' && av[1][1] == '\0')
		fractol->fractal.type = 3;
	else if (av[1][0] == '4' && av[1][1] == '\0')
		fractol->fractal.type = 4;
	else
	{
		ft_putstr_fd("\n\033[31mError: '", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd("' is not a valid argument\e[0m\n\n", 2);
		menu();
		return (1);
	}
	return (0);
}

/*
 * Funzione principale del programma Fractol.
 *
 * - Definisce la struttura principale che conterrà tutti i dati del programma.
 * - Controlla che sia stato passato almeno un argomento da linea di comando.
 * - Sceglie il tipo di frattale in base all'argomento (Julia, Mandelbrot, ecc.) tramite fractal_choice.
 * - Inizializza la connessione con la libreria grafica MiniLibX (mlx_init).
 * - Crea una nuova finestra grafica di dimensioni WIDTH x HEIGHT (mlx_new_window).
 * - Crea una nuova immagine (buffer) dove verrà disegnato il frattale (mlx_new_image).
 * - Ottiene il puntatore all'area di memoria dell'immagine e informazioni tecniche (mlx_get_data_addr).
 *   Le informazioni tecniche sono:
 *   bits_per_pixel: quanti bit occupa ogni pixel nell’immagine (es. 32 = 4 byte per pixel: RGBA).
line_length: quanti byte occupa ogni riga di pixel in memoria (può essere maggiore della larghezza in pixel × byte, per motivi di allineamento).
endian: indica l’ordine dei byte nei pixel (big endian o little endian).
Questi valori sono fondamentali per sapere come scrivere correttamente i colori
 dei pixel direttamente in memoria.
* 
 * - Inizializza i parametri del frattale (zoom, iterazioni, costanti, colori) con ft_init.
 * - Disegna il frattale sull'immagine con ft_draw.
 * - mlx_key_hook: permette di gestire gli eventi della tastiera. Ad esempio, se premi 
 *   un tasto, la funzione key viene chiamata, e passano i parametri necessari.
 * - mlx_mouse_hook: gestisce gli eventi del mouse (clic, movimento, ecc.). Qui la funzione mouse viene chiamata.
 * - mlx_hook: gestisce altri eventi generali, come la chiusura della finestra. 
 *   Il numero 17 è un codice per l'evento di chiusura della finestra (quando clicchi sulla "X" per chiudere la finestra).
 * - mlx_llop: mantiene il programma in esecuzione fino a quando la finestra non viene chiusa. 
 *   Senza questa riga, la finestra si chiuderebbe subito dopo l'apertura, perché il programma terminerebbe.
 * - Se manca l'argomento, stampa errore e mostra il menu di utilizzo.
 * - Termina il programma restituendo 0.
 */

/**
 * Initialize MLX, create window and image
 * 
 * @param f Pointer to the fractol structure
 * @return 0 on success, 1 on error
 */
static int init_mlx(t_fractol *f)
{
	// Initialize MLX
	f->mlx.mlx = mlx_init();
	if (!f->mlx.mlx)
	{
		ft_putstr_fd("Error: Failed to initialize MLX\n", 2);
		return (1);
	}

	// Create window
	f->mlx.win = mlx_new_window(f->mlx.mlx, WIDTH, HEIGHT, "Fractol");
	if (!f->mlx.win)
	{
		ft_putstr_fd("Error: Failed to create window\n", 2);
		return (1);
	}

	// Create image
	f->mlx.img = mlx_new_image(f->mlx.mlx, WIDTH, HEIGHT);
	if (!f->mlx.img)
	{
		ft_putstr_fd("Error: Failed to create image\n", 2);
		return (1);
	}

	// Get image data address
	f->mlx.addr = mlx_get_data_addr(f->mlx.img, &f->mlx.bits_per_pixel,
			&f->mlx.line_length, &f->mlx.endian);
	if (!f->mlx.addr)
	{
		ft_putstr_fd("Error: Failed to get image data address\n", 2);
		return (1);
	}

	return (0);
}

int	main(int argc, char **argv)
{
	t_fractol	f;

	// Check command line arguments
	if (argc < 2)
	{
		ft_putstr_fd("\n\033[31mError: Missing argument\e[0m\n\n", 2);
		menu();
		return (1);
	}

	// Initialize fractal type
	if (fractal_choice(&f, argv) != 0)
		return (1);

	// Setup signal handler for Ctrl+C
	signal(SIGINT, handle_signal);

	// Initialize MLX, window, and image with error handling
	if (init_mlx(&f) != 0)
		clean_exit(&f, 1);

	// Initialize fractal parameters
	ft_init(&f, argv);

	// Set up event hooks
	mlx_key_hook(f.mlx.win, key, &f);
	mlx_mouse_hook(f.mlx.win, mouse, &f);
	mlx_hook(f.mlx.win, 17, 0, close_window, &f);

	// Draw the fractal and start the event loop
	ft_draw(&f);
	mlx_loop(f.mlx.mlx);

	// This line is theoretically unreachable due to mlx_loop
	return (0);
}
