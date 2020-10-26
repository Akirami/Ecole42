#include "../includes/minirt.h"

int
	draw_axes(t_stuff *stuff, t_cam *cam)
{
	int i;
	int j;

	(void)cam;
	/*double camx = stuff->cam.pos[0];
	double camy = stuff->cam.pos[1];*/

	int ox = stuff->window.width / 2;
	int oy = stuff->window.height / 2;
	printf("CAMX: %f\n", stuff->cam.pos[0]);
	printf("CAMY: %f\n", stuff->cam.pos[1]);




	i = 0;
	j = oy;
	while (i++ < ox * 2)
	{
		if (i % 2 == 0)	
			mlx_pixel_put(stuff->context, stuff->window.win, i, j, 0x00ffaaaa);
	}
	i = ox;
	j = 0;
	while (j++ < oy * 2)
	{
		if (j % 2 == 0)
			mlx_pixel_put(stuff->context, stuff->window.win, i, j, 0x00aaffaa);
	}
	/*i = ox - cam->pos[0];
	j = oy + cam->pos[1];
	k = 0;
	while (k < 400)
	{
		mlx_pixel_put(stuff->context, stuff->window.win, 
			i - (i / cam->pos[2]), 
			j + (i / cam->pos[2]), 
			0x00aaaaff);
		k++;
	}*/
	return (0);
}

double
	calc_coef(double *s1, double *s2)
{
	if (s2[0] == s1[0])
		return (0);
	return ((s2[1] - s1[1])/(s2[0] - s1[0]));
}

double
	calc_b(double *s1, double ax)
{
	return (s1[1] - (ax * s1[0]));
}

void 
	swap_array(double *a, double *b, int j)
{
	int i;
	int tmp;

	i = 0;
    while (i < j)
    {
        tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
        i++;
    }
}

void
	cp_array(double *a, double *b, int i)
{
	int j;

	j = 0;
    while (j < i)
    {
        a[j] = b[j];
        j++;
    }
}

void
	fill_array_p(t_tr *t, double *p1, double *p2, double *p3)
{
	int i;

	i = 0;
    while (i < 2)
    {
        t->tr[0][i] = p1[i];
        t->tr[1][i] = p2[i];
        t->tr[2][i] = p3[i];
        i++;
    }
}

void
	fill_array_coor(double t[3][3], double *p1, double *p2, double *p3)
{
	int i;

	i = 0;
    while (i < 3)
    {
        t[0][i] = p1[i];
        t[1][i] = p2[i];
        t[2][i] = p3[i];
        i++;
    }
}

void
	fill_array(double tr[4][2], double *p1, double *p2, double *p3)
{
	int i;

	i = 0;
    while (i < 2)
    {
        tr[0][i] = p1[i];
        tr[1][i] = p2[i];
        tr[2][i] = p3[i];
        i++;
    }
}

void
	draw_each_lines(double *s1, double *s2, double b, t_stuff *stuff)
{
	int ox = stuff->window.width / 2;
	int oy = stuff->window.height / 2;
	int i;
	int j;

	i = (s1[1] < s2[1]) ? s1[1] : s2[1];
	j = (s2[1] > s1[1]) ? s2[1] : s1[1];
	while (i <= j)
	{
		mlx_pixel_put(stuff->context, stuff->window.win, ox + b, oy - i, stuff->t1.xcolor);
		i += 1;
	}
}

void
	draw_triagle(t_tr *t, double tr[3][2], int sq, t_stuff *stuff)
{
	while (!sq && t->mi_ma[0] <= t->mi_ma[1])
	{
		tr[1][0] = t->mi_ma[0];
		tr[1][1] = t->ax[0] * t->mi_ma[0] + t->dec[0];
		tr[2][0] = t->mi_ma[0];
		tr[2][1] = t->ax[1] * t->mi_ma[0] + t->dec[1];		
		draw_each_lines(tr[1], tr[2], t->mi_ma[0], stuff);
		t->mi_ma[0]++;
	}
	while (sq && t->mi_ma[0] < t->mi_ma[1])
	{
		tr[1][0] = t->mi_ma[1];
		tr[1][1] = t->ax[0] * t->mi_ma[1] + t->dec[0];
		tr[2][0] = t->mi_ma[1];
		tr[2][1] = t->ax[1] * t->mi_ma[1] + t->dec[1];
		draw_each_lines(tr[1], tr[2], t->mi_ma[1], stuff);
		t->mi_ma[1]--;
	}
}

void
	calc_triangle(t_tr *t, double tr[3][2], int sq, t_stuff *stuff)
{
	t->mi_ma[0] = (tr[0][0] <= tr[1][0]) ? tr[0][0] : tr[1][0];
	t->mi_ma[0] = (t->mi_ma[0] <= tr[2][0]) ? t->mi_ma[0] : tr[2][0];
	t->mi_ma[1] = (tr[0][0] >= tr[1][0]) ? tr[0][0] : tr[1][0];
	t->mi_ma[1] = (t->mi_ma[1] >= tr[2][0]) ? t->mi_ma[1] : tr[2][0];
	t->ax[0] = calc_coef(tr[0], tr[1]);
	t->dec[0] = calc_b(tr[1], t->ax[0]);
	t->ax[1] = calc_coef(tr[0], tr[2]);
	t->dec[1] = calc_b(tr[2], t->ax[1]);
	tr[1][0] = t->mi_ma[0];
	tr[2][0] = t->mi_ma[0];
	draw_triagle(t, tr, sq, stuff);
}

int
	def_triangle(t_stuff *stuff, t_tr *t, t_cam *cam)
{
	int sq;
	double tr1[3][2];

	draw_axes(stuff, cam);
	if (t->tr[0][0] > t->tr[1][0])
		swap_array(t->tr[0], t->tr[1], 2);
	if (t->tr[0][0] > t->tr[2][0])
		swap_array(t->tr[0], t->tr[2], 2);
	if (t->tr[1][0] > t->tr[2][0])
		swap_array(t->tr[1], t->tr[2], 2);
	t->tr[3][0] = t->tr[1][0];
	t->ax[0] = calc_coef(t->tr[0], t->tr[2]);
	t->b = calc_b(t->tr[2], t->ax[0]);
	t->tr[3][1] = t->ax[0] * t->tr[3][0] + t->b;
	sq = 0;
	sq = (t->tr[0][0] == t->tr[1][0] || t->tr[0][0] == t->tr[2][0]) ? 1 : 0;
	fill_array(tr1, t->tr[0], t->tr[1], t->tr[3]);
	calc_triangle(t, tr1, sq, stuff);
	sq = 0;
	sq = (t->tr[2][0] == t->tr[1][0] || t->tr[3][0] == t->tr[2][0]) ? 1 : 0;
	fill_array(tr1, t->tr[2], t->tr[1], t->tr[3]);
	calc_triangle(t, tr1, sq, stuff);
	return (1);
}

void saveppm(char *filename, unsigned char *img, int width, int height){
	/* FILE pointer */
	FILE *f;

	/* Open file for writing */
	f = fopen(filename, "wb");

	/* PPM header info, including the size of the image */
	fprintf(f, "/* XPM */\nstatic char * exemple_xpm[] = {\n");
	fprintf(f, "%d %d %d %d\n", width, height, 255, 3);
	/* Write the image data to the file - remember 3 byte per pixel */
	fwrite(img, 3, width*height, f);

	/* Make sure you close the file */
	fclose(f);
}

int
	project_z(t_stuff *stuff, t_cam *cam)
{
	t_tr *t;

	printf("CAM IN : %f %f %f\n", stuff->cam.pos[0], stuff->cam.pos[1], stuff->cam.pos[2]);
	printf("LOOK AT: %f %f %f\n", stuff->cam.look_at[0], stuff->cam.look_at[1], stuff->cam.look_at[2]);
	printf("FOV    : %f\n\n", stuff->cam.fov);
	printf("COOR:%f %f %f\n", stuff->t1.coor[0][0], stuff->t1.coor[0][1], stuff->t1.coor[0][2]);
	printf("COOR:%f %f %f\n", stuff->t1.coor[1][0], stuff->t1.coor[1][1], stuff->t1.coor[1][2]);
	printf("COOR:%f %f %f\n\n", stuff->t1.coor[2][0], stuff->t1.coor[2][1], stuff->t1.coor[2][2]);
	/*printf("CAM IN:%f %f %f\n", stuff->cam.pos[0], stuff->cam.pos[1], stuff->cam.pos[2]);
	printf("LOOK AT:%f %f %f\n", stuff->cam.look_at[0], stuff->cam.look_at[1], stuff->cam.look_at[2]);*/

	t_image		*im;
	if ((im = (t_image *)malloc(sizeof(t_image))) == NULL)
		return (0);
	im->img = mlx_new_image(stuff->context, stuff->window.width, stuff->window.height);
	im->ptr = mlx_get_data_addr(im->img, &im->bpp, &im->sizeline, &im->endian);
	printf("%d, %d, %d %ld\n", im->bpp, im->sizeline, im->endian, sizeof(t_image));



	int x,y;
	x = 0;
	y = 0;
	t_var v;

	sp s;
	s.pos.x = 200;
	s.pos.y = 200;
	s.pos.z = 100;
	s.radius = 100;

	ray r;	
	r.dir.x = 0;
	r.dir.y = 0;
	r.dir.z = 1;

	r.start.z = 0;
	while (y < stuff->window.height)
	{
		x = 0;
		r.start.y = y; 
		while (x < stuff->window.width)
		{
			r.start.x = x; 

			v.red = 200;
			v.green = 100;
			v.blue = 0;
			v.level = 0;
			v.coef = 1.0;

			double t = 20000;
			if (intersectRaySphere(&r, &s, &t))
			{
				printf("TI.DISCR: %f\n", t);
				int rgb[4];
				rgb[0] = 0;
				rgb[1] = (unsigned int)min(v.red * 255, 255);
				rgb[2] = (unsigned int)min(v.green * 255, 255);
				rgb[3] = (unsigned int)min(v.blue * 255, 255);
				*(int *)(im->ptr + (x * 4 + (y * im->sizeline))) = rgb_to_hex(rgb);
			}
			else
				*(int *)(im->ptr + (x * 4 + (y * im->sizeline))) = 25;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(stuff->context, stuff->window.win, im->img, 0, 0);
	/*saveppm("image.xpm", img, stuff->window.width, stuff->window.height);	*/

	if (!(t = (t_tr *)malloc(sizeof(t_tr))))
		return (-1);

	t->tr[0][0] = /*(stuff->cam.pos[0] - stuff->t1.coor[0][0]) +*/ stuff->t1.coor[0][0]; // * stuff->cam.fov) / (stuff->t1.coor[0][2] + 50 )) * stuff->cam.fov / (stuff->cam.pos[2] -  / stuff->cam.pos[0]; * cam->fov; * cam->look_at[0];
	t->tr[0][1] = /*(stuff->cam.pos[1] - stuff->t1.coor[0][1]) +*/ stuff->t1.coor[0][1]; // * stuff->cam.fov) / (stuff->t1.coor[0][2] + 50 )) * stuff->cam.fov / (stuff->cam.pos[2] -  / stuff->cam.pos[0]; * cam->fov; * cam->look_at[0];
	t->tr[1][0] = /*(stuff->cam.pos[0] - stuff->t1.coor[1][0]) +*/ stuff->t1.coor[1][0]; // * stuff->cam.fov) / (stuff->t1.coor[1][2] + 50 )) * stuff->cam.fov / (stuff->cam.pos[2] -  / stuff->cam.pos[0]; * cam->fov; * cam->look_at[1];
	t->tr[1][1] = /*(stuff->cam.pos[1] - stuff->t1.coor[1][1]) +*/ stuff->t1.coor[1][1]; // * stuff->cam.fov) / (stuff->t1.coor[1][2] + 50 )) * stuff->cam.fov / (stuff->cam.pos[2] -  / stuff->cam.pos[0]; * cam->fov; * cam->look_at[1];
	t->tr[2][0] = /*(stuff->cam.pos[0] - stuff->t1.coor[2][0]) +*/ stuff->t1.coor[2][0]; // * stuff->cam.fov) / (stuff->t1.coor[2][2] + 50 )) * stuff->cam.fov / (stuff->cam.pos[2] -  / stuff->cam.pos[0]; * cam->fov; * cam->look_at[2];
	t->tr[2][1] = /*(stuff->cam.pos[1] - stuff->t1.coor[2][1]) +*/ stuff->t1.coor[2][1]; // * stuff->cam.fov) / (stuff->t1.coor[2][2] + 50 )) * stuff->cam.fov / (stuff->cam.pos[2] -  / stuff->cam.pos[0]; * cam->fov; * cam->look_at[2];
	
	/*def_triangle(stuff, t, cam);*/
	return (1);
}



