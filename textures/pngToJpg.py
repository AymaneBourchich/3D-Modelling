from PIL import Image
from typing import Union
import os

def convert_png_to_jpg(inputPath: str, outputPath: str, backgroundColor: tuple[int, int, int] = (255, 255, 255)) -> None:
    image = Image.open(inputPath)

    # Convert PNG with alpha to RGB by pasting on a background
    if image.mode in ("RGBA", "LA") or (image.mode == "P" and "transparency" in image.info):
        background = Image.new("RGB", image.size, backgroundColor)
        image = image.convert("RGBA")
        background.paste(image, mask=image.split()[3])  # alpha channel
        image = background
    else:
        image = image.convert("RGB")

    # Ensure output extension is .jpg
    root, _ = os.path.splitext(outputPath)
    outputPath = root + ".jpg"

    image.save(outputPath, "JPEG", quality=95)

if __name__ == "__main__":
    convert_png_to_jpg("rebar.png", "rebar.jpg")