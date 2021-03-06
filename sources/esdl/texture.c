#include "rt.h"

static SDL_Surface *create_fallback_texture(SDL_Surface *surf)
{
  SDL_Rect rect;

  rect.x = 0;
  rect.y = 0;
  rect.w = 32;
  rect.h = 32;
  surf = esdl_create_surface(32, 32);
  esdl_draw_filled_square(surf, &rect, 0xff69b4ff, NULL);
  return (surf);
}

SDL_Texture *esdl_load_texture(SDL_Renderer *render,
                               const char *path, int *w, int *h)
{
  SDL_Surface *surf;
  SDL_Texture *tex;

  surf = IMG_Load(path);
  if (w != NULL)
    *w = surf->w;
  if (h != NULL)
    *h = surf->h;
  if (!surf)
  {
    ft_printf("Error while loading texture : \"%s\", \
              fallback texture created\n",
              path);
    surf = create_fallback_texture(surf);
  }
  tex = SDL_CreateTextureFromSurface(render, surf);
  SDL_FreeSurface(surf);
  return (tex);
}

int esdl_init_img(t_esdl *esdl)
{
  int ret;

  ret = 0;
  if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == -1)
  {
    ret = -1;
    ft_dprintf(2, "Error esdl_init_img() failed: %s\n", IMG_GetError());
  }
  esdl->img = 1;
  return (ret);
}
