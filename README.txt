Coordinate frames:
- .off file: Each .off file contains a set of triangles describing an object mesh. The triangles
  are given as floating point numbers in their own coordinate frame.
- We rotate and scale the .off object according to the input matrix. This is done to view the object
  at different angles, as well as to scale the object to fit in the screen.
- Screen coordinates [(0, SCREEN_WIDTH), (0, -SCREEN_HEIGHT)]: We take the intermediary floating point representation
  and then convert the points into integer coordinates that fit within the screen bounds.