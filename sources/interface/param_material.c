#include "rt.h"

static void material_color_bis(t_rt *rt)
{
  lst_active_button(&rt->panel.lst_button, BTN_PARAM5, true);
  lst_set_button(&rt->panel.lst_button, BTN_PARAM5,
                 actionparam((void *)rt, button_mattexture));
  if (rt->panel.viewparam.scene.this_obj->p_mat->m_text->type_texture ==
      TEXT_IMAGE)
    sprintf(rt->panel.viewparam.str_color, "Texture: %6s\"%s\"", " ",
            rt->panel.viewparam.scene.this_obj->p_mat->m_text->filename);
  else if (rt->panel.viewparam.scene.this_obj->p_mat->m_text->type_texture ==
           TEXT_CHCKBOARD)
    sprintf(rt->panel.viewparam.str_color, "Texture: %6sCheckboard", " ");
  else if (rt->panel.viewparam.scene.this_obj->p_mat->m_text->type_texture ==
           TEXT_LINEY)
    sprintf(rt->panel.viewparam.str_color, "Texture: %6sLine Y", " ");
  else if (rt->panel.viewparam.scene.this_obj->p_mat->m_text->type_texture ==
           TEXT_LINEX)
    sprintf(rt->panel.viewparam.str_color, "Texture: %6sLine X", " ");
  else if (rt->panel.viewparam.scene.this_obj->p_mat->m_text->type_texture ==
           TEXT_RAINBOW)
    sprintf(rt->panel.viewparam.str_color, "Texture: %6sRainbow", " ");
}

static void material_color(t_rt *rt)
{
  if (!rt->panel.viewparam.scene.this_obj->p_mat->m_text || rt->panel.viewparam.scene.this_obj->p_mat->m_text->type_texture == TEXT_NONE)
  {
    sprintf(rt->panel.viewparam.str_color, "Color: %10srgb(%.3g, %.3g, %.3g)",
            " ", rt->panel.viewparam.scene.this_obj->p_mat->albedo.x * 255, rt->panel.viewparam.scene.this_obj->p_mat->albedo.y * 255,
            rt->panel.viewparam.scene.this_obj->p_mat->albedo.z * 255);
    lst_active_button(&rt->panel.lst_button, BTN_PARAM5, true);
    lst_set_button(&rt->panel.lst_button, BTN_PARAM5,
                   actionparam((void *)rt, button_matalbedo));
  }
  else
    material_color_bis(rt);
}

static void param_material_bis(t_rt *rt)
{
  if (rt->panel.viewparam.scene.this_obj->p_mat->type_mat ==
      MAT_DIFF_LIGHT)
  {
    sprintf(rt->panel.viewparam.str_mat, "Material: %5sDiffuse Light", " ");
    sprintf(rt->panel.viewparam.str_param_m, " ");
    lst_active_button(&rt->panel.lst_button, BTN_PARAM4, true);
    lst_active_button(&rt->panel.lst_button, BTN_PARAM6, false);
    lst_set_button(&rt->panel.lst_button, BTN_PARAM4,
                   actionparam((void *)rt, button_mattype));
  }
  else if (rt->panel.viewparam.scene.this_obj->p_mat->type_mat == MAT_DIELECT)
  {
    sprintf(rt->panel.viewparam.str_mat, "Material: %5sDielectric", " ");
    sprintf(rt->panel.viewparam.str_param_m, "Refraction: %2s %.3g",
            " ", rt->panel.viewparam.scene.this_obj->p_mat->t);
    lst_active_button(&rt->panel.lst_button, BTN_PARAM4, true);
    lst_active_button(&rt->panel.lst_button, BTN_PARAM6, true);
    lst_set_button(&rt->panel.lst_button, BTN_PARAM4,
                   actionparam((void *)rt, button_mattype));
    lst_set_button(&rt->panel.lst_button, BTN_PARAM6,
                   actionparam((void *)rt, button_matdielect));
  }
  material_color(rt);
}

void get_param_material(t_rt *rt)
{
  if (rt->panel.viewparam.scene.this_obj->p_mat->type_mat == MAT_METAL)
  {
    sprintf(rt->panel.viewparam.str_mat, "Material: %5sMetallic", " ");
    sprintf(rt->panel.viewparam.str_param_m, "Reflection: %2s%.3g", " ",
            rt->panel.viewparam.scene.this_obj->p_mat->t);
    lst_active_button(&rt->panel.lst_button, BTN_PARAM4, true);
    lst_active_button(&rt->panel.lst_button, BTN_PARAM6, true);
    lst_set_button(&rt->panel.lst_button, BTN_PARAM4,
                   actionparam((void *)rt, button_mattype));
    lst_set_button(&rt->panel.lst_button, BTN_PARAM6,
                   actionparam((void *)rt, button_matmetal));
  }
  else if (rt->panel.viewparam.scene.this_obj->p_mat->type_mat == MAT_LAMBERT)
  {
    sprintf(rt->panel.viewparam.str_mat, "Material: %5sLambertian", " ");
    sprintf(rt->panel.viewparam.str_param_m, "");
    lst_active_button(&rt->panel.lst_button, BTN_PARAM4, true);
    lst_active_button(&rt->panel.lst_button, BTN_PARAM6, false);
    lst_set_button(&rt->panel.lst_button, BTN_PARAM4,
                   actionparam((void *)rt, button_mattype));
  }
  param_material_bis(rt);
}
