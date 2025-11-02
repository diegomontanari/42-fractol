#include "fractol.h"

/* -------------------------------------------------------------------------- */
/*  Controlla periodicamente il flag d'uscita impostato dal signal handler.   */
/*  Se il flag vale 1, chiama clean_exit() in un contesto sicuro.             */
/*  Viene eseguita ad ogni ciclo del loop MLX tramite mlx_loop_hook().        */
/* -------------------------------------------------------------------------- */
int	poll_exit_hook(void *param)
{
	t_fractol	*f;

	f = (t_fractol *)param;
	if (*exit_flag_slot())
		clean_exit(f, 0);
	return (0);
}