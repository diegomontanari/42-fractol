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
	fractol->fractal.xr = -2.0;
	fractol->fractal.yi = -1.30;
	if (fractol->fractal.type == 2)
	{
		fractol->fractal.xr = -2.5;
		fractol->fractal.yi = -1.30;
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
	fractol->fractal.height = 0;
	fractol->fractal.width = 0;
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
 * - Se av[1] == "1", imposta fractol->fractal.type = 1 (Julia).
 * - Se av[1] == "2", imposta fractol->fractal.type = 2 (Mandelbrot).
 * - Se av[1] == "3", imposta fractol->fractal.type = 3 (Rabbit).
 * - Se av[1] == "4", imposta fractol->fractal.type = 4 (Monster).
 * - Se il valore non è valido, stampa un messaggio di errore, mostra il menu e termina il programma.
 */
void	fractal_choice(t_fractol *fractol, char **av)
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
		printf("\n\033[31mERROR : %s is not a valid argument\e[0m\n\n", av[1]);
		menu();
		exit(0);
	}
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

int	main(int argc, char **argv)
{
	t_fractol	f;

	if (argc >= 2)
	{
		fractal_choice(&f, argv);
		f.mlx.mlx = mlx_init();
		f.mlx.win = mlx_new_window(f.mlx.mlx, WIDTH, HEIGHT, "Fractol");
		f.mlx.img = mlx_new_image(f.mlx.mlx, WIDTH, HEIGHT);
		f.mlx.addr = mlx_get_data_addr(f.mlx.img, &f.mlx.bits_per_pixel,
				&f.mlx.line_length, &f.mlx.endian);
		ft_init(&f, argv);
		ft_draw(&f);
		mlx_key_hook(f.mlx.win, key, &f);
		mlx_mouse_hook(f.mlx.win, mouse, &f);
		mlx_hook(f.mlx.win, 17, 0, close_window, &f);
		mlx_loop(f.mlx.mlx);
	}
	else
	{
		printf("\n\033[31mERROR : Missing argument\e[0m\n\n");
		menu();
	}
	return (0);
}
