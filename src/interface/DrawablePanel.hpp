
#ifndef __DELEGATE_H_
#define __DELEGATE_H_

#include <SFML/System/Vector2.hpp>

namespace interface{

class DrawablePanel {
public:
    virtual ~DrawablePanel() = 0;

    virtual void UpdateGraphics() = 0;
    virtual void UpdateDataAsync() = 0;
    virtual void SetDimensions(sf::Vector2f dimensions) = 0;

};

}
#endif
