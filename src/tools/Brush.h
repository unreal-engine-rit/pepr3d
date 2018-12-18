#pragma once
#include <cinder/Ray.h>
#include "tools/Tool.h"
#include "ui/IconsMaterialDesign.h"
#include "ui/SidePane.h"

namespace pepr3d {
struct BrushSettings {
    /// Index of the selected color
    size_t color = 0;

    /// Size of a brush in model space units
    float size = 0.2f;

    /// Paint only to triangles connected to the origin
    bool continuous = true;

    /// Paint onto backward facing triangles
    bool paintBackfaces = false;

    /// Will not create new triangles to match brush shape
    bool respectOriginalTriangles = false;

    /// When respecting original triangles should we paint triangles that are not fully inside the brush?
    bool paintOuterRing = false;

    bool operator==(const BrushSettings& other) const {
        return color == other.color && size == other.size && continuous == other.continuous &&
               paintBackfaces == other.paintBackfaces && respectOriginalTriangles == other.respectOriginalTriangles &&
               paintOuterRing == other.paintOuterRing;
    }
};

class Brush : public ITool {
   public:
    explicit Brush(MainApplication& app)
        : mApplication(app){}

    virtual std::string getName() const override {
        return "Brush";
    }

    virtual std::string getIcon() const override {
        return ICON_MD_BRUSH;
    }

     virtual void drawToSidePane(SidePane& sidePane) override;
    virtual void drawToModelView(ModelView& modelView) override;
    virtual void onModelViewMouseDown(ModelView& modelView, ci::app::MouseEvent event) override;
    virtual void onModelViewMouseUp(ModelView& modelView, ci::app::MouseEvent event) override;
    virtual void onModelViewMouseDrag(ModelView& modelView, ci::app::MouseEvent event) override;
    virtual void onModelViewMouseMove(ModelView& modelView, ci::app::MouseEvent event) override;

   private:
    /// Do painting tick on the model
    void paint();

    /// Stop paining
    void stopPaint();

    void updateHighlight() const;

    ci::Ray mLastRay;
    MainApplication& mApplication;

    BrushSettings mBrushSettings;

    bool mGroupCommands = false;

    /// How many times can we run this tool without updating the screen
    int mPaintsSinceDraw = 0;
    const int MAX_PAINTS_WITHOUT_DRAW = 1;
};
}  // namespace pepr3d
