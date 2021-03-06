#include "rt.h"

void bc_paraboloid(t_scene *s, t_parser *p, char *line)
{
  if (p->i_obj >= p->lim_obj || p->i_obj < 0)
  {
    ft_printf("XML %s ERROR - Can't assign + or - (%d) paraboloid than "
              "initiated at line %d: '%s'\n",
              __FUNCTION__, p->i_obj, p->l, line);
    exit(-1);
  }
  if (check_opt(p->opt) != E_TAB_PARABLOID || p->mat == false)
  {
    ft_printf("XML %s ERROR - Some flags are missing within <paraboloid>"
              "balise"
              " for objet %d at line %d: %s\n",
              __FUNCTION__, p->i_obj, p->l, line);
    exit(-1);
  }
  s->obj[p->i_obj] = new_object(
      s->obj[p->i_obj].p_obj,
      s->obj[p->i_obj].type_obj,
      s->obj[p->i_obj].p_mat, s->obj[p->i_obj].p_mat->type_mat);
  s->this_obj = &s->obj[p->i_obj];
  s->sizeof_obj = p->i_obj + 1;
  p->f = (void *)&bo_void;
  p->opt = 0;
  p->mat = false;
  p->lim_mat = 0;
  p->obj = -1;
  p->same--;
  ft_printf("\t- Paraboloid[%d] Initiated\n", s->sizeof_obj);
}

void bo_paraboloid(t_scene *s, t_parser *p, char *line)
{
  check_objsame(p, line, "paraboloid");
  p->i_obj++;
  if (p->i_obj >= p->lim_obj)
  {
    p->lim_obj += 8;
    if ((s->obj = (t_obj *)realloc(s->obj, p->lim_obj * sizeof(t_obj))) == NULL)
    {
      ft_printf("Realloc %s ERROR - Something went wrong trying to "
                "realloc the given structure at object %d\n",
                __FUNCTION__,
                p->i_obj);
      exit(-1);
    }
  }
  s->obj[p->i_obj].p_obj = (void *)new_paraboloid(v3_(0., 1., 0.),
                                                  v3_(0., 0., 0.), 1.0);
  s->obj[p->i_obj].type_obj = OBJ_PARABOLOID;
  p->f = (void *)&bo_void;
  p->opt |= p->byte[E_TAB_PARABLOID];
  p->obj = p->i_obj;
  p->opt_m = 0;
}
