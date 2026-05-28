import numpy as np


def printQuad(vertices: np.ndarray) -> None:
    """Expects 4 vertices in this order:

    X1 = top-left
    X2 = top-right
    X3 = bottom-left
    X4 = bottom-right
    """

    def formatVertex(vertex: np.ndarray) -> str:
        x = vertex[0]
        y = vertex[1]
        return f"({x:6.2f}, {y:6.2f})"

    x1 = formatVertex(vertices[0])
    x2 = formatVertex(vertices[1])
    x3 = formatVertex(vertices[2])
    x4 = formatVertex(vertices[3])

    print(f"{x1}   |     {x2}")
    print("----------------------------------------------")
    print(f"{x3}   |     {x4}")
    print("\n")
    print("############################")


# 1. Define square centered at origin (Each row is a vertex: shape 4x4)
vertices = np.array(
    [
        [-0.5, 0.5, 0.0, 1.0],  # Top-left
        [0.5, 0.5, 0.0, 1.0],  # Top-right
        [-0.5, -0.5, 0.0, 1.0],  # Bottom-left
        [0.5, -0.5, 0.0, 1.0],  # Bottom-right
    ]
)

print("Original Square:")
printQuad(vertices)


scaleX = 1.0
scaleY = 4.0
scaleZ = 1.0


def translate(vertices, x, y, z):
    translation = np.array(
        [
            [1.0, 0.0, 0.0, x],
            [0.0, 1.0, 0.0, y],
            [0.0, 0.0, 1.0, z],
            [0.0, 0.0, 0.0, 1.0],
        ]
    )
    result = vertices @ translation.T
    printQuad(result)
    return result


def scale(vertices, x, y, z):
    scale = np.array(
        [
            [x, 0.0, 0.0, 0.0],
            [0.0, y, 0.0, 0.0],
            [0.0, 0.0, z, 0.0],
            [0.0, 0.0, 0.0, 1.0],
        ]
    )
    result = vertices @ scale.T
    printQuad(result)
    return result


# 3. Transform using Row Vector notation: Vertices @ Translate.T
# (Shape: 4x4 @ 4x4 = 4x4)

print("BEGIN:")
x = vertices
printQuad(x)
x = translate(x, 0.5, 0, 0)
x = scale(x, 0.25, 1, 1.0)
x = translate(x, 0, 0.5, 0)
x = scale(x, 1, 0.0625, 1.0)
x = translate(x, -0.35, 2, 0)
