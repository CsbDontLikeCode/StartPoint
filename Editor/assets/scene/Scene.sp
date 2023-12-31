Scene: Untitled
Entities:
  - Entity: 8114658342792434278
    TagComponent:
      Tag: panel
    TransformComponent:
      Translation: [0.0780344605, 0.156438351, 0]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    CircleRendererComponent:
      Color: [0.598990381, 0.946619213, 0.586162746, 1]
      Thickness: 1
      Fade: 0.00499999989
    Rigidbody2DComponent:
      BodyType: Static
      FixedRotation: true
    CircleCollider2DComponent:
      Offset: [0, 0]
      Radius: 0.5
      Density: 1
      Friction: 0.5
      Restitution: 0
      RestitutionThreshold: 0.5
  - Entity: 3096618895960335335
    TagComponent:
      Tag: boundary2
    TransformComponent:
      Translation: [7.90557766, 0.222257912, 0]
      Rotation: [0, 0, 0]
      Scale: [1, 3.55865335, 1]
    SpriteRendererComponent:
      Color: [1, 1, 1, 1]
      TexturePath: NoTexture
    Rigidbody2DComponent:
      BodyType: Static
      FixedRotation: false
    BoxCollider2DComponent:
      Offset: [0, 0]
      Size: [0.5, 0.5]
      Density: 1
      Friction: 0.5
      Restitution: 0
      RestitutionThreshold: 0.5
  - Entity: 15212976850180723491
    TagComponent:
      Tag: boundary1
    TransformComponent:
      Translation: [-7.92361164, 0.270468652, 0]
      Rotation: [0, 0, 0]
      Scale: [1, 3.5, 1]
    SpriteRendererComponent:
      Color: [1, 1, 1, 1]
      TexturePath: NoTexture
    Rigidbody2DComponent:
      BodyType: Static
      FixedRotation: false
    BoxCollider2DComponent:
      Offset: [0, 0]
      Size: [0.5, 0.5]
      Density: 1
      Friction: 0.5
      Restitution: 0
      RestitutionThreshold: 0.5
  - Entity: 1150290727855704604
    TagComponent:
      Tag: azibao
    TransformComponent:
      Translation: [-0.394991577, 1.36523867, 9.8957014e-07]
      Rotation: [0, 0, -0.377201408]
      Scale: [0.999596894, 0.999596894, 1]
    SpriteRendererComponent:
      Color: [1, 1, 1, 1]
      TexturePath: assets\textures\azi.png
    Rigidbody2DComponent:
      BodyType: Dynamic
      FixedRotation: false
    BoxCollider2DComponent:
      Offset: [0, 0]
      Size: [0.5, 0.5]
      Density: 1
      Friction: 0.5
      Restitution: 0.800000012
      RestitutionThreshold: 0.5
  - Entity: 4131896594707875380
    TagComponent:
      Tag: camera
    TransformComponent:
      Translation: [0, 2, 15]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    CameraComponent:
      Camera:
        ProjectionType: 0
        PerspectiveFOV: 0.785398185
        PerspectiveNear: 0.00999999978
        PerspectiveFar: 1000
        OrthographicSize: 10
        OrthographicNear: -1
        OrthographicFar: 1
      Primary: true
      FixedAspectRatio: false
  - Entity: 6835808786385407323
    TagComponent:
      Tag: floor
    TransformComponent:
      Translation: [0, -1.63604867, 0]
      Rotation: [0, 0, 0]
      Scale: [16.8161049, 0.308908224, 1]
    SpriteRendererComponent:
      Color: [1, 1, 1, 1]
      TexturePath: NoTexture
    Rigidbody2DComponent:
      BodyType: Static
      FixedRotation: false
    BoxCollider2DComponent:
      Offset: [0, 0]
      Size: [0.5, 0.5]
      Density: 1
      Friction: 0.5
      Restitution: 0
      RestitutionThreshold: 0.5