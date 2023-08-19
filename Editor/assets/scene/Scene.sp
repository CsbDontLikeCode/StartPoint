Scene: Untitled
Entities:
  - Entity: 12837192831273
    TagComponent:
      Tag: azibao
    TransformComponent:
      Translation: [-0.130948395, 1.81228161, 0]
      Rotation: [0, 0, 1.04719758]
      Scale: [0.999602914, 0.999602914, 1]
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
  - Entity: 12837192831273
    TagComponent:
      Tag: camera
    TransformComponent:
      Translation: [0, 0, 8]
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
  - Entity: 12837192831273
    TagComponent:
      Tag: floor
    TransformComponent:
      Translation: [0, -1.63604867, 0]
      Rotation: [0, 0, 0]
      Scale: [8.90057945, 0.308908224, 1]
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