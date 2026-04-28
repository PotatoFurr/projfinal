Graphics pipeline (Claude):

Model Space
    ↓  [Model Matrix]
World Space
    ↓  [View Matrix]
View/Camera Space (Eye Space)
    ↓  [Projection Matrix]
Clip Space          ← w is now meaningful, NOT yet divided
    ↓  Perspective Division (divide by w)
Normalized Device Coordinates (NDC)
    ↓  Viewport Transform
Screen Space