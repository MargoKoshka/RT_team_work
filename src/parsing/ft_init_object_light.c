#include "rtv1.h"

t_light		*list_create(t_light *light, char **tab)
{
	light = (t_light *)malloc(sizeof(t_light));
	if (light == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	if (ft_len_wordtab(tab) != 5)
		ft_exit(ERR_OBJECT);
	init_coordinates(&light->pos, tab[1]);
	light->intensity = ft_atof(tab[2]);
	init_color(&light->color, tab[3]);
	if (ft_strcmp(tab[4], "Point") == 0)
		light->tip = e_point;
	if (ft_strcmp(tab[4], "Direct") == 0)
		light->tip = e_direct;
	if (ft_strcmp(tab[4], "Ambient") == 0)
		light->tip = e_ambient;
	light->next = NULL;
	return (light);
}

t_light		*init_light(t_light *light, char **tab)
{
	t_light *tmp;

	tmp = NULL;
	if (light == NULL)
		light = list_create(light, tab);
	else
	{
		tmp = list_create(tmp, tab);
		tmp->next = light;
		light = tmp;
	}
	return (light);
}
