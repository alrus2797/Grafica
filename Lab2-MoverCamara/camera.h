#ifndef CAMERA_H
#define CAMERA_H

#define CAM_PARALLEL 1
#define CAM_CONIC 2
#define CAM_TRIPODE 3
#define CAM_PAN 4

#define CAM_STOP 0
#define CAM_EXAMINAR 1
#define CAM_PASEAR 2


typedef struct _Camera
{
  // we consider a rigth handed reference system for the camera
  // V point where the camera is placed (world coordinates)
  // A point the camera is looking at   (world coordinates)
  // up vector : unit vector, perpendicular to AV (world componnents)
  // origin camera reference system : at V
  // Z camera : defined by vector from A to V (penetrates the viewer's eye)
  // Y camera : defined by up vector
  // X camera : looking from V towards A goes rigthwards
  float camViewX;  // View point
  float camViewY;
  float camViewZ;
  float camAtX;    // look At point
  float camAtY;
  float camAtZ;
  float camUpX;    // Up vector
  float camUpY;
  float camUpZ;
  float camAperture;  // field of view radians     // NOTE : OpenGL uses degrees

  // defined as they are used by OpenGL
  // always => positive ; Far > Near (distance from plane to camera origin)
  float camNear;
  float camFar;
  int      camProjection;    // PARALLEL or CONIC
  int      camMovimiento; // EXAMINAR, ANDAR, TRIPODE or PAN

  // ****** dependent values ******

  // window system dependent
  float    aspectRatio;

  // for ortho projection
  float x1, x2, y1, y2, z1, z2;

  // camera i j k vectors in world coordinates
  float camIX, camIY, camIZ;
  float camJX, camJY, camJZ;
  float camKX, camKY, camKZ;
} camera;

void DestroyCamera ( _Camera **theCamera );
camera *CreatePositionCamera( float positionX, float positionY, float positionZ );
void  SetCamera( _Camera *thisCamera, float viewX, float viewY, float viewZ,
                           float atX,   float atY,   float atZ,
                float upX,   float upY,   float upZ );

void  SetDependentParametersCamera( _Camera *thisCamera );
void  SetGLCamera( _Camera *thisCamera );
void  SetGLAspectRatioCamera( _Camera *thisCamera );

// Free camera advances "step" following vector VA, step admits negative values
void  AvanceFreeCamera( _Camera *thisCamera, float step );

// ROTATION
void  YawCamera( _Camera *thisCamera, float angle );// local axis Y camera

void Rotate_Latitude( _Camera *thisCamera, float inc );
void Rotate_Longitude( _Camera *thisCamera, float inc );

void PitchCamera( _Camera *thisCamera, float angle ); // local axis Z camera
void PanCamera( _Camera *thisCamera, float stepX, float stepY );

#endif /* CAMERA_H */
