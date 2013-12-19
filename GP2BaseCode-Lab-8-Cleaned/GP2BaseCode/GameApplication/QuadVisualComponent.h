#include "VisualComponent.h"

class QuadVisualComponent:public VisualComponent
{
public:
	QuadVisualComponent(){};
	~QuadVisualComponent(){};

	bool create(IRenderer * pRenderer);
};