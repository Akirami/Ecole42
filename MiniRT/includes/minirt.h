#ifndef MINIRT_H
# define MINIRT_H

# include "../3rdparty/libft/includes/libft.h"
# include "../3rdparty/minilibx/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include <pthread.h>
# include <stdbool.h>

/* --- */
# include <stdio.h>
# include <time.h>

# ifndef RES_X
#  define RES_X
# endif
# ifndef RES_Y
#  define RES_Y
# endif
# define INF 2147483647
# ifndef SAMPLING
#  define SAMPLING 2.0
# endif
# define TR_REF 0.15
# ifndef M_PI
#  define M_PI 3.14159265358979323846264338327950288
# endif
# define SPECULAR 1
# define EPSILON 0.00001
# define R_FILTER 1
# define G_FILTER 1
# define B_FILTER 1
# define TEXTURES 12
# define SAVE_DIR "./"

typedef struct	s_vec
{
	double 		x;
	double 		y;
	double 		z; 
}				vec;

typedef struct	s_image
{
	void		*ptr;
	char		*data;
	char		*tex;
	int			bpp;
	int			sizeline;
	int			width;
	int			height;
	int			endian;
}				t_image;

typedef struct	s_rep
{
	vec			u;
	vec			v;
	vec			w;
}				t_rep;

typedef struct	s_color
{
	double		r;
	double		g;
	double		b;
}				color;

typedef struct	s_light
{
	int			count;
	vec			pos;
	color		intensity;
	double		ratio;
	int			color[3];
}				light;

typedef struct	s_material
{
    color		diffuse;
    double		reflection;
    double		specular;
    int			type;
}				material;

typedef struct	s_pl
{
	vec			pos;
	vec			norm;
	material	mat;
}				t_pl; 

typedef struct	s_sqp
{
	vec			p[4];
	vec			ap;
	vec			e1;
	vec			e2;
	double		de1;
	double		de2;
	vec			v1;
	vec			z2;
	vec			z3;
	double		d2;
	double		d3;
	double		w;
	double		h;
}				t_sqp;

typedef struct	s_co
{
	vec			pos;
	vec			pos1;
	vec			dir;
	double		height;
	double		t;
	vec			dp;
	material	mat;
	double		angl;
	double		rad;
}				t_co;

typedef struct	s_cy
{
	vec			pos;
	vec			top;
	vec			hit[3];
	double		radius;
	double		delta;
	double		a;
	double		b;
	double		c;
	int			capuchon;
	vec			norm;
	vec			norm1;
	vec			i;
	vec			o;
	double		len;		
	material	mat;
}				t_cy;

typedef struct	s_sq
{
	vec			pos;
	vec			norm;
	double		len;
	material	mat;
	t_sqp		sqp;
	double		angle;
}				t_sq;

typedef struct	s_cube
{
	vec			pos;
	vec			norm;
	double		len;
	t_sq		sq[6];
	material	mat;	
}				t_cu;

typedef struct	s_sp
{
	vec			pos;
	double		radius;
	material	mat;
}				t_sp;

typedef struct	s_ray
{
	vec			start;
	vec			dir;
}				ray;

typedef struct	s_cam
{
	char		*img;
	vec 		pos;
	vec			look_at;
	vec			eye;
	vec			up;
	vec			right;
	double		fov;
	int			isdraw;
}				t_cam;

typedef struct	s_tr
{
	vec			p0;
	vec			p1;
	vec			p2;
	vec 		v0v1;
	vec			v0v2;
	vec			v1v2;
	vec			n;
	double		d;
	double		uu;
	double		uv;
	double		vv;
	material	mat;
}				t_tr;

typedef struct	s_pyramid
{
	vec			pos;
	vec			norm;
	double		height;
	double		width;
	t_sq		base;
	t_tr		t1;
	t_tr		t2;
	t_tr		t3;
	t_tr		t4;
}				t_py;

typedef struct	s_amb
{
	color		color;
	double		diff;
}				t_amb;

typedef struct
{
	double		a;
	double		b;
	double		c;
	double		t0;
	double		t1;
	double		discr;
	double		sqrtdiscr;
}				t_r_inter_sp;

typedef struct	s_window
{
	int			width;
	int			height;
	void		*win;
	double		scale;
	double		ratio;
}				t_window;

typedef struct	s_objects
{
	t_cam		cam[10];
	light		lights[10];
}				objects;

typedef struct	s_inter
{
	double 		t;
	bool		match;
	material	mat;
	vec			n;
	vec			hit;
	vec			lpos;
	vec			ldir;
	vec			opos;
	vec			odir;
	bool		is_l;
}				t_inter;

typedef struct	s_objs
{
	void		*ptr;
	int			type;
}				t_objs;

typedef struct	s_filters
{
	double		col[3];
	double		sepia;
	double		bw;
}				t_filters;

typedef struct	s_bmp_info_head
{
	uint32_t	bi_size;
	int			bi_width;
	int			bi_height;
	uint16_t	bi_planes;
	uint16_t	bi_bitcount;
	uint32_t	bi_compress;
	uint32_t	bi_sizeimage;
	int			bi_x_pelspermeter;
	int			bi_y_pelspermeter;
	uint32_t	bi_clr_used;
	uint32_t	bi_clr_important;
}				t_bmp_info_head;

typedef struct	s_bmp_file_head
{
	uint16_t	bf_type;
	uint32_t	bf_size;
	uint16_t	bf_reserved1;
	uint16_t	bf_reserved2;
	uint32_t	bf_offbits;
}				t_bmp_file_head;

typedef struct	s_stuff
{
	void		*context;
	t_window	window;
	t_image		im;
	t_image		text[TEXTURES];
	char		**img;
	char		*filename;
	t_filters	filt;
	objects		obj;
	t_amb		amb;
	t_cam		cam[10];
	light		lights[10];
	t_objs		*objs;
	int			save;
	int			obj_count;
	int			icam;
	int			cam_count;
	int			sp_count;
	int			cy_count;
	int			sq_count;
	int			li_count;
	int 		pl_count;
	int			tr_count;
	int			co_count;
	int			cu_count;
	clock_t		t_begin;
	bool		is_hud;
	uint64_t	millis;
	double		y;
	int			waiting;
}				t_stuff;

typedef struct	s_var
{
	int			level;
	double		coef;
	double		rgb[3];
	ray			r;
	vec			dist;
	double		t;
	double		x;
	double		y;
}				t_var;

typedef struct	s_thread_data
{
	t_stuff		*st;
	double		y;
}				t_thread_data;

void			*mlx_init();
void			*mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
int				mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);
int				mlx_loop (void *mlx_ptr);
int				hook_events(int x, int y, t_stuff *st);
int				key_events(int key, t_stuff *st);
int				load_textures(t_stuff *st);	
int				save_img(t_stuff *st);

int				main(int ac, char **av);
int				init_context(t_stuff *stuff);
int				main_loop(t_stuff *stuff);
int				get_window(t_stuff *stuff);
int				close_minirt(t_stuff *stuff);
int				close_minirt2(t_stuff *stuff);
int				error_message(char *str, t_stuff *st);
int				checking_row_data(char *str, t_stuff *stuff);
int				checking_obj_data(char **str, t_stuff *stuff);
int				get_window_size(char *str, t_stuff *stuff);
int				get_triangles_data(char *str, void **ptr, t_stuff *st);
int				get_cam_data(char *str, t_stuff *st);
int				get_ambient_light(char *str, t_stuff *st);
int				check_triangles_data(char *str, void **ptr, t_stuff *st);
int				get_spheres_data(char *str, void **ptr, t_stuff *st);
int				check_spheres_data(char *str, void **ptr, t_stuff *st);
int				check_light_data(char *str, t_stuff *stuff);
int				check_planes_data(char *str, void **ptr, t_stuff *st);
int				check_squares_data(char *str, void **ptr, t_stuff *st);
int				check_cylenders_data(char *str, void **ptr, t_stuff *st);
int				check_cones_data(char *str, void **ptr, t_stuff *st);
int				check_cubes_data(char *str, t_stuff *st, int j);
int				check_pyra_data(char *str, t_stuff *st, int j);
bool			check_c_range_uint(char c);
color			chess_map_sp(vec pt, color col, double type, t_sp sp);
color			chess_map_sqpl(vec p, color col, vec pos, vec norm);
char			*truncate_str(char *str);
bool			check_dir(vec dir);
void			mapping_sq(t_stuff *st, t_inter *ti, t_sq *sq);

void			rx(vec *v, float x);
void			ry(vec *v, float y);
void			rz(vec *v, float z);
void			rot(vec *v, vec axe);
double 			min(double a, double b);
double			max(double a, double b);
double			deg2rad(double deg);
void			n_vec(double a, double b, double c, vec *v);
void			ft_swap(double *x, double *y);
double			calc_dist(vec p0, vec p1);
void			sort_point(t_tr *tr, ray *r);
void			swap_point(vec *p0, vec *p1);
void			normalize_vec(vec *v);
vec				normalize_v(vec v);
double			vectordot(vec v1, vec v2);
vec				vectorcross(vec v1, vec v2);
vec				vectorscale(double c, vec v);
vec				vectorPlus(double c, vec *v);
vec				vectorsub(vec v1, vec v2);
vec				vectoradd(vec v1, vec v2);
vec				vectoradd3(vec v1, vec v2, vec v3);
void			double_to_vec(double coor[3], vec *v);
void			double_to_rgb(color *c, int rgb[3]);
char			*get_color(char *str, int[4]);
double			ft_atof(char *str);
char			*get_point(char *s, double coor[3]);
unsigned int	rgb_to_hex(int rgb[3]);
t_inter			invalid_ti(t_inter *ti);
vec				valid_obj(t_inter *ti);
void			calc_light_value(t_stuff *st, t_var *tv, t_inter *ti);
void			getpixel(t_stuff *st, double u, double v, t_inter *ti);
t_rep			calc_rep(const vec dir);
color			h_to_rgb(const int hex);
int				calc_i_double(char *str);

void			prepare_sq(t_sq *sq);
void			prepare_sq_map(t_sq *sq);
void			prepare_sq2(void *ptr);
void			prepare_tr(t_tr *tr);
void			prepare_cu(t_cu *cu);
void			generate_cu(t_sq *sq, int k);
t_inter			intersect_r_sp(t_stuff *st, void *ptr, t_inter *ti, ray *r);
t_inter			intersect_r_sq(t_stuff *st, void *ptr, t_inter *ti, ray *r);
t_inter			intersect_r_tr(t_stuff *st, void *ptr, t_inter *ti, ray *ra);
t_inter			intersect_r_pl(t_stuff *st, void *ptr, t_inter *ti, ray *r);
t_inter			intersect_r_cy(t_stuff *st, void *ptr, t_inter *ti, ray *r);
t_inter			intersect_r_cu(t_stuff *st, void *ptr, t_inter *ti, ray *r);
t_inter			intersect_r_co(t_stuff *st, void *ptr, t_inter *ti, ray *r);
t_inter			find_object(t_stuff *st, ray *r);
color			image_map(vec point, color col, double type);
int				set_color(double color[3]);
void			init_var(t_stuff *st, t_var *tv, double x, double y);
void			set_filters(t_stuff *st, int a, int b, int c);

int				prepare_stuff(t_stuff *st);
int				free_stuff(t_stuff *st);
int				draw_scene(t_stuff *st);
int				draw_hud(t_stuff *st);
void			*thr_func(void *arg);
void			display_hud(t_stuff *st);
t_inter			(*g_func_ptr[6])(t_stuff *st, void *obj, t_inter *ti, ray *r);
int 			(*g_objs_ptr[6])(char *str, void **obj, t_stuff *st);

#endif




