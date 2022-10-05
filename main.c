#include <mlx.h>
#include <libft.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	deal_key(int key, void *param)
{
	ft_putchar('x');
	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	// mlx_init function initializes the connection between 
	// your software and the display.
	mlx = mlx_init();
	if (!mlx)
		return (-1);
	mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
	mlx_pixel_put(mlx, mlx_win, 250, 250, 0xFFFFFF);
	mlx_key_hook(mlx_win, deal_key, (void *)0);

	// allows events to be received: 
	// 		key is pressed;
	// 		mouse button is pressed
	// 		part of the windows should be re-drawn (expose)
	// mlx_loop never returns; when an event happens, it calls a
	// user-defined function associated with this event.
	// each event can be assigned to different functions.
	// each window can define a different fucntion for the same event
	//
	mlx_loop(mlx);

	return (0);
}

