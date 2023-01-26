#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "./v2/game_state.h"
#include "nongamestate.h"

/*
 * renderer.h --
 *
 * Abstract class used to render the game state.
 *
 */

class Renderer {
public:
   virtual ~Renderer() { }

   virtual void Draw(snake::GameState &gs, NonGameState &ngs) = 0;
   virtual void SetStatusText(const char *text) = 0;
};

#endif
