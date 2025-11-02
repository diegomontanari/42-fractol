#include "fractol.h"

/* -------------------------------------------------------------------------- */
/*  Questa funzione custodisce un puntatore statico a t_fractol.              */
/*  Restituisce l'indirizzo del puntatore, così altre funzioni possono        */
/*  leggerlo o modificarlo senza usare variabili globali.                     */
/* -------------------------------------------------------------------------- */
t_fractol	**fractol_slot(void)
{
	static t_fractol	*ptr = NULL;
	return (&ptr);
}

/* -------------------------------------------------------------------------- */
/*  Salva il puntatore principale del programma nella "cassaforte" statica.   */
/*  Chiamata una sola volta all'inizio, subito dopo aver allocato t_fractol.  */
/* -------------------------------------------------------------------------- */
void	fractol_set(t_fractol *f)
{
	*fractol_slot() = f;
}

/* -------------------------------------------------------------------------- */
/*  Restituisce il puntatore salvato in precedenza tramite fractol_set().     */
/*  Può essere chiamata da qualsiasi parte del programma, ad esempio          */
/*  dall'hook o da funzioni che non ricevono direttamente t_fractol *.        */
/* -------------------------------------------------------------------------- */
t_fractol	*fractol_get(void)
{
	return (*fractol_slot());
}

/* -------------------------------------------------------------------------- */
/*  Custodisce un intero statico (flag di uscita).                            */
/*  Il signal handler lo imposta a 1 quando riceve SIGINT,                    */
/*  mentre l'hook di polling lo controlla per sapere se deve chiudere tutto.  */
/* -------------------------------------------------------------------------- */
int	*exit_flag_slot(void)
{
	static int	flag = 0;
	return (&flag);
}