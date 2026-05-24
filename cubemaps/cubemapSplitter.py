from pathlib import Path

from PIL import Image


def splitCubeMap(
    inputPath: str,
    outputDirectory: str,
) -> None:
    """
    Expected cubemap layout (4x3 grid):

            TOP
    LEFT  FRONT  RIGHT  BACK
            BOTTOM
    """

    image: Image.Image = Image.open(inputPath).convert("RGB")

    imageWidth, imageHeight = image.size

    faceWidth: int = imageWidth // 4
    faceHeight: int = imageHeight // 3

    if faceWidth != faceHeight:
        raise ValueError("Cubemap faces are not square")

    faceSize: int = faceWidth

    faces: dict[str, tuple[int, int]] = {
        "top": (1, 0),
        "left": (0, 1),
        "front": (1, 1),
        "right": (2, 1),
        "back": (3, 1),
        "bottom": (1, 2),
    }

    outputPath: Path = Path(outputDirectory)
    outputPath.mkdir(parents=True, exist_ok=True)

    for faceName, (gridX, gridY) in faces.items():
        left: int = gridX * faceSize
        upper: int = gridY * faceSize
        right: int = left + faceSize
        lower: int = upper + faceSize

        faceImage: Image.Image = image.crop((left, upper, right, lower))

        savePath: Path = outputPath / f"{faceName}.jpg"

        faceImage.save(savePath, "JPEG", quality=95)

        print(f"Saved: {savePath}")


if __name__ == "__main__":
    splitCubeMap(
        inputPath="blueSKy.png",
        outputDirectory="blueSky",
    )