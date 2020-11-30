/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 00:28:17 by mikhail           #+#    #+#             */
/*   Updated: 2020/11/07 14:04:22 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <pthread.h>
# include <stdbool.h>
# include "structure.h"
# include "menu.h"
# include "error.h"
# include "../minilibx_macos/mlx.h"
# include "../minilibx/mlx.h"
# include "libft.h"
# include "events.h"
# include "parsing.h"
# ifdef __linux__
#  include "key_linux.h"
# else
#  include "key_macos.h"
# endif
# define ABS(Value) ((Value) > 0 ? (Value) : -(Value))
# define WIDHT		1200
# define HIGHT		1200
# define W_MENU		400
# define K_FOV		20.0
# define K_ZOOM		1.0
# define K_MOVE		1.0
# define PI			3.14159265
# define K_DIR		0.087267
# define NUM_THREAD	16
# define DEPTH		7
# define NO_INTERSECT	-1
# define INTERSECT	1
# define NO_COLOR	-1
# define SHADOW		1
# define NO_SHADOW	0
# define OPEN		1
# define CLOSED		0
# define N_1		1
# define DEPTH_REFL	3
# define DEPTH_REFR	4
# define MIN_REFRACT	0.05
# define MIN_SAMPLE		1
# define MAX_SAMPLE		6
# define COLOR_BG_BLU	0x459AFA
# define COLOR_BG_BL	0x0
# define COLOR_BG_WHIT	0xFFFFFF
# define COLOR_STR	    0xF8F924
# define MAX_FILE_SIZE  15190
# define BUFF			4096
# define PERL_S         1000
# define D_ZERO         0.000001
# define CHESS_SUPPORT  999999
# define CHESS_DELETION 1

/*
** hook function
*/
int			close_window(void *param);
int			key_press(int key, t_rtv *p);
int			mouse_press(int button, int x, int y, t_rtv *p);
int			mouse_release(int button, int x, int y, void *param);
int			mouse_movement(int x, int y, t_rtv *p);
int			expose_hook(t_rtv *p);
void		ft_hook_operation(t_rtv *p);
void		ft_exit(void *param);
void		look(int key, t_rtv *p);
void		zoom(int key, t_rtv *p);
void		camera_start(t_rtv *p);
void		reflect(t_rtv *p);
void		aliasing_effects(t_rtv *p);
void		selected_object(int x, int y, t_rtv *p);
void		ft_move_object(int key, t_rtv *p);
void		free_memory(t_rtv *paint);
void		ft_put_pixel(t_rtv *paint, int x, int y, int color);
void		ft_init_texture(t_rtv *p);
void		ft_mlx_init(t_rtv *p);
void		ft_init_configuration(t_rtv *p);

/*
** menu function
*/

void		print_navigation(t_rtv *p);
void		ft_drawing_menu(t_rtv *p);
void		ft_window_menu(t_rtv *p);
void		print_instructions_for_obj(t_rtv *p);

/*
** vector function
*/

t_vector	ft_add_vectors(t_vector *v1, t_vector *v2);
t_vector	ft_sub_vectors(t_vector *v1, t_vector *v2);
t_vector	ft_multiply_vector_num(t_vector *vector, double num);
t_vector	ft_rotation_vector(t_vector *angle, t_vector *ray);
void		ft_rotate_vector(t_vector *angle, t_vector *ray);
void		ft_unit_vector(t_vector *vector);
double		ft_vector_scalar(t_vector *v1, t_vector *v2);
double		ft_vector_modul(t_vector *v);
double		ft_vector_projection_on_ray(t_vector *v1, t_vector *v2);

/*
** intersect obgects function
*/

void		ft_multi_thread_paint(t_rtv *paint);
void		ft_paint_scene(t_rtv *paint);
t_cross		ft_intersect_objects(t_rtv *p, t_vector *ray, t_vector *s);
t_cross		ft_raytrace_objects(t_object *object, t_vector *ray);
t_cross		ft_intersect_ray_sphere(t_object *sphere, t_vector *ray);
t_cross		ft_intersect_ray_plane(t_object *plane, t_vector *ray);
t_cross		ft_intersect_ray_hemisphere(t_object *sphere, t_vector *ray);
t_cross		ft_intersect_ray_ring(t_object *ring, t_vector *ray);
t_cross		ft_intersect_ray_tube(t_object *tube, t_vector *ray);
t_cross		ft_intersect_ray_cylinder(t_object *cylindr, t_vector *ray);
t_cross		ft_intersect_ray_cone(t_object *cone, t_vector *ray);
t_cross		ft_intersect_ray_paraboloid(t_object *paraboloid, t_vector *ray);
double		ft_solve_quadratic_equation_2(t_discr *discr);
void		ft_solve_quadratic_equation(t_discr *discr);
double		calc_angle(t_vector *pos, t_vector *ax, t_vector *ite, double max);
double		check_intersect(t_vector *ray, t_vector *p, t_vector *ax, double l);
void		init_axis(t_object *ring, t_vector *axis);
void		object_data(t_object *object, t_vector *cam);
void		calculate_constant(t_rtv *p, t_vector *start);

/*
** calculate axis normal obgects function
*/

t_vector	calculate_vector_norm(t_object *obj, t_cross *inter, t_vector *ray);
t_vector	vector_norm_tube(t_object *object, t_cross *intersect);
t_vector	vector_norm_cylindr(t_object *object, t_cross *intersect);
t_vector	vector_norm_empty_cone(t_object *object, t_cross *intersect);
t_vector	vector_norm_cone(t_object *object, t_cross *intersect);
t_vector	vector_norm_paraboloid(t_object *object, t_cross *intersect);
void		check_normal(t_vector *dir, t_vector *normal);

/*
** calculate color obgects function
*/

int			ft_local_color(t_rtv *p, t_cross *cross, t_vector *norm);
int			ft_reflection(t_rtv *p, t_start *data, double *min_refract);
int			ft_refraction(t_rtv *p, t_start *data, double *min_refract);
t_vector	new_start_vector(t_vector *intersect, t_vector *norm, double delta);
t_vector	ft_reflection_ray(t_vector *dir, t_vector *norm);
double		illumination(int s, t_vector *ray, t_vector *ref, t_vector *nor);
int			color(t_color *color, float percent);
int			result_color(int color1, int color2, float reflection);
int			calculate_result_color(float color[][2], int depth, int max_depth);

/*
** calculate aliasing effects
*/

int			ft_aliasing_effects(t_rtv *paint, t_vector *ray);
int			ft_chose_sampling(t_rtv *paint, int x, int y);
int			ft_color_object(t_rtv *paint, t_vector *ray);

/*
** init objects function
*/

void		init_coordinates(t_vector *vector, char *tab);
void		init_angle_norm(t_vector *angle, char *tab);
void		init_color(t_color *color, char *str);
void		init_tab_object(t_rtv *paint, char *src);
void		init_cone(t_rtv *p, char **tab, int *i);
void		init_cylindr(t_rtv *p, char **tab, int *i);
void		init_plane(t_rtv *p, char **tab, int *i);
void		init_sphere(t_rtv *p, char **tab, int *i);
void		init_hemisphere(t_rtv *p, char **tab, int *i);
void		init_ring(t_rtv *p, char **tab, int *i);
void		init_camera(t_rtv *p, char **tab);
void		init_window(t_rtv *p, char **tab);
t_light		*init_light(t_light *light, char **tab);
void		add_object_to_tab(t_rtv *paint, char **tab, int *i);
int			how_many_object(int fd);

/*
** screenshot function
*/
char		*create_name_file(const char *name, const char *type);
void		save_ppm_file(t_rtv *paint);
void		save_bmp_file(t_rtv *paint);
int			sepia(int color);
int			*create_perlinmap(void);
double		noise3(double x, double y, double z, int *perlin_tab);
t_color		makenoise_perlin(t_cross *intersect, int *perlin_tab, t_color *hit);
t_color		makenoise_marble(t_cross *intersect, int *perlin_tab, t_color *hit);
t_color		ft_get_texture_color(t_object *object, t_vector point);
t_color		ft_map_texture_cylindr(t_object *object, t_vector point);
t_color		ft_map_texture_plane(t_object *object, t_vector point);
t_color		ft_map_texture_sphere(t_object *object, t_vector point);
int			ft_gen_chess(int countu, int countv, double u, double v);
double		ft_lengthv(t_vector v);
double		ft_dotprod(t_vector v1, t_vector v2);
t_vector	ft_multkv(double k, t_vector v);
int			load_texture_blur(t_rtv *p, t_object *obj);
int			load_texture_earth(t_rtv *p, t_object *obj);
int			load_texture_grass(t_rtv *p, t_object *obj);
int			load_texture_wood(t_rtv *p, t_object *obj);
t_vector	vec_normalize(t_vector v);
void		get_tex_coord_sphere(t_object *obj, int *col, int *row, t_cross *c);
void		get_tex_coord_plane(t_object *obj, int *col, int *row, t_cross *c);
void		get_tex_coord_cone(t_object *obj, int *col, int *row, t_cross *c);
t_color		get_color_cone(t_object *object, t_cross *intersect);
t_color		get_color_plane(t_object *object, t_cross *intersect);
t_color		get_color_sphere(t_object *object, t_cross *intersect);
void		get_tex_coord_cylindr(t_object *ob, int *col, int *ro, t_cross *c);
t_color		get_color_cylindr(t_object *object, t_cross *intersect);
t_color		get_color(t_object *object, t_cross *intersect);
t_color		int_to_rgb(int p);
void		anaglyph(t_rtv *scene, int p1, int p2, int p);
void		motion_bler(t_rtv *scene, int p1, int p2, int p);
void		motion_bluer(t_rtv *s);
void		color_to_anaglyph(t_rtv *scene);
void		choose_texture(t_rtv *p, t_object *obj);
t_color		set_color_cartoon(t_color color, double light);
t_color		wave_pattern(t_vector *uv, t_color *mat);
double		compute_noise(t_noise perlin, double x, double y, double z);
double		grad(int hash, double x, double y, double z);
double		lerp(double t, double a, double b);
double		fade(double t);
int			apply(double shade, t_rtv *p, t_cross *in);
int			apply2(double shade, t_rtv *p, t_cross *in);
double		ft_calculate_lighting(t_rtv *p, t_cross *cross, t_vector *norm);
int			find_option1(char *str, int *index, int counter, t_rtv *rt);
int			fill_objects_end(char *str, int *index, t_rtv *rt, int counter);
int			f(char *str, int *index, char *mask);
int			go_to_coma(char *str, int i);
t_color		get_image_texel(t_object *obj, t_cross *intersect);
void		key_press1(int key, t_rtv *p);
void		effects(int key, t_rtv *p);
t_color		rainbow(t_object *obj, t_cross *inter, t_color *color);

#endif
